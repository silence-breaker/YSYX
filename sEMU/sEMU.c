#include <stdint.h>
uint8_t PC = 0;//ISA层面中PC位宽为4位, 但C语言中不存在4位的基础数据类型
uint8_t R[4];//GPR有4个寄存器
uint8_t M[16];//PC位宽是4所以最多16条指令


