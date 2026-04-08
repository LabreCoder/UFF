#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 80

void declara_vetor(char *vetor);
void codifica_vetor(char *vetor, char *new_vetor);
void imprime_vetor(char *vetor);

int main(void){
    char vetor[MAX];
    char vetor_codificado[MAX];

    printf("Olá! Digite os valores para o seu vetor:\n");
    declara_vetor(vetor);

    printf("\nVetor original:\n");
    imprime_vetor(vetor);

    printf("\n\nIremos codificar agora!\n");
    codifica_vetor(vetor, vetor_codificado);

    printf("\nVetor codificado:\n");
    imprime_vetor(vetor_codificado);

    return 0;
}

void declara_vetor(char *vetor){
    fgets(vetor, MAX, stdin);
    vetor[strcspn(vetor, "\n")] = '\0'; // Remove o \n
}

void imprime_vetor(char *vetor){
    for (int i = 0; vetor[i] != '\0'; i++){
        printf("%c", vetor[i]);
    }
    printf("\n");
}



void codifica_vetor(char *vetor,char *new_vetor){
    int pos = 0;
    while (vetor[pos]!='\0'){
        int k = 0;
        for (int i=pos; i<(pos + 5); i++){
            new_vetor[i] = vetor[i] + k;
            k++;
        }
        pos+=5;
    }
