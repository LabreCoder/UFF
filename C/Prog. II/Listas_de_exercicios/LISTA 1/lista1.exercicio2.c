/*Lista de exercícios 1 */
/*Exercício 2*/

/*Fazer um programa que recebe 3 valores inteiros do usuário e mostra o maior deles, o
menor deles, os valores pares e a média.*/

#include <stdio.h>

int main(void){
	
	int val1, val2, val3;
	int maior;
	int menor;
	float media;
	
	printf("Digite o primeiro valor inteiro: ");
	scanf("%d", &val1);
	
	printf("Digite o segundo valor inteiro: ");
	scanf("%d", &val2);
	
	printf("Digite o terceiro valor inteiro: ");
	scanf("%d", &val3);	
	
	if (val1 > val2)
		maior = val1;	
	else
		maior = val2;
	
	if (maior > val3)
		maior = maior;
	else 
		maior = val3;
	
	
	if (val1 < val2)
		menor = val1;	
	else
		menor = val2;
	
	if (menor < val3)
		menor = menor;
	else 
		menor = val3;
		
		printf("O maior valor é %d\n", maior);
		printf("O menor valor é %d\n", menor);
		
	printf("Valores pares: ");
	if (val1 % 2 == 0)
		printf("%d ", val1);
	if (val2 % 2 == 0)
		printf("%d ", val2);
	if (val3 % 2 == 0)
		printf("%d ", val3);
	printf("\n");
	
	
	media = (val1 + val2 + val3) / 3.0;
	
	printf("A média é %.1f", media);
}

