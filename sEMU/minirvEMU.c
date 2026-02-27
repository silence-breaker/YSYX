#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <am.h>
#include <klib-macros.h>
#include <stdbool.h> // 提供 bool 类型支持
//模拟RV32I指令集
typedef struct {
    uint32_t pc; //程序计数器
    uint32_t GPR[32]; //通用寄存器
    uint8_t M[700 * 1024]; //按字节寻址的内存(700KB)
    uint8_t P[0x40000]; //外设寄存器空间(256KB)，落在[0x20000000, 0x20040000)的地址空间
} RV32I_CPU;
static bool running = true; //ebreak指令执行后设置为false，main函数根据这个标志退出循环
//指令定义
/*
add, addi, lui, lw, lbu, sw, sb, jalr
*/

void step(RV32I_CPU *cpu){
    // 1. 取指
    //假设指令长度为4字节，从uint8_t转成uint32_t的指针之后解引用一次性往后读4个字节
    uint32_t inst = *(uint32_t *)&cpu->M[cpu->pc]; 
    
    //2. 译码
    uint8_t opcode = inst & 0x7F; //取最低7位
    uint8_t rd     = (inst >> 7) & 0x1F;
    uint8_t funct3 = (inst >> 12) & 0x07;
    uint8_t rs1    = (inst >> 15) & 0x1F;
    uint8_t rs2    = (inst >> 20) & 0x1F;
    uint8_t funct7 = (inst >> 25) & 0x7F;

    uint32_t next_pc = cpu->pc +4; //默认下一条指令地址为当前PC加4

    //3. 执行
    switch (opcode) {
        case 0x37: // LUI (U-Type)
            // LUI 将 20 位立即数置于 rd 高位，低 12 位补 0 
            cpu->GPR[rd] = inst & 0xFFFFF000; 
            break;

        case 0x13: // OP-IMM (如 ADDI)
            if (funct3 == 0x0) { // ADDI
                int32_t imm = (int32_t)inst >> 20; // 符号扩展 
                cpu->GPR[rd] = cpu->GPR[rs1] + imm;
                //GPR数据类型是无符号，imm是有符号，相加的时候自动转化为无符号（但是具体的01是没有变化的）
            }
            break;

        case 0x33: // OP (如 ADD)
            if (funct3 == 0x0 && funct7 == 0x00) { // ADD
                cpu->GPR[rd] = cpu->GPR[rs1] + cpu->GPR[rs2]; 
            }
            break;

        case 0x03: // LOAD (LW, LBU)
            {
                int32_t imm = (int32_t)inst >> 20;
                uint32_t addr = cpu->GPR[rs1] + imm;
                if (funct3 == 0x2){
                        if(addr < sizeof(cpu->M)) {
                            cpu->GPR[rd] = *(uint32_t *)&cpu->M[addr]; // LW 从内存空间加载
                        }
                        else {
                            printf("错误：访问地址 0x%08X 超出范围！\n", addr);
                            running = false; // 停止模拟器
                        }
                }       
                else if (funct3 == 0x4) {
                    if(addr < sizeof(cpu->M)) {
                        cpu->GPR[rd] = cpu->M[addr]; // LBU 从内存空间加载
                    }
                    else {
                        printf("错误：访问地址 0x%08X 超出范围！\n", addr);
                        running = false; // 停止模拟器
                    }
            }
            break;
        }
        case 0x23: // STORE (SW, SB)
            {
                //只有SB是能写入外设区域的，SW只能写入内存区域
                // S-Type 立即数被拆分在 inst[31:25] 和 inst[11:7] 
                int32_t imm = ((int32_t)(inst & 0xFE000000) >> 20) | ((inst >> 7) & 0x1F);
                uint32_t addr = cpu->GPR[rs1] + imm;
                if (funct3 == 0x2){
                    if(addr >= 0x20000000 && addr < 0x20040000) {
                        *(uint32_t *)&cpu->P[addr-0x20000000] = cpu->GPR[rs2];// SW 存储到外设寄存器空间
                    }
                    else if(addr < sizeof(cpu->M)) *(uint32_t *)&cpu->M[addr] = cpu->GPR[rs2]; // SW存储到内存空间
                    else {
                        printf("错误：存储地址 0x%08X 超出范围！\n", addr);
                        running = false; // 停止模拟器
                    }
                }  
                else if (funct3 == 0x0) {
                    if(addr < sizeof(cpu->M)) cpu->M[addr] = cpu->GPR[rs2] & 0xFF; // SB 存储到内存空间
                    else {
                        printf("错误：存储地址 0x%08X 超出范围！\n", addr);
                        running = false; // 停止模拟器
                    }
                }
            }
            break;

        case 0x67: // JALR
            {
                int32_t imm = (int32_t)inst >> 20;
                uint32_t target = (cpu->GPR[rs1] + imm) & ~1; // 最低位置 0（对1取反后想与）
                cpu->GPR[rd] = next_pc; // 保存返回地址 
                next_pc = target;
            }
            break;

        case 0x73: // SYSTEM 指令类
            if (funct3 == 0x0) {
            // 提取高 12 位立即数
            uint16_t func12 = (inst >> 20) & 0xFFF;
        
            if (func12 == 0x001) { // EBREAK
                printf("检测到 EBREAK 指令：程序请求进入调试模式或停机。\n");
                // 在这里你可以设置一个标志位让 main 函数退出循环
                if(cpu->GPR[rs1] == 0) {
                    printf("EBREAK: 程序正常结束。\n");
                    running = false;
                    break; // 正常退出
                } else {
                    printf("EBREAK: 程序异常结束，寄存器 x%d 的值为 %d\n", rs1, cpu->GPR[rs1]);
                    exit(1); // 异常退出
                }
            
            } else if (func12 == 0x000) { // ECALL
                printf("检测到 ECALL 指令：执行环境调用（系统调用）。\n");
                // 这里可以处理具体的系统调用逻辑
            }
            }
            break;
    }

    cpu->GPR[0] = 0; // 确保 x0 恒为 0 
    cpu->pc = next_pc;

}

void load_bin(RV32I_CPU *cpu, const char *filename) {
    FILE *file = fopen(filename, "rb"); // 以二进制只读方式打开
    if (file == NULL) {
        printf("错误：无法打开文件 %s\n", filename);
        exit(1);
    }

    // 将文件内容读入到内存 M 中
    // 参数含义：目标地址，每个单元大小(byte)，最大读取数量，文件指针
    size_t size = fread(cpu->M, 1, sizeof(cpu->M), file);
    //ebreak的指令是0x00100073，按照小端存储在内存中就是0x73 0x00 0x10 0x00（倒过来）
    cpu->M[0xdb0] = 0x73;
    cpu->M[0xdb1] = 0x00;
    cpu->M[0xdb2] = 0x10;
    cpu->M[0xdb3] = 0x00;
    printf("成功加载 %zu 字节到内存。\n", size);
    fclose(file);
}

void draw(uint8_t *P) {
  uint32_t* color = (uint32_t *)P;
  int row_draw = 256;
  int col_draw = 256;
  
  for(int y = 0; y < row_draw; y++) {
    // 一次性画出一整行（256个像素）
    // 参数：坐标(0, y)，数据源当前行指针，宽256，高1
    io_write(AM_GPU_FBDRAW, 0, y, &color[y * col_draw], col_draw, 1, false);
  }
  io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true); // 刷入屏幕
}

int main(const char *args) {
    // 检查是否传入了参数（args 为空指针或空字符串）
    if (args == NULL || args[0] == '\0') {
        printf("使用方法: 请通过 mainargs 传入 bin 文件路径\n");
        return 1;
    }
    // 初始化 CPU，PC=0, GPR全0 
    //使用static变量，把数据存储到数据段（栈空间太小）
    static RV32I_CPU cpu = {0}; 
    ioe_init(); // 初始化外设接口
    load_bin(&cpu, args); // 加载你指定的 bin 文件

    // 运行模拟器
    while (running) {
        step(&cpu);
        // 这里可以加上打印寄存器状态的逻辑，方便调试

    }
    printf("程序执行结束，接下来加载图像到窗口\n");
    draw(cpu.P); // 从外设寄存器空间加载图像数据到窗口
    while(1); // 保持窗口打开
    return 0;
}

