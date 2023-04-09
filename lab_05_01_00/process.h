#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>

#define RET_SUCCESS 0
#define NO_DATA_ERR -1
#define NO_POS_ERR -2
#define NO_NEG_ERR -3
#define NO_MAX_ERR -4

int process(FILE *f, int *max);

#endif // !PROCESS_H
