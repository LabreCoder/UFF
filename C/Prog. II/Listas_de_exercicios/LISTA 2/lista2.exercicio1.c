#include <stdio.h>

int e_primo(int num) {
    int i;
    int div = 0;
    for (i = 1; i <= num; i++) { // corrigido aqui
        if ((num % i) == 0)
            div++;
    }
    printf("O total de divisores é: %d\n",div);

    if (div > 2) {
        return 0; // Não é primo
    } else {
        return 1; // É primo
    }
}

int main(void) {
    int num;
    printf("Digite um número para ver se ele é primo: ");
    scanf("%d", &num);

    if (e_primo(num) == 0) {
        printf("NUMERO NÃO PRIMO\n");
    } else {
        printf("NUMERO PRIMO\n");
    }

    return 0;
}