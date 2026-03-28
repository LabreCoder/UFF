import java.util.Scanner;

public class A5_Exercicio_01 { //
    public static void main(String[] args){ 
        Scanner teclado = new Scanner(System.in);

        int a, b, soma, subtracao, multiplicacao, divisao;
        System.out.printf("Atribua um valor para a variável A: ");
        a = teclado.nextInt();

        System.out.printf("Atribua um valor para a variável B: ");
        b = teclado.nextInt();
        teclado.close();

        soma = a + b;
        subtracao = a - b;
        multiplicacao = a * b;
        divisao = a/b;

        System.out.printf("A soma de A e B é: %d\n", soma);
        System.out.printf("A subtração de A e B é: %d\n", subtracao);
        System.out.printf("A multiplicação de A e B é: %d\n", multiplicacao);
        System.out.printf("A divisão de A e B é: %d\n", divisao);
        
    }

}
