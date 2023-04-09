#include <stdio.h>
#define N 10

int read_size(int *n);
int read_array(int *a, int n);
int fibonacci(int n);
int fill_fibonacci(int *a, int n);
void print_array(int *a, int n);

int main(void)
{
    int n, a[2 * N + 1] = { 0 };
    int err = 0;

    if (read_size(&n) != 0)
        err = 1;
    else if (read_array(a, n) != 0)
        err = 2;
    else
    {
        n = fill_fibonacci(a, n);
    }

    switch (err)
    {
        case 1:
            printf("Error: Incorrect size\n");
            break;
        case 2:
            printf("Error: Incorrect array element\n");
            break;
        default:
            print_array(a, n);
    }

    return err;
}

int fibonacci(int n)
{
    int fib0 = 0;
    int fib1 = 1;
    for (int i = 0; i < n; i++)
    {
        fib0 += fib1;
        fib1 = fib0 - fib1;
    }

    return fib0;
}

void shift(int *a, int b, int e)
{
    for (int i = e; i > b; i--)
    {
        int buf = a[i];
        a[i] = a[i - 1];
        a[i - 1] = buf;
    }
}

int fill_fibonacci(int *a, int n)
{
    int j = 0;
    for (int i = 0; i < n; i++)
        if (a[i] % 3 == 0 && a[i] != 0)
        {
            shift(a, ++i, ++n);
            a[i] = fibonacci(j++);
        }

    return n;
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
