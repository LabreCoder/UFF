#include <stdio.h>
#include <stdlib.h>

int mdc_recursiva(int a, int bf) {
    printf("\n%d e %d", a, b);
    if (a % b == 0) {return b;}
    return mdc_recursiva (b, a % b);
}
int main() {
    int a=32, b=18;
    printf("\nResultado=%d",mdc_recursiva(a, b));
}

/* 
Será impresso as seguintes informações:
32 e 18 
18 e 14 
14 e 4
4 e 2

Resultado = 2
*/