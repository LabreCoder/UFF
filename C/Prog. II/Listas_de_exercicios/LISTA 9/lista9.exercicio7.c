#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    int mat;
    char nome[81];
} Aluno;

typedef struct prova {
    Aluno a;
    float q1, q2, q3, q4;
} Prova;

// Função compara
int compara(Prova *p1, Prova *p2) {
    float soma1 = p1->q1 + p1->q2 + p1->q3 + p1->q4;
    float soma2 = p2->q1 + p2->q2 + p2->q3 + p2->q4;
    if(soma1 < soma2)
        return 1;
    else if(soma1 > soma2)
        return 0;
    else {
        if(strcmp(p1->a.nome, p2->a.nome) > 0)
            return 1;
        else
            return 0;
    }
}

// Função troca
void troca(Prova **p1, Prova **p2) {
    Prova *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void ordena(int n, Prova **v) {
    int fim, i;
    for(fim = n - 1; fim > 0; fim--)
        for(i = 0; i < fim; i++)
            if(compara(v[i], v[i+1]))
                troca(&v[i], &v[i+1]);
}

int main(void) {
    int n = 3;
    Prova *provas[3];

    for (int i = 0; i < n; i++)
        provas[i] = (Prova *) malloc(sizeof(Prova));

    strcpy(provas[0]->a.nome, "Maria");
    provas[0]->q1 = provas[0]->q2 = provas[0]->q3 = provas[0]->q4 = 6;

    strcpy(provas[1]->a.nome, "Ana");
    provas[1]->q1 = provas[1]->q2 = provas[1]->q3 = provas[1]->q4 = 6;

    strcpy(provas[2]->a.nome, "Sandra");
    provas[2]->q1 = provas[2]->q2 = provas[2]->q3 = provas[2]->q4 = 7;

    ordena(n, provas);
    for (int i = 0; i < n; i++) {
        float soma = provas[i]->q1 + provas[i]->q2 + provas[i]->q3 + provas[i]->q4;
        printf("Aluno: %s, Soma: %.2f\n", provas[i]->a.nome, soma);
        free(provas[i]);
    }
    return 0;
}
