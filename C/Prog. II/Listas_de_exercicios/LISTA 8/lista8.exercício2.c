#include <stdio.h>
#include <stdlib.h>


int main()
{
    int l,c;
    int i,j;
    
    printf("Digite qual sera o tamanho das matrizes!");
    
    printf("\nLinhas = ");
    scanf("%d", &l);
    
    printf("\nColunas = ");
    scanf("%d", &c);
    
    int m1[l][c];
    int m2[l][c];
    int soma[l][c];
    
    printf("\nLendo primeira matriz\n");
    
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            printf("Digite o termo da linha %d, coluna %d: ", i, j);
            scanf("%d", &m1[i][j]);
        }
    }
    
    printf("\nLendo segunda matriz");
    
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            printf("Digite o termo da linha %d, coluna %d: ", i, j);
            scanf("%d", &m2[i][j]);
        }
    }
    
    
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            soma[i][j] = m1[i][j] + m2[i][j];
        }
    }
    
    printf("\nSoma realizada! Resultado final:\n") ;
    
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            printf("[%d] ", soma[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}