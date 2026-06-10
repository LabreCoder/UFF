## 📆 Data: 01/06/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 📚 Aula 18: Framework de Coleções (Collections Framework)

### 📝 Introdução
A décima nona aula teve como objetivo apresentar o ecossistema de **Collections** do Java. Compreendemos a transição do uso de Estruturas de Dados Primitivas (como variáveis simples de tipos primitivos e Arrays de tamanho fixo) para Estruturas de Dados Não-Primitivas Lineares e Não-Lineares de tamanho dinâmico.

---

### 🏗️ O que são as Coleções (Collections)?
O *Collections Framework* é um conjunto de interfaces e classes utilitárias que servem para armazenar e manipular coleções de objetos na memória de forma totalmente **dinâmica** (o tamanho da estrutura cresce ou diminui automaticamente). 

No topo dessa hierarquia temos a **Interface `Collection`**, da qual derivam as estruturas que utilizamos no dia a dia:

#### 1. List (Listas)
Representa uma sequência ordenada de elementos que **permite duplicatas**. Os elementos podem ser acessados diretamente por sua posição de índice (assim como nos vetores).

* **`ArrayList`:** A implementação mais comum. Baseada em um array dinâmico interno, ideal para cenários onde a leitura de dados é muito frequente.

```java
import java.util.List;
import java.util.ArrayList;

public class ExemploList {
    public static void main(String[] args) {
        List<String> listaNomes = new ArrayList<>();
        
        listaNomes.add("João");
        listaNomes.add("Victor");
        listaNomes.add("João"); // Permite duplicata tranquilamente

        System.out.println("Primeiro da lista: " + listaNomes.get(0));
    }
}
```

---

#### 2. Set (Conjuntos)

Representa uma coleção de elementos que **NÃO permite elementos duplicados**.

* **`HashSet`:** Uma implementação de alta performance que utiliza tabelas espelhadas (*Hash*). Os elementos **não possuem uma ordem garantida** de armazenamento.

```java
import java.util.Set;
import java.util.HashSet;

public class ExemploSet {
    public static void main(String[] args) {
        Set<String> palavras = new HashSet<>();
        
        palavras.add("Java");
        palavras.add("POO");
        palavras.add("Java"); // Esta duplicata será ignorada automaticamente

        System.out.println("Total de elementos únicos: " + palavras.size()); // Retorna 2
    }
}
```

---

#### 3. Map (Dicionários / Mapas)

O `Map` **não herda** diretamente da interface `Collection`, mas faz parte do framework. Ele mapeia dados através de pares de **Chave e Valor**. As chaves devem ser obrigatoriamente únicas, enquanto os valores podem se repetir.

* **`HashMap`:** Implementação padrão que armazena os dados sem uma ordem específica baseando-se no hash da chave.

```java
import java.util.Map;
import java.util.HashMap;

public class ExemploMap {
    public static void main(String[] args) {
        // Estrutura: Map<Tipo_Da_Chave, Tipo_Do_Valor>
        Map<String, String> dddPorMunicipio = new HashMap<>();
        
        dddPorMunicipio.put("21", "São Gonçalo / Rio de Janeiro");
        dddPorMunicipio.put("11", "São Paulo");
        
        // Buscando o valor através da chave
        System.out.println("Localidade do DDD 21: " + dddPorMunicipio.get("21"));
    }
}
```

---

### 🔄 Formas de Percorrer Coleções: `for`, `for-each` e `Iterator`

Vimos em aula que podemos iterar (percorrer) as coleções utilizando estruturas tradicionais como o `for` e `for-each`, mas também fomos apresentados ao conceito de **Iterator**.

#### O que é o `Iterator`?

O `Iterator` é um objeto utilitário projetado especificamente para navegar de forma segura por qualquer tipo de coleção, sendo uma ferramenta puramente voltada para a **leitura** dos dados.

* **`Iterator` Tradicional:** Realiza a navegação unidirecional (apenas do início para o fim).
* `hasNext()`: Verifica se ainda existe um próximo elemento na coleção.
* `next()`: Retorna o próximo elemento de fato.


* **`ListIterator`:** Uma variação mais robusta exclusiva para listas, que permite a navegação bidirecional.
* `hasPrevious()`: Verifica se existe um elemento anterior (permitindo navegar do fim até o começo).
* `previous()`: Retorna o elemento anterior.


```java
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ExemploIterator {
    public static void main(String[] args) {
        List<Integer> numeros = new ArrayList<>(List.of(10, 20, 30));
        
        // Criando o objeto Iterator para a lista
        Iterator<Integer> it = numeros.iterator();
        
        // Percorrendo de forma segura do início ao fim
        while (it.hasNext()) {
            System.out.println("Elemento via Iterator: " + it.next());
        }
    }
}
```

---

### 🎯 Conclusão

O uso do *Collections Framework* elimina a necessidade de criarmos estruturas de dados complexas manualmente (como listas encadeadas ou árvores) do zero. Saber escolher a coleção certa (`List` para dados ordenados, `Set` para evitar duplicatas e `Map` para buscas rápidas por chave) melhora drasticamente o desempenho e a legibilidade do código em Java.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 17: Tratamento de Exceções](https://www.google.com/search?q=../Aula_17/README.md)
* ➡️ **Próxima Aula:** [Aula 19: Programação Concorrente com Threads em Java](../Aula_19/README.md)