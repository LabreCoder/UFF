import java.util.List;
import java.util.ArrayList;

public class FraseInvertida {

    public String fraseComInversao(String frase) {
        List<Character> letras = new ArrayList<>();

        for (char l : frase.toCharArray()) {
            letras.add(l);
        }

        for (int i = letras.size() - 1; i >= 0; i--) {
            System.out.print(letras.get(i));
        }

        System.out.println();

        return frase;
    }

    public static void main(String[] args) {
        String frase = "Frase Invertida";

        FraseInvertida obj = new FraseInvertida();
        String teste = obj.fraseComInversao(frase);
    }
}