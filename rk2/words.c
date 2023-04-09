#include <stdio.h>
#include <string.h>
#include "words.h"

void init(word_t **mat, word_t *buf, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        mat[i] = buf + i * m;
    }
}

int inputwords(word_t **words, int n, int m)
{
    int err = RET_SUCCESS;

    for (int i = 0; i < n && !err; i++)
    {
        for (int j = 0; j < m && !err; j++)
        {
            // if (getword(words[i][j]) != 0)
            if (scanf("%s", words[i][j]) != 1)
            {
                err = INPUT_ERR;
            }
        }
    }

    return err;
}

// int getword(word_t word)
// {
//     int err = RET_SUCCESS;
//
//     if (fgets(word, WORDMAX, stdin) == NULL)
//     {
//         err = INPUT_ERR;
//     }
//     else
//     {
//         word[strcspn(word, "\n")] = '\0';
//     }
//
//     return err;
// }

void printwords(word_t **words, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%s ", words[i][j]);
        }
        printf("\n");
    }
}

void sortwords(word_t **words, int n, int m)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0 && get_sum_length(words[j - 1], m) > get_sum_length(words[j], m); j--)
        {
            swapwords(&words[j - 1], &words[j]);
        }
    }
}

int get_sum_length(word_t *words, int n)
{
    int sumlen = 0;
    for (int i = 0; i < n; i++)
    {
        sumlen += strlen(words[i]);
    }

    return sumlen;
}

void swapwords(word_t **a, word_t **b)
{
    word_t *buf = *a;
    *a = *b;
    *b = buf;
}
