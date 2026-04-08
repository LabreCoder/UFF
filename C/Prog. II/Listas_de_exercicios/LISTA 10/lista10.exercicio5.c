#include <stdio.h>
#include <stdlib.h>

int main(){
    char nome[100];
    scanf("%s", nome);
    FILE *arq = fopen(nome, "r");
    if(arq == NULL){
        printf("ERRO");
        exit(1);
    }
    double num, soma = 0;
    int n = 0;
    double *vet = NULL;
    while(fscanf(arq, "%lf", &num) == 1){
        n++;
        vet = (double *) realloc(vet, n * sizeof(double));
        vet[n-1] = num;
        soma += num;
    }
    fclose(arq);
    if(n > 0)
        printf("%.2lf\n", soma/n);
    else
        printf("0.00\n");
    free(vet);
    return 0;
}
