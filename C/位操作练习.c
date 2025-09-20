#include <stdio.h>
/*
int main(void)
{
    int i = 0xcffffff3;
    printf("%x\n",0xcffffff3>>2);//逻辑右移，无符号数
    printf("%x\n",i>>2);//算术右移，有符号数
    return 0;
}
*/

int countbit(unsigned int x)
{
    int count = 0;
    while(x)
    {
        count += x & 1;
        x >>= 1;
    }
    return count;

}

unsigned int multiply(unsigned int x, unsigned int y)
{

    unsigned int result = 0;
   
    while(y)
    {
        if(y & 1)
            result += x;
        x <<= 1;
        y >>= 1;
    }
    return result;

}

unsigned int rotate_right(unsigned int x, int n)
{
    int bits = sizeof(x) * 8;
    n %= bits;
    return (x >> n) | (x << (bits - n));
}


int main(void)
{
    int a[12]={0};
    char b[]="helloword";
    unsigned int x = 0x87654321;
    unsigned int y = 0x87654321;
    int n = 4;
    printf("countbit: %d\n", countbit(x));
    printf("multiply: %x\n", multiply(x, y));
    printf("rotate_right: %x\n", rotate_right(x, n));
    //不采用temp来交换数据
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    printf("x=%x,y=%x\n", x, y);
    printf("sizeof(a)=%lu,sizeof(b)=%lu\n", sizeof(a), sizeof(b));
    int i = 0;
    unsigned int sum = 0x0;
    for (i = 0; i < 16; i++)
	sum = sum + (1U<<i);
    printf("sum=%u\n", sum);
    return 0;
}