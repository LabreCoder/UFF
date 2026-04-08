#include <stdio.h>
#include <stdlib.h>

void calcula_corrida(float dist, float *b1, float *b2);
int main() {
    float d,b1 = 0, b2 = 0;

    printf("Digite a distancia percorrida pelo taxi:");
    scanf("%f", &d);

    calcula_corrida(d,&b1,&b2);

    printf("\nValor na bandeira 1 = %.2f", b1);
    printf("\nValor na bandeira 2 = %.2f", b2);


    
}

void calcula_corrida(float dist, float *b1, float *b2)
{
    *b1 = 4.95+(2.50*dist);
    *b2 = 4.95+(3*dist);
}
