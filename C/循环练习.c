#include <stdio.h>
#include <math.h>
/*计算两个整数的最大公约数

int calculate_gcd(int a, int b)
{
    a=fabs(a);
    b=fabs(b);
    while(b!=0)
    {
        int temp = b;
        b=a%b;
        a=temp;
    }
    return a;
}
int main(void)
{
    int a,b;
    printf("请输入两个整数：");
    scanf("%d %d",&a,&b);
    int gcd = calculate_gcd(a,b);
    printf("最大公约数是：%d\n",gcd);
    return 0;
}
*/

int cout_nine(void)
{
    int n = 100;
    int i = 0;
    while(n>=9)
    {
        if(n%9==0)
        {
            i++;
        }
        n--;
    }
    return i;
}

int main(void)
{
    int count = cout_nine();
    printf("1到100有%d个9的倍数\n",count);
    return 0;
}