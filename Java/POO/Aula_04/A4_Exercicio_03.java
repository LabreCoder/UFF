
public class A4_Exercicio_03{
    public static void main(String[] args) {    
        int i = 1, j = 2, k = 3;

        i = i > k ? i : k; // 3
        System.out.println("O valor de i é igual à: " + i);

        i = i > 0 ? j : k; // 2
        System.out.println("O valor de i é igual à: " + i);

        i = j > i ? ++k : --k; // 2
        System.out.println("O valor de i é igual à: " + i);

        i = (k == i && k != j) ? i + j : i - j; // 0
        System.out.println("O valor de i é igual à: " + i);
    }

}
