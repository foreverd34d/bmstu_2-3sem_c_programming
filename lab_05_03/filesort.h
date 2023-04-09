#ifndef FILESORT_H
#define FILESORT_H

#include <stdio.h>

#define NO_ARG_ERR      1
#define UNKNOWN_KEY_ERR 2
#define NO_COUNT_ERR    3
#define FILE_ERR        4

long getfsize(FILE *f);
int get_number_by_pos(FILE *f, long pos);
void put_number_by_pos(FILE *f, long pos, int num);
void create(FILE *f, long count);
void printnumbers(FILE *f);
void swappos(FILE *f, int pos1, int pos2);
void sort(FILE *f);

#endif // !FILESORT_H
