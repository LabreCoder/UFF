#include <stdio.h>
#include <stdlib.h>

int main() {
    int tam;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    // Alocação dinâmica do vetor
    int *vet = (int *)malloc(tam * sizeof(int));
    if (vet == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Leitura dos valores entre 0 e 9
    printf("Digite %d valores entre 0 e 9:\n", tam);
    for (int i = 0; i < tam; i++) {
        scanf("%d", &vet[i]);
    }

    // Verifica e imprime os valores repetidos
    int repetidos[10] = {0}; // Vetor para contar ocorrência dos números de 0 a 9

    for (int i = 0; i < tam; i++) {
        repetidos[vet[i]]++;
    }

    printf("Numeros que se repetem:\n");
    for (int i = 0; i <= 9; i++) {
        if (repetidos[i] > 1) {
            printf("%d ", i);
        }
    }
    printf("\n");

    // Liberação da memória
    free(vet);
    return 0;
}
