#include <stdio.h>
#include <string.h>
#include "stud.h"

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
        if (strcmp(action, "sb") == 0 && argc == 3)
        {
            FILE *f = fopen(argv[2], "r+b");
            if (f == NULL)
            {
                err = FILE_ERR;
            }
            else
            {
                sort_students(f);
                rewind(f);
                print_students(f);
                fclose(f);
            }
        }
        else if (strcmp(action, "fb") == 0 && argc == 5)
        {
            FILE *firstf = fopen(argv[2], "rb");
            FILE *secondf = fopen(argv[3], "wb");
            if (firstf == NULL || secondf == NULL)
            {
                err = FILE_ERR;
            }
            else
            {
                char substr[SURNAME_LEN + 1];
                strncpy(substr, argv[4], SURNAME_LEN);

                find_students(firstf, secondf, substr);
                fclose(firstf);
                fclose(secondf);
            }
        }
        else if (strcmp(action, "db") == 0 && argc == 3)
        {
            FILE *f = fopen(argv[2], "r+b");
            if (f == NULL)
            {
                err = FILE_ERR;
            }
            else
            {
                delete_students(f);
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
