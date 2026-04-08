#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elemento {
    int info; /* Valor inteiro armazenado */
    struct elemento *prox; /* Ponteiro para o próximo elemento */
};
typedef struct elemento Elemento;

Elemento* copia(Elemento* lst) {
    if(lst == NULL)
        return NULL;
    Elemento *copia_lst = NULL, *fim = NULL, *novo;
    Elemento *atual = lst;
    while(atual != NULL) {
        novo = (Elemento*) malloc(sizeof(Elemento));
        if(novo == NULL)
            exit(1);
        novo->info = atual->info;
        novo->prox = NULL;
        if(copia_lst == NULL) {
            copia_lst = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
        atual = atual->prox;
    }
    return copia_lst;
}
