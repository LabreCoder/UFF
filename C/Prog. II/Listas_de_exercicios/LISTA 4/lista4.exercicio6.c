#include <stdio.h>
#include <stdlib.h>

int valida_mail(char *s);
int main() {
    char c[65];
    printf("Digite seu endereço email:");
    scanf("%64[^@]", c);
    printf("\n(0) = email invalido\n(1) = email valido\nResposta = ");
    
    valida_mail(c);
}

int valida_mail(char *s)
{
    int i,j,k,l,r = 1;
    int contaletras = 0,contanumeros = 0;
    char letras [] = "abcdefghijklmnopqrstuvwxyz";
    char numeros [] = "0123456789";
    char especiais [] = "-_.";

    for (i=0; i<64 && s[i]!= '\0' ;i++){
        r = 0;
        for (j=0;j<26;j++){                        /*Verificando letras*/
            if (s[i]==letras[j]){
                contaletras++;
                r = 1;
                break;
            }
        } if (i>0 && r!= 1){                        /*Verificando numeros*/
            for (k=0;k<10;k++){
                if (s[i]==numeros[k]){
                    contanumeros++;
                    r = 1;
                    break;
                }
            }
        } if (i>0 && r!= 1){                        /*Verificando especiais*/
            for (l=0;l<3;l++){
                if (s[i]==especiais[l]){
                    if (s[i] == '.' && s[i-1] == '.'){r = 0;}
                    else {r=1;break;}
                }
            }
        } if (r == 0){break;}


        
    } if ((contaletras+contanumeros)<2){r = 0;}
    if (s[i-1] == '.'){r = 0;}
    printf("%d", r);
}