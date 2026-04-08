#define MAX 4
#define MAXNOME 31
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void atribui(char **nomes, int indice, char *nome);
char *get_sobrenome(char *nome);

int main() {
    int i;
    char **nomes;
    char *sobrenome;

    nomes = (char **)malloc(MAX * sizeof(char *));
    if (nomes == NULL) return 1;

    for (i = 0; i < MAX; i++) {
        nomes[i] = (char *)malloc(sizeof(char) * MAXNOME);
        if (nomes[i] == NULL) return 1;
    }

    atribui(nomes, 0, "Fulano Silva");
    atribui(nomes, 1, "Maria do Carmo");
    atribui(nomes, 2, "Beltrano Belmonte");
    atribui(nomes, 3, "Pedro dos Santos");

    for (i = 0; i < MAX; i++) {
        sobrenome = get_sobrenome(nomes[i]);
        printf("\n%s ", sobrenome);
        printf(" %d", strlen(sobrenome) > 5 ? i : 0); // 2o printf
        printf("\n\nAqui será retornado se o sobrenome é maior que 5 ou não, se for maior ele retorna o '%d' se não ele retorna '0'.\n\n",i);
        free(sobrenome); 
    }
    printf("\nAqui ele irá retornar a 4º letra do Sobrenome do 1º nome!");
    printf("\n%c", nomes[0][3]); // 3o printf
    

    // Libera nomes
    for (i = 0; i < MAX; i++) {
        free(nomes[i]);
    }
    free(nomes);

    return 0;
}

void atribui(char **nomes, int indice, char *nome) {
    strcpy(nomes[indice], nome); // copia a string ao invés de trocar o ponteiro
}

char *get_sobrenome(char *nome) {
    int len = strlen(nome);
    int i = len - 1;

    while (i >= 0 && nome[i] != ' ')i--;

    char *sobrenome = (char*)malloc((len - i)*sizeof(char));
    if (sobrenome == NULL) return NULL;

    strcpy(sobrenome, &nome[i + 1]);
    return sobrenome;
}
