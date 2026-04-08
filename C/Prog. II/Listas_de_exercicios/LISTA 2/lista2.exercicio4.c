#include <stdio.h>
#include <stdlib.h>

char sorteio(void) {
    return 'a' + (rand() % 26);
}

int main(void) {
    char letra_usuario;
    char letra_sorteada;

    letra_sorteada = sorteio();

    printf("Tente adivinhar a letra sorteada (entre 'a' e 'z'):\n");

    do {
        printf("Digite uma letra: ");
        scanf(" %c", &letra_usuario);  

        if (letra_usuario < letra_sorteada) {
            printf("A letra sorteada é MAIOR que '%c'.\n", letra_usuario);
        } else if (letra_usuario > letra_sorteada) {
            printf("A letra sorteada é MENOR que '%c'.\n", letra_usuario);
        } else {
            printf("Parabéns! Você acertou a letra: '%c'\n", letra_sorteada);
        }

    } while (letra_usuario != letra_sorteada);

    return 0;
}
