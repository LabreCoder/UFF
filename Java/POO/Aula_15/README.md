## 📆 Data: 11/05/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 🔄 Aula 15: Relacionamentos, Herança e Polimorfismo em POO

### 📝 Introdução
Esta aula deu continuidade aos conceitos fundamentais do paradigma de Orientação a Objetos (OO). Foram abordados de forma aprofundada a modelagem de estruturas complexas através de relacionamentos entre classes, além dos pilares de Herança e Polimorfismo.

---

## 🔗 Relacionamentos em Orientação a Objetos

Na POO, as classes não trabalham isoladas. Elas interagem entre si através de quatro tipos principais de relacionamentos:

### 1. Dependência
* Acontece quando uma classe utiliza outra **temporariamente** para executar uma ação pontual.
* Normalmente, a classe dependente recebe a outra como parâmetro de um método ou a instancia como uma variável local.
* É o relacionamento mais fraco e volátil entre duas classes.
* *Exemplo:* Uma classe `Impressora` depende de um objeto `Documento` apenas no momento em que o método `imprimir(Documento doc)` é chamado.

---

### 2. Associação
* Representa um vínculo estrutural permanente entre duas classes, indicando que um objeto "possui" ou "está ligado" a outro.
* **Associação Unidirecional:** Apenas uma classe conhece a existência da outra.
* **Associação Bidirecional:** Ambas as classes possuem referências mútuas e se conhecem.
* **Cardinalidade:** Define quantos objetos participam de cada lado da relação (1 para 1, 1 para muitos, muitos para muitos).
* *Exemplo:* Um `Cliente` pode possuir vários `Pedidos`, mas cada `Pedido` pertence a apenas um `Cliente`.

---

### 3. Composição (Relação Forte)
* É uma variação da associação onde existe uma relação de **"todo e parte"** muito rígida.
* A parte **não pode existir** de forma independente sem o todo. O ciclo de vida da parte é controlado inteiramente pelo todo.
* *Exemplo:* Um `CarrinhoCompras` e seus `ItemPedido`. Se o carrinho for destruído/deletado do sistema, os itens daquele carrinho deixam de existir automaticamente.

---

### 4. Agregação (Relação Fraca)
* Também é uma relação de **"todo e parte"**, mas de forma independente.
* A parte **pode existir** mesmo se o todo deixar de existir. Os objetos possuem ciclos de vida independentes.
* *Exemplo:* Uma `Equipe` e seus `Jogadores`. Se a equipe for dissolvida, os jogadores continuam existindo no sistema e podem ser transferidos para outra equipe.

---

## 🧬 Herança

A herança permite que uma classe (**subclasse** ou classe filha) adquira os atributos e métodos de outra classe (**superclasse** ou classe mãe), promovendo o reaproveitamento de código.

Em Java, utilizamos:
* **`extends`**: Palavra-chave para declarar que uma classe herda de outra.
* **`super`**: Utilizado dentro da subclasse para acessar construtores, atributos ou métodos da superclasse.

#### 💻 Exemplo Prático de Herança:

```java
// Superclasse (Mãe)
public class Veiculo {
    protected String marca;

    public void buzinar() {
        System.out.println("Bi-bi!");
    }
}

// Subclasse (Filha)
public class Carro extends Veiculo {
    private int quantidadePortas;

    public void emitirAlerta() {
        // Acessando o método da superclasse usando 'super'
        super.buzinar(); 
    }
}
```

> ⚠️ **Observação Importante:** Atributos e métodos `public` e `protected` são herdados naturalmente. Membros `private` são herdados, mas não podem ser acessados diretamente pela subclasse (sendo necessário o uso de getters e setters públicos).

#### 🛠️ Tipos de Herança

* **Herança Simples:** Uma classe herda de apenas uma única superclasse. (O Java suporta apenas este tipo para classes).
* **Herança Múltipla:** Uma classe herda de duas ou mais classes simultaneamente. (**O Java NÃO permite herança múltipla de classes** para evitar o problema do diamante, permitindo essa flexibilidade apenas através de Interfaces).

---

### 🏛️ Classes e Métodos Abstratos

Uma **Classe Abstrata** serve puramente como um "molde" ou conceito genérico para outras classes. Ela **não pode ser instanciada** diretamente (não podemos dar `new` nela).

* **Método Abstrato:** É um método que é apenas declarado (não possui corpo/código `{}`). Ele obriga, de forma contratual, todas as subclasses não-abstratas a implementarem sua própria lógica para aquele método.

```java
// Classe Abstrata
public abstract class FormaGeometrica {
    // Método Abstrato (Sem corpo)
    public abstract double calcularArea();
}
```

---

## 🎭 Polimorfismo

O polimorfismo (do grego: *muitas formas*) é a capacidade de um mesmo comportamento ser executado de maneiras diferentes dependendo do objeto real que o está executando. Se uma classe chamar o método `calcularArea()`, o resultado mudará caso o objeto seja um `Quadrado` ou um `Circulo`.

Existem dois tipos principais de polimorfismo em Java:

#### 1. Sobrecarga (Overload / Polimorfismo em Tempo de Compilação)

Ocorre dentro da **mesma classe**, onde criamos múltiplos métodos com o **mesmo nome**, mas com **assinaturas (parâmetros) diferentes**. O compilador decide qual método chamar com base nos argumentos passados.

```java
public class Calculadora {
    // Sobrecarga por tipo e quantidade de parâmetros
    public int somar(int a, int b) {
        return a + b;
    }

    public double somar(double a, double b) {
        return a + b;
    }
}
```

---

#### 2. Sobrescrita (Override / Polimorfismo em Tempo de Execução)

Ocorre quando uma subclasse reescreve e modifica a implementação de um método que foi herdado da sua superclasse. Utiliza-se a anotação `@Override` para segurança.

```java
// Subclasse de FormaGeometrica
public class Retangulo extends FormaGeometrica {
    private double base;
    private double altura;

    // Sobrescrita do método abstrato da classe mãe
    @Override
    public double calcularArea() {
        return base * altura;
    }
}
```

---

### 🎯 Conclusão

Compreender a diferença exata entre os tipos de relacionamentos (como Agregação vs. Composição) evita falhas graves na arquitetura do banco de dados e da memória do programa. Somado a isso, o uso correto de herança, classes abstratas e polimorfismo garante que o código Java seja escalável e fácil de estender no futuro.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 14: Apresentação DOJO](../Aula_14/README.md)
* ➡️ **Próxima Aula:** [Aula 16: Interfaces e Modularidade em Java](../Aula_16/README.md)