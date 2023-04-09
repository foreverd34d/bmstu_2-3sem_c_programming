#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

struct node
{
    void *data;
    node_t *next;
};

node_t *node_create(void *data)
{
    node_t *new = malloc(sizeof(node_t));
    if (new)
    {
        new->data = data;
        new->next = NULL;
    }
    return new;
}

static void node_free(node_t *node, void (*data_free)(void *))
{
    if (data_free)
    {
        data_free(node->data);
    }
    free(node);
}

void list_free(node_t *head, void (*data_free)(void *))
{
    node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        node_free(head, data_free);
    }
}

node_t *node_get_next(const node_t *node)
{
    return node ? node->next : NULL;
}

void *node_get_data(const node_t *node)
{
    return node ? node->data : NULL;
}

size_t list_len(const node_t *head)
{
    size_t len = 0;
    for (; head; head = head->next, len++);
    return len;
}

void *list_pop_node(node_t **head, node_t *node)
{
    void *data = NULL;
    if (head && *head && node)
    {
        if (*head == node)
        {
            data = pop_front(head);
        }
        else
        {
            node_t *prev = *head;
            for (node_t *cur = *head; !data && cur; prev = cur, cur = cur->next)
            {
                if (cur == node)
                {
                    data = cur->data;
                    prev->next = cur->next;
                    free(cur);
                    cur = prev;
                }
            }
        }
    }
    return data;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    for (; head && comparator(head->data, data); head = head->next);
    return head;
}

void *pop_front(node_t **head)
{
    void *data = NULL;
    if (head && *head)
    {
        node_t *head_old = *head;
        data = head_old->data;
        *head = head_old->next;
        free(head_old);
    }
    return data;
}

void append(node_t **head_a, node_t **head_b)
{
    node_t *head_new = *head_a;
    if (!head_new)
    {
        head_new = *head_b;
    }
    else
    {
        node_t *last_node = *head_a;
        for (; last_node->next; last_node = last_node->next);
        last_node->next = *head_b;
    }

    *head_b = NULL;
    *head_a = head_new;
}
