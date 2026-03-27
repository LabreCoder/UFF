
public class A4_Exercicio_04{
    public static void main(String[] args) {    
        System.out.println("O resultado de '5 * 4 / 6 + 7' é: " + (5 * 4 / 6 + 7)); // 10
        System.out.println("O resultado de '5 * 4 / (6 + 7)' é: " + (5 * 4 / (6 + 7))); // 1
        System.out.println("O resultado de '5 * 4.0 / 6 + 7' é: " + (5 * 4.0 / 6 + 7)); // 10.333
        System.out.println("O resultado de '5 * 4 % 6 + 7' é: " + (5 * 4 % 6 + 7)); // 9
        System.out.println("O resultado de '5 * 4 / (float)6 + 7' é: " + (5 * 4 / (float)6 + 7)); // 10.333
        System.out.println("O resultado de '(4 / 3) + (3.0 * 5)' é: " + ((4 / 3) + (3.0 * 5))); // 16.0
        System.out.println("O resultado de '(4 / 3.0) + (3 * 5)' é: " + ((4 / 3.0) + (3 * 5))); // 16.333
        System.out.println("O resultado de '(int)(4 / 3.0) + (3 * 5)' é: " + ((int)(4 / 3.0) + (3 * 5))); // 16
    }

}
