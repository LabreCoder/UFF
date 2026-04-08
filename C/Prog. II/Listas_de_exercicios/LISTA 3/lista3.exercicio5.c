#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

float max_vet(int n, float *vet);

int main()
{
    setlocale(LC_ALL, "");
    int n;
    float vet[100]; // Vetor com tamanho máximo

    printf("Por favor, digite o tamanho do vetor (máx 100): ");
    scanf("%d", &n);

    if (n > 100 || n <= 0) {
        printf("Erro: o tamanho deve estar entre 1 e 100.\n");
        return 1;
    }

    float max = max_vet(n, vet);
    printf("O maior valor desse vetor é: %.2f\n", max);

    return 0;
}

float max_vet(int n, float *vet) {
    int i;

    // Leitura dos elementos do vetor
    for (i = 0; i < n; i++) {
        printf("Digite o valor para vetor %d: ", i + 1);
        scanf("%f", &vet[i]);
    }

    // Inicializa max com o primeiro valor do vetor
    float max = vet[0];

    for (i = 1; i < n; i++) {
        if (vet[i] > max) {
            max = vet[i];
        }
    }

    return max;
}
