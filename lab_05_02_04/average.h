#ifndef AVERAGE_H
#define AVERAGE_H

#include <stdio.h>

#define RET_SUCCESS 0
#define ARG_ERR -1
#define FILE_ERR -2
#define READ_ERR -3
#define NO_RESULT_ERR -4

int minmaxind(FILE *f, int *minind, int *maxind);
double average(FILE *f, int start, int end);
int between_min_max(FILE *f, double *result);

#endif // !AVERAGE_H
