#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL,"Portuguese");
    printf("Assumindo que pulo[] é um vetor do tipo int, quais das seguintes expressões referenciam o valor do terceiro elemento da matriz? \na) *(pulo + 2) \nb) *(pulo + 4) \nc) pulo + 4 \nd) pulo + 2", setlocale(LC_ALL,""));
    printf("\nResposta: a. ");
    printf("Pois *(pulo +2) estará apontando para o valor que está em pulo[2], que é o terceiro valor, não pode ser o pulo + 2, pois iria puxar o endereço do pulo[2].");
}
