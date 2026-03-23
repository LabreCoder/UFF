import java.util.Scanner;

public class Exercicio_03{// Par ou Ímpar
    public static void main(String [] args){
        int a =  0;
        System.out.println("Digite um numero: ");
        try (Scanner teclado = new Scanner(System.in)) {
            a = teclado.nextInt();
            if ( a % 2 == 0){
                System.out.printf("%s e par\n", a);
            } else {
                System.out.printf("%s e impar\n", a);
            }
        }
    }
}
