#include <stdio.h>
#include <math.h> // Necessária para ceil e floor

int main() {
    float numero;

    printf("Digite um numero real (float): ");
    scanf("%f", &numero);

    printf("Numero original: %.2f\n", numero);
    printf("Arredondado para cima (ceil): %.0f\n", ceil(numero));
    printf("Arredondado para baixo (floor): %.0f\n", floor(numero));

    return 0;
}
