#include <stdio.h>
#include <stdlib.h>
 
float media(float *v, int n) {
float media = 0.0;
 
for (int i = 0; i < n; i++){
media = media + v[i];
}
 
return media/n;
}
 
int main ( void ) {
float *v;
float med = 0.0;
int i, n;
// Código feito
printf("Por favor, insira a quantidade que deseja realizar a leitura: ");
scanf("%d", &n);
 
v = (float*)malloc(n*sizeof(float));
 
for (i = 0; i < n; i++){
printf("Digite um valor para v[%d]: ",i+1);
scanf(" %f", &v[i]);
}
med = media(v,n);
 
printf("media = %f\n", med);
 
free(v);
 
return 0;
}
