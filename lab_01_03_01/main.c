#include <stdio.h>

int main(void)
{
    double va, ta, vb, tb;
    printf("Input Va, Ta, Vb, Tb: ");
    scanf("%lf%lf%lf%lf", &va, &ta, &vb, &tb);

    double vc = va + vb;
    double tc = (va * ta + vb * tb) / vc;

    printf("%lf %lf", vc, tc);

    return 0;
}

