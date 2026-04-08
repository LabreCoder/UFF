#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    float fa = *(const float *) a;
    float fb = *(const float *) b;
    return (fa > fb) - (fa < fb);
}

int main(){
    FILE *entrada = fopen("numeros.txt", "r");
    if(entrada == NULL){
        printf("ERRO");
        exit(1);
    }
    float *vet = NULL, num;
    int n = 0;
    while(fscanf(entrada, "%f", &num) == 1){
        n++;
        vet = (float *) realloc(vet, n * sizeof(float));
        vet[n-1] = num;
    }
    fclose(entrada);
    qsort(vet, n, sizeof(float), cmp);
    FILE *saida = fopen("numeros.bin", "wb");
    if(saida == NULL){
        printf("ERRO");
        exit(1);
    }
    fwrite(vet, sizeof(float), n, saida);
    fclose(saida);
    free(vet);
    return 0;
}
