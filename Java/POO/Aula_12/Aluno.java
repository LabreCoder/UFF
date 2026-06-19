public class Aluno {
    private String nome;
    private double trabalho1;
    private double p1;
    private double trabalho2;
    private double p2;

    public Aluno(String nome, double trabalho1, double p1, double trabalho2, double p2) {
        this.nome = nome;
        this.trabalho1 = trabalho1;
        this.p1 = p1;
        this.trabalho2 = trabalho2;
        this.p2 = p2;
    }

    public double calcularMedia() {
        return (trabalho1 + p1 + trabalho2 + p2) / 4;
    }

    public String status() {
        double media = calcularMedia();

        if (media > 6) {
            return "Aprovado";
        } else if (media >= 4) {
            return "Verificação Suplementar";
        } else {
            return "Reprovado";
        }
    }

    public void imprime() {
        System.out.println("Aluno: " + nome);
        System.out.printf("Notas -> T1: %.1f | P1: %.1f | T2: %.1f | P2: %.1f%n",
                trabalho1, p1, trabalho2, p2);
        System.out.printf("Média: %.2f%n", calcularMedia());
        System.out.println("Status: " + status());
        System.out.println("-----------------------------");
    }

    public static void main(String[] args) {
        Aluno a1 = new Aluno("Ana",    8.0, 7.5, 9.0, 8.5);
        Aluno a2 = new Aluno("Bruno",  5.0, 4.0, 6.0, 4.5);
        Aluno a3 = new Aluno("Carlos", 3.0, 2.5, 4.0, 3.5);
        Aluno a4 = new Aluno("Diana",  6.0, 6.0, 6.0, 6.0); // exatamente 6 → VS

        a1.imprime();
        a2.imprime();
        a3.imprime();
        a4.imprime();
    }
}