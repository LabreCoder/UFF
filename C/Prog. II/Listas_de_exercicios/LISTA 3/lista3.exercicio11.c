#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n;
    printf("Quantas pessoas irão participar dessa pesquisa? ");
    scanf("%d", &n);

    int idade;
    float altura;
    char sexo;

    int contF = 0; 
    int contM = 0; 

    float alturas[n];   
    float somaAlturas = 0;
    
    int i;
    for (i = 0; i < n; i++) {
        printf("\nPessoa %d:\n", i + 1);

        printf("Sexo (M/F): ");
        scanf(" %c", &sexo); // o espaço ignora espaços em branco

        printf("Idade: ");
        scanf("%d", &idade);

        printf("Altura (em metros): ");
        scanf("%f", &altura);

        if ((sexo == 'F' || sexo == 'f') && idade >= 20 && idade <= 35) {
            contF++;
        }

        if ((sexo == 'M' || sexo == 'm') && altura > 1.80) {
            contM++;
        }

        alturas[i] = altura;
        somaAlturas += altura;
    }

    float media = somaAlturas / n;

    // Cálculo da variância
    float somaQuadrados = 0;
    for (int i = 0; i < n; i++) {
        somaQuadrados += pow(alturas[i] - media, 2);
    }
    float variancia = somaQuadrados / n;

    printf("\nTotal de mulheres entre 20 e 35 anos: %d\n", contF);
    printf("Total de homens com mais de 1,80m: %d\n", contM);
    printf("Variância da altura: %.4f\n", variancia);

    return 0;
}
