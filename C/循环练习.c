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
/*计算1到100中9的倍数的个数

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
*/
/*输出100以内的素数
int is_prime(int n)
{
	int i;
	for (i = 2; i < n; i++)
		if (n % i == 0)
            return 0;
    return 1;
}

int main(void)
{
	int i;
	for (i = 2; i <= 100; i++) {
		if (is_prime(i))
			printf("%d\n", i);
	}
	return 0;
}
*/

/*
int main(void)
{
	int i, j;
	for (i=1; i<=9; i++) {
		for (j=1; j<=9; j++)
			printf("%d\t", i*j);
		printf("\n");
	}
	return 0;
}
*/
/*打印小九九
int main(void)
{
    int i,j;
    for(i=1;i<=9;i++)
    {
        for(j=1;j<=i;j++)
        {
            printf("%d\t",j*i);
        }
        printf("\n");
    }
    return 0;
}
*/
/*
int diamond(int n, char c)
{
    int i,j;
   
    if(n%2==0)
    {
        printf("请输入奇数\n");
        return -1;
    };
    for(i=1;i<=n;i++)
    {
        if(i<=n/2+1)
        {
            for(j=n/2+1-i;j>0;j--)
            {
                printf("\t");
            }
            for(j=1;j<=2*i-1;j++)
            {
                printf("%c\t",c);
            }
            printf("\n");
        }
        else
        {
            for(j=1;j<=i-n/2-1;j++)
            {
                printf("\t");
            }
            for(j=1;j<=2*(n-i)+1;j++)
            {
                printf("%c\t",c);
            }
            printf("\n");
        }
    };
    return 0;
};
int main(void)
{
    int n;
    char c;
    printf("请输入一个奇数和一个字符：");
    scanf("%d %c",&n,&c);
    diamond(n,c);
    return 0;
}
*/
