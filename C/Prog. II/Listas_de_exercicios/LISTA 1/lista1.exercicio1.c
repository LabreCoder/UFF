/*Lista de exercícios 1 */
/*Exercício 1*/

#include <stdio.h>

int main(void){
	
	int h, m, s;
	int segundos;
	
	printf("Digite um número inteiro de segundos: ");
	scanf("%d", &segundos);
	
	
	
	h = segundos / 3600;
	m = (segundos % 3600) / 60;
	s = (segundos % 3600) % 60;
	
	printf("%dh %dm %ds", h, m, s);
		
		
}

