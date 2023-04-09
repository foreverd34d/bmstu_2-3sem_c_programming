#include "list.h"
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

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    node_t *result = NULL;
    if (head && data && comparator)
    {
        for (; head && comparator(head->data, data); head = head->next);
        result = head;
    }
    return result;
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

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *sorted = NULL;
    if (!head || !head->next)
    {
        sorted = head;
    }
    else
    {
        node_t *head_middle = NULL;
        front_back_split(head, &head_middle);
        node_t *left = sort(head, comparator);
        node_t *right = sort(head_middle, comparator);
        sorted = sorted_merge(&left, &right, comparator);
    }
    return sorted;
}

void front_back_split(node_t *head, node_t **back)
{
    if (head && back)
    {
        node_t *fast, *slow, *slow_prev;
        fast = slow = slow_prev = head;

        while (fast && fast->next)
        {
            slow_prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        if (fast)
        {
            *back = slow->next;
            slow->next = NULL;
        }
        else
        {
            *back = slow;
            slow_prev->next = NULL;
        }
    }
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t dummy;
    node_t *temp = &dummy;
    node_t *a_current = *head_a;
    node_t *b_current = *head_b;

    for (; a_current && b_current; temp = temp->next)
    {
        if (comparator(a_current->data, b_current->data) < 0)
        {
            temp->next = a_current;
            a_current = a_current->next;
        }
        else
        {
            temp->next = b_current;
            b_current = b_current->next;
        }
    }

    temp->next = !a_current ? b_current : a_current;

    *head_a = *head_b = NULL;

    return dummy.next;
}
