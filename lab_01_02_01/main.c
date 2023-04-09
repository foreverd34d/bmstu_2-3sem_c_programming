#include <stdio.h>
#include <math.h>

float trapezoid_area(float a, float b, float phi);

int main(void)
{
    float a, b, phi;
    printf("Input a, b and angle: ");
    scanf("%f%f%f", &a, &b, &phi);

    if (a > b)
    {
        float buf = b;
        b = a;
        a = buf;
    }
    float area = trapezoid_area(a, b, phi);
 
    printf("Area = %f", area);

    return 0;
}

float trapezoid_area(float a, float b, float phi)
{
    return ((b * b - a * a) * tan(phi * M_PI / 180)) / 4; 
}

