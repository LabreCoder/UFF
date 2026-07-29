#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct aluno {
	int matricula;
	float cr;
	struct aluno *prox;
} TAluno;

typedef TAluno *Hash; //Hash é um vetor que será alocado dinamicamente

void inicializa(Hash *tab, int m) {
	int i;
	for (i = 0; i < m; i++) {
		tab[i] = NULL;
	}
}

TAluno *aloca(int mat, float cr) {
	TAluno *novo = (TAluno *) malloc(sizeof(TAluno));
	novo->matricula = mat;
	novo->cr = cr;
	novo->prox = NULL;
	return novo;
}

int hash(int mat, int m) {
	return mat % m;
}

void libera(Hash *tab, int m) {
    int i;
    for (i = 0; i < m; i++)
        if (tab[i]) {
            TAluno *p = tab[i];
            TAluno *q;
            while (p) {
                q = p;
                p = p->prox;
                free(q);
            }
        }
}

/*MODIFICAR ESTA FUNCAO*/
TAluno * busca(Hash *tab, int m, int mat) {
    int pos = hash(mat, m);

    TAluno * aux = tab[pos];

    while (aux != NULL && aux->matricula != mat) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        return NULL;
    }

    return aux;
}

/*MODIFICAR ESTA FUNCAO*/
void insere(Hash *tab, int m, int mat, float cr) {
    int ini = hash(mat, m);
    if (tab[ini] == NULL) {
        tab[ini] = aloca(mat, cr);
        return;
    }
    
    TAluno * aux = tab[ini];

    if (aux->matricula == mat) {
        aux->cr = cr;
        return;
    }

    while (aux->prox != NULL || aux->matricula == mat) {
        aux = aux->prox;
    }
    
    if (aux->matricula == mat) {
        aux->cr = cr;
        return;
    }

    aux->prox = aloca(mat, cr);
}

void imprime(Hash *tab, int m) {
    for (int i = 0; i < m; i++) {
        printf("%d: ", i);
        if (tab[i]) {
            TAluno *p = tab[i];
            printf("\n");
            while (p) {
                printf("\t%d\t%.2f\t%p\n", p->matricula, p->cr, p->prox);
                p = p->prox;
            }
        } else printf("NULL\n");
    }
}


int main() {
	int n, m;
	printf("Digite m (tamanho da tabela hash)... ");
	scanf("%d", &m);
	printf("Digite n (quantidade de matriculas)... ");
	scanf("%d", &n);

	if ((n <= 1) || (m <= 1)) return 0;

	Hash tab[m];
	inicializa(tab, m);

	int i, mat;
	float cr;
	for (i = 0; i < n; i++) {
		printf("Digite a matricula e o cr...\n");
		scanf("%d", &mat);
		scanf("%f", &cr);
		insere(tab, m, mat, cr);
	}
	imprime(tab, m);

	char resp;

	do {
		printf("Digite a matricula a ser procurada... ");
		scanf("%d", &mat);
		TAluno * p = busca(tab, m, mat);
		if (!p) printf("Elemento nao encontrado!\n");
		else {
			printf("%d\t%f\n", p->matricula, p->cr);
		}
		printf("Quer continuar? ");
		scanf(" %c", &resp);
	} while ((resp != 'N') && (resp != 'n'));
	imprime(tab, m);

	libera(tab, m);

	return 0;
}