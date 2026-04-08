#include <stdio.h>
#include <stdlib.h>

struct elemento {
    float info; /* Valor real armazenado */
    struct elemento *prox; /* Ponteiro para o próximo elemento */
};
typedef struct elemento Elemento;

Elemento* filtra(Elemento *lst, float min, float max) {
    Elemento *aux;
    while(lst != NULL && (lst->info < min || lst->info > max)) {
        aux = lst;
        lst = lst->prox;
        free(aux);
    }
    if(lst == NULL)
        return NULL;
    Elemento *atual = lst;
    while(atual->prox != NULL) {
        if(atual->prox->info < min || atual->prox->info > max) {
            aux = atual->prox;
            atual->prox = aux->prox;
            free(aux);
        } else {
            atual = atual->prox;
        }
    }
    return lst;
}
