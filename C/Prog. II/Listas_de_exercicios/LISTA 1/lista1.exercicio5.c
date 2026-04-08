/*Lista de exercícios 1 */
/*Exercício 5*/

/* Defina as variáveis a, b e c (tipo de dado) para obter todas as possíveis respostas para
os valores de ‘c’:
Suponha que:
a = 3
b = a / 2
c = b + 3.1
Valores possíveis para ‘c’?
1. c = 4.6
2. c = 4.1
3. c = 4*/

#include <stdio.h>

int main(void){
	int a;
	int b;
	float c;
	
	a = 3;
	b = a / 2;
	c = b + 3.1;
	
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	printf("c: %f\n", c);
}
