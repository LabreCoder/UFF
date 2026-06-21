public class Salario {

    abstract static class Funcionario {
        private String nome;
        private double salarioBruto;

        public Funcionario(String nome, double salarioBruto) {
            this.nome = nome;
            this.salarioBruto = salarioBruto;
        }

        public String getNome() { return nome; }
        public double getSalarioBruto() { return salarioBruto; }

        // Base de cálculo do IR (pode ser sobrescrita)
        protected double getBaseIR() {
            return salarioBruto;
        }

        protected double calcularIR() {
            double base = getBaseIR();
            if (base <= 900) return 0;
            if (base <= 1500) return base * 0.15;
            return base * 0.20;
        }

        public double getSalarioLiquido() {
            return getBaseIR() - calcularIR();
        }

        @Override
        public String toString() {
            return String.format(
                "%s | Bruto: R$ %.2f | IR: R$ %.2f | Líquido: R$ %.2f",
                nome, getSalarioBruto(), calcularIR(), getSalarioLiquido()
            );
        }
    }

    static class Estagiario extends Funcionario {
        public Estagiario(String nome, double salarioBruto) {
            super(nome, salarioBruto);
        }

        @Override
        protected double calcularIR() {
            return 0; // estagiários não pagam IR
        }

        @Override
        public String toString() {
            return "[Estagiário] " + super.toString();
        }
    }

    static class Vendedor extends Funcionario {
        private double percentualBonus;

        public Vendedor(String nome, double salarioBruto, double percentualBonus) {
            super(nome, salarioBruto);
            this.percentualBonus = percentualBonus;
        }

        public double getBonus() {
            return getSalarioBruto() * (percentualBonus / 100);
        }

        @Override
        protected double getBaseIR() {
            return getSalarioBruto() + getBonus(); // IR sobre bruto + bônus
        }

        @Override
        public String toString() {
            return String.format(
                "[Vendedor] %s | Bônus: R$ %.2f",
                super.toString(), getBonus()
            );
        }
    }

    public static void main(String[] args) {
        Funcionario[] funcionarios = {
            new Funcionario("Carlos", 800) {},    // anônimo, funcionário comum
            new Funcionario("Ana", 1200) {},
            new Funcionario("Pedro", 2000) {},
            new Estagiario("Joana", 1800),
            new Vendedor("Lucas", 1200, 30)       // 30% de bônus
        };

        for (Funcionario f : funcionarios) {
            System.out.println(f);
        }
    }
}