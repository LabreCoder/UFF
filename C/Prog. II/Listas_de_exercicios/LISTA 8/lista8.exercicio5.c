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

int **soma(int l1,int c1, int l2, int c2, int **m1, int **m2)
{
    int **m = NULL;
    
    if (l1!=l2 || c1!=c2){
        return m;
    }
    else{
        
        m = criamatriz(l1,c1);
        
        int i, j;
    
        printf("\nComeçando soma das matrizes!\n");
        for(i=0;i<l1;i++){
            for(j=0;j<c1;j++){
                m[i][j] = m1[i][j] + m2[i][j];
            }
        }
        
        return m;
        
    }
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

void diagonal(int l, int c, int **m, int*sd)
{

    if (l!= c){
        printf("Nao foi possivel fazer a soma das diagonais");
    }
    else{
        
        int i;
    
        for(i=0;i<l;i++){
            *sd+= m[i][i];
        }
        
    }
}

int **multiplica(int l1,int l2, int c1,int c2, int **m1, int **m2)
{
    int **m = NULL;
    
    if (l2 != c1){
        printf("Nao foi possivel fazer a multiplicacao");
    }
    else{
        
        m = criamatriz(l1,c2);
        
        int i,j,k;
        
        printf("\nComeçando multiplicacao das matrizes!\n");

        for(i=0;i<l1;i++){
            for(j=0;j<c2;j++){
                m[i][j] = 0;
                for (int k = 0; k < c1; k++) {
                    m[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }
        
        return m;
    }
    
}

void liberaMatriz(int linhas, int **matriz) {
    if (matriz == NULL) return; 
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]); 
    }
    free(matriz); 
}

int main()
{
    int l1,c1;
    int l2,c2;
    int**m1 = NULL, **m2 = NULL, **m3 = NULL;
    
    printf("Digite o número de linhas e colunas da primeira matriz:");
    scanf("%d%d", &l1,&c1);
    
    printf("Digite o número de linhas e colunas da segunda matriz:");
    scanf("%d%d", &l2,&c2);
    
    m1 = criamatriz(l1,c1);
    m2 = criamatriz(l2,c2);
    
    lematriz(l1,c1,m1);
    lematriz(l2,c2,m2);
    
    int **s = soma(l1,c1,l2,c2,m1,m2);
    if (s== NULL){
        printf("\nNão foi possível fazer a soma de matrizes\n");
    } else{
        imprime(l1,c1,s);
    }
    
    int sd1 = 0,sd2 = 0;
    
    printf("\nSoma da diagonal da primeira matriz: ");
    diagonal(l1,c1,m1,&sd1);
    printf("\nSoma = %d", sd1);
    
    printf("\nSoma da diagonal da primeira matriz");
    diagonal(l2,c2,m2,&sd2);
    printf("\nSoma = %d\n", sd2);   

    int **m = multiplica(l1,l2,c1,c2,m1,m2);
    if (m== NULL){
        printf("\nNão foi possível fazer a multiplicacao de matrizes\n");
    } else{
        imprime(l1,c2,m);
    }
    
    liberaMatriz(l1, m1);
    liberaMatriz(l2, m2);

    
    return 0;
}