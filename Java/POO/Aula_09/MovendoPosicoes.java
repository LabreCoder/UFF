import java.util.Random;
import java.util.Scanner;

public class MovendoPosicoes { // Esse programa irá realizar uma movimentação nos vetores, passando os valores uma posição para a frente, sendo o primeiro o valor 0 e o último perdido após as alterações
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        Random random = new Random();

        System.out.print("Digite um valor 'N': ");
        int n = teclado.nextInt();
        int[] v = new int[n];

        if (v.length > 2){ // Verifica se o tamanho do vetor é maior que 2 para conter o K e o P. Caso seja apenas 2, ele nem deve prosseguir, pois 'P' terá uma posição inválida.
            System.out.println("Digite um valor para 'K': ");
            int k = teclado.nextInt();
            v[0] = k;
            
            System.out.println("Digite um valor para 'P': ");
            int p = teclado.nextInt();
            v[1] = p;

            System.out.printf("Vetor: %d, %d, ", v[0],v[1]);
            for (int i = 2; i < v.length; i++){ // Aqui o programa irá gerar os valores aleatórios para as posições restantes
                v[i] = random.nextInt(10) + 1;
                System.out.printf("%d, ", v[i]);
            }
            
            for (int j = v.length - 1; j > 0; j--) { // Iŕa fazer as trocas de posições
                v[j] = v[j - 1];
            }

            v[0] = 0; // O valor para a primeira posição será 0
        
            System.out.print("agora o novo Vetor: ");
            for (int j = 0; j < v.length; j++){ System.out.print(v[j] + ", ");}
            System.out.println("depois da alteração.");
        }

        else{
            System.out.println("Posição Inválida");
        }

    teclado.close();
    }

}
