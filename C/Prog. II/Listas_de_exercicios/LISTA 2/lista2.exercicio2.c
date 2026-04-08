#include <stdio.h>

int soma(int valores);

int main(void){
    int n;
    printf("Digite a quantidade de números ímpares a serem somados:");
    scanf("%d",&n);
    printf("A soma dos %d primeiros números ímpares é: %d. \n",n,soma(n));
    
    return 0;
}

int soma(int valores){
    int i;
    int total = 0;
    for (i=0; i<valores; i++){
        total = (total + (2*i + 1));
    }
    
    return total;
}