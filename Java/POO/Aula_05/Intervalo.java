import java.util.Scanner;

public class Intervalo { // posição de um número N (antes, depois ou entre)
    public static void main(String[] args){ 
        Scanner teclado = new Scanner(System.in);
        int N, a, b;

        System.out.print("Digite um valor N: ");
        N = teclado.nextInt();

        System.out.print("Agora digite um valor para A: ");
        a = teclado.nextInt();

        System.out.print("Agora digite um valor para B: ");
        b = teclado.nextInt();
        
        if (a == b) {
            System.out.println("O valor de B não pode ser o mesmo de A!");
        } 
        else if (a > b) {

            if (N > a) {
                System.out.println("O número N está depois do intervalo");
            } 
            else if (N < b) {
                System.out.println("O número N está antes do intervalo");
            } 
            else if (N == a || N == b) {
                System.out.println("O valor de N é igual a A ou a B");
            }
            else {
                System.out.println("O número N está dentro do intervalo");
            }

        } 
        else { // caso b > a

            if (N > b) {
                System.out.println("O número N está depois do intervalo");
            } 
            else if (N < a) {
                System.out.println("O número N está antes do intervalo");
            } 
            else if (N == a || N == b) {
                System.out.println("O valor de N é igual a A ou a B");
            }
            else {
                System.out.println("O número N está dentro do intervalo");
            }

        }

        teclado.close();
    }
}