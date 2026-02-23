#include <stdint.h>
#include <stdio.h>
//采用uint8_t来表示ISA中的指令和PC，这是固定的8位无符号整数（相当于最高位不是作为符号位）
uint8_t PC = 0;//ISA层面中PC位宽为4位, 但C语言中不存在4位的基础数据类型
uint8_t R[4];//GPR有4个寄存器
uint8_t M[16];//PC位宽是4所以最多16条指令

//指令定义
/*
 7  6 5  4 3   2 1   0
+----+----+-----+-----+
| 00 | rd | rs1 | rs2 | R[rd]=R[rs1]+R[rs2]       add指令, 寄存器相加
+----+----+-----+-----+
| 10 | rd |    imm    | R[rd]=imm                 li指令, 装入立即数, 高位补0
+----+----+-----+-----+
| 11 |   addr   | rs2 | if (R[0]!=R[rs2]) PC=addr bner0指令, 若不等于R[0]则跳转
+----+----+-----+-----+
| 01 |   xxxx   | rs2 | printf("R[rs]=%d\n", R[rs])  out指令 输出寄存器值, 这里的xxxx不使用
*/

//指令周期函数，模拟每条指令的执行过程
void inst_cycle(){
    uint8_t inst = M[PC];
    uint8_t opcode = (inst & 0xC0) >> 6;
    switch(opcode) {
        case 0b00: //ADD
            uint8_t rd = (inst & 0x30) >> 4;
            uint8_t rs1 = (inst & 0x0C) >> 2;
            uint8_t rs2 = (inst & 0x03);
            R[rd] = R[rs1] + R[rs2];
            PC += 1;
            break;         
        case 0b10: //LI
            rd = (inst & 0x30) >> 4;
            uint8_t imm = (inst & 0x0F);
            R[rd] = imm;
            PC += 1;
            break;
        case 0b11: //bner0
            rs2 = (inst & 0x03);
            uint8_t addr = (inst & 0x3C) >> 2;
            if(R[0]!=R[rs2])
            {
                PC = addr;
            }
            else
            {
                PC += 1;
            }
            break;
        case 0b01: //OUT
            rs2 = (inst & 0x03);
            printf("R[%d]=%d\n", rs2, R[rs2]);
            PC += 1;
            break;
    }
}

//初始化指令内存，加载指令
int main(int n){
    M[0] = 0b10001010;
    M[1] = 0b10010000;
    M[2] = 0b10100000;
    M[3] = 0b10110001;
    M[4] = 0b00010111;
    M[5] = 0b00101001;
    M[6] = 0b11010001;
    M[7] = 0b01000010;
    M[8] = 0b11011111;
    while(1){
        inst_cycle();
        printf("当前PC值为%d\n",PC);
        
        

    }
}
