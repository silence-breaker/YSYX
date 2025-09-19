#include <stdio.h>
int main(void)
{
    int i = 0xcffffff3;
    printf("%x\n",0xcffffff3>>2);//逻辑右移，无符号数
    printf("%x\n",i>>2);//算术右移，有符号数
    return 0;
}
