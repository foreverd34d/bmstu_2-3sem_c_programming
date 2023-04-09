#include "towers.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define OK 0
#define ERR_MEM 1
#define ERR_ARGS 2
#define ERR_FILE_OPEN 10

#define ARR_MAX 10

int main(int argc, char **argv)
{
    int err = OK;

    if (argc != 2)
    {
        err = ERR_ARGS;
    }
    else
    {
        FILE *f = fopen(argv[1], "r");
        if (f == NULL)
        {
            err = ERR_FILE_OPEN;
        }
        else
        {
            tower_t *towers[ARR_MAX];
            int len = read_towers_file(f, towers, ARR_MAX);
            fclose(f);

            if (len <= 0)
            {
                err = ERR_MEM;
            }
            else
            {
                print_towers(towers, len);
                tower_t *merged = towers_merge(towers, len);
                if (!merged)
                {
                    err = ERR_MEM;
                }
                else
                {
                    print(merged);
                }
                clear(merged);
            }

            clear_towers(towers, len);
        }
    }

    return err;
}
