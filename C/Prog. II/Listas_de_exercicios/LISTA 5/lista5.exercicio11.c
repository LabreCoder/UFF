#include <stdio.h>
#include <string.h>

int main() {
    char str[21]; // 20 caracteres + 1 para o '\0'
    int i, len;

    printf("Digite uma string (max 20 caracteres): ");
    fgets(str, sizeof(str), stdin);

    // Remove o '\n' se estiver presente
    str[strcspn(str, "\n")] = '\0';

    len = strlen(str);

    printf("String invertida: ");
    for (i = len - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }

    printf("\n");

    return 0;
}
