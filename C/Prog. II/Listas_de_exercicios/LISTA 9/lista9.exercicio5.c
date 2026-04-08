#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct endereco {
    char rua[100];
    int numero;
} Endereco;

typedef struct notas {
    float p1, p2, p3;
} Notas;

typedef struct aluno {
    int mat;
    char nome[81];
    Notas nota;
    Endereco *end;
} Aluno;

// (a) Função alocaAlunos
Aluno **alocaAlunos(int n) {
    Aluno **a = (Aluno **) malloc(n * sizeof(Aluno *));
    for (int i = 0; i < n; i++) {
        a[i] = (Aluno *) malloc(sizeof(Aluno));
        a[i]->end = (Endereco *) malloc(sizeof(Endereco));
    }
    return a;
}

// (b) Função atribui
void atribui(Aluno **a, int indice, int matricula, char *nome,
             float nota1, float nota2, float nota3, char *nomeRua, int numero) {
    a[indice]->mat = matricula;
    strcpy(a[indice]->nome, nome);
    a[indice]->nota.p1 = nota1;
    a[indice]->nota.p2 = nota2;
    a[indice]->nota.p3 = nota3;
    strcpy(a[indice]->end->rua, nomeRua);
    a[indice]->end->numero = numero;
}

int main(void) {
    int n = 3;
    Aluno **alunos = alocaAlunos(n);
    atribui(alunos, 0, 10, "Um", 1, 1, 1, "Getulio Vargas", 100);
    atribui(alunos, 1, 20, "Dois", 8, 8, 8, "Amaral Peixoto", 200);
    atribui(alunos, 2, 30, "Tres", 9, 9, 9, "Ouro Verde", 300);

    for (int i = 0; i < n; i++) {
        printf("Aluno %d: Matricula: %d, Nome: %s, Notas: %.1f, %.1f, %.1f, Endereco: %s, %d\n",
               i+1, alunos[i]->mat, alunos[i]->nome,
               alunos[i]->nota.p1, alunos[i]->nota.p2, alunos[i]->nota.p3,
               alunos[i]->end->rua, alunos[i]->end->numero);
    }

    for (int i = 0; i < n; i++) {
        free(alunos[i]->end);
        free(alunos[i]);
    }
    free(alunos);
    return 0;
}
