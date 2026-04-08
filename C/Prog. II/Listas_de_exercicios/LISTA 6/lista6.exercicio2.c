#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *compactar(char *s);
int main()
{
    char s [100], *resultado;
    int i;
    
    printf("Digite seu texto: ");
    scanf("%99[^\n]", s);
    
    resultado = compactar(s);
    printf("\nResultado = %s", resultado);
    
    free (resultado);
    return 0;
}

char *compactar(char *s) {
    if (s == NULL) {
        return NULL;
    }

    int inicio = 0;
    while (s[inicio] == ' ') {
        inicio++;
    }

    int fim = strlen(s) - 1;
    while (fim >= inicio && s[fim] == ' ') {
        fim--;
    }

    int tamanho = fim - inicio + 1;
    char *resultado = (char *)malloc((tamanho + 1) * sizeof(char));

    if (resultado == NULL) {
        return NULL;
    }

    strncpy(resultado, s + inicio, tamanho);
    resultado[tamanho] = '\0';

    return resultado;
}