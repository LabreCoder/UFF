#include <stdio.h>
#include <stdlib.h>

float *acima_da_media(int n, float *vet, int *tam);
void repeticao(int *vet, int tam);

int main() {
    int n, i, tam;
    float *v, *v_acima;
    printf("Digite quantos numeros voce deseja que o vetor tenha: ");
    scanf("%d", &n);

    v = (float*) malloc(n * sizeof(float));
    if (v == NULL) {
        printf("Falta memoria\n");
        exit(1);
    }

    printf("\nAgora digite os elementos do vetor: ");
    for (i = 0; i < n; i++) {
        scanf("%f", &v[i]);
    }

    v_acima = acima_da_media(n, v, &tam);

    if (v_acima != NULL && tam > 0) {
        printf("\nElementos acima da media:\n");
        for (i = 0; i < tam; i++) {
            printf("%.0f ", v_acima[i]);
        }
    } else {
        printf("\nNenhum elemento acima da media");
    }

    printf("\n\nAgora, repeticoes dos elementos:\n");
    // Chamando a função repeticao para contar e imprimir as repetições
    repeticao((int*) v, n);

    free(v);
    free(v_acima);

    return 0;
}

float *acima_da_media(int n, float *vet, int *tam) {
    int i, j = 0, c = 0, acima = 0;
    float *vetresposta, soma = 0, media;

    // 1) Verificando média
    for (i = 0; i < n; i++) {
        soma += vet[i];
        c++;
    }
    media = soma / c;

    // 2) Contando quantos elementos são acima da média
    for (i = 0; i < n; i++) {
        if (vet[i] > media) {
            acima++;
        }
    }

    // 3) Criando vetor de resposta
    vetresposta = (float*) malloc(acima * sizeof(float));
    if (vetresposta == NULL) return NULL;

    // 4) Preenchendo vetor de resposta
    for (i = 0; i < n; i++) {
        if (vet[i] > media) {
            vetresposta[j] = vet[i];
            j++;
        }
    }

    *tam = acima;
    return vetresposta;
}

void repeticao(int *vet, int tam) {
    int i, j, cont;
    int *verificado = (int*) calloc(tam, sizeof(int)); // Marca os elementos já verificados

    if (verificado == NULL) {
        printf("Falta memoria\n");
        return;
    }

    // Contando e imprimindo as repetições
    for (i = 0; i < tam; i++) {
        if (verificado[i] == 0) { // Só verifica elementos não verificados
            cont = 1;
            for (j = i + 1; j < tam; j++) {
                if (vet[i] == vet[j]) {
                    cont++;
                    verificado[j] = 1; // Marca como verificado
                }
            }
            printf("Elemento %d aparece %d vez(es)\n", vet[i], cont);
        }
    }

    free(verificado);
}
