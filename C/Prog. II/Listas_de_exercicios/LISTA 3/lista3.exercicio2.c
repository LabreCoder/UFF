#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, ""); // permite acentos e ç

    int i = 3, j = 5;
    int *p, *q;
    p = &i;
    q = &j;

    printf("Qual é o valor das seguintes expressões?\n");
    printf("a) p == &i\n");
    printf("b) *p - *q\n");
    printf("c) **&p\n");
    printf("d) 3 * -(*p) / (*q) + 7\n");

    printf("\nRespostas:\n");

    if (p == &i) {
        printf("a) É verdadeiro (1)!\n");
    } else {
        printf("a) É falso (0)\n");
    }

    printf("b) %d\n", (*p - *q));
    printf("c) %d\n", **&p);
    printf("d) %d\n", (3 * -(*p) / (*q) + 7));

    return 0;
}
