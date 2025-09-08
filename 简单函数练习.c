#include <stdio.h>

int add1(int x)
{
    x=x+1;
    return x;
};

int main(void)
{
    int a=5;
    int b;
    b=add1(a);
    printf("%d\n", b);
    return 0;
};