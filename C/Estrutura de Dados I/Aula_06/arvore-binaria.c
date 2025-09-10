#include "arvore-binaria.h"

TNoA *inicializa(void) {
    return NULL;
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%c\n", nodo->info);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else printf("vazio");
}

void imprimeProfundidade(TNoA * raiz, int tab){

	if (raiz != NULL)
	{
		
		printf("%c\n", raiz->info);
		for (int i=0; i<tab; i++){
                        printf("-");

		imprimeProfundidade(raiz->esq, tab+2);
		imprimeProfundidade(raiz->dir, tab+2);
		}
	}
}

void imprimePosOrdem(TNoA * raiz, int tab){

        if (raiz != NULL)
        {
                imprimePosOrdem(raiz->esq, tab+2);
                imprimePosOrdem(raiz->dir, tab+2);
		printf("%c\n", raiz->info);
                for (int i=0; i<tab; i++){
                        printf("-");

                }
		printf("%c\n",raiz->info);
        }
}

void imprimeSimetrico(TNoA * raiz, int tab){

        if (raiz != NULL)
        {
                imprimeSimetrico(raiz->esq, tab+2);
                printf("%c\n", raiz->info);
                for (int i=0; i<tab; i++){
                        printf("-");
		}
		printf("%c\n",raiz->info);

		imprimeSimetrico(raiz->dir, tab+2);
                
        }
}


TNoA *criaNo(char ch) {
    TNoA *novo;
    novo = (TNoA *) malloc(sizeof(TNoA));
    novo->info = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int main(void) {
    TNoA *raiz;
    raiz = criaNo('A');
    raiz->esq = criaNo('B');
    raiz->dir = criaNo('C');
    raiz->dir->esq = criaNo('D');
    raiz->dir->dir = criaNo('E');
//imprime(raiz, 0);
    printf("\n");
    imprimeProfundidade(raiz,0);
	printf("\n");
	imprimeSimetrico(raiz,0);
	printf("\n");
	imprimePosOrdem(raiz,0);


};
