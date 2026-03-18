import java.util.Scanner;

public class MyName{
    public static void main(String [] args){
        System.out.println("Digite seu nome: ");
        Scanner teclado = new Scanner(System.in);
        System.out.println("Olá, meu nome é " + teclado.nextLine());
    }
}