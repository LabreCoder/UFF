#include <conio.h>
#include <stdio.h>
#include <locale.h>

void main(){

setlocale(LC_ALL,"");
float vet[100] = {1.1,2.2,3.3,4.4,5.5};
float *f;
int i;
f = vet;
printf("contador/valor/valor/endereco/endereco");
for(i = 0 ; i <= 4 ; i++){
printf("\ni = %d",i);
printf(" vet[%d] = %.1f",i, vet[i]);
printf(" *(f + %d) = %.1f",i, *(f+i));
printf(" &vet[%d] = %X",i, &vet[i]);
printf(" (f + %d) = %X",i, f+i);
}
printf("\nO resultado será esse: \n");
printf("i = 0 vet[0] = 1.1 *(f + 0) = 1.1 &vet[0] = 60FDE0 (f + 0) = 60FDE0\n");
printf("i = 1 vet[1] = 2.2 *(f + 1) = 2.2 &vet[1] = 60FDE4 (f + 1) = 60FDE4\n");
printf("i = 2 vet[2] = 3.3 *(f + 2) = 3.3 &vet[2] = 60FDE8 (f + 2) = 60FDE8\n");
printf("i = 3 vet[3] = 4.4 *(f + 3) = 4.4 &vet[3] = 60FDEC (f + 3) = 60FDEC\n");
printf("i = 4 vet[4] = 5.5 *(f + 4) = 5.5 &vet[4] = 60FDF0 (f + 4) = 60FDF0");
}
