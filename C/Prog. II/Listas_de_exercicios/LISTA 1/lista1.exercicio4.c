/*Lista de exercícios 1 */
/*Exercício 4*/

/*Um funcionário da UFF precisa validar as notas de 3 provas fornecidas por um
professor e indicar: a média, se está aprovado/reprovado e se tem direito de realizar a VS.
Inicialmente, faça um programa que recebe como entrada as 3 notas e mostre os
resultados solicitados. Posteriormente, coloque o código de cálculo da média em uma
função. Em um passo seguinte, realize os controles necessários para não receber notas
inválidas.*/

#include <stdio.h>

float calc_media(float n1, float n2, float n3){
	float media;
	media = (n1 + n2 + n3) / 3.0;
	return (media);
}



int main(void){
	
	float nota1, nota2, nota3;
	float nota;
	
	printf("Digite a primeira nota: ");
	scanf("%f", &nota1);
	if (nota1 < 0 || nota1 > 10)
    printf("Nota inválida!\n");
    

	printf("Digite a segunda nota: ");
	scanf("%f", &nota2);
	if (nota2 < 0 || nota2 > 10)
    printf("Nota inválida!\n");
    
	
	printf("Digite a terceira nota: ");
	scanf("%f", &nota3);
	if (nota2 < 0 || nota2 > 10) 
    printf("Nota inválida!\n");
	
	
	nota = calc_media(nota1, nota2, nota3);
	printf("Média do aluno %f\n", nota);
	
	if (nota < 4)
		printf("Aluno reprovado!");
	
	if (nota > 4 && nota < 6)
		printf("Aluno apto a realizar a VS");
		
	if (nota >= 6)
		printf("Aluno aprovado com média %.2f\n", nota);
}
