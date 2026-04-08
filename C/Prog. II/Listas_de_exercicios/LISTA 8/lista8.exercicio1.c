#include <stdio.h>
#include <stdlib.h>

int somaLinhasIguais(int linhas, int colunas, int matriz[linhas][colunas]) {
    int soma_ref = 0, soma, i, j;
    for(j = 0; j < colunas; j++) {
        soma_ref += matriz[0][j];
    }
    for(i = 1; i < linhas; i++) {
        soma = 0;
        for(j = 0; j < colunas; j++) {
            soma += matriz[i][j];
        }
        if(soma != soma_ref)
            return 0;
    }
    return 1;
}

int main() {
    int linhas, colunas;
    printf("Digite o numero de linhas: ");
    scanf("%d", &linhas);
    printf("Digite o numero de colunas: ");
    scanf("%d", &colunas);
    int matriz[linhas][colunas];
    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
    if(somaLinhasIguais(linhas, colunas, matriz))
        printf("A soma de cada linha e igual.\n");
    else
        printf("A soma de cada linha nao e igual.\n");
    return 0;
}
