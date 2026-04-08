#include <stdio.h>

int fibonacci(int quantidade);

int main(void){
    int n;
    printf("Digite a quantidade de números da série da Fibonacci que você quer ver:");
    scanf("%d",&n);
    printf("\nO último valor dessa série é: %d ",fibonacci(n));
    
    return 0;
}

int fibonacci(int quantidade){
    int i;
    int soma = 1;
    int temp1 = 0;
    int temp2 = 0;
    printf("1 ");
    for (i=2;i<=quantidade;i++){
        temp2 = temp1;
        temp1 = soma;
        soma = (temp1 + temp2);
        printf("%d ", soma);
    }
    return soma;
}