#include <stdio.h>
void f1 ( int v) {
    v = v + 1;
    printf (" f1 = %d\n " , v );
}
void f2 ( int *v) {
    *v = *v + 1;
    printf (" f2 = %d\n " , *v );
}
int f3 ( int v) {
    v = v + 1;
    printf (" f3 = %d\n " , v );
    return v;
}
int main (void) {
    int v = 1;
    f1 ( v ); // O primeiro valor irá retornar 2;
    f2 (&v ); // O segundo valor irá retornar 2, porém mudando o valor original de 'v';
    v = f3 ( v ); // O terceiro irá retornar 3, pois 'v' vale 2, então depois de passar pela função, ele irá valer 3.
    printf (" main = %d \n" , v );
    return 0;
}
