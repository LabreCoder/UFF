#include <stdio.h>
#include <stdlib.h>

int main(){
    char nome[20];
    FILE *arq;
    for (int i = 1; i <= 10; i++){
        sprintf(nome, "teste%02d.txt", i);
        arq = fopen(nome, "w");
        if(arq == NULL){
            printf("ERRO");
            exit(1);
        }
        fprintf(arq, "Texto do arquivo %d", i);
        fclose(arq);
    }
    return 0;
}
