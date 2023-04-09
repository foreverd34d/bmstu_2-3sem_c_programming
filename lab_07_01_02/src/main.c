#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/errcodes.h"
#include "../inc/numio.h"
#include "../inc/numsort.h"
#include "../inc/numkey.h"

int main(int argc, char **argv)
{
    int err = RET_SUCCESS;
    FILE *fout = NULL;
    int *num_b = NULL, *num_e;

    if (argc != 3 && !(argc == 4 && strcmp(argv[3], "f") == 0))
    {
        err = ERR_ARG;
    }
    else
    {
        FILE *fin = fopen(argv[1], "r");
        if (fin == NULL)
        {
            err = ERR_FILE_OPEN;
        }
        else
        {
            fout = fopen(argv[2], "w");
            if (fout == NULL)
            {
                fclose(fin);
                err = ERR_FILE_OPEN;
            }
        }

        if (!err)
        {
            err = read_numbers_file(&num_b, &num_e, fin);
            fclose(fin);
            if (!err)
            {
                if (argc == 4)
                {
                    int *fil_b = NULL, *fil_e = NULL;
                    err = key(num_b, num_e, &fil_b, &fil_e);
                    if (!err)
                    {
                        free(num_b);
                        num_b = fil_b;
                        num_e = fil_e;
                    }
                }

                if (!err)
                {
                    mysort(num_b, num_e - num_b, sizeof(int), comp_int);
                }
            }
        }
    }

    if (!err)
    {
        print_numbers_file(num_b, num_e, fout);
    }

    free(num_b);
    if (fout != NULL)
    {
        fclose(fout);
    }

    return err;
}
