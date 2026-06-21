import java.util.Scanner;

class ContadorPrimos extends Thread {

    private int inicio;
    private int fim;
    private int quantidadePrimos;

    public ContadorPrimos(int inicio, int fim) {
        this.inicio = inicio;
        this.fim = fim;
        this.quantidadePrimos = 0;
    }

    @Override
    public void run() {
        for (int i = inicio; i <= fim; i++) {
            if (ehPrimo(i)) {
                quantidadePrimos++;
            }
        }
    }

    public int getQuantidadePrimos() {
        return quantidadePrimos;
    }

    private boolean ehPrimo(int numero) {
        if (numero < 2) {
            return false;
        }

        for (int i = 2; i <= Math.sqrt(numero); i++) {
            if (numero % i == 0) {
                return false;
            }
        }

        return true;
    }
}

public class PrimosComThreads {

    public static void main(String[] args) throws InterruptedException {

        Scanner scanner = new Scanner(System.in);

        System.out.print("Digite um número: ");
        int n = scanner.nextInt();

        int meio = n / 2;

        ContadorPrimos thread1 = new ContadorPrimos(0, meio);
        ContadorPrimos thread2 = new ContadorPrimos(meio + 1, n);

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        int totalPrimos =
            thread1.getQuantidadePrimos() +
            thread2.getQuantidadePrimos();

        System.out.println(
            "Quantidade de números primos entre 0 e " +
            n + ": " + totalPrimos
        );

        scanner.close();
    }
}