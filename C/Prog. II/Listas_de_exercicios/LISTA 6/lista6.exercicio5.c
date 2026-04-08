#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* cifra_cesar(char* msg) {
    int len = strlen(msg);
    char* codificada = (char*)malloc((len + 1) * sizeof(char)); // +1 para o '\0'

    if (codificada == NULL) {
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        char c = msg[i];

        if (isalpha(c)) {
            if (islower(c)) {
                codificada[i] = ((c - 'a' + 3) % 26) + 'a';
            } else {
                codificada[i] = ((c - 'A' + 3) % 26) + 'A';
            }
        } else {
            codificada[i] = c;
        }
    }

    codificada[len] = '\0';
    return codificada;
}

int main() {
    char mensagem[1024];

    printf("Digite a mensagem a ser codificada:\n");
    if (fgets(mensagem, sizeof(mensagem), stdin) != NULL) {
        // Remove o '\n' do final, se houver
        mensagem[strcspn(mensagem, "\n")] = '\0';

        char* codificada = cifra_cesar(mensagem);
        if (codificada) {
            printf("Mensagem codificada: %s\n", codificada);
            free(codificada);
        } else {
            printf("Erro ao alocar memória.\n");
        }
    } else {
        printf("Erro ao ler entrada.\n");
    }

    return 0;
}
