#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    int dia, mes, ano;
} Data;

typedef struct local {
    char ender[81];
    int sala;
} Local;

typedef struct notas {
    float geral;
    float especifica;
} Notas;

typedef struct candidato {
    int inscr;
    char nome[81];
    Data nasc;
    Local *loc;
    Notas nt;
} Candidato;

// (a) Função para ler e alocar os dados dos candidatos
Candidato **leCandidatos(int n) {
    Candidato **v = (Candidato **) malloc(n * sizeof(Candidato *));
    for (int i = 0; i < n; i++) {
        v[i] = (Candidato *) malloc(sizeof(Candidato));
        printf("\nCandidato %d\n", i+1);
        printf("Inscricao: ");
        scanf("%d", &v[i]->inscr);
        printf("Nome: ");
        scanf(" %[^\n]", v[i]->nome);
        printf("Data de nascimento (dia mes ano): ");
        scanf("%d %d %d", &v[i]->nasc.dia, &v[i]->nasc.mes, &v[i]->nasc.ano);
        v[i]->loc = (Local *) malloc(sizeof(Local));
        printf("Endereco do local: ");
        scanf(" %[^\n]", v[i]->loc->ender);
        printf("Numero da sala: ");
        scanf("%d", &v[i]->loc->sala);
        printf("Nota geral: ");
        scanf("%f", &v[i]->nt.geral);
        printf("Nota especifica: ");
        scanf("%f", &v[i]->nt.especifica);
    }
    return v;
}

// (b) Função para imprimir os dados dos candidatos
void imprimeCandidatos(Candidato **v, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCandidato %d\n", i+1);
        printf("Inscricao: %d\n", v[i]->inscr);
        printf("Nome: %s\n", v[i]->nome);
        printf("Data: %02d/%02d/%04d\n", v[i]->nasc.dia, v[i]->nasc.mes, v[i]->nasc.ano);
        printf("Local: %s, sala %d\n", v[i]->loc->ender, v[i]->loc->sala);
        printf("Notas: Geral %.2f, Especifica %.2f\n", v[i]->nt.geral, v[i]->nt.especifica);
    }
}

// (c) Função para alterar o local de prova de um candidato
void alteraLocal(Candidato **v, int n, int inscricao) {
    for (int i = 0; i < n; i++) {
        if(v[i]->inscr == inscricao) {
            printf("Novo endereco do local: ");
            scanf(" %[^\n]", v[i]->loc->ender);
            printf("Nova sala: ");
            scanf("%d", &v[i]->loc->sala);
            return;
        }
    }
    printf("Candidato nao encontrado.\n");
}

int main() {
    int n, op, cod;
    Candidato **candidatos = NULL;
    do {
        printf("\nMenu:\n1. Ler candidatos\n2. Imprimir candidatos\n3. Alterar local de prova\n0. Sair\nOpcao: ");
        scanf("%d", &op);
        if(op == 1) {
            printf("Quantidade de candidatos: ");
            scanf("%d", &n);
            candidatos = leCandidatos(n);
        } else if(op == 2) {
            if(candidatos)
                imprimeCandidatos(candidatos, n);
            else
                printf("Nao ha candidatos.\n");
        } else if(op == 3) {
            printf("Informe a inscricao: ");
            scanf("%d", &cod);
            alteraLocal(candidatos, n, cod);
        }
    } while(op != 0);

    if(candidatos) {
        for (int i = 0; i < n; i++) {
            free(candidatos[i]->loc);
            free(candidatos[i]);
        }
        free(candidatos);
    }
    return 0;
}
