#include <stdio.h>
#include <string.h>
#include <conio.h> // Para getch() e _getch()

#define MAX 8

// Função para verificar se o caractere é válido (letra ou número)
int caractere_valido(char c) {
    return ( (c >= '0' && c <= '9') ||
             (c >= 'A' && c <= 'Z') ||
             (c >= 'a' && c <= 'z') );
}

// Função para ler entrada com exibição de caracteres válidos
void ler_usuario(char *usuario) {
    int i = 0;
    char c;

    while (i < MAX) {
        c = _getch(); // Lê sem mostrar no console

        if (c == 13) // Enter
            break;

        if (caractere_valido(c)) {
            usuario[i++] = c;
            printf("%c", c);
        }
    }

    usuario[i] = '\0';
    printf("\n");
}

// Função para ler senha com exibição de asteriscos
void ler_senha(char *senha) {
    int i = 0;
    char c;

    while (i < MAX) {
        c = _getch(); // Lê sem mostrar

        if (c == 13) // Enter
            break;

        if (caractere_valido(c)) {
            senha[i++] = c;
            printf("*");
        }
    }

    senha[i] = '\0';
    printf("\n");
}

int main() {
    char usuario_cadastrado[MAX + 1], senha_cadastrada[MAX + 1];
    char usuario_digitado[MAX + 1], senha_digitada[MAX + 1];

    printf("=== Cadastro ===\n");
    printf("Digite o nome de usuario (max %d caracteres): ", MAX);
    ler_usuario(usuario_cadastrado);

    printf("Digite a senha (max %d caracteres): ", MAX);
    ler_senha(senha_cadastrada);

    printf("\n=== Login ===\n");
    printf("Digite o nome de usuario: ");
    ler_usuario(usuario_digitado);

    printf("Digite a senha: ");
    ler_senha(senha_digitada);

    // Comparação
    if (strcmp(usuario_cadastrado, usuario_digitado) == 0 &&
        strcmp(senha_cadastrada, senha_digitada) == 0) {
        printf("\nOK\n");
    } else {
        printf("\nAcesso negado\n");
    }

    return 0;
}