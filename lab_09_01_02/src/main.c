#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "error_codes.h"
#include "items.h"
#include "item_io.h"
#include "item_utils.h"

int main(int argc, char **argv)
{
    int err = OK;
    if (argc != 2 && argc != 3)
    {
        err = ERR_ARG;
    }
    else
    {
        item_t *items = NULL;
        ssize_t items_len = 0;

        FILE *f = fopen(argv[1], "r");
        if (f == NULL)
        {
            err = ERR_FILE;
        }
        else if (argc == 2)
        {
            items_len = read_items_file(&items, f);

            if (items_len <= 0)
            {
                err = ERR_STRUCT;
            }
            else
            {
                sort_by_density(items, items_len);
                print_items_file(items, items_len, stdout);
            }
        }
        else if (argc == 3 && strlen(argv[2]) > 0)
        {
            items_len = read_items_file(&items, f);

            if (items_len <= 0)
            {
                err = ERR_STRUCT;
            }
            else
            {
                item_t *filtered_items = NULL;
                int filtered_items_len = 0;
                filtered_items_len = filter_by_prefix(&filtered_items, filtered_items_len, items, items_len, argv[2]);

                if (filtered_items_len < 0)
                {
                    err = ERR_MEM;
                }
                else
                {
                    print_items_file(filtered_items, filtered_items_len, stdout);
                }

                items_free(&filtered_items, items_len);
            }
        }
        else
        {
            err = ERR_ARG;
        }

        if (f != NULL)
        {
            fclose(f);
        }

        items_free(&items, items_len);
    }

    return err;
}
