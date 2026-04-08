#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL,"");
    printf("Qual é a saída deste programa supondo que i ocupa o endereço 4094 na memória?\n");
    int i=5, *p;
    int endereco_i;
    endereco_i = 4094;
    p = &i;

    printf("Respostas:\n");
    printf("O valor hexadecimal e o valor hexadecimal de 4094 é: %x.\n",endereco_i);
    printf("O '*p' = 5, logo 5 + 2 = %d.\n", *p+2);
    printf("O '*p' = 5, logo 3*5 = %d\n.",3**p);
}
