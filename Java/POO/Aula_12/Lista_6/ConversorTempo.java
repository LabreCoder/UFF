import java.util.Scanner;

public class ConversorTempo {
    private int totalSegundos;

    public ConversorTempo(int totalSegundos) {
        this.totalSegundos = totalSegundos;
    }

    // ── Leitura ──────────────────────────────────────────────
    public static int lerSegundos() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Digite o tempo em segundos: ");
        int segundos = sc.nextInt();
        sc.close();
        return segundos;
    }

    // ── Cálculos ─────────────────────────────────────────────
    public int getHoras() {
        return totalSegundos / 3600;
    }

    public int getMinutos() {
        return (totalSegundos % 3600) / 60;
    }

    public int getSegundos() {
        return totalSegundos % 60;
    }

    // ── Escrita ───────────────────────────────────────────────
    public void imprime() {
        System.out.printf("%d segundo(s) equivale a: %dh %dm %ds%n",
                totalSegundos, getHoras(), getMinutos(), getSegundos());
    }

    // ── Main ──────────────────────────────────────────────────
    public static void main(String[] args) {
        int entrada = lerSegundos();
        ConversorTempo tempo = new ConversorTempo(entrada);
        tempo.imprime();
    }
}