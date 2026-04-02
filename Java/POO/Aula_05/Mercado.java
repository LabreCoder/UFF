import java.util.Scanner;


public class Mercado { // o programa irá calcular se o cliente tem desconto ou não
    public static void main(String[] args){ 
        Scanner teclado = new Scanner(System.in);
        
        System.out.print("Digite o nome do produto desejado: ");
        String nome_produto = teclado.nextLine();
        
        System.out.print("Digite o preço do produto: ");
        float preço_produto = teclado.nextFloat();
        
        System.out.print("Digite a quantidade do produto desejado: ");
        int quantidade_produto = teclado.nextInt();
        
        System.out.println("Produto: " + nome_produto);
        System.err.println("Quantidade: " + quantidade_produto);
        
        if (quantidade_produto <= 10 && quantidade_produto > 0) {
            System.out.printf("Preço: R$%.2f\n", preço_produto);
        } else if (quantidade_produto >= 11 && quantidade_produto <= 20) {
            System.out.printf("Preço: R$%.2f\n", preço_produto*0.90);
        } else if (quantidade_produto >= 21 && quantidade_produto <= 50) {
            System.out.printf("Preço: R$%.2f\n", preço_produto*0.80); 
        }else if (quantidade_produto > 50) {
            System.out.printf("Preço: R$%.2f\n" , preço_produto*0.75); 
        } else {
            System.out.println("Quantidade inválida.");
        }

        teclado.close();
    }

}
