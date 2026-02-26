#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//模拟RV32I指令集
typedef struct {
    uint32_t pc; //程序计数器
    uint32_t GPR[32]; //通用寄存器
    uint8_t M[1024]; //按字节寻址的内存
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
    }

    cpu->GPR[0] = 0; // 确保 x0 恒为 0 
    cpu->pc = next_pc;

}