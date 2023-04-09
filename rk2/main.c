#include <stdio.h>
#include "words.h"

/*
 * Вводится квадратная матрица размером от 1 до 5,
 * макс. размер слова 10.
 * Отсортировать строки матрицы на основании
 * суммарной длины всех слов строки
 */

int main(void)
{
    int err = RET_SUCCESS;

    word_t buffer[MATMAX][MATMAX];
    word_t *words[MATMAX];
    int n;

    if (scanf("%d", &n) != 1 || n <= 0 || n > MATMAX)
    {
        err = INPUT_ERR;
    }
    else
    {
        init(words, &buffer[0][0], n, n);
        if (inputwords(words, n, n) != 0)
        {
            err = INPUT_ERR;
        }
        else
        {
            sortwords(words, n, n);
        }
    }

    if (!err)
    {
        printwords(words, n, n);
    }
    
    return err;
}
