#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/numsort.h"

void mysort(void *arr, size_t len, size_t size, int comp(const void *, const void *))
{
    char *beg = (char *) arr;
    char *end = (char *) arr + len * size;

    // Don't run the loop if len == 0
    len = len == 0 ? 1 : len;

    char *last_swap_p = end - size;
    char *last_swap_p_cur = last_swap_p;
    for (size_t i = 0; i < len - 1 && last_swap_p != beg; i++)
    {
        for (char *p = beg; p < end - (end - last_swap_p); p += size)
        {
            if (comp(p, p + size) > 0)
            {
                swap(p, p + size, size);
                last_swap_p_cur = p;
            }
        }
        last_swap_p = last_swap_p_cur;
    }
}

void swap(void *a, void *b, size_t size)
{
    void *buffer = malloc(size);
    if (buffer != NULL)
    {
        memcpy(buffer, a, size);
        memmove(a, b, size);
        memcpy(b, buffer, size);
        free(buffer);
    }
}

int comp_int(const void *a, const void *b)
{
    const int na = *((const int *)a);
    const int nb = *((const int *)b);
    return na - nb;
}
