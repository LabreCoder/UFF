#include <stdio.h>
#include <stdlib.h>

int define_vetor(int n);
int impressao_vetor(int n, int *vetor);

int main() {
    int n = 10;
    if (define_vetor(n) == -1) {
        printf("Erro ao alocar memória.\n");
    }

    return 0;
}

int define_vetor(int n){
    // Aloca memória para o vetor
    int *vetor = (int*)malloc(n * sizeof(int));
    if (vetor == NULL)return -1;
    
    for (int i = 0; i < n; i++) {
        vetor[i] = 5 * (i + 1);
    }
    int result = impressao_vetor(n, vetor);

    free(vetor);

    return result;
}

int impressao_vetor(int n, int *vetor){
    for (int i = 0; i < n; i++) {
        printf("O vetor[%d]: %d\n", i, vetor[i]);
    }
    return 0;
}
