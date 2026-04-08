#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
    int dd, mm, aa; /* Dia, mes e ano */
};

typedef struct data Data;
struct compromisso {
    char descricao[81]; /* Descricao do compromisso */
    Data dta; /* Data do compromisso */
};
typedef struct compromisso Compromisso;

Compromisso* busca(int n, Compromisso** vet, int d, int m, int a);

int main() {
    int n = 4;
    Compromisso **compromisso = malloc(n * sizeof(Compromisso*));
    if (compromisso == NULL) return 1;

    int dias[4][3] = {
        {5, 4, 2025},
        {7, 5, 2025},
        {12, 8, 2025},
        {25, 12, 2025}
    };

    char *descricoes[] = {"Academia", "Faculdade", "Casamento", "Igreja"};

    for (int i = 0; i < n; i++) {
        compromisso[i] = malloc(sizeof(Compromisso));
        if (compromisso[i] == NULL) return 1;

        compromisso[i]->dta.dd = dias[i][0];
        compromisso[i]->dta.mm = dias[i][1];
        compromisso[i]->dta.aa = dias[i][2];
        strcpy(compromisso[i]->descricao, descricoes[i]);
    }
    
    int d = 12, m = 8, a = 2025;
    Compromisso* achado = busca(n, compromisso, d, m, a);

    if (achado != NULL) {
        printf("Compromisso encontrado: %s em %02d/%02d/%04d\n",
            achado->descricao, achado->dta.dd, achado->dta.mm, achado->dta.aa);
    } 
    else {
        printf("Compromisso não encontrado.\n");
    }
    for (int i=0; i<n; i++){
        free(compromisso[i]);
    }
    free(compromisso);
    
    return 0;
}

Compromisso* busca(int n, Compromisso** vet, int d, int m, int a){
    int ini = 0;
    int fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        // Comparar ano
        if (vet[meio]->dta.aa < a) {
            ini = meio + 1;
        } else if (vet[meio]->dta.aa > a) {
            fim = meio - 1;
        } else {
            // Comparar mês
            if (vet[meio]->dta.mm < m) {
                ini = meio + 1;
            } else if (vet[meio]->dta.mm > m) {
                fim = meio - 1;
            } else {
                // Comparar dia
                if (vet[meio]->dta.dd < d) {
                    ini = meio + 1;
                } else if (vet[meio]->dta.dd > d) {
                    fim = meio - 1;
                } else {
                    // Achou!
                    return vet[meio];
                }
            }
        }
    }

    return NULL;  // Não encontrou
