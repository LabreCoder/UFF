#include <stdio.h>

int main(void) {
    int X;
    int Z;
    printf("Digite um número para X: ");
    scanf("%d",&X);
    printf("\nAgora digite um número maior que X para Z: ");
    scanf("%d",&Z);
    
    do {
        if (Z<=X){
            printf("Digite um número maior que X para Z: \n");
            scanf("%d",&Z);
        }
    }
    while (Z<=X);
    
    printf("%d e %d (",X,Z);
    
    int sum;
    sum = X;
    int cont = 1;
    while (sum<=Z){
        printf("%d",X);
        X++;
        cont++;
        sum = sum + X;
        if (sum<=Z){
            printf(" + ");
        }
        else{
            continue;
        }
    }
    
    printf(" + %d = %d) Quantidade total de números até passar o Z: %d",X,sum,cont);
    return 0;
}
