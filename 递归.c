#include <stdio.h>
#include <math.h>
/* 阶乘递归
int factorial(int n)
{
    if(n==0)
    {
        return 1;
    }
    else 
    return n*factorial(n-1);
}

int main(void)
{
    int num;
    printf("Enter a non-negative integer: ");
    scanf("%d", &num);
    if(num < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        printf("Factorial of %d is %d\n", num, factorial(num));
    }
    return 0;
}
*/
/*计算最大公约数
int calculate_gcd(int a, int b)
{
    a=fabs(a);
    b=fabs(b);
    if(b==0)
        return a;
    else
    {
        if(a%b==0)
            return b;
        else
            return calculate_gcd(b, a%b);
    }
}


int main(void)
{
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    int gcd = calculate_gcd(a, b);
    printf("GCD of %d and %d is %d\n", a, b, gcd);
    return 0;
}
*/
int calculate_Fibonacci(int n)
{
    if(n==0)
        return 0;
    else if(n==1)
        return 1;
    else
        return calculate_Fibonacci(n-1)+calculate_Fibonacci(n-2);
}

int main(void)
{
    int n;
    printf("Enter a non-negative integer: ");
    scanf("%d", &n);
    if(n < 0) {
        printf("Fibonacci is not defined for negative numbers.\n");
    } else {
        printf("Fibonacci of %d is %d\n", n, calculate_Fibonacci(n));
    }
    return 0;
}

