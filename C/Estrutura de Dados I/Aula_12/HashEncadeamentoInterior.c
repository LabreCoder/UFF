#include <stdio.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIBERADO 0
#define OCUPADO 1

typedef struct aluno {
    int matricula;
    float cr;
    int prox;
    int ocupado;
} TAluno;

typedef TAluno *Hash; //Hash é um vetor que será alocado dinamicamente

TAluno *aloca(int mat, float cr, int status, int prox) {
    TAluno *novo = (TAluno *) malloc(sizeof(TAluno));
    novo->matricula = mat;
    novo->cr = cr;
    novo->ocupado = status;
    novo->prox = prox;
    return novo;
}

void inicializa(Hash *tab, int m) {
    int i;
    for (i = 0; i < m; i++) {
        tab[i] = aloca(-1, -1, LIBERADO, -1);
    }
}

int hash(int mat, int m) {
    return mat % m;
}

void libera(Hash *tab, int m) {
    int i;
    for (i = 0; i < m; i++) {
        if (tab[i]) {
            free(tab[i]);
        }
    }
}

/*
 * Função busca assume que a tabela tenha sido inicializada da
    seguinte maneira: T[i].ocupado = LIBERADO,
    e T[i].pont = -1, para 0 < i < m-1

RETORNO:
     Se chave mat for encontrada, achou = 1,
     função retorna endereço onde mat foi encontrada

     Se chave mat não for encontrada, achou = 0, e há duas
     possibilidades para valor retornado pela função:
	   endereço de algum compartimento livre, encontrado
                  na lista encadeada associada a h(mat)
	   -1 se não for encontrado endereço livre
 */
int busca(Hash *tab, int m, int mat, int *achou) {
    *achou = -1;
    int temp = -1;
    int end = hash(mat, m);
    while (*achou == -1) {
        TAluno *aluno = tab[end];
        if (!aluno->ocupado) {
            //achou compartimento livre -- guarda para retorná-lo caso chave não seja encontrada
            temp = end;
        }
        if (aluno->matricula == mat && aluno->ocupado) {
            //achou chave procurada
            *achou = 1;
        } else {
            if (aluno->prox == -1) {
                //chegou no final da lista encadeada
                *achou = 0;
                end = temp;
            } else {
                //avança para o próximo
                end = aluno->prox;
            }
        }
    }
    return end;
}

/*
 * Função insere assume que pos é o endereço onde será efetuada a inserção.
 * Para efeitos de escolha de pos, a tabela foi considerada como circular,
 * isto é, o compartimento 0 é o seguinte ao m-1
 */
void insere(Hash *tab, int m, int mat, float cr) {
    int achou;
    int pos;
    int temp = -1;
    int end = busca(tab, m, mat, &achou);
    if (!achou) {
        if (end != -1) {
            //Não encontrou a chave, mas encontrou posição livre
            //Inserção será realizada nessa posição livre encontrada pela busca
            pos = end;
        } else {
            //Não foi encontrada posição livre na lista encadeada durante a busca
            //Será necessário percorrer a tabela para encontrar uma posição
            int i = 1; //numero de tentativas realizadas
            pos = hash(mat, m);
            while (i <= m) { //serao realizadas no maximo m tentativas
                if (tab[pos]->ocupado) {
                    pos = (pos + 1) % m; //considera que tabela é circular
                    i++;
                } else {//achou compartimento livre
                    i = m + 2;//força saída do loop
                }
            }
            if (i == m + 1) {
                printf("A tabela esta cheia. Ocorreu overflow. Insercao nao realizada!\n");
                return;
            }
            //Ajusta os ponteiros para preparar a insercao
            temp = tab[hash(mat, m)]->prox;
            tab[hash(mat, m)]->prox = pos;
            tab[pos]->prox = temp;

        }
        tab[pos]->ocupado = OCUPADO;
        tab[pos]->matricula = mat;
        tab[pos]->cr = cr;
    } else {
        printf("Matricula ja existe. Insercao invalida! \n");
    }
}

void exclui(Hash *tab, int m, int mat) {
    int achou;
    int end = busca(tab, m, mat, &achou);
    if (achou) {
        //remove marcando flag para liberado
        tab[end]->ocupado = LIBERADO;
    } else {
        printf("Matricula nao encontrada. Remocao nao realizada!");
    }
}

//void exclui(Hash *tab, int m, int mat) {
//    int achou;
//    int pos = busca(tab, m, mat, &achou);
//    if (achou) {
//        int prox = tab[pos]->prox;
//        int ultimo = pos;
//        //encontra o último nó da lista encadeada
//        while (prox != -1) {
//             ultimo = tab[pos]->prox;
//             prox = tab[ultimo]->prox;
//        }
//        //copia o ultimo nó da lista encadeada para a posição do nó que vai ser apagado
//        tab[pos]->matricula = tab[ultimo]->matricula;
//        tab[pos]->cr = tab[ultimo]->cr;
//
//
//        //remove marcando flag para liberado
//        tab[pos]->ocupado = LIBERADO;
//    } else {
//        printf("Matricula nao encontrada. Remocao nao realizada!");
//    }
//}

void imprime(Hash *tab, int m) {
    int i, h;
    char s[10];
    for (i = 0; i < m; i++) {
        h = i;
        printf("%d:\n", h);
        TAluno *p = tab[h];

        if (p->ocupado) {
            strcpy(s, "OCUPADO");
        }
        else strcpy(s, "LIBERADO");
        printf("\tmat: %d\tcr: %.2f\tprox: %d\tstatus: %s\n", p->matricula, p->cr, p->prox, s);
    }
}

int main() {
    int n, m;
    printf("Digite m (tamanho da tabela hash)... ");
    scanf("%d", &m);
    printf("Digite n (quantidade de matriculas)... ");
    scanf("%d", &n);

    if ((n <= 1) || (m <= 1)) return 0;

    Hash *tab[m];
    inicializa(tab, m);
    imprime(tab, m);

    int i, mat;
    float cr;
    for (i = 0; i < n; i++) {
        printf("Digite a matricula e o cr...\n");
        scanf("%d", &mat);
        scanf("%f", &cr);
        insere(tab, m, mat, cr);
        imprime(tab, m);
    }


    char resp;
    do {
        printf("Digite a matricula a ser removida... ");
        scanf("%d", &mat);
        exclui(tab, m, mat);
        imprime(tab, m);
        printf("Quer continuar? ");
        scanf(" %c", &resp);
    } while ((resp != 'N') && (resp != 'n'));

    do {
        printf("Digite a matricula a ser procurada... ");
        scanf("%d", &mat);
        int achou;
        int end = busca(tab, m, mat, &achou);
        if (achou == 0) printf("Elemento nao encontrado!\n");
        else {
            TAluno *p = tab[end];
            printf("%d\t%f\n", p->matricula, p->cr);
        }
        printf("Quer continuar? ");
        scanf(" %c", &resp);
    } while ((resp != 'N') && (resp != 'n'));
    imprime(tab, m);

    for (i = 0; i < n / 2; i++) {
        printf("Digite a matricula e o cr...\n");
        scanf("%d", &mat);
        scanf("%f", &cr);
        insere(tab, m, mat, cr);
        imprime(tab, m);
    }

    libera(tab, m);
    return 0;
}