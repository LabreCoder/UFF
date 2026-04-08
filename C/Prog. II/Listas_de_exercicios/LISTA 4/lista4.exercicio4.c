#include <stdio.h>
#include <stdlib.h>

int testa_PA(int n, int* v);

int main() {
    int *v;
    int n,resultado,i;
    printf("Digite qual e o tamanho do vetor:\n");
    scanf("%d", &n);

    v = (int *) malloc(n*sizeof(int)); /*Criando vetor no tamanho certo*/
    if(v==NULL){printf("Memoria insuficiente"); exit(1);}

    printf("Digite os valores do seu vetor:\n");
    for (i=0;i<n;i++){scanf("%d",&v[i]);}

    resultado = testa_PA(n,v);

    printf("%d", resultado);

}

int testa_PA(int n, int* v)
{
    int i,k;
    for (i=1;i<n;i++){
        if(i==1){
            k=v[i]-v[i-1];
        }else if (k != v[i]-v[i-1]){
            return 0;
        }

    }

    return k;
}
