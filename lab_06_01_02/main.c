#include <stdio.h>
#include <string.h>
#include "items.h"

void print_err(int err);

int main(int argc, char **argv)
{
    int err = RET_SUCCESS;
    if (argc < 2)
    {
        err = ERR_ARG;
    }
    else
    {
        item_t items[STRUCTMAX];
        FILE *f = fopen(argv[1], "r");
        if (f == NULL)
        {
            err = ERR_FILE;
        }
        else if (argc == 2)
        {
            int len = read_items(items, f);
            fclose(f);
            if (len <= 0)
            {
                err = ERR_STRUCT;
            }
            else
            {
                sort_by_density(items, len);
                print_items(items, len);
            }
        }
        else if (argc == 3 && strlen(argv[2]) > 0 && strlen(argv[2]) <= NAMEMAX)
        {
            int len = read_items(items, f);
            fclose(f);
            if (len <= 0)
            {
                err = ERR_STRUCT;
            }
            else
            {
                len = filter_by_prefix(items, len, argv[2]);
                print_items(items, len);
            }
        }
        else
        {
            err = ERR_ARG;
        }
    }

    return err;
}
