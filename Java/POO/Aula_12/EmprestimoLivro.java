public class EmprestimoLivro {
    public static void main (String[] args){

        // Definindo as pessoas
        Pessoa joao = new Pessoa("João");
        Pessoa bea = new Pessoa("Bea");
        Pessoa ana = new Pessoa("Ana");

        // Definindo os Livros
        Livro madagascar = new Livro("Madagascar");
        Livro guerraNasEstrelas = new Livro("Star Wars");
        Livro sherlock = new Livro("Sherlock Holmes");

        // Definindo os Empréstimos
        Emprestimo emprestimo = new Emprestimo(joao, madagascar);
        Emprestimo emprestimo1 = new Emprestimo(bea, sherlock);
        Emprestimo emprestimo2 = new Emprestimo(ana, guerraNasEstrelas);

        // Definindo uma devolução
        emprestimo.devolverEmprestimo(joao);

        // Testando a devolução de um Livro já devolvido
        emprestimo.devolverEmprestimo(joao);
    }
}

class Emprestimo {
    private Livro livro;
    private Pessoa pessoa;

    public Emprestimo(Pessoa pessoa, Livro livro){
        this.livro = livro;
        this.pessoa = pessoa;
        solicitarEmprestimo(pessoa, livro);
    }

    private void solicitarEmprestimo(Pessoa pessoa, Livro livro){
        pessoa.pegarLivro(livro);
    }

    public void devolverEmprestimo(Pessoa pessoa){
        if (this.pessoa == pessoa){
            pessoa.devolverLivro(this.livro);
        } else {
            System.out.printf("%s não pode devolver o livro %s pois ele não é seu.\n", pessoa.getNome(), this.livro.getNome());
        }
    }
}

class Livro {
    private final String nome;
    private boolean emprestado = false;

    public Livro(String nome) {
        this.nome = nome;
    }

    public String getNome(){
        return this.nome;
    }

    public boolean emprestado(){
        return this.emprestado;
    }

    public void setEmprestimo(String nomeSolicitante){
        if (!emprestado()){
            System.out.printf("O livro %s está sendo emprestado para: %s.\n", this.nome, nomeSolicitante);
            this.emprestado = true;
            return;
        }
        System.out.printf("Livro %s já foi emprestado.\n", this.nome);
    }

    public void setDevolucao(String nomeSolicitante){
        if (this.emprestado){
            System.out.printf("O livro %s está sendo devolvido por: %s.\n", this.nome, nomeSolicitante);
            this.emprestado = false;
            return;
        }
        System.out.printf("Livro %s já foi devolvido.\n", this.nome);
    }
}

class Pessoa {
    private String nome;

    public Pessoa(String nome){
        this.nome = nome;
    }

    public String getNome(){
        return this.nome;
    }

    public void pegarLivro(Livro livro){
        livro.setEmprestimo(this.nome);
    }

    public void devolverLivro(Livro livro){
        livro.setDevolucao(this.nome);
    }
}