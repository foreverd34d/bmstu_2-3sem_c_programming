#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define STRMAX 256

#define RET_SUCCESS         0
#define NO_INPUT_ERR        1
#define NO_RESULT_ERR       2
#define STR_OVERFLOW_ERR    3

char *trim(char *str);

bool isip(char *str);
int strnchr(const char *str, char ch);
bool isipnum(const char *str);

int main(void)
{
    int err = RET_SUCCESS;
    char str[STRMAX + 2];
    bool result;

    if (fgets(str, STRMAX + 2, stdin) == NULL)
    {
        err = NO_INPUT_ERR;
    }
    else
    {
        str[strcspn(str, "\n")] = '\0';
        if (strlen(str) > STRMAX)
        {
            err = STR_OVERFLOW_ERR;
        }
        else
        {
            result = isip(trim(str));
        }
    }

    if (!err)
    {
        if (result)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }

    return err;
}

char *trim(char *str)
{
    // Trim trailing spaces
    char *back = str;
    for (; *back; back++);
    while (isspace(*(--back)))
    {
        *back = '\0';
    }

    // Trim leading spaces
    for (; isspace(*str); str++);

    return str;
}

bool isip(char *str)
{
    bool result = true;
    int c = 0;

    if (strnchr(str, '.') != 3)
    {
        result = false;
    }
    else
    {
        char *part = strtok(str, ".");
        while (part != NULL && result)
        {
            if (!isipnum(part) || ++c > 4)
            {
                result = false;
            }
            part = strtok(NULL, ".");
        }
        if (c < 4)
        {
            result = false;
        }
    }

    return result;
}

int strnchr(const char *str, char ch)
{
    int c = 0;

    for (; *str; str++)
    {
        if (*str == ch)
        {
            c++;
        }
    }

    return c;
}

bool isipnum(const char *str)
{
    // Check if the number is not too long
    bool result = strlen(str) <= 3 ? true : false;

    // Check if the number is made out of digits
    for (const char *p = str; *p && result; p++)
    {
        if (!isdigit(*p))
        {
            result = false;
        }
    }

    // Check if the number is between 0 and 255
    if (result)
    {
        long num = strtol(str, NULL, 10);
        if (num < 0 || num > 255)
        {
            result = false;
        }
    }

    return result;
}
