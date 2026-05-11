## 📆 Data - 11/05/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# Introdução

* Esta aula deu continuidade aos conteúdos abordados na última aula teórica, aprofundando conceitos fundamentais do paradigma de Orientação a Objetos (O.O).
  Os principais temas estudados foram:

---

# Relacionamentos em Orientação a Objetos

Foram apresentados os principais tipos de relacionamento entre classes dentro da Programação Orientada a Objetos:

## 1. Dependência

* A dependência ocorre quando uma classe utiliza outra temporariamente para executar alguma ação.
* Esse relacionamento normalmente acontece por meio de parâmetros de métodos, variáveis locais ou chamadas pontuais.
* É considerado um relacionamento mais fraco entre classes, pois uma classe apenas “depende” momentaneamente da outra para funcionar.

---

## 2. Associação

* A associação representa um vínculo entre duas classes, indicando que objetos podem se relacionar entre si.
* Foi mostrado que existem dois tipos principais de associação:

### Associação Unidirecional

* Apenas uma classe conhece a outra.

### Associação Bidirecional

* As duas classes possuem conhecimento uma da outra.

* Também foi trabalhado o conceito de **cardinalidade**, utilizado para definir quantos objetos podem participar daquela relação.

Exemplos:

* Um cliente pode possuir vários pedidos.
* Um pedido pertence a apenas um cliente.

---

## 3. Composição

* A composição representa uma relação forte entre o todo e suas partes.
* Nesse tipo de relacionamento, a parte depende diretamente do todo para existir.

Exemplo:

* Um carrinho de compras e seus itens.

Se o carrinho deixar de existir, os itens daquele carrinho também deixam de existir dentro daquele contexto.

### Características:

* A parte é criada dentro do todo.
* A existência da parte está diretamente ligada ao objeto principal.

---

## 4. Agregação

* A agregação também representa uma relação entre todo e parte, porém de maneira mais fraca que a composição.
* Nesse caso, a parte pode existir independentemente do todo.

Exemplo:

* Uma equipe e seus jogadores.

Os jogadores podem existir mesmo sem fazer parte de uma equipe específica.

### Características:

* A parte é passada como parâmetro na criação ou alteração do todo.
* Os objetos possuem ciclos de vida independentes.

---

# Herança

* Foi explicado que na herança existe uma **superclasse**, responsável por armazenar atributos e métodos genéricos que serão compartilhados entre suas subclasses.

* As subclasses herdam características da superclasse, evitando repetição de código e promovendo reutilização.

Em Java, utilizamos:

* `extends` → para herdar de outra classe;
* `super` → para acessar atributos e métodos da superclasse.

Exemplo:

```java
public class CarroNovo extends Carro {

    public static void metodo() {
        super.metodo();
    }
}
```

Sintaxe geral:

```java
public class NomeDaClasse extends NomeDaSuperclasse {
}
```

### Observações importantes

* Tudo que estiver definido como `public` ou `protected` poderá ser herdado pela subclasse.
* Elementos `private` não podem ser acessados diretamente pela subclasse.

---

## Tipos de Herança

### Herança Simples

* Uma classe herda de apenas uma superclasse.

### Herança Múltipla

* Uma classe poderia herdar de várias classes ao mesmo tempo.
* O Java não permite herança múltipla de classes, apenas de interfaces.

---

## Classes Abstratas

* Classes abstratas não podem ser instanciadas diretamente.
* Elas servem como modelo para outras classes.

Além disso, podem possuir métodos abstratos, que obrigam as subclasses a implementarem suas próprias versões.

Exemplo:

```java
public abstract class Veiculo {

    public abstract double area();
}
```

### Método Abstrato

* Não possui implementação na classe abstrata.
* Cada subclasse define sua própria regra de funcionamento para esse método.

---

# Polimorfismo

* O polimorfismo permite que um mesmo comportamento aconteça de maneiras diferentes em classes diferentes.

Exemplo:

* Um método chamado `calcularArea()` pode funcionar de forma diferente em um círculo, quadrado ou triângulo.

Esse conceito ajuda a tornar o código mais flexível, reutilizável e organizado.

---

## Tipos de Polimorfismo

### 1. Sobrecarga (Overload)

* Acontece quando existem vários métodos com o mesmo nome, porém com parâmetros diferentes.

Para ocorrer sobrecarga, deve haver diferença em:

* tipo;
* quantidade;
* ordem dos parâmetros.

Exemplo:

```java
public void somar(int a, int b) {
}

public void somar(double a, double b) {
}
```

---

### 2. Sobrescrita (Override)

* A sobrescrita acontece quando uma subclasse redefine um método herdado da superclasse.

* Muito utilizada com herança e classes abstratas.

Exemplo:

```java
@Override
public double area() {
    return largura * altura;
}
```

* Nesse caso, a subclasse cria uma implementação própria para o método herdado.
