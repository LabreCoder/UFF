#include <stdio.h>
#include <stdlib.h>


int *aprovados(int n, int *mat, float *notas, int *tam);
int main()
{
    int *m, n, i, tam = 0,*a;
    float *notas;
    
    printf("Digite a quantidade de alunos: ");
    scanf("%d", &n);
    
    /*Criando vetores*/
    
    m = (int*) malloc(n*sizeof(int));
    if (m==NULL){printf("\nMemoria insuficiente");exit(1);}
    
    notas = (float*) malloc(n*sizeof(float));
    if (notas==NULL){printf("\nMemoria insuficiente");exit(1);}
    
    /*Preenchendo vetores*/
    
    for (i=0;i<n;i++){
        printf("\nDigite a matricula: ");
        scanf("%d", &m[i]);
        printf("\nDigite a nota desse aluno(a): ");
        scanf("%f", &notas[i]);
        
    }
    
    a = aprovados(n, m,notas,&tam);
    
    printf("\n%d alunos foram aprovados.\n Seus numeros de matricula sao: ", tam);
    for (i=0;i<tam;i++)
        printf("%d ", a[i]);
    
    free(m);
    free(notas);
    free(a);
    
    return 0;
}

int *aprovados(int n, int *mat, float *notas, int *tam)
{
    int i,c = 0,j=0;
    int *aprovados;
    
    for (i=0;i<n;i++){
        if (notas[i]>= 5.0){c++;}
    }
    
    
    aprovados = (int*) malloc(c*sizeof(int));
    if (aprovados==NULL){printf("Memoria insuficiente");exit(1);}
    
    for (i=0;i<n;i++){
        if (notas[i]>= 5.0){aprovados[j] = mat[i];j++;}
    }
    
    *tam = c;
    
    return aprovados;

}