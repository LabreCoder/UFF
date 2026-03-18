import java.util.Scanner;

public class GrauCelcius{
    public static void main(String [] args){
        double C =  0;
        double F = 0;
        System.out.println("Digite a temperatura em Celsius: ");
        Scanner teclado = new Scanner(System.in);
        C = teclado.nextDouble();
        F = (C * 1.8) + 32;
        System.out.printf("%s graus C equivalem a %s graus F\n", C, F);

    }
}