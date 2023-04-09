#include <stdio.h>
#include "process.h"

int main(void)
{
    int err = RET_SUCCESS;
    int max;
    if (!(err = process(stdin, &max)))
    {
        printf("%d\n", max);
    }
    return err;
}
