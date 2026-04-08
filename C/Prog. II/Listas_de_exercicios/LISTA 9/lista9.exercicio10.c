#include <stdio.h>
#include <string.h>

#define MAX 3

struct aluno {
    char nome[50];
    int idade;
    float media;
};

// Protótipos
void le(struct aluno turma[]);
void imprime(struct aluno turma[]);
void ordena_medias(struct aluno turma[]);

int main(void) {
    struct aluno turma[MAX];

    le(turma);

    puts("\nImprimindo dados lidos da turma.");
    puts("Digite qualquer coisa para continuar.");
    getchar();
    imprime(turma);

    ordena_medias(turma);

    puts("\nImprimindo dados ordenados da turma.");
    puts("Digite qualquer coisa para continuar.");
    getchar();
    imprime(turma);

    return 0;
}

// Função para ler dados dos alunos
void le(struct aluno turma[]) {
    for (int i = 0; i < MAX; i++) {
        printf("\nAluno %d:\n", i + 1);
        printf("Nome: ");
        fgets(turma[i].nome, sizeof(turma[i].nome), stdin);
        turma[i].nome[strcspn(turma[i].nome, "\n")] = '\0'; // remove o \n

        printf("Idade: ");
        scanf("%d", &turma[i].idade);

        printf("Média: ");
        scanf("%f", &turma[i].media);
        getchar(); // limpa o buffer após o scanf
    }
}

// Função para imprimir os dados da turma
void imprime(struct aluno turma[]) {
    printf("\n--- Dados dos Alunos ---\n");
    for (int i = 0; i < MAX; i++) {
        printf("Aluno %d: %s | Idade: %d | Média: %.2f\n",
               i + 1, turma[i].nome, turma[i].idade, turma[i].media);
    }
}

// Função para ordenar os alunos pela média (crescente)
void ordena_medias(struct aluno turma[]) {
    struct aluno temp;
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = 0; j < MAX - 1 - i; j++) {
            if (turma[j].media > turma[j + 1].media) {
                temp = turma[j];
                turma[j] = turma[j + 1];
                turma[j + 1] = temp;
            }
        }
    }
}
