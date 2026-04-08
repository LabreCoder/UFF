#include <stdio.h>
#include <stdlib.h>



int main()
{
    int tabela[5][5] = {
        {00,15,30,05,12},
        {15,00,10,17,28},
        {30,10,00,03,11},
        {05,17,03,00,80},
        {12,28,11,80,00},
        
    };
    
    int i;
    
    for(i=0;i<5;i++){
        for (int j = i + 1; j < 5; j++){
            printf("\nDistancia entre cidade %d e %d = %d",i+1,j+1,tabela[i][j]);
        }
    }
    
    return 0;
}