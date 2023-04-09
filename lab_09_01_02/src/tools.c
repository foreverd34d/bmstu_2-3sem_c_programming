#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

int read_pos_double(double *to, const char *from)
{
    int err = 0;
    char *after = NULL;
    double num = strtod(from, &after);
    if (*after != '\0' || *after == *from || isspace(*from))
    {
        err = 1;
    }
    else if (num <= 0)
    {
        err = 2;
    }
    else
    {
        *to = num;
    }

    return err;
}

bool is_empty(const char *str)
{
    bool result = true;
    for (; *str; str++)
    {
        if (!isspace(*str))
        {
            result = false;
        }
    }
    return result;
}

bool starts_with(const char *str, const char *part)
{
    return strncmp(str, part, strlen(part)) == 0;
}
