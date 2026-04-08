#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    /*Iniciando numero secreto*/
    srand(time(NULL));
    int a = rand() % 101;

    /*Tentativas*/
    int ten = 0;
    int n;

    /*Loop enquanto ele não acertar*/
    do{
        printf("Tente advinhar o numero que eu pensei: ");
        scanf("%d", &n);

        if (n>a){
            printf("\nO numero que eu pensei e menor, tente novamente\n");
            ten++;
        }else if (n<a){
            printf("\nO numero que eu pensei e maior, tente novamente\n");
            ten++;
        }else{
            ten++;
            printf("Voce acertou!\nParabens!\nSeu numero de tentativas:%d", ten);
        }
    }while(n!=a);
}