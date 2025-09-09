#include <math.h>
#include <stdio.h>
/*
void print_logarithm(double x)
{
	if (x <= 0.0) {
		printf("Positive numbers only, please.\n");
		return;
	}
	printf("The log of x is %f", log(x));
}

int main(void)
{
    print_logarithm(10.0);
    print_logarithm(-5.0);
    return 0;
}
*/
//gcc 深入理解函数练习.c -lm 需要链接数学库，同时编译生成可执行文件
int is_leap_year(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 1;
    } else {
        return 0;
    }
}

double myround(double x)
{
    if(x >= 0) {
        return floor(x + 0.5);
    } else {
        return ceil(x - 0.5);
    }
}

int main(void)
{
    int year;
    double x;
    printf("Enter a year: ");
    scanf("%d", &year);
    if (is_leap_year(year)) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }
    printf("Enter a number: ");
    scanf("%lf", &x);
    printf("The rounded value is %f\n", myround(x));
    return 0;
}