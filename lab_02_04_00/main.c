#include <stdio.h>
#define N 10
#define OF_ERR 100

int read_array(int *a, int *n);
void swap(int *a, int *b);
void bubble_sort(int *a, int n);
void print_array(int *a, int n);

int main(void)
{
    int a[N], n = 0;
    int err = read_array(a, &n);

    if (err == 0 || err == OF_ERR)
        bubble_sort(a, n);

    switch (err)
    {
        case 1:
            printf("Error: Incorrect input\n");
            break;
        case 0:
        case OF_ERR:
            print_array(a, n);
    }

    return err;
}

int read_array(int *a, int *n)
{
    int err = 0, x;
    int rc = scanf("%d", &x);
    if (rc != 1)
        err = 1;

    while (rc == 1 && err == 0)
    {
        if (*n >= N)
            err = OF_ERR;
        else
        {
            a[(*n)++] = x;
            rc = scanf("%d", &x);
        }
    }

    return err;
}

void swap(int *a, int *b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

void bubble_sort(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(&a[j], &a[j + 1]);
}

void print_array(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
