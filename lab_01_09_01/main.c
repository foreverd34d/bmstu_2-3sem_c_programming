#include <stdio.h>
#include <math.h>

double sqrtsum(double x, int n);

int main(void)
{
    double x;
    double sum = 0;
    int err = 0;

    if (scanf("%lf", &x) != 1 || x < 0)
        err = 1;
    else
    {
        int n = 1;
        while (err == 0 && x >= 0)
        {
            sum += sqrtsum(x, n++);
            if (scanf("%lf", &x) != 1)
                err = 1;
        }
    }

    if (err == 0)
    {
        sum = sin(sum);
        printf("%lf", sum);
    }

    return err;
}

double sqrtsum(double x, int n)
{
    return sqrt(x / n);
}
