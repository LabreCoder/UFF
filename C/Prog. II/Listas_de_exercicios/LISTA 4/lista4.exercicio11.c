#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 20

int operacao(int v1, int v2, char c);

int main() {
    setlocale(LC_ALL, "");
    int v1[MAX], v2[MAX], v4[MAX];
    char v3[MAX];
    int i;

    printf("Digite assim: \n'valor1' \n'operador' \n'valor2'\n");

    for (i = 0; i < MAX; i++) {
        printf("\nValor %d de v1: ", i + 1);
        scanf("%d", &v1[i]);

        printf("Operador: ");
        scanf(" %c", &v3[i]);  // espaço antes do %c para ignorar '\n'

        printf("Valor %d de v2: ", i + 1);
        scanf("%d", &v2[i]);

        v4[i] = operacao(v1[i], v2[i], v3[i]);
    }

    // Mostrar resultados
    printf("\nResultados das operações:\n");
    for (i = 0; i < MAX; i++) {
        printf("%d %c %d = %d\n", v1[i], v3[i], v2[i], v4[i]);
    }

    return 0;
}

int operacao(int v1, int v2, char c) {
    int resultado = 0;

    if (c == '+') {
        resultado = v1 + v2;
    } else if (c == '-') {
        resultado = v1 - v2;
    } else if (c == '*') {
        resultado = v1 * v2;
    } else if (c == '/') {
        if (v2 != 0) {
            resultado = v1 / v2;
        } else {
            printf("Erro: divisão por zero!\n");
        }
    } else {
        printf("Operador inválido: %c\n", c);
    }

    return resultado;
}
