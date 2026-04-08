import java.util.Random;
import java.util.Scanner;

public class NumeroNoVetor {
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        Random random = new Random();

        System.out.print("Digite um valor 'N': ");
        int n = teclado.nextInt();
        int[] v = new int[n];

        System.out.println("Digite um valor para 'K': ");
        int k = teclado.nextInt();

        for (int i = 0; i < v.length; i++){
            v[i] = random.nextInt(10) + 1; // Coloquei para gerar até o número 10, caso queiram fazer o teste, coloquem random.nextInt(1) que ele apenas irá gerar o 0 e depois coloquem o valor de 'K' para 0 e o programa irá imprimir todas as posições que K foi encontrado
            System.out.printf(((k == v[i]) ? ("'K' apareceu na posição 'v[" + i + "]'; \n") : "Número não encontrado\n"));           
        }
        teclado.close();
    }
}

