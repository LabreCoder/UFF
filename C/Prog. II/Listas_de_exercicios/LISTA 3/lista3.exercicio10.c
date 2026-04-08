#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Protótipo da função
float media(int n, float *v);

int main() {
    setlocale(LC_ALL,"Portuguese");
    int n, i;
    float vet[100];  // Tamanho máximo arbitrário, pesquisei e isso apenas não permite mais de 100 valores para esse vetor
    float resultado;

    printf("Quantos números deseja inserir para calcular a média? ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Número inválido de elementos.\n");
        return 1; // ele encerra o programa sem continuar
    }

    for (i = 0; i < n; i++) {
        printf("Digite o valor %d: ", i + 1);
        scanf("%f", &vet[i]);
    }

    resultado = media(n, vet);
    printf("A média dos valores é: %.2f\n", resultado);

    return 0;
}

// Implementação da função média
float media(int n, float *v) {
    float soma = 0;
    for (int i = 0; i < n; i++) {
        soma += v[i];
    }
    return (soma / n);
}
