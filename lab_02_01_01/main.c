#include <stdio.h>
#define N 10

int multiply_odd(int *a, int n);
int read_size(int *n);
int read_array(int *a, int n);
void print_array(int *a, int n);

int main(void)
{
    int n, a[N], err;

    err = read_size(&n);
    if (err == 0)
        err = read_array(a, n);

    int res;
    if (err == 0)
        res = multiply_odd(a, n);

    if (err == 1)
        printf("Error: Incorrect input");
    else if (err == 2)
        printf("Error: Incorrect array length");
    else if (res)
        printf("Result: %d\n", res);
    else 
    {
        printf("Error: No result\n");
        err = 3;
    }

    return err;
}

int multiply_odd(int *a, int n)
{
    int res = 1;
    int has_changed = 0;
    for (int i = 0; i < n; i++)
        if (a[i] % 2 != 0)
        {
            has_changed = 1;
            res *= a[i];
        }

    if (!has_changed)
        res = 0;

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
