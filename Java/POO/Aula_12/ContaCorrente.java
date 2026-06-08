public class ContaCorrente {
    private float saldo = 100F;

    public static void main (String [] args){
        ContaCorrente c = new ContaCorrente();

        // Verificando o saldo atual
        c.getSaldo();

        // Depositando 100 reais
        c.Depositar(100);

        // Sacando 198.5
        c.Sacar(198.5F);

        // Sacando 200
        c.Sacar(200F);
    }

    public void getSaldo(){
        System.out.printf("Saldo atual - R$%.2f\n", this.saldo);
    }
    public float Depositar(float valor){
        this.saldo = this.saldo + valor;
        System.out.printf("Depósito de R$%.2f realizado.\n", valor);
        getSaldo();
        return this.saldo;
    }

    public float Sacar(float valor){
        float taxa = 1.5F;
        if (this.saldo>=(valor + taxa)){
            this.saldo = this.saldo - (valor + taxa);
            System.out.printf("Saque de R$%.2f realizado.\n", valor);
            getSaldo();
            return this.saldo;
        }
        System.out.printf("Saldo insuficiente para essa operação. Lembre-se que temos uma taxa de R$%.2f a ser cobrada.\n", taxa);
        getSaldo();
        return this.saldo;
    }
}

