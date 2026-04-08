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
    int p1 = 0,p2= 0,p3= 0,p4= 0,p5= 0,p6= 0,p0= 0;
    
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            switch(tabuleiro[i][j]){
                case 1:
                    p1++;
                    break;
                case 2:
                    p2++;
                    break;
                case 3:
                    p3++;
                    break;
                case 4:
                    p4++;
                    break;
                case 5:
                    p5++;
                    break;
                case 6:
                    p6++;
                    break;
                case 0:
                    p0++;
                    break;
            }
        }
    }
    
    printf("--------QTD DE PEÇAS--------\n");
    printf("\npeoes = %d",p1);
    printf("\navalos = %d",p2);
    printf("\ntorres = %d",p3);
    printf("\nbispos = %d",p4);
    printf("\nreis = %d",p5);
    printf("\nrainhas = %d",p6);
    printf("\nausencia de peças = %d",p0);


    return 0;
}