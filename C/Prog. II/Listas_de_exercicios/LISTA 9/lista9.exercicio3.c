#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct assalariados {
    char nome[51];
    char sexo;
    int idade;
    float salario;
    char estado[3];
} Assalariados;

// (a) Função cadastra
Assalariados *cadastra(char *nome, char sexo, int idade, float salario, char *estado) {
    Assalariados *p = (Assalariados *) malloc(sizeof(Assalariados));
    strcpy(p->nome, nome);
    p->sexo = sexo;
    p->idade = idade;
    p->salario = salario;
    strcpy(p->estado, estado);
    return p;
}

// (b) Função imprime
void imprime(Assalariados **ptr, int numAssalariados) {
    for (int i = 0; i < numAssalariados; i++) {
        printf("Nome: %s, Sexo: %c, Idade: %d, Salario: %.2f, Estado: %s\n",
               ptr[i]->nome, ptr[i]->sexo, ptr[i]->idade, ptr[i]->salario, ptr[i]->estado);
    }
}

// (c) Função relatorio
void relatorio(Assalariados **ptr, int numAssalariados) {
    char *estados[27] = {"AC","AL","AM","AP","BA","CE","DF","ES","GO","MA",
                          "MG","MS","MT","PA","PB","PE","PI","PR","RJ","RN",
                          "RO","RR","RS","SC","SE","SP","TO"};
    int quant[27] = {0};
    for (int i = 0; i < numAssalariados; i++) {
        if(ptr[i]->sexo == 'M' && ptr[i]->idade > 40 && ptr[i]->salario > 1000.0) {
            for (int j = 0; j < 27; j++) {
                if(strcmp(ptr[i]->estado, estados[j]) == 0) {
                    quant[j]++;
                    break;
                }
            }
        }
    }
    for (int j = 0; j < 27; j++) {
        if(quant[j] > 0)
            printf("Estado=%s com %d homens maiores de 40 anos e salario maior que R$ 1000,00\n",
                   estados[j], quant[j]);
    }
}

int main(void) {
    int numAssalariados = 3;
    Assalariados **pessoas = (Assalariados **) malloc(numAssalariados * sizeof(Assalariados *));
    pessoas[0] = cadastra("Fulano de tal", 'M', 45, 1500.00, "RJ");
    pessoas[1] = cadastra("Ciclano", 'M', 50, 2500.00, "RS");
    pessoas[2] = cadastra("Beltrano", 'M', 42, 500.00, "RS");

    imprime(pessoas, numAssalariados);
    relatorio(pessoas, numAssalariados);

    for (int i = 0; i < numAssalariados; i++)
        free(pessoas[i]);
    free(pessoas);
    return 0;
}
