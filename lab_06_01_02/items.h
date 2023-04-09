#ifndef ITEMS_H
#define ITEMS_H

//
// Includes
//

#include <stdio.h>
#include <stdbool.h>


//
// Error codes
//

#define RET_SUCCESS 0
#define ERR_ARG     1
#define ERR_FILE    2
#define ERR_STRUCT  3


//
// Struct definition
//

#define STRUCTMAX   15
#define NAMEMAX     25

typedef struct item_t
{
    char name[NAMEMAX + 1];
    double weight;
    double volume;
} item_t;


//
// Functions
//

// itemio.c
int read_items(item_t *dest, FILE *from);
void print_items(const item_t *items, int len);
// void print_items_prefix(const item_t *items, int len, const char *prefix);

// itemsort.c
void sort_by_density(item_t *items, int len);
double get_density(item_t item);
void swap_items(item_t *a, item_t *b);
int filter_by_prefix(item_t *items, int len, const char *prefix);

// tools.c
int read_pos_double(double *to, const char *from);
bool starts_with(const char *str, const char *part);
bool is_empty(const char *str);

#endif // !ITEMS_H
