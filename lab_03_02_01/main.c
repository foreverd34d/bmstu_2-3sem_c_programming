#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 10

int read_size(int *n, int *m);
int read_matrix(int **a, int n, int m);
int digit_sum(int x);
int find_min_ind(int **a, int n, int m, int *ind);

void init(int **a, int *buf, int n, int m);
void swap(int *a, int *b);
void del_row(int **a, int n, int m, int row);
void del_col(int **a, int n, int m, int col);
void print_matrix(int **a, int n, int m);

int main(void)
{
    int buf[N][M], n, m;
    int ind[2] = { 0 }, *a[N];
    int err = 0;

    if (read_size(&n, &m) != 0)
        err = 1;
    else if (n == 1 || m == 1)
        err = 3;
    else if (init(a, &buf[0][0], n, m), read_matrix(a, n, m) != 0)
        err = 2;
    else if (find_min_ind(a, n, m, ind) != 0)
        err = 3;
    else
    {
        del_row(a, n--, m, ind[0]);
        del_col(a, n, m--, ind[1]);
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

void swap(int *a, int *b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

int find_min_ind(int **a, int n, int m, int *ind)
{
    int err = 0, min = digit_sum(a[0][0]);
    int max = min;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int sum = digit_sum(a[i][j]);
            if (sum < min)
            {
                min = sum;
                ind[0] = i;
                ind[1] = j;
            }
            else if (sum > max)
                max = sum;
        }
    if (min == max)
        err = 1;

    return err;
}

void del_row(int **a, int n, int m, int row)
{
    for (int i = row; i < n - 1; i++)
        for (int j = 0; j < m; j++)
            swap(&a[i][j], &a[i + 1][j]);
}

void del_col(int **a, int n, int m, int col)
{
    for (int i = 0; i < n; i++)
        for (int j = col; j < m - 1; j++)
            swap(&a[i][j], &a[i][j + 1]);
}

int read_size(int *n, int *m)
{
    int err = 0;
    if (scanf("%d", n) != 1 || scanf("%d", m) != 1)
        err = 1;
    else if (*n <= 0 || *n > 10 || *m <= 0 || *m > 10)
        err = 2;

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
