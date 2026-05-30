public class ClassMercado {
    public static void main(String[] args) {

        // Aqui iremos definir os produtos, sua quantidade dentro do estoque e também o seu preço
        Produtos[] estoque = new Produtos[4];

        estoque[0] = new Produtos("Arroz",    100, 5.99f);
        estoque[1] = new Produtos("Feijão",   50,  8.50f);
        estoque[2] = new Produtos("Macarrão", 200, 3.25f);
        estoque[3] = new Produtos("Azeite",   30,  25.00f);
        
        Mercado mercado = new Mercado(estoque);
        mercado.exibirEstoque();

        // Criamos um cliente e também realizamos uma um pedido
        Cliente cliente = new Cliente("João");

        String[] itensDesejados_1   = {"Arroz", "Feijão"};
        int[]    quantDesejadas_1   = {1, 10};
        String[] itensDesejados_2   = {"Macarrão", "Azeite"};
        int[]    quantDesejadas_2   = {100, 10};
        cliente.setPedido(itensDesejados_1, quantDesejadas_1, mercado);
        cliente.setPedido(itensDesejados_2, quantDesejadas_2, mercado);

        // Exibe os pedidos
            cliente.exibirTodosPedidos();
            System.out.println("\n--- Estoque após os pedidos ---");
            mercado.exibirEstoque();
    }
}

// -------------------------------------------------------

class Produtos {
    private final String item;
    private int quantidade;
    private float preco;  // final: ninguém muda o preço após criação

    public Produtos(String item, int quantidade, float preco) {
        this.item = item;
        this.quantidade = quantidade;
        this.preco = preco;
    }

    public String getItem() {
        return this.item;
    }

    public int getQuantidade() {
        return this.quantidade;
    }

    public float getPreco() {
        return this.preco;
    }

    // Tenta baixar do estoque — retorna false se não houver quantidade suficiente
    public boolean baixarEstoque(int quantidade) {
        if (quantidade <= 0) {
            System.out.println("Quantidade inválida para o item: " + this.item);
            return false;
        }
        if (quantidade > this.quantidade) {
            System.out.printf("Estoque insuficiente para '%s'. Disponível: %d, Solicitado: %d%n", this.item, this.quantidade, quantidade);
            return false;
        }
        this.quantidade -= quantidade;
        return true;
    }
}

// -------------------------------------------------------

class Mercado {
    private Produtos[] estoque;

    public Mercado(Produtos[] estoque) {
        this.estoque = estoque;
    }

    // Busca um produto pelo nome — retorna null se não encontrar
    public Produtos buscarProduto(String nomeItem) {
        for (Produtos p : estoque) {
            if (p.getItem().equalsIgnoreCase(nomeItem)) {
                return p;
            }
        }
        return null;
    }

    public void exibirEstoque() {
        System.out.println("\n=== Estoque do Mercado ===");
        for (Produtos p : estoque) {
            System.out.printf("  %-10s | Qtd: %3d | Preço: R$%.2f%n",
                    p.getItem(), p.getQuantidade(), p.getPreco());
        }
    }
}

// -------------------------------------------------------

class Pedido {
    private int id;
    private Produtos[] itensDoPedido;
    private int[] quantidadesDoPedido;
    private int totalItens;

    public Pedido(int id, String[] itens, int[] quantidades, Mercado mercado) {
        this.id = id;
        this.itensDoPedido = new Produtos[itens.length];
        this.quantidadesDoPedido = new int[itens.length];
        this.totalItens = 0;

        montar(itens, quantidades, mercado);
    }

    // Valida cada item contra o estoque do mercado e monta o pedido
    private void montar(String[] itens, int[] quantidades, Mercado mercado) {
        int tamanho = Math.min(itens.length, quantidades.length);

        for (int i = 0; i < tamanho; i++) {
            Produtos produtoNoEstoque = mercado.buscarProduto(itens[i]);

            // Verifica se o produto existe no mercado
            if (produtoNoEstoque == null) {
                System.out.println("Produto '" + itens[i] + "' não encontrado. Item cancelado.");
                continue;  // pula para o próximo item
            }

            // Tenta baixar do estoque
            boolean reservado = produtoNoEstoque.baixarEstoque(quantidades[i]);
            if (!reservado) {
                System.out.println("Item '" + itens[i] + "' cancelado por falta de estoque.");
                continue;
            }

            // Item aprovado: adiciona ao pedido
            itensDoPedido[totalItens] = produtoNoEstoque;
            quantidadesDoPedido[totalItens] = quantidades[i];
            totalItens++;
        }
    }

    public boolean temItens() {
        return totalItens > 0;
    }

    public void exibirPedido() {
        System.out.println("\n=== Pedido #" + id + " ===");
        if (!temItens()) {
            System.out.println("  Nenhum item confirmado no pedido.");
            return;
        }
        float total = 0;
        for (int i = 0; i < totalItens; i++) {
            float subtotal = itensDoPedido[i].getPreco() * quantidadesDoPedido[i];
            System.out.printf("  %-10s | Qtd: %d | R$%.2f x %d = R$%.2f%n",
                    itensDoPedido[i].getItem(),
                    quantidadesDoPedido[i],
                    itensDoPedido[i].getPreco(),
                    quantidadesDoPedido[i],
                    subtotal);
            total += subtotal;
        }
        System.out.printf("  TOTAL: R$%.2f%n", total);
    }
}

// -------------------------------------------------------

class Cliente {
    private String nome;
    private static int contadorId = 0;
    private Pedido[] pedidos;
    private int totalPedidos;

    public Cliente(String nome) {
        this.nome = nome;
        this.pedidos = new Pedido[10]; // máximo de 10 pedidos por cliente
        this.totalPedidos = 0;
    }

    public String getNome() {
        return this.nome;
    }

    public void setPedido(String[] itens, int[] quantidades, Mercado mercado) {
        if (totalPedidos >= pedidos.length) {
            System.out.println("Limite de pedidos atingido para o cliente: " + this.nome);
            return;
        }

        contadorId++;
        System.out.println("\nProcessando pedido do cliente: " + this.nome);
        Pedido novoPedido = new Pedido(contadorId, itens, quantidades, mercado);

        if (novoPedido.temItens()) {
            pedidos[totalPedidos] = novoPedido;
            totalPedidos++;
        } else {
            System.out.println("Pedido cancelado: nenhum item pôde ser atendido.");
        }
    }

    // Retorna um pedido específico pelo índice
    public Pedido getPedido(int indice) {
        if (indice < 0 || indice >= totalPedidos) {
            System.out.println("Pedido #" + indice + " não encontrado.");
            return null;
        }
        return pedidos[indice];
    }

    // Exibe todos os pedidos do cliente
    public void exibirTodosPedidos() {
        if (totalPedidos == 0) {
            System.out.println("Cliente " + this.nome + " não possui pedidos.");
            return;
        }
        System.out.println("\n=== Pedidos de " + this.nome + " ===");
        for (int i = 0; i < totalPedidos; i++) {
            pedidos[i].exibirPedido();
        }
    }
}