#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define LOOP_EXIT -10

#define ERR_FILE 2
#define ERR_MEM 3

typedef struct
{
    int **field;
    int **shoots;
    int size;
} field_t;

int read_field_file(field_t *field, FILE *f);
int get_field_size(FILE *f);

int field_create(field_t *f, int n);
void field_free(field_t *f);

void play(field_t *f);
void select_cell(int *x, int *y);

int main(int argc, char **argv)
{
    int err = 0;

    if (argc != 2)
    {
        err = 1;
    }
    else
    {
        FILE *f = fopen(argv[1], "r");
        field_t field;
        if (!f)
        {
            err = ERR_FILE;
        }
        else 
        {
            if (read_field_file(&field, f))
            {
                err = ERR_MEM;
            }
            else
            {
                play(&field);
                field_free(&field);
            }

            fclose(f);
        }
    }

    return err;
}

int field_create(field_t *f, int n)
{
    int err = 0;

    field_t temp;

    temp.size = n;
    temp.field = calloc(n, sizeof(int *));
    temp.shoots = calloc(n, sizeof(int *));

    if (!temp.field || !temp.shoots)
    {
        free(temp.field);
        free(temp.shoots);
        err = 1;
    }
    else
    {
        for (int i = 0; !err && i < n; i++)
        {
            temp.field[i] = malloc(n * sizeof(int));
            temp.shoots[i] = malloc(n * sizeof(int));
            if (!temp.field[i] || !temp.shoots[i])
            {
                field_free(&temp);
                err = 1;
            }
        }
    }

    if (!err)
    {
        *f = temp;
    }

    return err;
}

void field_free(field_t *f)
{
    for (int i = 0; i < f->size; i++)
    {
        free(f->field[i]);
        free(f->shoots[i]);
    }
    free(f->field);
    free(f->shoots);
}

int read_field_file(field_t *field, FILE *f)
{
    int err = 0;
    int size = get_field_size(f);
    rewind(f);

    field_t temp;
    if (field_create(&temp, size))
    {
        err = 1;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                fscanf(f, "%d", &temp.field[i][j]);
            }
        }

        *field = temp;
    }
    return err;
}

int get_field_size(FILE *f)
{
    char *line = NULL;
    size_t size = 0;

    while (getline(&line, &size, f) != -1)
    {
        size++;
    }

    free(line);

    return size;
}

void play(field_t *f)
{
    int x, y;
    bool running = true;

    while (running)
    {
        select_cell(&x, &y);
        if (x == LOOP_EXIT)
        {
            running = false;
        }
        else if (x > -1 && x < f->size && y > -1 && y < f->size)
        {
            f->shoots[x][y] = 1;
            int got = f->field[x][y];
            if (got != 0)
            {
                // TODO: proveryat' potoplenie
                printf("2_%d", got);
            }
            else
            {
                puts("1");
            }

        }
        else
        {
            puts("0");
        }
    }
}

void select_cell(int *x, int *y)
{
    char *x_t = NULL;
    int y_t;

    char *buffer = NULL;
    size_t size = 0;

    if (getline(&buffer, &size, stdin) == -1)
    {
        *x = LOOP_EXIT;
    }
    else if (sscanf(buffer, "%s%d", x_t, &y_t) != 2)
    {
        *x = LOOP_EXIT;
    }
    else
    {
        *x = x_t[0] - 'a';
        *y = y_t;
    }
}
