import java.util.HashSet;
import java.util.Set;

public class PalavrasNaoRepetidas {

    public int contarPalavrasNaoRepetidas(String frase) {
        Set<String> palavras = new HashSet<>();

        for (String palavra : frase.split(" ")) {
            palavras.add(palavra.toLowerCase());
        }

        return palavras.size();
    }

    public static void main(String[] args) {
        String frase = "java é legal java é divertido, mas é java";

        PalavrasNaoRepetidas obj = new PalavrasNaoRepetidas();

        System.out.println(
            "Quantidade de palavras não repetidas: "
            + obj.contarPalavrasNaoRepetidas(frase)
        );
    }
}