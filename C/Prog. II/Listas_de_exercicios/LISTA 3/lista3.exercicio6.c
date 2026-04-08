#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int maiores(int n, int *vet, int x);

int main()
{
    setlocale(LC_ALL,"");

    int n;
    int vet[100]; // Vetor fixo com capacidade máxima

    printf("Por favor, digite o tamanho do vetor (máx 100): ");
    scanf("%d", &n);

    if (n > 100 || n <= 0) {
        printf("Erro: o tamanho deve estar entre 1 e 100.\n");
        return 1;
    }

    // Preenchimento do vetor
    for (int i = 0; i < n; i++) {
        printf("Digite o valor para vetor %d: ", i+1);
        scanf("%d", &vet[i]);
    }

    int x;
    printf("Digite um número para verificar quais números são maiores que ele: ");
    scanf("%d", &x);

    maiores(n, vet, x);

    return 0;
}

int maiores(int n, int *vet, int x) {
    int contador = 0;

    for (int i = 0; i < n; i++) {
        if (vet[i] > x) {
            contador++;
        }
    }

    printf("\nA quantidade de números maiores que %d no vetor é: %d\n", x, contador);
    return contador;
}
