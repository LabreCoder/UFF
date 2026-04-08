#include <stdio.h>
#include <stdlib.h>

int iguais(int *r, int *s);
int main (void)
{
    int r[5], s[10];
    int i;

    printf("Digite os elementos da lista R:"); /*Lendo lista r*/
    for (i=0;i<5;i++)
        scanf("%d", &r[i]);

    printf("\nDigite os elementos da lista S:"); /*Lendo lista s*/
    for (i=0;i<10;i++)
        scanf("%d", &s[i]);

    iguais(r,s);

}

int iguais(int *R, int *S)
{
    int i,j,x[5],c=0,k,repetido;
    for (j=0;j<10;j++){ /*Verificando lista S*/
        for (i=0;i<5;i++){/*Verificando lista R*/
            if (S[j]==R[i]){

                    repetido = 0;

                    if (c==0){ /*Verificando quantos elementos a lista já tem*/
                        x[c]=S[j];
                        c++;
                    }else {
                        for (k=0;k<c;k++){
                            if (x[k]==S[j]){repetido = 1; break;}
                        }
                        if (repetido == 0){x[c]=S[j];c++;}
                    }
            }

        }

    }
    printf("\nElementos comuns (sem repeticao): ");
    for (i = 0; i < c; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}
