#ifndef NUMKEY_H
#define NUMKEY_H

#include <stddef.h>
#include "errcodes.h"

#define ERR_KEY_ARGS        20
#define ERR_KEY_NO_RESULT   21

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
size_t get_neg_ind(const int *beg, const int *end);

#endif // !NUMKEY_H
