import java.util.Scanner;

public class Calculadora{
    int estadoMemoria;

    public void getEstadoMemoria(){
        System.out.println("Estado da memória: " + this.estadoMemoria);
    }
    public void somar(int a){
        System.out.println("O valor da soma é: " + (this.estadoMemoria += a));
    }
    public void subtrair(int a){
        if (a > this.estadoMemoria) {
            System.out.println("O valor não pode ser maior que o estado de memória.");
            return;
        }
        System.out.println("O valor da subtração é: " + (this.estadoMemoria -= a));
    }
    public void multiplicar(int a){
        System.out.println("O valor da multiplicação é: " + (this.estadoMemoria *= a));
    }
    public void dividir(int a){
        if (a <= 0){
            System.out.println("Valor inválido para realizar a divisão.");
            return;
        }
        System.out.println("O valor da divisão é: " + (this.estadoMemoria /=a));
    }
    public void limparMemoria(){
        this.estadoMemoria = 0;
    }

    public static void main(String[] args){
        Scanner teclado = new Scanner(System.in);
        Calculadora c = new Calculadora();

        boolean executando = true;

        while (executando){
            c.getEstadoMemoria();
            System.out.println("Opções: ");

            System.out.println("(1) Somar\n" +
                    "(2) Subtrair\n" +
                    "(3) Multiplicar\n" +
                    "(4) Dividir\n" +
                    "(5) Limpar Memória\n" +
                    "(6) Sair do programa\n" +
                    "Qual opção você deseja?\n");
            int opcao = teclado.nextInt();
            int valor = 0;
            if  (opcao < 5) {
                System.out.println("Digite o valor desejado para operar com o estado de memória: ");
                valor = teclado.nextInt();
            }

            switch (opcao){
                case 1:
                    c.somar(valor);
                    break;
                case 2:
                    c.subtrair(valor);
                    break;
                case 3:
                    c.multiplicar(valor);
                    break;
                case 4:
                    c.dividir(valor);
                    break;
                case 5:
                    c.limparMemoria();
                    break;
                case 6:
                    executando = false;
                    break;
                default:
                    System.out.println("Por favor, escolha uma das opções viáveis.");
            }
        }
        teclado.close();
    }
}