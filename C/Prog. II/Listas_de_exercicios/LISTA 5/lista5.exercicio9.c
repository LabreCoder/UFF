#include <stdio.h>
#include <string.h>

int main() {
    char nome[100], endereco[150], telefone[50];
    char informacoes[300]; // buffer para armazenar as informações concatenadas

    // Entrada de dados
    printf("Digite o nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' final

    printf("Digite o endereco: ");
    fgets(endereco, sizeof(endereco), stdin);
    endereco[strcspn(endereco, "\n")] = '\0';

    printf("Digite o telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    // Concatenação das strings
    strcpy(informacoes, "Nome: ");
    strcat(informacoes, nome);
    strcat(informacoes, " | Endereco: ");
    strcat(informacoes, endereco);
    strcat(informacoes, " | Telefone: ");
    strcat(informacoes, telefone);

    // Exibição do resultado
    printf("\nInformacoes concatenadas:\n%s\n", informacoes);

    return 0;
}
