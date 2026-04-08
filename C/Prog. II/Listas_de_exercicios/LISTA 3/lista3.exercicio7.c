#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL,"");

    int *pti;
    int veti[] = {10, 7, 2, 6, 3};
    pti = veti;

    char resposta;

    printf("Analise as afirmativas abaixo e escolha qual delas é FALSA:\n\n");

    printf("a) *pti == %d\n", *pti);
    printf("b) *(pti + 2) == %d\n", *(pti + 2));
    printf("c) pti[4] == %d\n", pti[4]);
    printf("d) pti[1] == %d\n", pti[1]);
    printf("e) *(veti + 3) == %d\n", *(veti + 3));

    printf("\nDigite a letra da afirmativa que você acha que é FALSA: ");
    scanf(" %c", &resposta);

    printf("\nAnalisando as afirmativas:\n\n");

    printf("a) *pti é igual a 10 -> Correto! *pti aponta para veti[0] = 10.\n");
    printf("b) *(pti + 2) é igual a 2 -> Correto! *(pti + 2) aponta para veti[2] = 2.\n");
    printf("c) pti[4] é igual a 3 -> Correto! pti[4] é o mesmo que veti[4] = 3.\n");
    printf("d) pti[1] é igual a 10 -> FALSO! pti[1] aponta para veti[1] = 7, não para 10.\n");
    printf("e) *(veti + 3) é igual a 6 -> Correto! *(veti + 3) aponta para veti[3] = 6.\n");

    printf("\nA afirmativa FALSA é: d\n");

    if (resposta == 'd' || resposta == 'D') {
        printf("Parabéns! Você acertou.\n");
    } else {
        printf("Resposta incorreta. A alternativa falsa era a letra d.\n");
    }

    return 0;
}
