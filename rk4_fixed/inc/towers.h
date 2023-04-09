#ifndef TOWERS_H
#define TOWERS_H

#include <stdbool.h>
#include <stdio.h>

typedef struct node node_t;
typedef struct tower tower_t;

tower_t *init(void);
bool push(tower_t *t, int size);
int pop(tower_t *t);
void clear(tower_t *t);
void print(tower_t *t);

int read_towers_file(FILE *f, tower_t **towers, int max_len);
void print_towers(tower_t **towers, int len);
void clear_towers(tower_t **towers, int len);

tower_t *towers_merge(tower_t **towers, int len);

#endif
