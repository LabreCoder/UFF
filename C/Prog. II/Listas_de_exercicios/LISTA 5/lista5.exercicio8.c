#include <stdio.h>
#include <string.h>

int main() {
    char palavra1[100], palavra2[100];

    printf("Digite a primeira palavra: ");
    scanf("%s", palavra1);

    printf("Digite a segunda palavra: ");
    scanf("%s", palavra2);

    // a. Verifica se as palavras são iguais
    if (strcmp(palavra1, palavra2) == 0) {
        printf("As palavras sao iguais.\n");
    } else {
        printf("As palavras sao diferentes.\n");
    }

    // b. Verifica se a segunda palavra é substring da primeira
    if (strstr(palavra1, palavra2) != NULL) {
        printf("A segunda palavra eh uma substring da primeira.\n");
    } else {
        printf("A segunda palavra NAO eh uma substring da primeira.\n");
    }

    return 0;
}