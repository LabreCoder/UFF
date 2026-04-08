#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float busca(char *arquivo, char *matricula) {
    FILE *arq = fopen(arquivo, "r");
    if(arq == NULL){
        printf("ERRO");
        exit(1);
    }
    char mat[20];
    float cr;
    while(fscanf(arq, "%s %f", mat, &cr) == 2) {
        if(strcmp(mat, matricula) == 0) {
            fclose(arq);
            return cr;
        }
    }
    fclose(arq);
    return -1.0;
}

int main() {
    char matBusca[20];
    scanf("%s", matBusca);
    float resultado = busca("matriculas.txt", matBusca);
    printf("%.1f\n", resultado);
    return 0;
}
