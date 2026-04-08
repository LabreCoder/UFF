#include <stdio.h>
#include <stdlib.h>

int *repeticao(int *vet, int tam, int *n);

int main() {
    int tam, i, n;
    int vet[] = {1, 5, 8, 4, 4, 5, 0, 8, 8};
    
    tam = 9; // Definindo o tamanho do vetor como 9
    
    // Chamando a função repeticao para obter os valores repetidos
    int *resposta = repeticao(vet, tam, &n);
    
    // Imprimindo os valores que se repetem
    printf("Valores repetidos: ");
    for (i = 0; i < n; i++) {
        printf("%d ", resposta[i]);
    }
    
    // Liberando a memória alocada
    free(resposta);
    
    return 0;
}

int *repeticao(int *vet, int tam, int *n) {
    int i, j, cont;
    int *resposta = (int*) malloc(tam * sizeof(int)); // Alocando memória para a resposta
    int *verificado = (int*) calloc(tam, sizeof(int)); // Para verificar quais elementos já foram verificados
    
    if (resposta == NULL || verificado == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    
    *n = 0;  // Inicializando o contador de elementos repetidos

    // Percorrendo o vetor e identificando elementos repetidos
    for (i = 0; i < tam; i++) {
        if (verificado[i] == 0) {  // Se o elemento ainda não foi verificado
            cont = 1;
            for (j = i + 1; j < tam; j++) {
                if (vet[i] == vet[j]) {
                    cont++;
                    verificado[j] = 1;  // Marca o elemento como verificado
                }
            }
            if (cont > 1) {
                resposta[*n] = vet[i];  // Se houver repetição, adiciona ao vetor de resposta
                (*n)++;
            }
        }
    }

    // Liberando o vetor de verificação
    free(verificado);
    
    return resposta;  // Retorna o vetor com os valores repetidos
}
