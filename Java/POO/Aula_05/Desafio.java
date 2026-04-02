import java.util.Random;

public class Desafio {
    public static void main(String[] args) {
        Random random = new Random();
        int numero = random.nextInt(1, 60);
        System.out.println("Número gerado: " + numero);
    }
}