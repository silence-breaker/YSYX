#include <stdio.h>
#include <math.h>
/*复数运算
struct complex_number{
    float x,y;
};

int main(void)
{
    struct complex_number z1;
    float x,y;
    printf("请输入实部和虚部\n");
    scanf("%f %f",&x,&y);
    z1.x=x;
    z1.y=y;
    if(x!=0&&y!=0)
    {
        printf("%f+%fi\n",z1.x,z1.y);
    }
    else if(x==0&&y!=0)
    {
        printf("%fi\n",z1.y);
    }
    else if(x!=0&&y==0)
    {
        printf("%f\n",z1.x);
    }
    else
        printf("0");
    return 0;
}
*/
struct rational{
    int a,b;
}
struct rational make_rational(int x,int y)
{
    struct rational a;
    a.a=x;
    a.b=y;
    return a;
}

int main(void)
{
	struct rational a = make_rational(1, 8); /* a=1/8 */
	struct rational b = make_rational(-1, 8); /* b=-1/8 */
	print_rational(add_rational(a, b));
	print_rational(sub_rational(a, b));
	print_rational(mul_rational(a, b));
	print_rational(div_rational(a, b));

	return 0;
}