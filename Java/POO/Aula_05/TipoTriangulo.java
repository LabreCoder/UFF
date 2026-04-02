import java.util.Scanner;

public class TipoTriangulo { 
    public static void main(String[] args){ 
        Scanner teclado = new Scanner(System.in);
        int a, b, c;

        System.out.print("Digite o valor para A: ");
        a = teclado.nextInt();
        System.out.print("Digite o valor para B: ");
        b = teclado.nextInt();
        System.out.print("Digite o valor para C: ");
        c = teclado.nextInt();
        if ((a < (b + c)) && (b < (a + c)) && (c < (a + b))){
            if ((a == b && b == c)){
                System.out.println("O triângulo é Equilátero!");
            }
            else if ((a == b) || (a == c) || (b == c)){
                System.out.println("O triângulo é Isósceles!");
            }
            else{
                System.out.println("O triângulo é Escaleno!");
            }
        }
        else{
            System.out.println("Isso não é um triângulo :( \n");
        }
        teclado.close();
    }

}
