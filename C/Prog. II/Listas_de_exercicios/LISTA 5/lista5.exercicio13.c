#include <stdio.h>
#include <string.h>

int main() {
    char origem[] = "Exemplo de string!";
    char destino[20];

    // 1. strncpy: copia até 10 caracteres
    strncpy(destino, origem, 10);
    destino[10] = '\0'; // Garantir fim da string
    printf("1. strncpy - primeiros 10 caracteres: %s\n", destino);

    // 2. strchr: encontrar primeira ocorrência do caractere 'd'
    char *ptr = strchr(origem, 'd');
    if (ptr != NULL) {
        printf("2. strchr - primeira ocorrencia de 'd': %s\n", ptr);
    } else {
        printf("2. strchr - caractere 'd' nao encontrado.\n");
    }

    // 3. strspn: contar quantos caracteres iniciais pertencem a um conjunto
    const char *conjunto = "Exempol";
    size_t len = strspn(origem, conjunto);
    printf("3. strspn - qtd de caracteres iniciais pertencentes a '%s': %zu\n", conjunto, len);

    return 0;
}
