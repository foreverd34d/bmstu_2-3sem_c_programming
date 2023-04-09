#include <stdio.h>
#define N 10
#define M 10

int read_size(int *n, int *m);
int read_matrix(int **a, int n, int m);
int find_max(int *a, int n);

void init(int **a, int *buf, int n, int m);
void swap(int *x, int *y);
void swap_rows(int **x, int **y);
void find_max_arr(int **a, int *max, int n, int m);
void sort_by_arr(int **a, int *key, int n);
void print_matrix(int **a, int n, int m);

int main(void)
{
    int buf[N][M], n, m;
    int *a[N], max[N];
    int err = 0;

    if (read_size(&n, &m) != 0)
        err = 1;
    else if (init(a, &buf[0][0], n, m), read_matrix(a, n, m) != 0)
        err = 2;
    else
    {
        find_max_arr(a, max, n, m);
        sort_by_arr(a, max, n);
    }

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

int find_max(int x[], int n)
{
    int max_el = x[0];

    for (int i = 1; i < n; i++)
        if (x[i] > max_el)
            max_el = x[i];

    return max_el;
}

void find_max_arr(int **a, int *max, int n, int m)
{
    for (int i = 0; i < n; i++)
        max[i] = find_max(a[i], m);
}

void swap(int *x, int *y)
{
    int buf = *x;
    *x = *y;
    *y = buf;
}

void swap_rows(int **x, int **y)
{
    int *buf = *x;
    *x = *y;
    *y = buf;
}

void sort_by_arr(int **a, int *key, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int max_ind = i;
        for (int j = i + 1; j < n; j++)
            if (key[j] > key[max_ind])
                max_ind = j;
       
        if (max_ind != i)
        {
            swap(&key[i], &key[max_ind]);
            swap_rows(&a[i], &a[max_ind]);
        }
    }
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
