#ifndef TOWERS_H
#define TOWERS_H

#include <stdbool.h>

typedef struct node node_t;
typedef struct tower tower_t;

tower_t *init(void);
bool push(tower_t *t, int size);
int pop(tower_t *t);
void clear(tower_t *t);
void print(tower_t *t);

#endif
