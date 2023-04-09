#include <stdio.h>
#include "average.h"

int minmaxind(FILE *f, int *minind, int *maxind)
{
    int err = RET_SUCCESS;

    int local_minind = 0, local_maxind = 1;
    double min, max;

    // Initialize min and max with two first numbers of seq
    rewind(f);
    if (fscanf(f, "%lf%lf", &min, &max) != 2)
    {
        err = READ_ERR;
    }
    else
    {
        // Swap min and max if min is greater than max
        if (min > max)
        {
            double buf = min;
            min = max;
            max = buf;
            local_minind = 1;
            local_maxind = 0;
        }

        // Check other numbers
        double num;
        for (int i = 2; fscanf(f, "%lf", &num) == 1; i++)
        {
            if (num > max)
            {
                local_maxind = i;
                max = num;
            }

            if (num < min)
            {
                local_minind = i;
                min = num;
            }
        }
        // Check for read errors
        if (!feof(f))
        {
            err = READ_ERR;
        }
        else
        {
            *minind = local_minind;
            *maxind = local_maxind;
        }
    }

    return err;
}

double average(FILE *f, int start, int end)
{
    double num, sum = 0;
    int len = end - start - 1;

    // Skip numbers before start
    rewind(f);
    for (int i = 0; i <= start; i++)
    {
        fscanf(f, "%lf", &num);
    }

    // Summarize numbers after start and before end
    for (int i = 0; i < len; i++)
    {
        fscanf(f, "%lf", &num);
        sum += num;
    }

    return sum / len;
}

int between_min_max(FILE *f, double *result)
{
    int err = RET_SUCCESS;
    
    int minind, maxind;
    err = minmaxind(f, &minind, &maxind);
    if (!err)
    {
        int from = minind < maxind ? minind : maxind;
        int to = minind >= maxind ? minind : maxind;
        if (to - from == 1)
        {
            err = NO_RESULT_ERR;
        }
        else
        {
            *result = average(f, from, to);
        }
    }

    return err;
}
