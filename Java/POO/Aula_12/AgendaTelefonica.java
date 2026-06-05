public class AgendaTelefonica {
    public static void main(String[] args){
        // Criando uma agenda
        Agenda agenda = new Agenda();

        // Definindo os contatos
        Contato contato = new Contato("João", "123456");
        Contato contato2 = new Contato("Bea", "987654321");
        Contato contato3 = new Contato("Ana", "987654321");

        // Adicionando os contatos à Agenda
        agenda.setContato(contato);
        agenda.setContato(contato2);
        agenda.setContato(contato3);
        
        // Imprimindo os contatos existentes
        System.out.println();
        agenda.getContatos();
        System.out.println();

        // Excluindo um contato
        agenda.excluirContato(contato2);
        
        System.out.println();
        agenda.getContatos();
        System.out.println();
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------

class Agenda{
    // O que podemos ter dentro de uma agenda?
    // Contatos - nome e telefone
    // O que podemos fazer dentro da Agenda?
    // Listar os contatos; editar um contato e apagar um contato
    private Contato[] contatos = new Contato[100]; // Defini uma Array com no máximo 100 contatos
    public int contatosId = 0;

    public void setContato(Contato contato){

        if(contatoExiste(contato)){
            System.out.println("\nContato já existe.");
            return;
        }

        contatos[contatosId] = contato;
        contatosId++;

        System.out.printf("\nContato %s adicionado com sucesso.", contato.getNome());
    }

    public void getContatos(){ // Irá listar os contatos
        if (contatosId > 0){
            for (int i = 0; i < contatosId; i++){
                Contato c = contatos[i];

                System.out.printf("\nContato id: %d   |   Nome: %s    |   Número: %s",
                    i + 1, // Eu coloquei o valor começando a partir de 1 para ficar visivelmente melhor
                    c.getNome(),
                    c.getNumero()
                );
            }
        }
        else{ System.out.println("\nAinda não foi adicionado nenhum contato."); }
    }

    public void editNome(Contato contato, String newNome){
        for (int i = 0; i < contatosId; i++){
            Contato c = contatos[i];
            boolean inList = (c.getNome().equals(contato.getNome())) && (c.getNumero().equals(contato.getNumero()));
            if (inList){
                c.updateNome(newNome);
                System.out.print("\nNome atualizado");
            }
            else{ System.out.println("\nContato não encontrado");}
        }
    }

    public void editNumero(Contato contato, String newNumero){
        for (int i = 0; i < contatosId; i++){
            Contato c = contatos[i];            
            if ((c.getNome().equals(contato.getNome())) && (c.getNumero().equals(contato.getNumero()))){
                c.updateNumero(newNumero);
                System.out.print("\nNúmero atualizado");
            }
            else{ System.out.println("\nContato não encontrado");}

        }
    }

    private boolean contatoExiste(Contato contato){
        for(int i = 0; i < contatosId; i++){

            boolean mesmoNome = contatos[i].getNome().equals(contato.getNome());

            boolean mesmoNumero = contatos[i].getNumero().equals(contato.getNumero());

            if(mesmoNome && mesmoNumero){
                return true;
            }
        }

        return false;
    }

    public void excluirContato(Contato contato){

        int indice = -1;
        for(int i = 0; i < contatosId; i++){

            if(contatos[i].getNome().equals(contato.getNome()) && contatos[i].getNumero().equals(contato.getNumero())){
                indice = i;
                break;
            }
        }

        if(indice == -1){
            System.out.println("\nContato não encontrado.");
            return;
        }

        for(int i = indice; i < contatosId - 1; i++){
            contatos[i] = contatos[i + 1];
        }

        contatos[contatosId - 1] = null;
        contatosId--;

        System.out.printf("\nContato %s removido.", contato.getNome());
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------

class Contato{
    private String nome;
    private String numero;

    public Contato(String nome, String numero){
        this.nome = nome;
        this.numero = numero;
    }
    /*
    public void getContato(){
        System.out.println("Contato");
        getNome();
        getNumero();
    }
    */

    public String getNome(){
        return this.nome;
    }

    public String getNumero(){
        return this.numero;
    }

    public void updateNome(String novoNome){
        this.nome = novoNome;
    }

    public void updateNumero(String novoNumero){
        this.numero = novoNumero;
    }
}