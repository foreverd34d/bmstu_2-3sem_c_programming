#include <stdio.h>

int euclid(int a, int b);

int main(void)
{
    int a, b, c, err = 0;
    printf("Input a and b: ");
    
    if (scanf("%d%d", &a, &b) != 2 || a <= 0 || b <= 0)
        err = 1;
    else
        c = euclid(a, b);

    if (err)
        printf("Input error. Enter a number");
    else
        printf("NOD = %d", c);
    
    return err;
}

int euclid(int a, int b)
{
    while (a != b) 
    {
        if (a > b)
            a -= b;
        else 
            b -= a;
    }

    return a;
}

