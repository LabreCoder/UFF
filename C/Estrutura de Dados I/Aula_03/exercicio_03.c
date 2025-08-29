
#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

TLista* cria_lista (void);
TLista* insere_inicio (TLista* li, int i);
TLista* insere_fim (TLista* li, int i);
TLista* insere_ordenado (TLista* li, int i);
void imprime (TLista* li);

TLista* cria_lista (void) {
    return NULL;
}

TLista* insere_inicio (TLista* li, int i) {
    TLista* novo = (TLista*) malloc(sizeof(TLista));
    novo->info = i;
    novo->prox = li;
    return novo;
}

TLista* insere_fim (TLista* li, int i) {
    TLista* novo = (TLista*) malloc(sizeof(TLista));
    novo->info = i;
    novo->prox = NULL;
    TLista* p = li;
    if (p == NULL) { //se a lista estiver vazia
        li = novo;
    }
    else {
        while (p->prox != NULL) { //encontra o ultimo elemento
            p = p->prox;
        }
        p->prox = novo;
    }
    return li;
}

TLista* insere_ordenado (TLista* li, int i) {
	TLista * novo = (TLista*)malloc(sizeof(TLista));
	novo->info = i;
	novo->prox = NULL;
	TLista* p = li;
	if (p == NULL){
		novo->prox = NULL;
		li = novo;
	
	}

	else if (p->info > i){
		novo->prox = li;
		li = novo;
	}
	else {
		while (p->prox != NULL && p->prox->info <i){
			p = p->prox;
		}
		novo->prox = p->prox;
		p->prox = novo;
	}
	return li;
}

//Achar o elemento com info = i e remover da lista.
//Assumir que existe apenas 1 elemento com info = i na lista.
TLista* exclui (TLista* li, int i) {
	TLista * p;

	if (li == NULL) return NULL;

	else{
		if (p->info == i){
			p = li->prox; 
			free(li);
			return p;
	
		}
	li->prox = exclui(li->prox,i);
       	return li; 	
	}

}
void imprime_lista(TLista *li) {
    TLista* p;
    for (p = li; p != NULL; p = p->prox)
        printf("info = %d\n", p->info);
}

int main (void) {
    TLista* l1;
    TLista* l2;
    TLista* l3; /* declara listas não inicializadas */
    /* Insere elementos no inicio da lista */
    l1 = cria_lista(); /* cria e inicializa lista como vazia */
    l1 = insere_inicio(l1, 2);
    l1 = insere_inicio(l1, 3);
    l1 = insere_inicio(l1, 5);
    l1 = insere_inicio(l1, 4);
    printf("Lista 1:\n");
    imprime_lista(l1);

    /* Insere elementos no final da lista*/
    l2 = cria_lista(); /* cria e inicializa lista como vazia */
    l2 = insere_fim(l2, 2);
    l2 = insere_fim(l2, 3);
    l2 = insere_fim(l2, 5);
    l2 = insere_fim(l2, 4);
    printf("Lista 2:\n");
    l2 = exclui(l2,2);
    imprime_lista(l2);


    /* Insere elementos de forma que a lista esteja sempre ordenada */
    /*l3 = cria_lista();
    l3 = insere_ordenado(l3, 2);
    l3 = insere_ordenado(l3, 5);
    l3 = insere_ordenado(l3, 3);
    l3 = insere_ordenado(l3, 4);
    l3 = insere_ordenado(l3, 1);
    printf("Lista 3:\n");
    imprime_lista(l3);
*/
    return 0;
}

