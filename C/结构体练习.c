#include <stdio.h>
#include <math.h>
/*数据抽象练习
struct rational{
    int numerator;
    int denominator;
};
struct rational make_rational(int numerator, int denominator)
{
    struct rational r;
    r.numerator = numerator;
    r.denominator = denominator;
    return r;
}
int find_gcd(int a, int b)
{
    if (b == 0)
        return a;
    return find_gcd(b, a % b);
}
struct rational add_rational(struct rational a, struct rational b)
{
    struct rational r;
    r.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    r.denominator = a.denominator * b.denominator;
    int gcd = find_gcd(r.denominator, r.numerator);
    r.numerator /= gcd;
    r.denominator /= gcd;
    return r;
}
struct rational sub_rational(struct rational a, struct rational b)
{
    struct rational r;
    r.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    r.denominator = a.denominator * b.denominator;
    int gcd = find_gcd(r.denominator, r.numerator);
    r.numerator /= gcd;
    r.denominator /= gcd;
    return r;
}
struct rational mul_rational(struct rational a, struct rational b)
{
    struct rational r;
    r.numerator = a.numerator * b.numerator;
    r.denominator = a.denominator * b.denominator;
    int gcd = find_gcd(r.denominator, r.numerator);
    r.numerator /= gcd;
    r.denominator /= gcd;
    return r;
}
struct rational div_rational(struct rational a, struct rational b)
{
    struct rational r;
    r.numerator = a.numerator * b.denominator;
    r.denominator = a.denominator * b.numerator;
    int gcd = find_gcd(r.denominator, r.numerator);
    r.numerator /= gcd;
    r.denominator /= gcd;
    return r;
}
void print_rational(struct rational r)
{
    printf("%d/%d\n", r.numerator, r.denominator);
}
int main(void)
{
	struct rational a = make_rational(1, 8); 
	struct rational b = make_rational(-1, 8); 
	print_rational(add_rational(a, b));
	print_rational(sub_rational(a, b));
	print_rational(mul_rational(a, b));
	print_rational(div_rational(a, b));

	return 0;
}
*/
enum coordinate_type{RECTANGULAR, POLAR};

struct complex_struct{
    enum coordinate_type t;
    double a,b;
};
struct complex_struct make_from_real_img(double x, double y)
{
	struct complex_struct z;
	z.t = RECTANGULAR;
	z.a = x;
	z.b = y;
	return z;
}

struct complex_struct make_from_mag_ang(double r, double A)
{
	struct complex_struct z;
	z.t = POLAR;
	z.a = r;
	z.b = A;
	return z;
}

double real_part(struct complex_struct z)
{
    if(z.t== RECTANGULAR)
    {
        return z.a;
    }
    else
    {
        return z.a * cos(z.b);
    }
}

double imag_part(struct complex_struct z)
{
    if(z.t== RECTANGULAR)
    {
        return z.b;
    }
    else
    {
        return z.a * sin(z.b);
    }
}

double magnitude(struct complex_struct z)
{
    if(z.t== RECTANGULAR)
    {
        return sqrt(z.a*z.a + z.b*z.b);
    }
    else
    {
        return z.a;
    }
}

double angle(struct complex_struct z)
{
    if(z.t== RECTANGULAR)
    {
        return atan2(z.b, z.a);
    }
    else
    {
        return z.b;
    }
}
