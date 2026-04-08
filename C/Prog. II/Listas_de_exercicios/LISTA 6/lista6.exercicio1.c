#include <stdio.h>
#include <stdlib.h>

float *acima_da_media(int n, float *vet, int *tam);
int main() {
    int n, i, tam;
    float *v,*v_acima;
    printf("Digite quantos numeros voce deseja que o vetor tenha: ");
    scanf("%d", &n);

    v = (float*) malloc (n*sizeof(float));
    if (v==NULL){printf("Falta memoria\n");exit(1);}

    printf("\nAgora digite os elementos do vetor: ");
    for (i=0;i<n;i++)
        scanf("%f", &v[i]);

    v_acima = acima_da_media(n,v,&tam);

    if (v_acima!= NULL&&tam>0){
        printf("\nElementos acima da media:");
        for (i=0;i<tam;i++){
            printf("\n%.0f", v_acima[i]);
        }
    }else {printf("\nNenhum elemento acima da media");}

    free(v);
    free(v_acima);
}

float *acima_da_media(int n, float *vet, int *tam)
{
    int i,j = 0, c = 0,acima = 0;
    float *vetresposta,soma = 0,media;

    /*1) Verificando media*/
    for (i=0;i<n;i++){
        soma+= vet[i];
        c++;
    }
    media = soma/c;

    /*2) vendo quantos elementos sao acima da media*/
    for (i=0;i<n;i++){
        if (vet[i]>media){acima++;}
    }

    /*3) Criando vetresposta*/
    vetresposta = (float*) malloc (acima*sizeof(float));
    if (vetresposta == NULL) return NULL;


    /*4) preenchendo vetresposta*/
    for (i=0;i<n;i++){
        if (vet[i]>media){
            vetresposta[j] = vet[i];
            j++;
        }
    }

    *tam = acima;
    return vetresposta;

}
