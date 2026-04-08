#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("Digite um numero aleatorio:");
    scanf("%d", &a);

    printf("\nNumero invertido:");
    while(a>0){
        int r = a%10;
        printf("%d", r);
        a = a/10;
    }
    return 0;
}