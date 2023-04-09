#include <stdio.h>
#include <math.h>
#define EPS 0.000000001

int location(long double ax, long double ay, long double bx, long double by, long double px, long double py);
int fequal(long double a, long double b);

int main(void)
{
    long double ax, ay, bx, by;
    long double px, py;

    int err = 0, result;

    if (scanf("%Lf%Lf%Lf%Lf%Lf%Lf", &ax, &ay, &bx, &by, &px, &py) != 6)
        err = 1;
    else if (fequal(ax, bx) && fequal(ay, by))
        err = 2;
    else
        result = location(ax, ay, bx, by, px, py);

    if (!err)
        printf("%d\n", result);

    return err;
}

int fequal(long double a, long double b)
{
    return fabsl(a - b) < EPS;
}
    
// 2, if located lower; 1, if located on the line; 0, if located higher
int location(long double ax, long double ay, long double bx, long double by, long double px, long double py)
{
    int res = 0;
    if (fequal(ax, bx))
    {
        if (fequal(ax, px))
            res = 1;
        else if (px > ax)
            res = 2;
    }
    else
    {
        long double loc = ((px - ax) * (by - ay) / (bx - ax)) + ay - py;

        if (fabsl(loc) < EPS)
            res = 1;
        else if (loc > 0)
            res = 2;
    }

    return res;
}
