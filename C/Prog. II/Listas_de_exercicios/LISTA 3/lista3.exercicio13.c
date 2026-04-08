#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,d;
    float e,f,g,h;
    char v[10];
    int x;
    int *p;
    p = &a;

    printf("O conteúdo do endereço de a é: %d\n", *p);

    p++;

    printf("O valor, depois de incrementar o ponteiro p é: %d\n", *p);

    printf("\nExplicação:\nO conteúdo do endereço de a é: 0.\nIsso mostra que 'a' tem valor 0. Como não inicializou 'a', ele recebeu lixo de memória — mas neste caso, coincidiu de ser 0.");
    printf("\n\nA incrementar *p (p++), ele pulou para o próximo bloco de memória de sizeof(int) bytes (geralmente 4 bytes à frente). O valor, depois de incrementar o ponteiro p é: 6422040");
    printf("\n\nAgora estamos acessando o conteúdo do endereço logo após 'a', que provavelmente é 'b' — mas pesquisei e fiquei sabendo que isso não garantido em C.");
    printf("\n\nComo 'b' também não foi inicializado, ele tem um valor indefinido — neste caso, era 6422040 (valor aleatório na memória).");

    return 0;
}
