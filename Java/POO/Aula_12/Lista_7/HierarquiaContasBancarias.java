import java.util.ArrayList;
import java.util.List;

public class HierarquiaContasBancarias {
    // =========================================================
    // Classe base abstrata
    // =========================================================

    static abstract class Conta {

        private int numero;
        protected double saldo;

        public Conta(int numero, double saldoInicial) {
            this.numero = numero;
            this.saldo = saldoInicial;
        }

        public int getNumero() {
            return numero;
        }

        public double getSaldo() {
            return saldo;
        }

        public void depositar(double valor) {
            if (valor <= 0) {
                System.out.println("Valor de depósito inválido.");
                return;
            }
            saldo += valor;
            System.out.printf("Depósito de R$ %.2f realizado. Saldo atual: R$ %.2f%n", valor, saldo);
        }

        public boolean sacar(double valor) {
            if (valor <= 0) {
                System.out.println("Valor de saque inválido.");
                return false;
            }
            if (valor > saldo) {
                System.out.printf("Saldo insuficiente. Saldo disponível: R$ %.2f%n", saldo);
                return false;
            }
            saldo -= valor;
            System.out.printf("Saque de R$ %.2f realizado. Saldo atual: R$ %.2f%n", valor, saldo);
            return true;
        }

        @Override
        public String toString() {
            return String.format("Conta #%d | Saldo: R$ %.2f", numero, saldo);
        }
    }

    // =========================================================
    // Conta Comum
    // =========================================================

    static class ContaComum extends Conta {

        public ContaComum(int numero, double saldoInicial) {
            super(numero, saldoInicial);
        }

        @Override
        public String toString() {
            return "[Conta Comum] " + super.toString();
        }
    }

    // =========================================================
    // Conta Poupança
    // =========================================================

    static class ContaPoupanca extends Conta {

        private double percentualRendimento;

        public ContaPoupanca(int numero, double saldoInicial, double percentualRendimento) {
            super(numero, saldoInicial);
            this.percentualRendimento = percentualRendimento;
        }

        public double getPercentualRendimento() {
            return percentualRendimento;
        }

        public void render() {
            double rendimento = saldo * (percentualRendimento / 100.0);
            saldo += rendimento;
            System.out.printf("Rendimento de %.2f%% aplicado: +R$ %.2f. Saldo atual: R$ %.2f%n",
                    percentualRendimento, rendimento, saldo);
        }

        @Override
        public String toString() {
            return String.format("[Conta Poupança] Conta #%d | Saldo: R$ %.2f | Rendimento: %.2f%%",
                    getNumero(), getSaldo(), percentualRendimento);
        }
    }

    // =========================================================
    // Conta Especial
    // =========================================================

    static class ContaEspecial extends Conta {

        private double limite;

        public ContaEspecial(int numero, double saldoInicial, double limite) {
            super(numero, saldoInicial);
            this.limite = limite;
        }

        public double getLimite() {
            return limite;
        }

        @Override
        public boolean sacar(double valor) {
            if (valor <= 0) {
                System.out.println("Valor de saque inválido.");
                return false;
            }
            if (valor > saldo + limite) {
                System.out.printf("Saque negado. Disponível (saldo + limite): R$ %.2f%n", saldo + limite);
                return false;
            }
            saldo -= valor;
            System.out.printf("Saque de R$ %.2f realizado. Saldo atual: R$ %.2f%n", valor, saldo);
            return true;
        }

        @Override
        public String toString() {
            return String.format("[Conta Especial] Conta #%d | Saldo: R$ %.2f | Limite: R$ %.2f",
                    getNumero(), getSaldo(), limite);
        }
    }

    // =========================================================
    // Banco
    // =========================================================

    static class Banco {

        private String nome;
        private List<Conta> contas;

        public Banco(String nome) {
            this.nome = nome;
            this.contas = new ArrayList<>();
        }

        public void adicionarConta(Conta conta) {
            contas.add(conta);
            System.out.println("Conta adicionada: " + conta);
        }

        public Conta buscarConta(int numero) {
            for (Conta c : contas) {
                if (c.getNumero() == numero) {
                    return c;
                }
            }
            return null;
        }

        public void listarContas() {
            System.out.println("\n=== Contas do " + nome + " ===");
            for (Conta c : contas) {
                System.out.println(c);
            }
            System.out.println("================================\n");
        }
    }

    // =========================================================
    // Main
    // =========================================================

    public static void main(String[] args) {

        Banco banco = new Banco("Banco UFF");

        ContaComum    contaComum    = new ContaComum(1001, 500.00);
        ContaPoupanca contaPoupanca = new ContaPoupanca(2001, 1000.00, 0.5);
        ContaEspecial contaEspecial = new ContaEspecial(3001, 200.00, 300.00);

        banco.adicionarConta(contaComum);
        banco.adicionarConta(contaPoupanca);
        banco.adicionarConta(contaEspecial);

        banco.listarContas();

        // Conta Comum
        System.out.println(">>> Conta Comum #1001");
        contaComum.depositar(150.00);
        contaComum.sacar(100.00);
        contaComum.sacar(700.00); // deve falhar
        System.out.printf("Saldo final: R$ %.2f%n%n", contaComum.getSaldo());

        // Conta Poupança
        System.out.println(">>> Conta Poupança #2001");
        contaPoupanca.depositar(500.00);
        contaPoupanca.sacar(200.00);
        contaPoupanca.render();
        contaPoupanca.sacar(5000.00); // deve falhar
        System.out.printf("Saldo final: R$ %.2f%n%n", contaPoupanca.getSaldo());

        // Conta Especial
        System.out.println(">>> Conta Especial #3001");
        contaEspecial.depositar(100.00);
        contaEspecial.sacar(250.00);  // usa saldo + entra no limite
        contaEspecial.sacar(400.00);  // deve falhar
        System.out.printf("Saldo final: R$ %.2f%n%n", contaEspecial.getSaldo());

        banco.listarContas();
    }
}
