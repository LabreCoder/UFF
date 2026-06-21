import java.util.Scanner;
import java.util.InputMismatchException;

public class NewCalculadora {

    static class RaizNegativaException extends Exception {
        public RaizNegativaException() {
            super("Erro: raiz de número negativo não é permitida.");
        }
    }

    int estadoMemoria;

    public void getEstadoMemoria() {
        System.out.println("Estado da memória: " + this.estadoMemoria);
    }

    public void somar(int a) {
        System.out.println("Resultado: " + (this.estadoMemoria += a));
    }

    public void subtrair(int a) {
        System.out.println("Resultado: " + (this.estadoMemoria -= a));
    }

    public void multiplicar(int a) {
        System.out.println("Resultado: " + (this.estadoMemoria *= a));
    }

    public void dividir(int a) throws ArithmeticException {
        if (a == 0) throw new ArithmeticException("Erro: divisão por zero não é permitida.");
        System.out.println("Resultado: " + (this.estadoMemoria /= a));
    }

    public void raiz() throws RaizNegativaException {
        if (this.estadoMemoria < 0) throw new RaizNegativaException();
        double resultado = Math.sqrt(this.estadoMemoria);
        System.out.printf("Resultado: %.2f%n", resultado);
    }

    public void limparMemoria() {
        this.estadoMemoria = 0;
        System.out.println("Memória limpa.");
    }

    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        Calculadora c = new Calculadora();
        boolean executando = true;

        while (executando) {
            c.getEstadoMemoria();
            System.out.println(
                "(1) Somar\n" +
                "(2) Subtrair\n" +
                "(3) Multiplicar\n" +
                "(4) Dividir\n" +
                "(5) Raiz quadrada\n" +
                "(6) Limpar Memória\n" +
                "(7) Sair\n" +
                "Opção: "
            );

            try {
                int opcao = teclado.nextInt();
                int valor = 0;

                if (opcao >= 1 && opcao <= 4) {
                    System.out.print("Digite o valor: ");
                    valor = teclado.nextInt();
                }

                switch (opcao) {
                    case 1: c.somar(valor);     break;
                    case 2: c.subtrair(valor);  break;
                    case 3: c.multiplicar(valor); break;
                    case 4: c.dividir(valor);   break;
                    case 5: c.raiz();           break;
                    case 6: c.limparMemoria();  break;
                    case 7: executando = false; break;
                    default: System.out.println("Opção inválida.");
                }

            } catch (InputMismatchException e) {
                System.out.println("Entrada inválida. Digite um número inteiro.");
                teclado.nextLine(); // limpa o buffer
            } catch (ArithmeticException | RaizNegativaException e) {
                System.out.println(e.getMessage());
            }
        }

        teclado.close();
    }
}