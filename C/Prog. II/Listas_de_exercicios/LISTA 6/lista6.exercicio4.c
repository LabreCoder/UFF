#include <stdio.h>
#include <stdlib.h>

int *premiados(int n, int *inscr, float *t1, int p1,float *t2, int p2, int *tam);
int main()
{
    int n, *in, p1, p2, i, tam = 0, *maiorm;
    float *t1,*t2;

    printf("Diga a quantidade de participantes do concurso: ");
    scanf("%d", &n);

    /*Criando vetores*/

    in = (int*) malloc (n*sizeof(int));
    if (in==NULL){printf("Memoria insuficiente ;-;");exit(1);}

    t1 = (float*) malloc(n*sizeof(float));
    if (t1==NULL){printf("Memoria insuficiente ;-;");exit(1);}

    t2 = (float*) malloc(n*sizeof(float));
    if (t2==NULL){printf("Memoria insuficiente ;-;");exit(1);}

    printf("\nDigite o peso do primeiro teste: ");
    scanf("%d", &p1);

    printf("\nDigite o peso do segundo teste: ");
    scanf("%d", &p2);

    for (i=0;i<n;i++){
        printf("\nDigite a inscrição do participante:");
        scanf("%d", &in[i]);
        printf("\nDigite a nota no primeiro teste: ");
        scanf("%f", &t1[i]);
        printf("\nDigite a nota no segundo teste: ");
        scanf("%f", &t2[i]);
        }

    maiorm = premiados(n,in,t1, p1, t2, p2, &tam);

    printf("\nO aluno (ou os alunos) que teve a maior media foi: ");
    for (i=0;i<tam;i++)
        printf("%d", maiorm[i]);


    free(in);
    free(t1);
    free(t2);
    free(maiorm);
    return 0;
}

int *premiados(int n, int *inscr, float *t1, int p1,float *t2, int p2, int *tam)
{
    int i, soma,c = 1, j = 0,*maiorm;
    float *med, maior = -1.0;

    /**Media ponderada*/

    med = (float*) malloc (n*sizeof(float));

    for (i=0;i<n;i++){
        med[i] = ((t1[i]*p1) + (t2[i]*p2))/(p1+p2);
    }

    /*Maior media*/
    for (i=0;i<n;i++){
        if (med[i]>maior){
            maior = med[i];
            c = 1;
        }else if (med[i]==maior){
            c++;
        }
    }


    maiorm = (int*) malloc (c*sizeof(int));
    if (maiorm==NULL){printf("Memoria insuficiente ;-;");exit(1);}

    for (i=0;i<n;i++){
        if (med[i] == maior){
            maiorm[j] = inscr[i];
            j++;
        }
    }

    *tam = c;
    return maiorm;
}




