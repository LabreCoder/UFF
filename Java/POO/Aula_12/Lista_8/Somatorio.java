import java.util.Scanner;
import java.util.InputMismatchException;

public class Somatorio {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int soma = 0;

        while (true) {
            try {
                System.out.print("Digite um número: ");
                int numero = scanner.nextInt();

                if (numero <= 0) {
                    break;
                }

                soma += numero;

            } catch (InputMismatchException e) {
                System.out.println("Entrada inválida. Digite um número inteiro.");
                scanner.nextLine(); // limpa o buffer
            }
        }
        System.out.println("Somatório: " + soma);
        scanner.close();
    }
}