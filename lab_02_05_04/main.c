#include <stdio.h>
#include <stddef.h>
#define N 10

int count_uniq(int *beg, int *end);
int read_size(int *n);
int read_array(int *beg, int *end);
void print_array(int *beg, int *end);

int main(void)
{
    int n, a[N];
    int *end;

    int err = read_size(&n);
    if (err == 0)
    {
        end = a + n;
        err = read_array(a, end);
    }

    int result;
    if (err == 0)
        result = count_uniq(a, end);
    
    if (err == 1)
        printf("Error: Incorrect input\n");
    else if (err == 2)
        printf("Error: Incorrect array length\n");
    else if (result == 0)
    {
        printf("Error: No result\n");
        err = 3;
    }
    else
        printf("%d\n", result);

    return err;
}

int count_uniq(int *beg, int *end)
{
    int c = 0;
    int uniq;
    for (int *pa = beg; pa < end; pa++)
    {
        uniq = 1;
        for (int *pb = pa; pb >= beg && uniq == 1; pb--)
            if (*pa == *pb && pa != pb)
                uniq = 0;

        if (uniq)
            c++;
    }

    return c;
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

int read_array(int *beg, int *end)
{
    int err = 0;
    for (int *pa = beg; pa < end && err == 0; pa++)
        if (scanf("%d", pa) != 1)
            err = 1;

    return err;
}

void print_array(int *beg, int *end)
{
    for (int *pa = beg; pa < end; pa++)
        printf("%d ", *pa);
    printf("\n");
}
