#include <stdio.h>

unsigned int isbyte(int n);
unsigned int locbyte(unsigned int byte, int loc);
unsigned int getbyte(unsigned int num, int loc);
void printbin(unsigned int num, int n);

int main(void)
{
    unsigned int b1, b2, b3, b4, err = 0;
    unsigned int packed = 0;

    if (scanf("%u%u%u%u", &b1, &b2, &b3, &b4) != 4)
        err = 1;
    else if (!(isbyte(b1) && isbyte(b2) && isbyte(b3) && isbyte(b4)))
        err = 2;
    else
    {
        packed = locbyte(b1, 1) + locbyte(b2, 2) + locbyte(b3, 3) + locbyte(b4, 4);
    }

    if (!err)
    {
        printf("Result: ");
        printbin(packed, 32);
        printf("\n");
        for (int i = 1; i <= 4; i++)
            printf("%u ", getbyte(packed, i));
        printf("\n");
    }
    else
    {
        switch (err)
        {
            case 1:
                printf("Error: incorrect input\n");
                break;
            case 2:
                printf("Error: byte overflow\n");
                break;
            default:
                printf("Error: unknown\n");
        }
    }
    
    return err;
}

unsigned int isbyte(int n)
{
    return n >= 0 && n <= 255;
}

unsigned int locbyte(unsigned int byte, int loc)
{
    unsigned int shift = 4 - loc;
    return byte << (8 * shift);
}

void printbin(unsigned int num, int n)
{
    if (n != 0)
    {
        printbin(num >> 1, n - 1);
        printf("%u", num % 2);
    }
}

unsigned int getbyte(unsigned int num, int loc)
{
    unsigned int shift = 8 * (4 - loc);
    return (num >> shift) & 255;
}
