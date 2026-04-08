#include <stdio.h>
#include<stdlib.h>

int soma (int *vetor,int n, int i)
{

    if (i>n){return 0;}
    
    if(vetor[i]%2 != 0){
        return vetor[i] + soma(vetor,n,i+1);
    }else{
        return soma(vetor,n,i+1);
    }
    
    
}

int main()
{
    int n,i;
    int *vet;
    
    printf("Digite a qtd de elementos do vetor:");
    scanf("%d",&n);
    
    vet =(int*) malloc (n*sizeof(int));
    if(vet==NULL){printf("Memoria insuficiente");exit(1);}
    
    printf("\nDigite os elementos do vetor:\n");
    for(i=0;i<n;i++){
        printf("\nElemento %d: ",i+1);
        scanf("%d",&vet[i]);
    }
    
    int s = soma(vet,n,0);
    printf("Soma dos impares = %d",s);
    
    
    free(vet);

    return 0;
}