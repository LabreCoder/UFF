#include <stdio.h>
#include <stdlib.h>

typedef struct noA{
	char info;
	struct noA *esq;
	struct noA *dir;
} TNoA;

void imprime(TNoA *nodo, int tab){
	for (int i = 0; i < tab; i++){
		printf("-");
	}
	if (nodo != NULL){
		printf("%c\n", nodo->info);
		imprime(nodo->esq, tab + 2);
		printf("\n");
		imprime(nodo->dir, tab + 2);
	} else printf("vazio");
}

TNoA *criaNo(char ch){
	TNoA *novo;
	novo = (TNoA *) malloc(sizeof(TNoA));
	novo->info = ch;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

void profundidade(TNoA* a){
	if (a!= NULL){
		printf("%c ",a->info);
		profundidade(a->esq);
		profundidade(a->dir);
	}
}


void conta_nos(TNoA* a, int* cont){

	if (a!= NULL){
		*cont = *cont + 1;
                printf("%c ",a->info);
		printf("-> Nó: %d \n",*cont);
                conta_nos(a->esq, cont);
                conta_nos(a->dir, cont);

	}	
}


int main(void){
	TNoA *raiz;
	raiz = criaNo('A');
	raiz->esq = criaNo('B');
	raiz->dir = criaNo('C');
	raiz->dir->esq = criaNo('D');
	raiz->dir->dir = criaNo('E');
	raiz->esq->esq = criaNo('F');
	raiz->esq->dir = criaNo('G');
	imprime(raiz, 0);
	printf("\n");
	int quant_nos = 0;
	conta_nos(raiz, &quant_nos);
	printf("\n Quantidade de nós na árvore: %d \n", quant_nos);
};
