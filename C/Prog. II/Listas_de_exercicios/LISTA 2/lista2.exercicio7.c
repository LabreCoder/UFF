#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265

void calc_circulo(float r, float *circunferencia, float *area);

int main()
{
    float r, c, a;
    printf("Diga qual e o raio do circulo:");
    scanf("%f", &r);

    calc_circulo(r, &c, &a);
    printf("Circunferencia: %.2f\n Area: %.2f", c, a);


    return 0;
}

void calc_circulo(float r, float *circunferencia, float *area)
{
    *circunferencia = PI*r*r;
    *area = 2*PI*r;
}