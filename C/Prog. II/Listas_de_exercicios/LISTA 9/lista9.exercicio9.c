#include <stdio.h>

#define MAX 3

typedef struct aluno {
    int mat;
    char nome[81];
    float media;
} ALUNO;

// Função le
void le(ALUNO turma[], int tam) {
    for (int i = 0; i < tam; i++) {
        scanf("%d", &turma[i].mat);
        scanf(" %[^\n]", turma[i].nome);
        scanf("%f", &turma[i].media);
    }
}

// Função imprime
void imprime(ALUNO turma[], int tam) {
    for (int i = 0; i < tam; i++)
        printf("%d %s %.2f\n", turma[i].mat, turma[i].nome, turma[i].media);
}

// Função ordena
void ordena(ALUNO turma[], int tam) {
    int i, foraOrdem, jaOrdenados = 0;
    ALUNO temp;
    do {
        foraOrdem = 0;
        for (i = 0; i < tam - 1 - jaOrdenados; i++) {
            if (turma[i].media > turma[i+1].media) {
                temp = turma[i];
                turma[i] = turma[i+1];
                turma[i+1] = temp;
                foraOrdem = 1;
            }
        }
        jaOrdenados++;
    } while (foraOrdem);
}

int main(void) {
    ALUNO turma[MAX];
    le(turma, MAX);
    imprime(turma, MAX);
    ordena(turma, MAX);
    imprime(turma, MAX);
    return 0;
}
