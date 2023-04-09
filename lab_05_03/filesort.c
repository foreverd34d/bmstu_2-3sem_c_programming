#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filesort.h"

long getfsize(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    rewind(f);
    return pos;
}

int get_number_by_pos(FILE *f, long pos)
{
    int num;
    fseek(f, pos * sizeof(num), SEEK_SET);
    fread(&num, sizeof(num), 1, f);
    return num;
}

void put_number_by_pos(FILE *f, long pos, int num)
{
    fseek(f, pos * sizeof(num), SEEK_SET);
    fwrite(&num, sizeof(num), 1, f);
}

void create(FILE *f, long count)
{
    srand(time(NULL));
    for (long i = 0; i < count; i++)
    {
        int num = rand() % 10000;
        fwrite(&num, sizeof(num), 1, f);
    }
}

void printnumbers(FILE *f)
{
    int num;
    while (fread(&num, sizeof(num), 1, f) == 1)
    {
        printf("%d\n", num);
    }
}

void swappos(FILE *f, int pos1, int pos2)
{
    int buf = get_number_by_pos(f, pos2);
    put_number_by_pos(f, pos2, get_number_by_pos(f, pos1));
    put_number_by_pos(f, pos1, buf);
}

void sort(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long end = ftell(f);
    fseek(f, 0, SEEK_SET);
    long beg = ftell(f);

    for (long i = beg + 1; i * (long) sizeof(int) < end; i++)
    {
        for (long j = i; j > beg && get_number_by_pos(f, j - 1) > get_number_by_pos(f, j); j--)
        {
            swappos(f, j - 1, j);
        }
    }
}
