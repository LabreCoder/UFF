#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float media (int *vetor, int n)
{
    int i;
    float soma = 0;
    
    for(i=0;i<n;i++){
        soma += vetor[i];
    }
    
    return soma/n;
}

float variancia(int*vetor, int n, float media)
{
    int i;
    float soma = 0;
    
    for (i=0;i<n;i++){
        soma += powf(vetor[i]-media,2);
    }
    
    return soma/n;
}

int main()
{   
    int lista [80]; 
    int i = 0;
    char nome[80];
    
    nome [0] = '\0';
    
    printf("Digite os nomes (digite fim para encerrar)\n");
    
    while (strcmp(nome, "fim") != 0 && i<80){
        
        printf("Digite aqui: ");
        scanf("%79s", nome);
        
        if (strcmp(nome, "fim") != 0){
            lista[i] = strlen(nome);
            i++;
        }
        else{
            break;
        }
        

    }
    
    float m = media(lista,i);
    float v = variancia(lista,i,m);
    
    printf("\nMedia = %.1f", m);
    printf("\nVariancia = %.1f",v);

    return 0;
}