#include "towers.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define OK 0
#define ERR_MEM 1

int towers_play(tower_t *fst, tower_t *sec, tower_t *trd);
bool tower_fill(tower_t *t, int from, int to);

int main(void)
{
    int err = OK;

    tower_t *fst = init();
    tower_t *sec = init();
    tower_t *trd = init();

    if (!fst || !sec || !trd || !tower_fill(fst, 1, 4))
    {
        err = ERR_MEM;
    }
    else
    {
        err = towers_play(fst, sec, trd);
    }

    clear(fst);
    clear(sec);
    clear(trd);

    return err;
}

int towers_play(tower_t *fst, tower_t *sec, tower_t *trd)
{
    int err = OK;

    printf("1 tower:\n");
    print(fst);
    printf("2 tower:\n");
    print(sec);
    printf("3 tower:\n");
    print(trd);

    return err;
}

bool tower_fill(tower_t *t, int from, int to)
{
    bool suc = true;
    for (int i = to; suc && i >= from; i--)
    {
        if (!push(t, i))
        {
            suc = false;
        }
    }
    return suc;
}
