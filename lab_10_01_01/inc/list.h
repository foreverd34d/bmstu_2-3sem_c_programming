#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct node node_t;

node_t *node_create(void *data);
void list_free(node_t *head, void (*data_free)(void *));

node_t *node_get_next(const node_t *node);
void *node_get_data(const node_t *node);

size_t list_len(const node_t *head);

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));
void *pop_front(node_t **head);

void append(node_t **head_a, node_t **head_b);

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

#endif // !LIST_H
