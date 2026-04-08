#include <stdio.h>
#include <stdlib.h>
#define max 10

void troca(int*x, int*y);
int main (void)
{
    int x[max], y[max];
    int i;

    printf("Digite os valores da lista X:");
    for (i=0;i<max;i++)
        scanf("%d", &x[i]);

    printf("\n-------->Elementos de x \n");
    for (i = 0;i<max;i++)
        printf("%d ", x[i]);

    troca(x,y);

    printf("\n--------> Elementos de y \n");
    for (i = 0;i<max;i++)
        printf("%d ", y[i]);
}

void troca(int *x, int *y)
{
    int i, j=max-1;
    for (i=0;i<max;i++,j--)
        y[j] = x[i];
}