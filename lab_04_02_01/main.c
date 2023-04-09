#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STRMAX      256
#define WORDMAX     16
#define WCMAX       128
#define DELIMS      ",;:-.!? "

#define RET_SUCCESS         0
#define NO_INPUT_ERR        1
#define NO_WORDS_ERR        2
#define STR_OVERFLOW_ERR    3


void init(char **mat, char *buf);

int splitwords(char **dest, char *raw);
bool isdelim(char ch);

void sortstrs(char **strs, int srtc);
void swapstr(char **a, char **b);

int uniq(char **strs, int strc);
void rmpos(char **strs, int strc, int pos);

void printstrs(char **strs, int strc);


int main(void)
{
    int err = RET_SUCCESS;

    char raw[STRMAX + 2];
    char buffer[WCMAX][WORDMAX + 1];
    char *words[WCMAX];
    int wordc;

    if (fgets(raw, STRMAX + 2, stdin) == NULL)
    {
        err = NO_INPUT_ERR;
    }
    else if (raw[0] == '\n')
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
                sortstrs(words, wordc);
                wordc = uniq(words, wordc);
            }
        }
    }

    if (!err)
    {
        printf("Result:");
        printstrs(words, wordc);
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

    char word[WORDMAX + 2];
    int wordlen = 0;

    for (; *raw && wordc != -1; raw++)
    {
        if (!isdelim(*raw))
        {
            // Check if the word is too big
            word[wordlen++] = *raw;
            if (wordlen > WORDMAX)
            {
                wordc = -1;
            }
        }
        else if (wordlen != 0)
        {
            word[wordlen] = '\0';
            strcpy(dest[wordc++], word);
            wordlen = 0;
        }
    }

    // Copy last word if needed
    if (wordc != -1 && wordlen != 0)
    {
        word[wordlen] = '\0';
        strcpy(dest[wordc++], word);
    }

    return wordc;
}


bool isdelim(char ch)
{
    bool result = true;
    if (strchr(DELIMS, ch) == NULL)
    {
        result = false;
    }
    return result;
}


void sortstrs(char **strs, int srtc)
{
    for (int i = 1; i < srtc; i++)
    {
        for (int j = i; j > 0 && strcmp(strs[j - 1], strs[j]) > 0; j--)
        {
            swapstr(strs + j, strs + j - 1);
        }
    }
}


void swapstr(char **a, char **b)
{
    char *buf = *a;
    *a = *b;
    *b = buf;
}


int uniq(char **strs, int strc)
{
    int newc = strc;
    for (int i = 0; i < newc - 1; i++)
    {
        if (strcmp(strs[i + 1], strs[i]) == 0)
        {
            rmpos(strs, newc--, i--);
        }
    }

    return newc;
}


void rmpos(char **strs, int strc, int pos)
{
    for (int i = pos; i < strc - 1; i++)
    {
        swapstr(strs + i, strs + i + 1);
    }
}


void printstrs(char **strs, int strc)
{
    for (int i = 0; i < strc; i++)
    {
        printf(" %s", strs[i]);
    }
    printf("\n");
}
