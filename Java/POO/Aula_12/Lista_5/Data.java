import java.time.Year;

public class Data {
    private int dia;
    private int mes;
    private int ano;

    public Data(int dia, int mes, int ano) {
        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
    }

    public boolean dataValida() {
        // Verifica se mês está entre 1 e 12
        if (mes < 1 || mes > 12) {
            return false;
        }

        // Verifica se o dia é ao menos 1
        if (dia < 1) {
            return false;
        }

        // Fevereiro: depende se é bissexto
        if (mes == 2) {
            int maxDia = anoBissexto() ? 29 : 28;
            return dia <= maxDia;
        }

        // Meses com 30 dias: abril(4), junho(6), setembro(9), novembro(11)
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            return dia <= 30;
        }

        // Demais meses têm 31 dias
        return dia <= 31;
    }

    // Versão que evita recursão infinita
    public boolean anoBissexto() {
        // Verifica apenas o ano, sem chamar dataValida()
        if (mes < 1 || mes > 12 || dia < 1) return false;
        return Year.isLeap(ano);
    }

    // Imprime com separador definido pelo usuário
    public void imprime(char separador) {
        if (dataValida()) {
            System.out.printf("%02d%c%02d%c%d%n", dia, separador, mes, separador, ano);
        } else {
            System.out.println("INVÁLIDA");
        }
    }

    // Imprime com separador default "/"
    public void imprime() {
        imprime('/');
    }

    public static void main(String[] args) {
        Data d1 = new Data(29, 2, 2024); // Ano bissexto: válida
        Data d2 = new Data(29, 2, 2023); // Não bissexto: inválida
        Data d3 = new Data(31, 4, 2023); // Abril tem 30 dias: inválida
        Data d4 = new Data(15, 8, 2023); // Válida

        System.out.println("=== Separador default '/' ===");
        d1.imprime();
        d2.imprime();
        d3.imprime();
        d4.imprime();

        System.out.println("\n=== Separador '-' ===");
        d1.imprime('-');
        d4.imprime('-');

        System.out.println("\n=== Ano Bissexto ===");
        System.out.println("29/02/2024 é bissexto? " + d1.anoBissexto());
        System.out.println("29/02/2023 é bissexto? " + d2.anoBissexto());
    }
}