#include <stdio.h>
#include <stdlib.h>

typedef struct sNoA {
	int chave;
	struct sNoA *esq;
	struct sNoA *dir;
} TNoA;

void imprime(TNoA *nodo, int tab) {
	for (int i = 0; i < tab; i++) {
		printf("-");
	}
	if (nodo != NULL) {
		printf("%d\n", nodo->chave);
		imprime(nodo->esq, tab + 2);
		printf("\n");
		imprime(nodo->dir, tab + 2);
	} else printf("vazio");
}

TNoA *insere(TNoA *no, int chave) {
	if (no == NULL) {
		no = (TNoA *) malloc(sizeof(TNoA));
		no->chave = chave;
		no->esq = NULL;
		no->dir = NULL;
	} else if (chave < (no->chave))
		no->esq = insere(no->esq, chave);
	else if (chave > (no->chave)) {
		no->dir = insere(no->dir, chave);
	} else {
		printf("Inserção inválida! ");
		exit(1);
	}
	return no;
}

TNoA *maior_no_esquerda(TNoA *no) {
	TNoA *atual = no;

	/* loop para encontrar o nó mais à direita */
	while (atual->dir != NULL)
		atual = atual->dir;
	return atual;
}

/*Esta função recebe a raiz da árvore ou sub-arvore e a chave a ser excluída
Retorna ponteiro para a nova raiz da sub-árvore sendo modificada*/
TNoA *exclui(TNoA *raiz, int chave) {
	// Caso base - nada a fazer
	if (raiz == NULL) return raiz;

	// Se chave é menor do que a chave da raiz,
	//procura na subárvore esquerda
	if (chave < raiz->chave)
		raiz->esq = exclui(raiz->esq, chave);

	// Se chave é maior do que a chave da raiz,
	//procura na subárvore direita
	else if (chave > raiz->chave)
		raiz->dir = exclui(raiz->dir, chave);

	// Senão, a chave é igual e esse é o nó que tem que ser excluído
	else{
		// só tem subárvore direita ou nenhuma subárvore
		if (raiz->esq == NULL){
			TNoA *temp = raiz->dir;
			free(raiz);
			return temp;
			
		// só tem subárvore esquerda ou nenhuma subárvore
		} else if (raiz->dir == NULL){
			TNoA *temp = raiz->esq;
                        free(raiz);
			return temp;	

		} else { // nó com 2 filhos - pega o maior da subárvore esquerda
			TNoA *temp = maior_no_esquerda(raiz->esq);
			raiz->chave = temp->chave; 
			raiz->esq = exclui(raiz->esq, temp->chave);
	
		}
	}
	return raiz;
}

int main(void) {
	TNoA *raiz, *no;
	raiz = NULL;
	//arvore usada no slide da disciplina
	raiz = insere(raiz, 200);
	//subarvore esquerda
	insere(raiz, 100);
	insere(raiz, 80);
	insere(raiz, 150);
	insere(raiz, 70);
	insere(raiz, 65);
	insere(raiz, 79);
	insere(raiz, 120);
	insere(raiz, 110);
	insere(raiz, 130);

	//subarvore direita
	insere(raiz, 300);
	insere(raiz, 250);
	insere(raiz, 400);
	insere(raiz, 220);
	insere(raiz, 270);
	insere(raiz, 260);
	insere(raiz, 350);
	insere(raiz, 500);

	printf("\n\nArvore original: \n");
	imprime(raiz, 0);

	exclui(raiz, 100);
	exclui(raiz, 150);
	exclui(raiz, 80);
	exclui(raiz, 270);
	exclui(raiz, 400);
	exclui(raiz, 200);

	printf("\n\nArvore resultante da exclusão: \n");
	imprime(raiz, 0);
}
