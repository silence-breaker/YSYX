#include <stdio.h>
int ten_position(int x)
{
    int y=0;
    y=x/10;
    y=y%10;
    if(x>0)
    {
        return y;
    }
    else
    {
        return -y;
    }
}
int one_position(int x)
{
    int y=0;
    y=x%10;
    if(x>0)
    {
        return y;
    }
    else
    {
        return -y;
    }
}


int main(void)
{
    int a =0;
    int b =0;
    int c =0;
    printf("请输入一个整数\n");
    scanf("%d",&a);
    b=ten_position(a);
    c=one_position(a);
    printf("十位数是：%d\n",b);
    printf("个位数是：%d\n",c);
}