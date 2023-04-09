#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 10

int read_size(int *n, int *m);
int read_matrix(int **a, int n, int m);
int digit_sum(int x);
int find_by_sum(int **a, int *res, int *res_i, int *res_j, int n, int m);

void init(int **a, int *buf, int n, int m);
void insert(int **a, int *from, int *from_i, int *from_j, int l);
void shift(int *x, int n, int c);
void print_matrix(int **a, int n, int m);

int main(void)
{
    int buf[N][M], n, m;
    int *a[N];
    int err = 0;
    int b[N * N], bi[N * N], bj[N * N];
    int l = -1;

    if (read_size(&n, &m) != 0)
        err = 1;
    else if (init(a, &buf[0][0], n, m), read_matrix(a, n, m) != 0)
        err = 2;
    else
        l = find_by_sum(a, b, bi, bj, n, m);

    if (l == 0)
        err = 3;
    else if (err == 0)
    {
        shift(b, l, 3);
        insert(a, b, bi, bj, l);
    }

    switch (err)
    {
        case 1:
            printf("Error: Incorrect size\n");
            break;
        case 2:
            printf("Error: Incorrect matrix element\n");
            break;
        case 3:
            printf("Error: No result\n");
            break;
        default:
            printf("Result:\n");
            print_matrix(a, n, m);
    }

    return err;
}

int digit_sum(int x)
{
    int sum = 0;
    x = abs(x);
    while (x > 0)
    {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int find_by_sum(int **a, int *res, int *res_i, int *res_j, int n, int m)
{
    int len = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (digit_sum(a[i][j]) > 10)
            {
                res[len] = a[i][j];
                res_i[len] = i;
                res_j[len++] = j;
            }

    return len;
}

void shift(int x[], int n, int c)
{
    for (int i = 0; i < c; i++)
    {
        int buf = x[0];
        for (int j = 0; j < n - 1; j++)
            x[j] = x[j + 1];
       
        x[n - 1] = buf;
    }
}

void insert(int **a, int *from, int *from_i, int *from_j, int l)
{
    for (int i = 0; i < l; i++)
        a[from_i[i]][from_j[i]] = from[i];
}

int read_size(int *n, int *m)
{
    int err = 0;
    if (scanf("%d%d", n, m) != 2 || *n <= 0 || *n > 10 || *m <= 0 || *m > 10)
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
