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
    
    int c1,c2;
    
    printf("Digite a primeira cidade: ");
    scanf("%d",&c1);
    
    printf("Digite a segunda cidade: ");
    scanf("%d",&c2);
    
    int i,j;
    
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(i+1 == c1 && j+1==c2){
                printf("Distancia entre cidade %d e %d = %d",c1,c2,tabela[i][j]);
                break;
            }
        }
    }
    
    return 0;
}