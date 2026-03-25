import java.util.Scanner;

public class A3_Exercicio_01{//Name
    public static void main(String [] args){
        System.out.println("Digite seu nome: ");
        try (Scanner teclado = new Scanner(System.in)) {
            System.out.println("Olá, meu nome é " + teclado.nextLine());
            teclado.close();
        }
    }
}