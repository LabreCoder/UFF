#include <stdio.h>

int main() {
    char palavra[21];
    int i = 0;

    printf("Digite uma palavra: ");
    fgets(palavra, sizeof(palavra), stdin);
    while (palavra[i] != '\0') {
        if (palavra[i] == '\n') {
            palavra[i] = '\0';
            break;
        }
        i++;
    }

    printf("Primeira letra: %c\n", palavra[0]);

    printf("Ultima letra: %c\n", palavra[i - 1]);

    printf("Numero de letras: %d\n", i);

    return 0;
}
