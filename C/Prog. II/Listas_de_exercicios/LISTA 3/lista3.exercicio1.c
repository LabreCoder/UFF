#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define PI 3.14159265F

void calc_circulo(float r, float * circunferencia, float * area);

int main()
{
    setlocale(LC_ALL,"");
    float circunferencia;
    float area;
    float r;
    printf("Digite o valor do raio:");
    scanf("%f",&r);
    calc_circulo(r, &circunferencia, &area);
    printf("Se valor do raio é: %.2f, então terá uma área com o valor de: %.2f e uma circunferência com valor de: %.2f", r,area,circunferencia);
    return 0;
    system("pause");
}

void calc_circulo(float r, float * circunferencia, float * area){
    *area = PI*r*r;
    *circunferencia = PI*r*2;
}
