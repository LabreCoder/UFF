#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista *prox;
} TLista;

TLista *cria_lista(void);
TLista *insere_fim_recursivo(TLista *li, int i);
TLista *insere_ordenado_recursivo(TLista *li, int i);
void imprime_lista(TLista *li);


TLista *cria_lista(void) {
    return NULL;
}

TLista *insere_fim_recursivo(TLista *li, int i) {
    if (li == NULL || li->prox == NULL) {
        TLista *novo = (TLista *) malloc(sizeof(TLista));
        novo->info = i;
        novo->prox = NULL;
        if (li == NULL) {
            li = novo;
        } else li->prox = novo;
    }
    else
        insere_fim_recursivo(li->prox, i);
    return li;
}

TLista *insere_ordenado_recursivo(TLista *li, int i) {
    if (li == NULL || li->prox == NULL) { //lista vazia
        TLista *novo = (TLista *) malloc(sizeof(TLista));
        novo->info = i;
        novo->prox = NULL;
        if (li == NULL)
            li = novo;
        else { /* inserir no meio da lista */
            if (li->info > i) {
                novo->prox = li;
                li = novo;
            }
            else li->prox = novo;
        }
    } else {
        if (li->info > i) {
            TLista *novo = (TLista *) malloc(sizeof(TLista));
            novo->info = i;
            novo->prox = li;
            li = novo;
        }
        else li->prox = insere_ordenado_recursivo(li->prox, i);
    }
    return li;
}


void imprime_lista(TLista *li) {
    TLista *p;
    for (p = li; p != NULL; p = p->prox)
        printf("info = %d\n", p->info);
}

TLista* exclui(TLista *li, int i){

	TLista* prox;

	if(li == NULL) return NULL;

	//Se eh o elemento a ser excluido, exclui
	if(li->info == i){
		prox = li->prox;
		free(li);
		return prox;
	}

	//Se não é, chama exclui no li->prox
	li->prox = exclui(li->prox, i);
	return li;
}

int main(void) {
    TLista *l1;
    TLista *l2;
    TLista *l3; /* declara listas não inicializadas */
    /* Insere elementos no inicio da lista */
    l1 = cria_lista(); /* cria e inicializa lista como vazia */
    l1 = insere_fim_recursivo(l1, 2);
    l1 = insere_fim_recursivo(l1, 3);
    l1 = insere_fim_recursivo(l1, 5);
    l1 = insere_fim_recursivo(l1, 4);
    printf("Lista 1:\n");
    imprime_lista(l1);

    /* Insere elementos no final da lista*/
    l2 = cria_lista(); /* cria e inicializa lista como vazia */
    l2 = insere_ordenado_recursivo(l2, 2);
    l2 = insere_ordenado_recursivo(l2, 5);
    l2 = insere_ordenado_recursivo(l2, 3);
    l2 = insere_ordenado_recursivo(l2, 4);
    l2 = insere_ordenado_recursivo(l2, 1);
    printf("Lista 2:\n");
    l2 = exclui(l2, 5);
    imprime_lista(l2);

    return 0;
}
