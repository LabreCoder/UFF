import java.util.Scanner;

public class Exercicio_02{// Celsius para Fahrenheit
    public static void main(String [] args){
        double C =  0;
        double F = 0;
        System.out.println("Digite a temperatura em Celsius: ");
        try (Scanner teclado = new Scanner(System.in)) {
            C = teclado.nextDouble();
            F = (C * 1.8) + 32;
            System.out.printf("%f graus C equivalem a %f graus F\n", C, F);
        }
    }
}