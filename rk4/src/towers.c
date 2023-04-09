#include "towers.h"
#include <stdlib.h>
#include <stdio.h>

struct node
{
    int data;
    node_t *next;
};

struct tower
{
    node_t *head;
};

static node_t *new_node(int data)
{
    node_t *new = malloc(sizeof(node_t));
    if (new)
    {
        new->data = data;
        new->next = NULL;
    }
    return new;
}

tower_t *init(void)
{
    tower_t *new = malloc(sizeof(tower_t));
    if (new)
    {
        new->head = NULL;
    }
    return new;
}

bool push(tower_t *t, int size)
{
    bool suc = false;
    if (t && size >= 1 && size <= 9)
    {
        node_t *new_head = new_node(size);
        if (new_head)
        {
            new_head->next = t->head;
            t->head = new_head;
            suc = true;
        }
    }
    return suc;
}

int pop(tower_t *t)
{
    int res = 0;
    if (t && t->head)
    {
        node_t *old_head = t->head;
        res = old_head->data;
        t->head = old_head->next;
        free(old_head);
    }
    return res;
}

void clear(tower_t *t)
{
    if (t)
    {
        // node_t *next = head;
        // for (node_t *head = t->head; head; head = next)
        // {
        //     next = head->next;
        //     free(head);
        // }

        while (pop(t) != 0);

        free(t);
    }
}

static void print_ring(int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("*");
    }
    printf("\n");
}

void print(tower_t *t)
{
    if (t)
    {
        for (node_t *head = t->head; head; head = head->next)
        {
            print_ring(head->data);
        }
    }
}
