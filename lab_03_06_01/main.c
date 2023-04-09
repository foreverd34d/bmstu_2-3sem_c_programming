#include <stdio.h>
#define N 10
#define M 10

int read_size_sq(int *n, int *m);
void init(int **a, int *buf, int n, int m);
void fill_clockwise(int **a, int n);
void print_matrix(int **a, int n, int m);

int main(void)
{
    int buf[N][N], n, m;
    int *a[N];
    int err = 0;

    if (read_size_sq(&n, &m) != 0)
        err = 1;
    else
    {
        init(a, &buf[0][0], n, m);
        fill_clockwise(a, n);
    }

    if (err == 1)
        printf("Error: Incorrect size\n");
    else
    {
        printf("Result:\n");
        print_matrix(a, n, m);
    }

    return err;
}

void fill_clockwise(int **a, int n)
{
    int x = 1;
    a[n / 2][n / 2] = n * n;
    for (int i = 0; i < (n / 2); i++)
    {
        for (int j = i; j < n - i; j++)
            a[i][j] = x++;

        for (int j = i + 1; j < n - i - 1; j++)
            a[j][n - i - 1] = x++;

        for (int j = n - i - 1; j > i - 1; j--)
            a[n - i - 1][j] = x++;

        for (int j = n - i - 2; j > i; j--)
            a[j][i] = x++;
    }
}

int read_size_sq(int *n, int *m)
{
    int err = 0;
    if (scanf("%d", n) != 1 || scanf("%d", m) != 1)
        err = 1;
    else if (*n <= 0 || *n > 10 || *m <= 0 || *m > 10)
        err = 2;
    else if (*n != *m)
        err = 3;

    return err;
}

void init(int **a, int *buf, int n, int m)
{
    for (int i = 0; i < n; i++)
        a[i] = buf + i * m;
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
