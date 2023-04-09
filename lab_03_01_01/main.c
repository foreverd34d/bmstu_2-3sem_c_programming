#include <stdio.h>
#define N 10
#define M 10

int read_size(int *n, int *m);
int read_matrix(int **a, int n, int m);

void init(int **a, int *buf, int n, int m);
void print_matrix(int **a, int n, int m);
void print_array(int *a, int n);
void find_symmetric(int **a, int *b, int n, int m);

int main(void)
{
    int buf[N][M], n, m;
    int err = 0;
    int *a[N];
    int res[N] = { -1 };

    if (read_size(&n, &m) != 0)
        err = 1;
    else if (init(a, &buf[0][0], n, m), read_matrix(a, n, m) != 0)
        err = 2;
    else
        find_symmetric(a, res, n, m);

    switch (err)
    {
        case 1:
            printf("Error: Incorrect size\n");
            break;
        case 2:
            printf("Error: Incorrect matrix element\n");
            break;
        default:
            print_array(res, n);
            break;
    }

    return err;
}

int read_size(int *n, int *m)
{
    int err = 0;
    if (scanf("%d%d", n, m) != 2 || *n <= 0 || *n > 10 || *m <= 0 || *m > 10)
        err = 1;

    return err;
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

void print_array(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void find_symmetric(int **a, int *b, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        int is_symmetric = 1;
        for (int j = 0; j < m && is_symmetric; j++)
            if (a[i][j] != a[i][m - j - 1])
                is_symmetric = 0;

        if (is_symmetric)
            b[i] = 1;
        else
            b[i] = 0;
    }
}
