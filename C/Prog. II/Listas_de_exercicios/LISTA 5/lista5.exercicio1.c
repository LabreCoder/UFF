#include <stdio.h>

void contarVogais(const char *str, int *numVogais) {
    *numVogais = 0;
    while (*str) {
        char c = *str;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            (*numVogais)++;
        }
        str++;
    }
}

int main() {
    const char *texto = "Exemplo de string";
    int numVogais;
    contarVogais(texto, &numVogais);
    printf("Numero de vogais: %d\n", numVogais);
    return 0;
}
