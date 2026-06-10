## 📆 Data: 08/06/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 🧵 Aula 19: Programação Concorrente com Threads em Java

### 📝 Introdução
A vigésima aula teve como objetivo compreender o conceito de **Threads** e como implementar a concorrência/paralelismo dentro da plataforma Java. Aprendemos que, por padrão, todo programa Java roda sob uma thread principal chamada `main`. A partir dela, podemos disparar novas threads para executar tarefas simultâneas em segundo plano.

---

### 🛠️ Formas de Criar e Iniciar uma Thread em Java

Para definir o código que uma Thread deve executar, o Java nos fornece duas abordagens tradicionais:

#### Forma 1: Implementando a Interface `Runnable` (Recomendado)
Nesta abordagem, criamos uma classe que assina o contrato da interface funcional `Runnable` e implementa o método `run()`. Em seguida, passamos essa instância como argumento ao criar o objeto `Thread`.

```java
// Criando a tarefa que implementa a interface
public class MinhaTarefa implements Runnable {
    @Override
    public void run() {
        System.out.println("Thread criada via interface Runnable em execução!");
    }
}

// Inicialização no método main
public class Main {
    public static void main(String[] args) {
        Thread t1 = new Thread(new MinhaTarefa());
        t1.start(); // O método start() inicializa a thread e chama o run() internamente
    }
}
```

#### Forma 2: Herdando da Classe `Thread` (`extends`)

Nesta abordagem, criamos uma subclasse direta de `Thread` e sobrescrevemos o método `run()`. Como a classe filha já é uma Thread, basta instanciá-la e chamá-la diretamente.

```java
// Herdando diretamente da classe base Thread
public class MinhaThread extends Thread {
    @Override
    public void run() {
        System.out.println("Thread criada via herança (extends Thread) em execução!");
    }
}

// Inicialização no método main
public class Main {
    public static void main(String[] args) {
        MinhaThread t2 = new MinhaThread();
        t2.start();
    }
}
```

---

### ⚖️ O Dilema: Devo aplicar Herança (`extends`) ou Interface (`implements`)?

Uma das principais discussões da aula foi decidir qual das duas formas aplicar no dia a dia do desenvolvimento. **A boa prática de mercado recomenda priorizar a Interface (`implements Runnable`)**.

#### Por que evitar o `extends Thread`?

1. **Restrição de Herança Simples:** O Java não permite herança múltipla. Se a sua classe fizer `extends Thread`, ela nunca mais poderá herdar nenhuma outra classe do seu sistema (como `Pessoa`, `Funcionario`, etc.).
2. **Acoplamento:** Fazer herança cria um vínculo muito forte. Se você quer apenas executar uma tarefa, não há necessidade de herdar todas as propriedades internas e pesadas da classe `Thread`.
3. **Separação de Responsabilidades:** Utilizando `Runnable`, você separa a **Tarefa** (o código que vai rodar) do **Mecanismo de Execução** (a Thread em si). Isso facilita o reaproveitamento de código e a integração futura com estruturas avançadas como Pools de Threads (`ExecutorService`).

---

### 💻 Exemplo Prático Completo (Concorrência em Ação)

Para visualizar as duas threads rodando ao mesmo tempo (disputando o processador), criamos um fluxo com estruturas de repetição:

```java
class TarefaLoop implements Runnable {
    private String nome;

    public TarefaLoop(String nome) {
        this.nome = nome;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println("[" + nome + "] - Passo " + i);
            try {
                Thread.sleep(500); // Pausa a thread por 500 milissegundos
            } catch (InterruptedException e) {
                System.out.println("Thread interrompida.");
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        // Criando duas threads independentes com a mesma lógica de tarefa
        Thread t1 = new Thread(new TarefaLoop("Thread_A"));
        Thread t2 = new Thread(new TarefaLoop("Thread_B"));

        // Disparando as duas para rodarem em paralelo
        t1.start();
        t2.start();

        System.out.println(">>> Thread MAIN finalizou sua linha de código! <<<");
    }
}
```

---

### 🎯 Conclusão

O uso de Threads permite criar sistemas muito mais rápidos e responsivos (como servidores web que atendem múltiplos clientes ou interfaces gráficas que não travam durante downloads). Contudo, a programação concorrente exige atenção redobrada, pois threads compartilhando o mesmo recurso de memória podem gerar condições de corrida, necessitando do uso de sincronização (`synchronized`).

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 18: Framework de Coleções (Collections)](https://www.google.com/search?q=../Aula_18/README.md)