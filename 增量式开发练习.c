#include <stdio.h>
#include <math.h>
double calculate_distance(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

double calculate_area(double radius)
{
    // M_PI is defined in math.h
    return M_PI * radius * radius;
}

int main(void)
{
    double x1, y1, x2, y2;
    printf("Enter coordinates of point 1 (x1 y1): ");
    scanf("%lf %lf", &x1, &y1);
    printf("Enter coordinates of point 2 (x2 y2): ");
    scanf("%lf %lf", &x2, &y2);
    double distance = calculate_distance(x1, y1, x2, y2);
    printf("Distance between points: %lf\n", distance);

    double area = calculate_area(distance);
    printf("Area of the circle: %lf\n", area);

    return 0;
}