#include <stdio.h>

// Protótipo da função
int total_de_notas(int valor);

int main() {
    int valor, total;

    printf("Digite o valor em reais (inteiro): R$ ");
    scanf("%d", &valor);

    total = total_de_notas(valor);

    printf("Total de notas utilizadas: %d\n", total);

    return 0;
}

// Função que calcula o total mínimo de notas
int total_de_notas(int valor) {
    int notas[] = {100, 50, 20, 10, 5, 2, 1};
    int i, total = 0;

    for (i = 0; i < 7; i++) {
        total += valor / notas[i];  // Conta quantas notas desse tipo
        valor = valor % notas[i];   // Atualiza o restante do valor
    }

    return total;
}
