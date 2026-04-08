#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    int matricula;
    float *vNotas; // Vetor de 5 notas
    char nome[100];
} Aluno;

typedef struct Materia {
    Aluno *V;      // Vetor de alunos
    float media[5]; // Médias das 5 provas
    int nAlunos;
} Materia;

// (A) fillAluno
Aluno* fillAluno() {
    Aluno *al = (Aluno *) malloc(sizeof(Aluno));
    al->vNotas = (float *) malloc(5 * sizeof(float));
    scanf("%d", &al->matricula);
    scanf(" %[^\n]", al->nome);
    for (int i = 0; i < 5; i++)
        scanf("%f", &al->vNotas[i]);
    return al;
}

// (B) fillMateria
Materia* fillMateria(int numAlunos) {
    Materia *m = (Materia *) malloc(sizeof(Materia));
    m->nAlunos = numAlunos;
    m->V = (Aluno *) malloc(numAlunos * sizeof(Aluno));
    for (int i = 0; i < numAlunos; i++) {
        Aluno *temp = fillAluno();
        m->V[i] = *temp;
        free(temp);
    }
    return m;
}

// (C) mediaMateria
void mediaMateria(Materia *m1) {
    for (int prova = 0; prova < 5; prova++) {
        float soma = 0;
        for (int i = 0; i < m1->nAlunos; i++)
            soma += m1->V[i].vNotas[prova];
        m1->media[prova] = soma / m1->nAlunos;
    }
}

// (D) mostraMateria
void mostraMateria(Materia *m1) {
    for (int i = 0; i < m1->nAlunos; i++) {
        printf("%d %s ", m1->V[i].matricula, m1->V[i].nome);
        for (int j = 0; j < 5; j++)
            printf("%.2f ", m1->V[i].vNotas[j]);
        printf("\n");
    }
    for (int i = 0; i < 5; i++)
        printf("Media prova %d: %.2f\n", i+1, m1->media[i]);
}

int main() {
    int numAlunos;
    scanf("%d", &numAlunos);
    Materia *m1 = fillMateria(numAlunos);
    mediaMateria(m1);
    mostraMateria(m1);
    for (int i = 0; i < m1->nAlunos; i++)
        free(m1->V[i].vNotas);
    free(m1->V);
    free(m1);
    return 0;
}
