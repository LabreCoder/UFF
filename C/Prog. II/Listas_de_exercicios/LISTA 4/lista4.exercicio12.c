#include <stdio.h>
#include <string.h>

int main() {
    char s[21], c;
    printf("Digite uma frase de até 20 caracteres: ");
    scanf("%20[^\n]",s);
    
    getchar();
    printf("\nDigite um caracter: ");
    scanf("%c",&c);
    
    int i;
    for(i=0;s[i]!='\0';i++){
        if (s[i]==c)
        continue;
        else
        printf("%c",s[i]);
    }

    return 0;
}