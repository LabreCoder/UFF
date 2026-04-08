#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL,"Portuguese");
    char c[51];
    int verificador = 0;
    printf("Por favor, escreva uma frase de até no máximo 50 caracteres: ");
    scanf("%50[^\n]", c);
    
    int i, j, cont;
    
    for (i=0; c[i]!='\0';i++){
        verificador = 1;
        cont = 0;
        for (j=0;j<i;j++){
            if (c[j]==c[i]){
                verificador = 0;
                break;
            }
            else verificador = 1;
        }
        if (verificador==1){
            for (j=i; c[j]!='\0';j++){
                if (c[j]==c[i]){
                    cont++;
                }
            }
            printf("\n'%c' = %d", c[i],cont);
        }
        
    }
    
    return printf("\n\nCódigo executado com sucesso!!");

    //return 0;
}