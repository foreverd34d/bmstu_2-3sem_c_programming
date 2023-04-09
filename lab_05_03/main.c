/*
 * Выбранный тип: int
 * Тип сортировки: сортировка вставками
 * Направление сортировки: по возрастанию
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesort.h"

int main(int argc, char **argv)
{
    int err = 0;

    if (argc < 2)
    {
        err = NO_ARG_ERR;
    }
    else
    {
        char *action = argv[1];
        if (strcmp(action, "c") == 0 && argc == 4)
        {
            long count = strtol(argv[2], NULL, 10);
            if (count <= 0)
            {
                err = NO_COUNT_ERR;
            }
            else
            {
                FILE *f = fopen(argv[3], "wb");
                if (f == NULL)
                {
                    err = FILE_ERR;
                }
                else
                {
                    create(f, count);
                    fclose(f);
                }
            }
        }
        else if (strcmp(action, "p") == 0 && argc == 3)
        {
            FILE *f = fopen(argv[2], "rb");
            if (f == NULL || getfsize(f) <= 0 || getfsize(f) % 4 != 0)
            {
                err = FILE_ERR;
            }
            else
            {
                printnumbers(f);
                fclose(f);
            }
        }
        else if (strcmp(action, "s") == 0 && argc == 3)
        {
            FILE *f = fopen(argv[2], "r+b");
            if (f == NULL || getfsize(f) <= 0 || getfsize(f) % 4 != 0)
            {
                err = FILE_ERR;
            }
            else
            {
                sort(f);
                fclose(f);
            }
        }
        else
        {
            err = UNKNOWN_KEY_ERR;
        }
    }

    return err;
}
