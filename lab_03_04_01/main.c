#include <stdio.h>
#define N 10
#define M 10

int read_size_sq(int *n, int *m);
int read_matrix(int **a, int n, int m);
void init(int **a, int *buf, int n, int m);
void print_matrix(int **a, int n, int m);
void swap_rows(int *x, int *y, int b, int e);
void swap_hourglass(int **a, int n);

int main(void)
{
    int buf[N][M], n, m;
    int *a[N];
    int err = 0;

    if (read_size_sq(&n, &m) != 0)
        err = 1;
    else if (init(a, &buf[0][0], n, m), read_matrix(a, n, m) != 0)
        err = 2;
    else
        swap_hourglass(a, n);

    switch (err)
    {
        case 1:
            printf("Error: Incorrect size\n");
            break;
        case 2:
            printf("Error: Incorrect matrix element\n");
            break;
        default:
            printf("Result:\n");
            print_matrix(a, n, m);
    }

    return err;
}

void swap_rows(int *x, int *y, int b, int e)
{
    for (int i = b; i <= e; i++)
    {
        int buf = x[i];
        x[i] = y[i];
        y[i] = buf;
    }
}

void swap_hourglass(int **a, int n)
{
    for (int i = 0; i < (n / 2); i++)
        swap_rows(a[i], a[n - i - 1], i, n - i - 1);
}

int read_size_sq(int *n, int *m)
{
    int err = 0;
    if (scanf("%d%d", n, m) != 2 || *n <= 0 || *n > 10
        || *m <= 0 || *m > 10 || *n != *m)
        err = 1;

    return err;
}

void init(int **a, int *buf, int n, int m)
{
    for (int i = 0; i < n; i++)
        a[i] = buf + i * m;
}

int read_matrix(int **a, int n, int m)
{
    int err = 0;
    for (int i = 0; i < n && err == 0; i++)
        for (int j = 0; j < m && err == 0; j++)
            if (scanf("%d", &a[i][j]) != 1)
                err = 1;
    return err;
}


void print_matrix(int **a, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
