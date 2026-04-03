public class Multiplicacao { // tabela de multiplicação de 1 a 10
    public static void main(String[] args){ 
        
        int N = 1;
        while (N <= 10){
            for (int j = 1; j <= 10; j++){
                System.out.printf("%d x %d = %d; ", N, j, N * j);
            }
            System.out.print("\n");
            N++;
        }
    }
}