#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct funcionario {
    char nome[81]; /* nome do funcionário */
    float valor_hora; /* valor da hora de trabalho em Reais */
    int horas_mes; /* horas trabalhadas em um mês */
} Funcionario;

void carrega(int n, Funcionario **vet, char *arquivo) {
    FILE *arq = fopen(arquivo, "r");
    if (arq == NULL) {
        printf("ERRO");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        if (fgets(vet[i]->nome, 81, arq) == NULL) break;
        vet[i]->nome[strcspn(vet[i]->nome, "\n")] = '\0';
        fscanf(arq, "%f %d%*c", &vet[i]->valor_hora, &vet[i]->horas_mes);
    }
    fclose(arq);
}

int main() {
    int n;
    scanf("%d%*c", &n);
    Funcionario **vet = (Funcionario **) malloc(n * sizeof(Funcionario *));
    for (int i = 0; i < n; i++)
        vet[i] = (Funcionario *) malloc(sizeof(Funcionario));
    carrega(n, vet, "funcionarios.txt");
    for(int i = 0; i < n; i++){
        printf("%s %.2f %d\n", vet[i]->nome, vet[i]->valor_hora, vet[i]->horas_mes);
        free(vet[i]);
    }
    free(vet);
    return 0;
}
