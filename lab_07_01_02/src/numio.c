#include <stdio.h>
#include <stdlib.h>
#include "../inc/numio.h"

int read_numbers_file(int **dest_b, int **dest_e, FILE *from)
{
    int err = RET_SUCCESS;
    int len = get_numbers_amount(from);
    if (len == 0)
    {
        err = ERR_FILE_EMPTY;
    }
    else if (len < 0)
    {
        err = ERR_FILE_READ;
    }
    else
    {
        *dest_b = malloc(len * sizeof(int));
        if (dest_b == NULL)
        {
            err = ERR_MEM;
        }
        else
        {
            *dest_e = *dest_b + len;
            get_numbers_file(*dest_b, *dest_e, from);
        }
    }
    return err;
}

int get_numbers_amount(FILE *f)
{
    rewind(f);
    int amount = 0;
    int num;
    for (; fscanf(f, "%d", &num) == 1; amount++);
    if (!feof(f))
    {
        amount = -1;
    }
    return amount;
}

void get_numbers_file(int *dest_b, int *dest_e, FILE *from)
{
    rewind(from);
    for (; dest_b < dest_e && fscanf(from, "%d", dest_b) == 1; dest_b++);
}

void print_numbers_file(int *src_b, int *src_e, FILE *dest)
{
    rewind(dest);
    for (; src_b < src_e; src_b++)
    {
        fprintf(dest, "%d ", *src_b);
    }
}
