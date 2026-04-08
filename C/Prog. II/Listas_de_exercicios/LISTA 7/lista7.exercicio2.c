#include <stdio.h>
#include <string.h>
int main (void) {
    char *frase = "Otimo teste";
    char *p , misterio[80];
    int i = 0;
    int j = 0;
    p = frase + strlen(frase) - 1;
    printf("Nesse ponto, o 'p' irá receber o valor do último caracter apontada no ponteiro 'frase', no caso o 'e' \n");
    while (*p != ' ') {
        misterio[i] = *p;
        i++; p--;
        }
    printf("Aqui nós estaremos colocando os valores do ponteiro 'frase' da Direita para a Esquerda até chegar no primeiro espaço ' '. \n");
    printf("Teremos, então, os valores misterio[0] = 'e', misterio[1] = 't', misterio[2] = 's', misterio[3] = 'e', misterio[4] = 't'.");
        misterio[i] = ' '; i++;
    while (frase[j] != ' ') {
        misterio [i] = frase[j];
        j++; i++;
        }
        printf("Aqui iremos inserir os valores iniciais do ponteiro 'frase' na string mistério, até o primeiro ' ' do ponteiro 'frase'. \n");
        printf("Teremos, então, misterio[6] = 'O', misterio[7] = 't', misterio[8] = 'i', misterio[9] = 'm', misterio[10] = 'o',");
        misterio[i] = '\0';
        printf("Aqui ele finaliza a string com o '\\0'. \n\n");
        puts (misterio);
    return 0;
}
