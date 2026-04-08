#include <stdio.h>
#include <string.h>
#define MAX 50
int main (void) {
char texto[MAX +2], temp ;
int tam , i;
gets(texto);
tam = strlen ( texto );
for (i = 0; i < tam ; i ++) {
temp = texto[i];
texto[i] = texto[ tam -1 - i ];
texto[strlen(texto) -1 - i] = temp ;
}
puts ( texto );

printf("O programa nem irá rodar por causa do gets que foi retirado de algumas versões anteriores. Porém em resumo, eles está trocando a primeira palavra pela última, está escrevendo de trás para frente.");

return 0;
