#include <stdio.h>

int contarOcorrencias(const char *cadeia, char caractere) {
    int contador = 0;
    while (*cadeia) {
        if (*cadeia == caractere) {
            contador++;
        }
        cadeia++;
    }
    return contador;
}

int main() {
    char cadeia[21];
    char caractere;

    printf("Digite uma cadeia de ate 20 caracteres: ");
    fgets(cadeia, sizeof(cadeia), stdin);
    printf("Digite um caractere para contar: ");
    scanf(" %c", &caractere);

    int ocorrencias = contarOcorrencias(cadeia, caractere);
    printf("O caractere '%c' aparece %d vezes na cadeia.\n", caractere, ocorrencias);
    return 0;
}
