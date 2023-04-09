#include <stdio.h>
#include <math.h>

double maclaurin(double x, double eps);
double func(double x);

int main(void)
{
    double x, eps;
    double s, f, delta_abs, delta_rel;
    int err = 0;

    if (scanf("%lf%lf", &x, &eps) != 2)
        err = 1;
    else if (eps > 1 || eps <= 0 || fabs(x) >= 1)
        err = 2;
    else
    {
        s = maclaurin(x, eps);
        f = func(x);
        delta_abs = fabs(f - s);
        delta_rel = delta_abs / fabs(f);
    }

    switch (err)
    {
        case 1:
            printf("Incorrect input\n");
            break;
        case 2:
            printf("Incorrect data\n");
            break;
        default:
            printf("%lf %lf %lf %lf", s, f, delta_abs, delta_rel);
    }

    return err;
}

double func(double x)
{
    return atan(x);
}

double maclaurin(double x, double eps)
{
    double el = x;
    double sum = el;
    int sign = 1;
    int n = 3;

    while (fabs(el) >= eps)
    {
        el = pow(-1, sign) * pow(x, n) / n;
        sum += el;
        n += 2;
        sign++;
    }

    return sum;
}

