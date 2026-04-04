import java.util.Scanner;

public class Strings{ // 
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        System.out.print("Digite uma frase: ");
        String frase = teclado.nextLine();

        int contador = 0;

        for (int i = 0; i < frase.length(); i++) {
            if (frase.charAt(i) == 'A' || frase.charAt(i) == 'a') {
                contador++;
            }
        }

        System.out.printf("A frase é: %s\n", frase);
        System.out.printf("A frase teve um total de: %d caracteres.\n", frase.length());
        System.out.printf("A frase em maiúsculo ficará assim: %s.\n", frase.toUpperCase());
        System.out.printf("A frase em minúsculo ficará assim: %s.\n", frase.toLowerCase());
        System.out.printf("A letra 'A' apareceu %d vezes.\n", contador);
        
        teclado.close();
    }

}