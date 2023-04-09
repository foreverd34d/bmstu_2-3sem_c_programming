#include <stdio.h>
#define N 10

void swap(int *a, int *b);
void group_zeros(int a[], int n);
void group_even(int a[], int n);

int main(void)
{
	int n, a[N], errorcode = 0;

	if (scanf("%d", &n) != 1)
	    errorcode = 1;
	else if (n < 1 || n > 10)
	    errorcode = 2;

	for (int i = 0; i < n; i++)
	{
	    if (scanf("%d", &a[i]) != 1)
		    errorcode = 1;
	}

    if (errorcode == 0)
    {
        group_zeros(a, n);
        group_even(a, n);
    }

    if (errorcode == 1)
        printf("Error: Incorrect input\n");
    else if (errorcode == 2)
        printf("Error: Incorrect array length\n");
    else
        for (int i = 0; i < n; i++)
            printf("%d ", a[i]);
    
    printf("\n");
    return errorcode;
}

void swap(int *a, int *b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

void group_zeros(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i; j < n - 1 ; j++)
            if (a[j] == 0)
                swap(&a[j], &a[j + 1]);
}

void group_even(int a[], int n)
{
    int l = 0;
    for (int i = 0; i < n; i++)
        if (a[i] % 2 == 0 && a[i] != 0)
        {
            for (int j = i; j > l; j--)
                swap(&a[j], &a[j - 1]);
            l++;
        }
}
