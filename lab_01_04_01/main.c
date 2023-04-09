#include <stdio.h>

int main(void)
{
    int apartment;
    printf("Input apartment number: ");
    scanf("%d", &apartment);
    apartment--;
 
    int entrance = apartment / 36 + 1;
    int floor = (apartment % 36) / 4 + 1;

    printf("Entrance = %d\n", entrance);
    printf("Floor = %d\n", floor);
    return 0;
}

