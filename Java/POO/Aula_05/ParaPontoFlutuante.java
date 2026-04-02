import java.util.Scanner;

public class ParaPontoFlutuante { // converter para ponto flutuante
    public static void main(String[] args){ 
        Scanner teclado = new Scanner(System.in);

        float a, b, soma, subtracao, multiplicacao, divisao;
        System.out.printf("Atribua um valor para a variável A: ");
        a = teclado.nextInt();

        System.out.printf("Atribua um valor para a variável B: ");
        b = teclado.nextInt();
        teclado.close();

        soma = a + b;
        multiplicacao = a * b;
        divisao =  a/b;

        System.out.printf("A soma de A e B é: %.2f\n", soma);
        if (a > b) {
            subtracao = a - b;
            System.out.printf("A subtração de A e B é: %.2f\n", subtracao);
        }
        else{
            subtracao = b - a;
            System.out.printf("A subtração de B e A é: %.2f\n", subtracao);

        }
        System.out.printf("A multiplicação de A e B é: %.2f\n", multiplicacao);
        System.out.printf("A divisão de A e B é: %.2f\n", divisao);
        
    }

}
