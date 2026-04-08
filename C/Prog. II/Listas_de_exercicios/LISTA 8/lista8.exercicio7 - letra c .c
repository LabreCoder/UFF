#include <stdio.h>
#include <stdlib.h>

int calculadistancia(int t[5][5],int c1,int c2){
    return t[c1-1][c2-1];
}

int main()
{
    int tabela[5][5] = {
        {00,15,30,05,12},
        {15,00,10,17,28},
        {30,10,00,03,11},
        {05,17,03,00,80},
        {12,28,11,80,00},
        
    };
    
    int n;
    printf("Digite quantas cidades voce percorreu: ");
    scanf("%d", &n);
    
    int *v = (int*) malloc (n*sizeof(int));
    if (v==NULL){printf("Memoria insuficiente");exit(1);}
    
    int i;
    printf("\nDigite as cidades");
    for(i=0;i<n;i++){
        printf("\n%da cidade = ",i+1);
        scanf("%d", &v[i]);
    }
    
    int soma = 0;
    for(i=0;i<n-1;i++){
        
        int c1 = v[i];
        int c2 = v[i+1];
        
        soma += calculadistancia(tabela,c1,c2);
    }
    
    printf("Soma total = %d",soma);
    
    free(v);
    
    
    return 0;
}