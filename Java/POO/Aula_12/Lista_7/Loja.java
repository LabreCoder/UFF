abstract class UsuarioAbstrato {
    protected String nome;
    protected String senha;

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setSenha(String senha) {
        this.senha = senha;
    }

    public String getNome() {
        return this.nome;
    }

    protected String getSenha() {
        return this.senha;
    }
}

class Cliente extends UsuarioAbstrato {
    private final String cpf;
    private final String matricula;
    private String email;
    private String telefone;

    public Cliente(String cpf, String matricula) {
        this.cpf = cpf;
        this.matricula = matricula;
    }

    public String getCpf() {
        return cpf;
    }

    public String getMatricula() {
        return matricula;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getTelefone() {
        return telefone;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }
}

class Funcionario extends UsuarioAbstrato {
    private final String matricula;

    public Funcionario(String matricula) {
        this.matricula = matricula;
    }

    public String getMatricula() {
        return matricula;
    }

    public void realizarVenda(String produto, double valor) {
        System.out.println("Venda realizada por " + getNome() +
                ": Produto = " + produto + ", Valor = R$" + valor);
    }

    public void cancelarVenda(int idVenda) {
        System.out.println("Venda #" + idVenda + " cancelada por " + getNome());
    }

    public void consultarEstoque(String produto) {
        System.out.println("Consultando estoque do produto: " + produto);
    }
}

class Gerente extends Funcionario {

    public Gerente(String matricula) {
        super(matricula);
    }

    public void fecharCaixa(double totalVendas) {
        System.out.println("Caixa fechado por " + getNome() +
                ". Total em vendas: R$" + totalVendas);
    }

    public void gerarRelatorio() {
        System.out.println("Relatório gerado pelo gerente " + getNome());
    }
}

public class Loja {
    public static void main(String[] args) {

        // --- Cliente ---
        Cliente cliente = new Cliente("123.456.789-00", "MAT001");
        cliente.setNome("João Silva");
        cliente.setSenha("senha123");
        cliente.setEmail("joao@email.com");
        cliente.setTelefone("(21) 99999-0000");

        System.out.println("=== CLIENTE ===");
        System.out.println("Nome: " + cliente.getNome());
        System.out.println("CPF: " + cliente.getCpf());
        System.out.println("Matrícula: " + cliente.getMatricula());
        System.out.println("Email: " + cliente.getEmail());
        System.out.println("Telefone: " + cliente.getTelefone());

        // --- Funcionário ---
        Funcionario funcionario = new Funcionario("FUNC001");
        funcionario.setNome("Maria Souza");
        funcionario.setSenha("func456");

        System.out.println("\n=== FUNCIONÁRIO ===");
        System.out.println("Nome: " + funcionario.getNome());
        funcionario.realizarVenda("Notebook", 3500.00);
        funcionario.consultarEstoque("Mouse");

        // --- Gerente ---
        Gerente gerente = new Gerente("GER001");
        gerente.setNome("Carlos Lima");
        gerente.setSenha("ger789");

        System.out.println("\n=== GERENTE ===");
        System.out.println("Nome: " + gerente.getNome());
        gerente.realizarVenda("Teclado", 250.00);
        gerente.fecharCaixa(15000.00);
        gerente.gerarRelatorio();
    }
}