/*Lista de exercícios 1 */
/*Exercício 3*/

/*Fazer um programa que recebe um símbolo de operação do usuário (+, -, / ou *) e dois
números reais. O programa deve retornar o resultado da operação recebida sobre estes
dois números.*/


#include <stdio.h>

int main(void){
	
	float num1;
	float num2;
	char op;
	float res;

	printf("Digite uma operação que deseja realizar (+, -, / ou *): ");
	scanf(" %c", &op);
	
	printf("Digite o primeiro número real: ");
	scanf("%f", &num1);
	
	printf("Digite o segundo número real: ");
	scanf("%f", &num2);
	
	if (op == '+')
		res = num1 + num2;
		
	if (op == '-')
		res = num1 - num2;
		
	if (op == '/')
		res = num1 / num2;
		
	if (op == '*')
		res = num1 * num2;
		
	printf("Resultado %.2f\n", res);
	
}


