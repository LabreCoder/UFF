#include <stdio.h>
#include <stdlib.h>

typedef struct sNoAVL {
	int chave;
	int fb;
	struct sNoAVL *esq;
	struct sNoAVL *dir;
} TNoAVL;

void imprime(TNoAVL *no, int tab) {
	for (int i = 0; i < tab; i++) {
		printf("-");
	}
	if (no != NULL) {
		printf("%d (fb = %d)\n", no->chave, no->fb);
		imprime(no->esq, tab + 2);
		printf("\n");
		imprime(no->dir, tab + 2);
	} else printf("vazio");
}

TNoAVL *rotacao_direita(TNoAVL *p) {
	// Faz rotação de p para direita e retorna ponteiro para a nova raiz
	TNoAVL *u = p->esq;
	p->esq = u->dir;
	u->dir = p;
	
	// Ajustar FBs: em rotação simples, ambos ficam balanceados
	p->fb = 0;
	u->fb = 0;
	
	return u;
}

TNoAVL *rotacao_esquerda(TNoAVL *p) {
	// Faz rotação de p para esquerda e retorna ponteiro para a nova raiz
	TNoAVL *u = p->dir;
	p->dir = u->esq;
	u->esq = p;
	
	// Ajustar FBs: em rotação simples, ambos ficam balanceados
	p->fb = 0;
	u->fb = 0;
	
	return u;
}

TNoAVL *rotacao_dupla_direita(TNoAVL *p) {
	// Rotação dupla: esquerda-direita
	TNoAVL *u = p->esq;
	TNoAVL *v = u->dir;  // Nó intermediário que será a nova raiz
	
	// Guardar FB de v ANTES das rotações (crucial!)
	int fb_v = v->fb;
	
	// Primeira rotação: esquerda em u
	u->dir = v->esq;
	v->esq = u;
	p->esq = v;
	
	// Segunda rotação: direita em p
	p->esq = v->dir;
	v->dir = p;
	
	// Ajustar FBs baseado no FB original de v
	if (fb_v == -1) {
		// v tinha subárvore esquerda mais alta
		p->fb = 1;   // p ficará com direita mais alta
		u->fb = 0;   // u ficará balanceado
	} else if (fb_v == 1) {
		// v tinha subárvore direita mais alta
		p->fb = 0;   // p ficará balanceado
		u->fb = -1;  // u ficará com esquerda mais alta
	} else {
		// v estava balanceado (inserção foi em v)
		p->fb = 0;
		u->fb = 0;
	}
	v->fb = 0;  // nova raiz sempre fica balanceada
	
	return v;
}

TNoAVL *rotacao_dupla_esquerda(TNoAVL *p) {
	// Rotação dupla: direita-esquerda
	TNoAVL *u = p->dir;
	TNoAVL *v = u->esq;  // Nó intermediário que será a nova raiz
	
	// Guardar FB de v ANTES das rotações
	int fb_v = v->fb;
	
	// Primeira rotação: direita em u
	u->esq = v->dir;
	v->dir = u;
	p->dir = v;
	
	// Segunda rotação: esquerda em p
	p->dir = v->esq;
	v->esq = p;
	
	// Ajustar FBs baseado no FB original de v
	if (fb_v == 1) {
		// v tinha subárvore direita mais alta
		p->fb = -1;  // p ficará com esquerda mais alta
		u->fb = 0;   // u ficará balanceado
	} else if (fb_v == -1) {
		// v tinha subárvore esquerda mais alta
		p->fb = 0;   // p ficará balanceado
		u->fb = 1;   // u ficará com direita mais alta
	} else {
		// v estava balanceado
		p->fb = 0;
		u->fb = 0;
	}
	v->fb = 0;  // nova raiz sempre fica balanceada
	
	return v;
}

TNoAVL *caso1(TNoAVL *p) {
	// Chave foi inserida à esquerda de p e causou fb = -2
	// Verificar se a rotação é simples ou dupla
	
	if (p->esq->fb == 1) {
		// Subárvore esquerda tem direita mais alta: rotação dupla
		p = rotacao_dupla_direita(p);
	} else {
		// Subárvore esquerda tem esquerda mais alta ou balanceada: rotação simples
		p = rotacao_direita(p);
	}
	
	return p;
}

TNoAVL *caso2(TNoAVL *p) {
	// Chave foi inserida à direita de p e causou fb = 2
	// Verificar se a rotação é simples ou dupla
	
	if (p->dir->fb == -1) {
		// Subárvore direita tem esquerda mais alta: rotação dupla
		p = rotacao_dupla_esquerda(p);
	} else {
		// Subárvore direita tem direita mais alta ou balanceada: rotação simples
		p = rotacao_esquerda(p);
	}
	
	return p;
}

TNoAVL *insere(TNoAVL *p, int chave, int *flag) {
	/* Insere nó em uma árvore AVL, onde p representa a raiz da árvore,
	chave é a chave a ser inserida e flag é um booleano que indica se 
	é necessário propagar operação de cálculo de fb */
	
	if (p == NULL) {
		p = (TNoAVL *) malloc(sizeof(TNoAVL));
		p->chave = chave;
		p->esq = NULL;
		p->dir = NULL;
		p->fb = 0;
		*flag = 1;
		printf("\nInseriu %d", p->chave);
		
	} else if (chave < p->chave) {
		// Recursão à esquerda
		p->esq = insere(p->esq, chave, flag);
		
		if (*flag) {
			// Inseriu: verificar balanceamento
			switch (p->fb) {
				case -1:
					// Era -1, agora fica -2: DESBALANCEOU
					p = caso1(p);
					*flag = 0;  // Não propaga mais (árvore balanceada)
					break;
				case 0:
					// Era balanceado, agora fica -1
					p->fb = -1;
					// *flag continua 1: propaga altura
					break;
				case 1:
					// Era 1, agora fica 0: BALANCEOU
					p->fb = 0;
					*flag = 0;  // Não propaga mais (altura não mudou)
					break;
			}
		}
		
	} else if (chave > p->chave) {
		// Recursão à direita
		p->dir = insere(p->dir, chave, flag);
		
		if (*flag) {
			// Inseriu: verificar balanceamento
			switch (p->fb) {
				case 1:
					// Era 1, agora fica 2: DESBALANCEOU
					p = caso2(p);
					*flag = 0;  // Não propaga mais (árvore balanceada)
					break;
				case 0:
					// Era balanceado, agora fica 1
					p->fb = 1;
					// *flag continua 1: propaga altura
					break;
				case -1:
					// Era -1, agora fica 0: BALANCEOU
					p->fb = 0;
					*flag = 0;  // Não propaga mais (altura não mudou)
					break;
			}
		}
	}
	// else: chave já existe, não faz nada
	
	return p;
}

// Função auxiliar para calcular altura (para verificação)
int altura(TNoAVL *p) {
	if (p == NULL) return 0;
	int h_esq = altura(p->esq);
	int h_dir = altura(p->dir);
	return 1 + (h_esq > h_dir ? h_esq : h_dir);
}

// Função para verificar se a árvore é AVL válida
int verifica_avl(TNoAVL *p) {
	if (p == NULL) return 1;
	
	int h_esq = altura(p->esq);
	int h_dir = altura(p->dir);
	int fb_calculado = h_dir - h_esq;
	
	// Verificar se FB está correto
	if (fb_calculado != p->fb) {
		printf("ERRO: Nó %d tem FB=%d mas deveria ser %d\n", 
		       p->chave, p->fb, fb_calculado);
		return 0;
	}
	
	// Verificar se FB está dentro do limite AVL
	if (fb_calculado < -1 || fb_calculado > 1) {
		printf("ERRO: Nó %d está desbalanceado (FB=%d)\n", 
		       p->chave, fb_calculado);
		return 0;
	}
	
	return verifica_avl(p->esq) && verifica_avl(p->dir);
}

int main() {
	TNoAVL *raiz = NULL;
	int ok;
	
	printf("=== Inserindo elementos na AVL ===");
	
	// Árvore do exercício

	int vetor[] = {50, 1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 7, 60, 43, 16, 67, 34, 35};
	for (int i = 0; i < sizeof(vetor)/sizeof(vetor[0]); i++) {
		raiz = insere(raiz, vetor[i], &ok);
	}
	/*// Árvore para testar todas as rotações
	raiz = insere(raiz, 50, &ok);
	raiz = insere(raiz, 40, &ok);
	raiz = insere(raiz, 30, &ok);
	raiz = insere(raiz, 55, &ok);
	raiz = insere(raiz, 60, &ok);
	raiz = insere(raiz, 57, &ok);
	raiz = insere(raiz, 58, &ok);
	raiz = insere(raiz, 52, &ok);
	raiz = insere(raiz, 51, &ok);
	*/
	printf("\n\n=== Estrutura da Árvore ===\n");
	imprime(raiz, 0);
	
	printf("\n\n=== Verificação de Propriedades AVL ===\n");
	if (verifica_avl(raiz)) {
		printf("✓ Árvore AVL válida! Todos os FBs estão corretos.\n");
	} else {
		printf("✗ Árvore possui erros!\n");
	}
	
	printf("\nAltura total da árvore: %d\n", altura(raiz));
	
	return 0;
}