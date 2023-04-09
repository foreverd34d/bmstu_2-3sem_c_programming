#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 10

int read_size(int *n);
int read_array(int *a, int n);
int is_prime(int x);
int copy_prime(int *from, int *to, int n);
void print_array(int *a, int n);

int main(void)
{
    int n, a[N], err;

    err = read_size(&n);
    if (err == 0)
        err = read_array(a, n);

    int b[N] = { 0 }, j;
    if (err == 0)
        j = copy_prime(a, b, n);

    if (err == 1)
        printf("Error: Incorrect input\n");
    else if (err == 2)
        printf("Error: Incorrect array length\n");
    else if (j == 0)
    {
        printf("Error: No result\n");
        err = 3;
    }
    else
        print_array(b, j);
    
    return err;
}

int copy_prime(int *from, int *to, int n)
{
    int j = 0;
    for (int i = 0; i < n; i++)
        if (is_prime(from[i]))
        {
            to[j] = from[i];
            j++;
        }

    return j;
}

int is_prime(int x)
{
    int res = 1;
    if (x <= 1 || x == 0)
        res = 0;
    else if (abs(x) == 2)
        res = 1;
    else
    {
        for (int d = 2; d <= sqrt(x) + 1 && res == 1; d++)
        {
            if (x % d == 0)
                res = 0;
        }
    }

    return res;
}

int read_size(int *n)
{
    int err = 0;
    if (scanf("%d", n) != 1)
        err = 1;
    else if (*n <= 0 || *n > 10)
        err = 2;

    return err;
}

int read_array(int *a, int n)
{
    int err = 0;
    for (int i = 0; i < n && err == 0; i++)
        if (scanf("%d", &a[i]) != 1)
            err = 1;

    return err;
}


void print_array(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
