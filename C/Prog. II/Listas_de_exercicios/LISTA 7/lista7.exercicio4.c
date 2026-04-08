#include <stdio.h>

#define TAMANHO 26

// Função para preencher o vetor com as letras minúsculas
void inicializa_vetor(char *vetor) {
    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = 'a' + i;
    }
}

// Função para imprimir o vetor
void imprime_vetor(char *vetor) {
    for (int i = 0; i < TAMANHO; i++) {
        printf("vetor[%d]: %c\n", i, vetor[i]);
    }
    printf("Fim\n");
}

int main() {
    char vetor[TAMANHO];  // vetor de 26 letras
    inicializa_vetor(vetor);
    imprime_vetor(vetor);
    return 0;
}
