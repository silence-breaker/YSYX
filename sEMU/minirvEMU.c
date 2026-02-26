#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//模拟RV32I指令集
typedef struct {
    uint32_t pc; //程序计数器
    uint32_t GPR[32]; //通用寄存器
    uint8_t M[1024*512]; //按字节寻址的内存(512KB)
} RV32I_CPU;

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
                if (funct3 == 0x2)      cpu->GPR[rd] = *(uint32_t *)&cpu->M[addr]; // LW 
                else if (funct3 == 0x4) cpu->GPR[rd] = cpu->M[addr];               // LBU 
            }
            break;

        case 0x23: // STORE (SW, SB)
            {
                // S-Type 立即数被拆分在 inst[31:25] 和 inst[11:7] 
                int32_t imm = ((int32_t)(inst & 0xFE000000) >> 20) | ((inst >> 7) & 0x1F);
                uint32_t addr = cpu->GPR[rs1] + imm;
                if (funct3 == 0x2)      *(uint32_t *)&cpu->M[addr] = cpu->GPR[rs2]; // SW 
                else if (funct3 == 0x0) cpu->M[addr] = cpu->GPR[rs2] & 0xFF;        // SB 
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
                    exit(0); // 正常退出
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
    cpu->M[0x1218] = 0x73;
    cpu->M[0x1219] = 0x00;
    cpu->M[0x121A] = 0x10;
    cpu->M[0x121B] = 0x00;
    printf("成功加载 %zu 字节到内存。\n", size);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("使用方法: %s <filename.bin>\n", argv[0]);
        return 1;
    }

    RV32I_CPU cpu = {0}; // 初始化 CPU，PC=0, GPR全0
    load_bin(&cpu, argv[1]); // 加载你指定的 bin 文件

    // 运行模拟器
    while (1) {
        step(&cpu);
        // 这里可以加上打印寄存器状态的逻辑，方便调试
        if (cpu.pc >= 1024*512) break; // 简单防止越界
    }
    return 0;
}

