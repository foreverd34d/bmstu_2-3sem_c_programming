#include <stdio.h>
#include <string.h>

#define STRMAX      256
#define WORDMAX     16
#define WCMAX       128
#define DELIMS      ",;:-.!? "

#define RET_SUCCESS         0
#define NO_INPUT_ERR        1
#define NO_WORDS_ERR        2
#define STR_OVERFLOW_ERR    3
#define NO_RESULT_ERR       4


void init(char **mat, char *buf);

int splitwords(char **dest, char *raw);

int getresult(char *result, char **strs, int strc);
char *leaveuniq(char *str);
void rmchar(char *str, int pos);
void swapchars(char *a, char *b);


int main(void)
{
    int err = RET_SUCCESS;

    char raw[STRMAX + 2];
    char result[STRMAX + 1];
    int reslen = 0;

    if (fgets(raw, STRMAX + 2, stdin) == NULL)
    {
        err = NO_INPUT_ERR;
    }
    else if (raw[0] == '\0')
    {
        err = NO_WORDS_ERR;
    }
    else
    {
        // Remove \n at the end of the string
        raw[strcspn(raw, "\n")] = '\0';
        if (strlen(raw) > STRMAX)
        {
            err = STR_OVERFLOW_ERR;
        }
        else
        {
            char buffer[WCMAX][WORDMAX + 1];
            char *words[WCMAX];
            int wordc;

            init(words, &buffer[0][0]);
            wordc = splitwords(words, raw);

            if (wordc == 0)
            {
                err = NO_WORDS_ERR;
            }
            else if (wordc < 0)
            {
                err = STR_OVERFLOW_ERR;
            }
            else
            {
                reslen = getresult(result, words, wordc);
            }
        }
    }

    if (reslen == 0)
    {
        err = NO_RESULT_ERR;
    }
    else if (!err)
    {
        printf("Result: %s\n", result);
    }

    return err;
}


void init(char **mat, char *buf)
{
    for (int i = 0; i < WCMAX; i++)
    {
        mat[i] = buf + i * (WORDMAX + 1);
    }
}


int splitwords(char **dest, char *raw)
{
    int wordc = 0;
    char *word;

    word = strtok(raw, DELIMS);

    while (word != NULL && wordc != -1)
    {
        if (strlen(word) > WORDMAX)
        {
            wordc = -1;
        }
        else
        {
            strcpy(dest[wordc++], word);
        }
        word = strtok(NULL, DELIMS);
    }

    return wordc;
}


int getresult(char *result, char **strs, int strc)
{
    result[0] = '\0';
    char *laststr = strs[strc - 1];

    // Put strings in reversed order
    for (int i = strc - 2; i >= 0; i--)
    {
        // Ignore strings equal to the last one
        if (strcmp(strs[i], laststr) != 0)
        {
            char *newword = leaveuniq(strs[i]);
            strncat(result, newword, WORDMAX);
            strcat(result, " ");
        }
    }

    int reslen = strlen(result);

    // Remove space at the end of the result
    if (reslen > 0)
    {
        result[strlen(result) - 1] = '\0';
    }

    return reslen;
}


char *leaveuniq(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        for (int j = i + 1; str[j]; j++)
        {
            if (str[i] == str[j])
            {
                rmchar(str, j--);
            }
        }
    }

    return str;
}


void rmchar(char *str, int pos)
{
    int len = pos;
    for (; str[len + 1]; len++)
    {
        swapchars(&str[len + 1], &str[len]);
    }
    str[len] = '\0';
}


void swapchars(char *a, char *b)
{
    char buf = *a;
    *a = *b;
    *b = buf;
}
