#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_preposition(const char *word) {
    const char *prepositions[] = {"de", "do", "da", "dos", "das"};
    for (int i = 0; i < 5; i++) {
        if (strcasecmp(word, prepositions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char palavra[30];

    printf("Digite o nome completo (fim com ENTER):\n");

    while (scanf("%s", palavra) == 1) {
        if (!is_preposition(palavra)) {
            printf("%c.", toupper(palavra[0]));
        }

        // Verifica o próximo caractere sem consumir (lookahead)
        int c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        ungetc(c, stdin); // devolve o caractere lido ao buffer
    }

    printf("\n");
    return 0;
}
