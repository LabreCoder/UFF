import java.util.Scanner;

public class OrdemPessoas { // Serão criados dois vetores, um com o nome de cada pessoa e o outro com a idade respectiva. Após isso iremos realizar algumas ordenações
    public static void main(String[] args){
        Scanner teclado = new Scanner(System.in);

        int tamanho_vetores = 10;

        String[] nome_pessoas = new String[tamanho_vetores];
        int[] idade_pessoas = new int[tamanho_vetores];


        for (int i = 0; i < tamanho_vetores; i++){ // Entrada de dados
            System.out.print("Digite o nome da pessoa: ");
            nome_pessoas[i] = teclado.nextLine();

            System.out.print("Digite a idade da pessoa: ");
            idade_pessoas[i] = teclado.nextInt();
            teclado.nextLine();
        }

        for (int i = 0; i < tamanho_vetores - 1; i++){ // iremos ordenar por ordem alfabética
            for (int j = 0; j < tamanho_vetores - 1 - i; j++){
                if (nome_pessoas[j].compareTo(nome_pessoas[j + 1]) > 0){

                    // troca nomes
                    String tempNome = nome_pessoas[j];
                    nome_pessoas[j] = nome_pessoas[j + 1];
                    nome_pessoas[j + 1] = tempNome;

                    // troca idades junto
                    int tempIdade = idade_pessoas[j];
                    idade_pessoas[j] = idade_pessoas[j + 1];
                    idade_pessoas[j + 1] = tempIdade;
                }
            }
        }

        System.out.println("\nOrdenado por nome:");
        for (int i = 0; i < tamanho_vetores; i++){
            System.out.println(nome_pessoas[i] + " - " + idade_pessoas[i]);
        }

        for (int i = 0; i < tamanho_vetores - 1; i++){ // iremos ordenar por idade crescente
            for (int j = 0; j < tamanho_vetores - 1 - i; j++){
                if (idade_pessoas[j] > idade_pessoas[j + 1]){

                    // troca idades
                    int tempIdade = idade_pessoas[j];
                    idade_pessoas[j] = idade_pessoas[j + 1];
                    idade_pessoas[j + 1] = tempIdade;

                    // troca nomes junto
                    String tempNome = nome_pessoas[j];
                    nome_pessoas[j] = nome_pessoas[j + 1];
                    nome_pessoas[j + 1] = tempNome;
                }
            }
        }

        System.out.println("\nOrdenado por idade:");
        for (int i = 0; i < tamanho_vetores; i++){
            System.out.println(nome_pessoas[i] + " - " + idade_pessoas[i]);
        }
    teclado.close();
    }
}