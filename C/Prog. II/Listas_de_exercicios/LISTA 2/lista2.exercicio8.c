#include <stdio.h>
#include <stdlib.h>

int teste (int n)
{
    int a = n/100;
    int b = n%100;
    int c = a+b;
    int d = c*c;

    return d;
}

int main()
{
    int num;
    do{
        printf("Digite um numero de 4 algarismos: ");
        scanf("%d", &num);
    }while (num<1000 || num>9999);

    int r = teste(num);
    if (r==num){
        printf("\nEsse numero possui as mesmas caracteristicas que 3025");
    }else{
        printf("\nEsse numero nao possui as mesmas caracteristicas que 3025");
    }

}