/*Lista de exercícios 1*/
/*Exercício 6*/

/*Implemente uma função que calcule as raízes de uma equação do segundo grau, do
tipo ax2 + bx + c = 0. Observação: para o cálculo da raiz quadrada de um número, utilize
a função sqrt. Consulte a documentação de como usá-la no programa.*/

#include <stdio.h>
#include <math.h>

void calc_raiz(double a, double b, double c) {
    double delta = (b * b) - (4 * a * c);

    double raiz1 = (-b + sqrt(delta)) / (2 * a);
    double raiz2 = (-b - sqrt(delta)) / (2 * a);

    printf("Delta: %lf\n", delta);
    printf("Raiz 1: %lf\n", raiz1);
    printf("Raiz 2: %lf\n", raiz2);
}

int main() {
    double a, b, c;

    printf("Digite os coeficientes a, b e c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    calc_raiz(a, b, c);

    return 0;
}

