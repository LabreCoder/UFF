#include <stdio.h>
#include <conio.h>

int main()
{
    char vetor[81];
    char carac;
    int i = 0;

    printf("Digite a frase (máx. 80 caracteres, pressione Enter para terminar):\n");

    while (i < 80)
    {
        carac = getch();

        if (carac == '\r')  // Enter pressionado
            break;

        vetor[i] = carac;
        printf("%c", carac);  // Mostra o caractere digitado
        i++;
    }

    vetor[i] = '\0';  // Finaliza a string

    printf("\nA frase separada por palavras em cada linha ficará assim: \n");

    int j;
    for (j=0; j<i; j++){
        if (vetor[j]!= ' '){
            printf("%c",vetor[j]);
        }
        else{
            printf("\n");
            continue;
        }
    }
    return 0;
}
