#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define tamanho_vet 10

int main(){

    setlocale(LC_ALL,"Portuguese");
    int vet[tamanho_vet];
    int *inicio, *fim;

    srand(time(NULL)); // é para os aleatórios não ficarem iguais toda vez que iniciar o programa

    int i;
    for (i=0; i<(tamanho_vet/2); i++){
        inicio = &vet[i];
        *inicio = (rand() % 100);
        printf("A(%d): %d -- A(%d): ",i+1, *inicio, (tamanho_vet-i));

        fim = &vet[tamanho_vet-i-1];
        *fim = (rand() %100);
        printf("%d\n", *fim);
    }

    printf("\nEscrevendo o vetor na ordem, ficaria assim: \n");
    for (i=0; i<(tamanho_vet);i++)
    printf("%d\n",vet[i]);

	return 0;
}
