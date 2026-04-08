#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int comecoBarBar(const char *str) {
    while(isspace(*str)) str++;
    return (str[0] == '/' && str[1] == '/');
}

int main() {
    char nome[100];
    scanf("%s", nome);
    FILE *entrada = fopen(nome, "r");
    if(entrada == NULL){
        printf("ERRO");
        exit(1);
    }
    char novoNome[120];
    sprintf(novoNome, "SEM_COMENTARIOS_%s", nome);
    FILE *saida = fopen(novoNome, "w");
    if(saida == NULL){
        printf("ERRO");
        exit(1);
    }
    char linha[1024];
    while(fgets(linha, 1024, entrada) != NULL) {
        if(!comecoBarBar(linha))
            fputs(linha, saida);
    }
    fclose(entrada);
    fclose(saida);
    return 0;
}
