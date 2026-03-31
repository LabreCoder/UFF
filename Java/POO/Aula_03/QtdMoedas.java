import java.util.Scanner;

public class QtdMoedas{// Moedas
    public static void main(String [] args){
        int a =  0;
        System.out.println("Digite um numero: ");
        try (Scanner teclado = new Scanner(System.in)) {

        a = teclado.nextInt();
        if (a / 100 != 0){
            if (a / 100 == 1){
                System.out.printf("%s moeda de 1 real\n", a / 100);
            }
            else {
                System.out.printf("%s moedas de 1 real\n", a / 100);
                a = a % 100;
            }
        }
        else {
            System.out.printf("Nenhuma de 1 real\n", a / 100);
        }
        if (a / 50 != 0){
            if (a / 50 == 1){
                System.out.printf("%s moeda de 50 centavos\n", a / 50);
            }
            else {
                System.out.printf("%s moedas de 50 centavos\n", a / 50);
                a = a % 50;
            }
        }
        else {
            System.out.printf("Nenhuma de 50 centavos\n", a / 50);
        }
        if (a / 25 != 0){
            if (a / 25 == 1){
                System.out.printf("%s moeda de 25 centavos\n", a / 25);
            }
            else {
                System.out.printf("%s moedas de 25 centavos\n", a / 25);
            }
            a = a % 25;
        }
        else {
            System.out.printf("Nenhuma de 25 centavos\n", a / 25);
        }
        if (a / 10 != 0){
            if (a / 10 == 1){
                System.out.printf("%s moeda de 10 centavos\n", a / 10);
            }
            else {
                System.out.printf("%s moedas de 10 centavos\n", a / 10);
            }
            a = a % 10;
        }
        else {
            System.out.printf("Nenhuma de 10 centavos\n", a / 10);
        }
        if (a / 5 != 0){
            if (a / 5 == 1){
                System.out.printf("%s moeda de 5 centavos\n", a / 5);
            }
            else {
                System.out.printf("%s moedas de 5 centavos\n", a / 5);
            }
            a = a % 5;
        }
        else {
            System.out.printf("Nenhuma de 5 centavos\n", a / 5);
        }
        if (a / 1 != 0){
            if (a / 1 == 1){
                System.out.printf("%s moeda de 1 centavo\n", a / 1);
            }
            else {
                System.out.printf("%s moedas de 1 centavo\n", a / 1);
            }
        }
        else {
            System.out.printf("Nenhuma de 1 centavo\n", a / 1);
        }

        }
    }
}