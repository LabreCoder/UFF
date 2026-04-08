#include <stdio.h>
#include <stdlib.h>

int **criamatriz (int linhas, int colunas)
{
    int i,j;
    
    int **m = (int**) malloc (linhas*sizeof(int*));
    if(m==NULL){printf("Memoria insuficiente");exit(1);}
    
    for(i=0;i<linhas;i++){
        m[i] = (int*) malloc (colunas*sizeof(int));
        if (m[i] == NULL){
            printf("Memoria insuficiente");
            
            for (int k = 0;k<i;k++){
                free(m[k]);
            }
            free(m);
            exit(1);
        }
    }
    
    return m;
}

void lematriz(int linhas ,int colunas,int **m)
{
    int i, j;
    
    printf("\nComeçando leitura da matriz!\n");
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            printf("Digite o elemento da linha %d, coluna %d: ", i, j);
            scanf("%d", &m[i][j]);
        }
    }
}

int **transposta(int linhas, int colunas, int **m)
{
    int i,j;
    
    int **transposta = criamatriz(linhas,colunas);
    
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            transposta[j][i] = m[i][j];
        }
    }
    
    return transposta;
}

void verifica(int **transposta, int **matriz, int linhas, int colunas)
{
    int i, j, k = 0;
    
    for (i=0;i<linhas;i++) {
        for(j=0;j<colunas;j++){
            if (transposta[i][j] != matriz[i][j]){
                k = 1;
            }
        }
    }
    
    if (k!=1){printf("\nA matriz e simetrica");}
    else{printf("\nA matriz nao e simetrica!");}
}

void liberaMatriz(int linhas, int **matriz) {
    if (matriz == NULL) return; 
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]); 
    }
    free(matriz); 
}

void imprime(int linhas,int colunas, int **m){
    int i,j;
    
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            printf("[%d]", m[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int l,c;
    int **m = NULL;
    int **mtransposta = NULL;
    
    
    printf("Digite qual sera o tamanho das matrizes!");
    
    printf("\nLinhas = ");
    scanf("%d", &l);
    
    printf("\nColunas = ");
    scanf("%d", &c);
    
    m = criamatriz(l,c);
    lematriz(l,c, m);
    mtransposta = transposta(l,c,m);
    
    printf("\n Matriz original:\n");
    imprime(l,c,m);
    
    printf("\n Matriz transposta:\n");
    imprime(l,c,mtransposta);
    
    verifica(mtransposta,m,l,c);
    
    
    liberaMatriz(l,m);
    liberaMatriz(l,mtransposta);
    
    
}