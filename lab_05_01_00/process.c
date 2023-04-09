#include <stdio.h>
#include "process.h"

int process(FILE *f, int *max)
{
    int count = 0;
    int lmin = -1, lmax = -1;
    int prev = 0, num;

    for (; fscanf(f, "%d", &num) == 1; count++)
    {
        if (prev < 0)
        {
            if (num > lmax || lmax == -1)
            {
                lmax = num;
            }
            else if (num < lmin || lmin == -1)
            {
                lmin = num;
            }
        }
        prev = num;
    }

    int err = RET_SUCCESS;
    if (!err)
    {
        if (count == 0)
        {
            err = NO_DATA_ERR;
        }
        else if (lmax <= 0)
        {
            if (prev < 0)
            {
                err = NO_POS_ERR;
            }
            else
            {
                err = NO_NEG_ERR;
            }
        }
        // Check if all suitable numbers are equal
        else if (lmax == lmin)
        {
            err = NO_MAX_ERR;
        }
        else
        {
            *max = lmax;
        }
    }

    return err;
}
