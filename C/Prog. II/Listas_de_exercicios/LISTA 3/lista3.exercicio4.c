#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL,"");
    int num, max, min;
    printf("Digite um número para ver se ele é primo: ");
    scanf("%d", &num);
    if (divs(num, &max, &min) == 0){
        printf("%d não é um número primo!\n", num);
    }
    else{
        printf("%d é um número primo!\n", num);
    }
    printf("O maior divisor de %d é: %d e o menor é: %d", num, max, min);

    return 0;
}

int divs(int n, int *max, int *min){

    int i;
    int div = 0;
    for (i = 1; i <= n; i++) {
        if ((n % i) == 0){
            div++;
            if(div == 1){
            *min = i;
            }
            else{
                *max = i;
            }
        }
    }

    printf("O total de divisores é: %d\n", div);
    if (div > 2) {
        return 0; // Não é primo
    } else {
        return 1; // É primo
    }
}
