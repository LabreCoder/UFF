import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class ContadorPalavras {

    public void contarOcorrencias(String frase) {

        char[] caracteresRemover = {
                '.', ',', ';', ':', '!', '?',
                '(', ')', '[', ']', '{', '}',
                '"', '\''
        };

        for (char c : caracteresRemover) {
            frase = frase.replace(String.valueOf(c), "");
        }

        String[] palavras = frase.split(" ");

        Map<String, Integer> contagem = new HashMap<>();

        for (String palavra : palavras) {
            palavra = palavra.toLowerCase();

            contagem.put(
                    palavra,
                    contagem.getOrDefault(palavra, 0) + 1
            );
        }

        System.out.println("Ocorrências de cada palavra:");

        for (String palavra : contagem.keySet()) {
            System.out.println(palavra + ": " + contagem.get(palavra));
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Digite uma frase: ");
        String frase = scanner.nextLine();

        ContadorPalavras obj = new ContadorPalavras();
        obj.contarOcorrencias(frase);

        scanner.close();
    }
}