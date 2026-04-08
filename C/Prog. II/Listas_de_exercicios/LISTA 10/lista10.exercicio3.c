#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float media(char *mat, char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "r");
    if(arq == NULL){
        printf("ERRO");
        exit(1);
    }
    char matricula[20];
    float p1, p2, p3;
    while(fscanf(arq, "%s %f %f %f", matricula, &p1, &p2, &p3) == 4) {
        if(strcmp(matricula, mat) == 0){
            fclose(arq);
            return (p1 + p2 + p3)/3;
        }
    }
    fclose(arq);
    return -1.0;
}

int main() {
    char matBuscada[20];
    scanf("%s", matBuscada);
    float mediaAluno = media(matBuscada, "notas.txt");
    printf("%.1f\n", mediaAluno);
    return 0;
}
