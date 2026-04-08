#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    int a, b, c;

    printf("Digite dois numeros:");
    scanf("%d %d", &a, &b);

    c = pow(a,b);
    printf("\n%d elevado a %d = %d", a, b, c);
    return 0;
}
