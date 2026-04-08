#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <string.h>  // Inclui a biblioteca para manipulação de strings (não utilizada neste código)

int main(void) {
    char texto[] = "foi muito facil";  // Declara e inicializa uma string com a frase
    int i;  // Declara uma variável inteira para uso como índice

    // Primeiro loop: percorre a string até encontrar o primeiro espaço ou o final da string
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ' ') break;  // Se encontrar um espaço, interrompe o loop
    }

    i++;  // Avança o índice para o caractere seguinte ao espaço encontrado

    // Segundo loop: imprime os caracteres restantes da string a partir da posição atual
    for (; texto[i] != '\0'; i++) {
        printf("%c", texto[i]);  // Imprime o caractere atual
    }

    return 0;  // Indica que o programa terminou com sucesso
}
