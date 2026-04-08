#include <stdio.h>
#include <stdlib.h>

int mdc(int a, int b)
{
    int i = 2;
    int r = 1;
    while(a>1 || b>1)
    {
        if (a%i == 0 && b%i == 0){
            a = a/i;
            b = b/i;
            r = r*i;
        }else if (a%i == 0){a = a/i;}
        else if (b%i == 0) {b = b/i;}
        else{i++;}
    }
    return r;
}

int main()
{
    int a,b,c;
    printf("Digite dois numeros:");
    scanf("%d %d", &a, &b);

    c = mdc(a,b);
    printf("O MDC desses numeros e : %d", c);
    return 0;
}
