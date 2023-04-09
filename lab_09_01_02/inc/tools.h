#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>

int read_pos_double(double *to, const char *from);
bool starts_with(const char *str, const char *part);
bool is_empty(const char *str);

#endif // !TOOLS_H
