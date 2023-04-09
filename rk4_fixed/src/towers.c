#include "towers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    if (t && t->head)
    {
        int ring_cur = pop(t) ;
        if (ring_cur > 0)
        {
            print(t);
            print_ring(ring_cur);
            push(t, ring_cur);
        }
    }
}

static bool str_to_tower(char *str, tower_t *t)
{
    bool suc = true;
    char *part = strtok(str, " ");
    while (suc && part)
    {
        long num = strtol(part, NULL, 10);
        if (!push(t, num))
        {
            suc = false;
        }
        part = strtok(NULL, " ");
    }
    return suc;
}

int read_towers_file(FILE *f, tower_t **towers, int max_len)
{
    int len = 0;

    if (f)
    {
        char *buffer = NULL;
        size_t bufsize = 0;
        bool err = false;

        while (!err && getline(&buffer, &bufsize, f) != -1 && len < max_len)
        {
            buffer[strcspn(buffer, "\n")] = '\0';

            tower_t *new = init();
            if (!new || !str_to_tower(buffer, new))
            {
                err = true;
            }

            if (!err)
            {
                towers[len++] = new;
            }
            else
            {
                clear(new);
            }
        }

        if (err)
        {
            for (int i = 0; i < len; i++)
            {
                clear(towers[i]);
            }
            len = 0;
        }

        free(buffer);
    }

    return len;
}

void clear_towers(tower_t **towers, int len)
{
    for (int i = 0; i < len; i++)
    {
        clear(towers[i]);
    }
}

void print_towers(tower_t **towers, int len)
{
    for (int i = 0; i < len; i++)
    {
        print(towers[i]);
        printf("\n");
    }
}

static int rings_max(tower_t **towers, int *rings, int len)
{
    int max = 0;
    int max_ind = 0;

    for (int i = 0; i < len; i++)
    {
        if (max == 0 || (rings[i] > max && rings[i] > 0))
        {
            max = rings[i];
            max_ind = i;
        }
    }

    rings[max_ind] = pop(towers[max_ind]);

    return max;
}

static tower_t *tower_reversed(tower_t *t)
{
    tower_t *rev = NULL;
    if (t)
    {
        rev = init();
        if (rev)
        {
            bool err = false;
            int cur;

            while (!err && (cur = pop(t)) > 0)
            {
                err = !push(rev, cur);
            }

            if (err)
            {
                clear(rev);
                rev = NULL;
            }
        }
    }
    return rev;
}

tower_t *towers_merge(tower_t **towers, int len)
{
    tower_t *new = NULL;
    tower_t *reversed = init();

    if (reversed && len > 0)
    {
        int *rings_maxes = malloc(len * sizeof(int));
        bool err = false;

        if (!rings_maxes)
        {
            err = true;
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                rings_maxes[i] = pop(towers[i]);
            }

            int max;
            while (!err && (max = rings_max(towers, rings_maxes, len)) > 0)
            {
                err = !push(reversed, max);
            }

            if (!err)
            {
                new = tower_reversed(reversed);
            }
        }

        if (err)
        {
            clear(new);
            new = NULL;
        }

        free(rings_maxes);
    }

    clear(reversed);

    return new;
}
