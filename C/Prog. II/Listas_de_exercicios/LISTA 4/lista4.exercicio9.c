#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL,"Portuguese");

    int v[7];
    int i;

    for (i=0; i<7; i++)   {
        printf("Digite o valor do vetor na posição (%d): ", i+1);
        scanf("%d", &v[i]);
        printf("\n");
    }
    for (i=0; i<7; i++){
        printf("Teremos o valor: %d na posicao: %d\n", v[i], (i+1));
    }

    int n;
    printf("Digite um valor inteiro para retornarmos a posição dele: ");
    scanf("%d", &n);
    printf("\n");

    printf("Teremos: ");
    char verificador;
    int pos;
    for (i=0; i<7; i++){
        if (n==v[i]){
            verificador = 'True';
            pos = i;
        }
        if (i>0){
            v[i] = v[i] + v[i-1];
            printf("%d, ", v[i]);
        }
        else {
            printf("%d,", v[i]);
        }
    }
    printf(" com a troca de valores");
    if (verificador != 'True')
        return -1;
	else
        printf("A posição do item (%d) é: %d", n, pos);
        return 0;

}
