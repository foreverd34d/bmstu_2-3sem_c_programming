#include <stdio.h>
#include "average.h"

int main(int argc, char **argv)
{
    int err = RET_SUCCESS;
    double result = 0;

    if (argc != 2)
    {
        err = ARG_ERR;
    }
    else
    {
        FILE *f = fopen(argv[1], "r");
        if (f == NULL)
        {
            err = FILE_ERR;
        }
        else
        {
            err = between_min_max(f, &result);
            fclose(f);
        }
    }

    if (!err)
    {
        printf("%lf\n", result);
    }

    return err;
}
