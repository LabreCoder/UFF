#include <stdio.h>
#include <stdlib.h>



int main()
{
    int tabuleiro[8][8] = {
        {1,3,0,5,4,0,2,1},
        {1,0,1,0,0,1,0,0}, 
        {0,0,0,0,1,0,6,0},
        {1,0,0,1,1,0,0,1},
        {0,1,0,4,0,0,1,0},
        {0,0,3,1,0,0,1,1},
        {1,0,6,6,0,0,1,0},
        {1,0,5,0,1,1,0,6}
        
    };
    
    int i,j;
    int peoes = 0,bispos = 0,a = 0;
    
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(tabuleiro[i][j] == 1){
                peoes++;
            }else if(tabuleiro[i][j] == 4){
                bispos++;
            }else if(tabuleiro[i][j] == 0){
                a++;
            }
        }
    }
    
    printf("Qtd de peoes = %d",peoes);
    printf("\nQtd de bispos = %d",bispos);
    printf("\nQtd de bispos + peoes = %d",bispos+peoes);
    printf("\nQtd de ausencias de peça = %d",a);

    return 0;
}