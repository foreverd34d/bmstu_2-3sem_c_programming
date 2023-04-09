#include <stddef.h>
#include <stdlib.h>
#include "../inc/numkey.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int err = RET_SUCCESS;
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src)
    {
        err = ERR_KEY_ARGS;
    }
    else if (pb_dst == NULL || pe_dst == NULL)
    {
        err = ERR_KEY_ARGS;
    }
    else if (pb_src == *pb_dst || pe_src == *pe_dst)
    {
        err = ERR_KEY_ARGS;
    }
    else
    {
        size_t neg_ind = get_neg_ind(pb_src, pe_src);
        if (neg_ind == 0)
        {
            err = ERR_KEY_NO_RESULT;
        }
        else
        {
            int *dest = malloc(neg_ind * sizeof(int));
            if (dest == NULL)
            {
                err = ERR_MEM;
            }
            else
            {
                *pb_dst = dest;
                *pe_dst = *pb_dst + neg_ind;

                int *el = *pb_dst;
                for (size_t i = 0; i < neg_ind; i++)
                {
                    *(el)++ = *(pb_src)++;
                }
            }
        }
    }
    return err;
}

size_t get_neg_ind(const int *beg, const int *end)
{
    size_t len = end - beg;
    size_t result = len;
    for (const int *el = beg; el < end && result == len; el++)
    {
        if (*el < 0)
        {
            result = el - beg;
        }
    }
    return result;
}
