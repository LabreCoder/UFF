## 📆 Data: 25/05/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 17: Tratamento de Exceções em Java

### 📝 Introdução
A décima oitava aula teve como objetivo compreender e aplicar o **Tratamento de Exceções** (Exception Handling) dentro da Programação Orientada a Objetos utilizando a linguagem Java. 

O tratamento de erros é fundamental para construir softwares resilientes, impedindo que a aplicação quebre inesperadamente ao se deparar com situações anômalas, tais como:
* Divisão por zero;
* Tentativa de ler um arquivo inexistente;
* Acesso a um índice inválido de um vetor (`ArrayIndexOutOfBoundsException`);
* Entrada de dados com formato incorreto.

Toda a estrutura de exceções do Java baseia-se na biblioteca padrão `java.lang.Throwable`, que se divide em duas grandes categorias: **Errors** e **Exceptions**.

---

### ⚠️ Errors vs. 🛠️ Exceptions

#### 1. Errors (`java.lang.Error`)
Representam problemas graves de infraestrutura ou recursos do ambiente que a aplicação **não deve tentar tratar**, pois geralmente envolvem falhas do Sistema Operacional, do Hardware ou da própria JVM.
* **Características:** Não são capturados por blocos `try...catch`.
* **Exemplos comuns:** 
  * `OutOfMemoryError` (Falta de memória RAM para a JVM).
  * `StackOverflowError` (Estouro de pilha, comum em recursões infinitas).

#### 2. Exceptions (`java.lang.Exception`)
Representam condições de erro disparadas pela aplicação que **podem e devem ser tratadas** pelo desenvolvedor para que o programa continue rodando com segurança. As exceções dividem-se em dois tipos:

* **Checked Exceptions (Exceções Verificadas):** São checadas pelo compilador em tempo de compilação. O Java obriga o desenvolvedor a tratá-las (com `try-catch`) ou a declará-las (com `throws`), caso contrário o código nem compila.
  * *Exemplo:* `IOException`, `FileNotFoundException`.

* **Unchecked Exceptions (Exceções Não-Verificadas / Runtime):** Herdam da classe `RuntimeException`. Acontecem exclusivamente em tempo de execução e o compilador não obriga o seu tratamento prévio.
  * *Exemplo:* `ArithmeticException`, `NullPointerException`.

---

### 🛠️ Como Tratar Exceções em Java

O Java disponibiliza cinco palavras-chave para o controle de fluxos de exceção: `try`, `catch`, `finally`, `throw` e `throws`.

#### 🧰 Estrutura `try ... catch ... finally`
* **`try`**: Delimita o bloco de código que pode vir a lançar uma exceção.
* **`catch`**: Captura a exceção gerada no bloco `try` e executa um comportamento corretivo.
* **`finally`**: Bloco opcional que **sempre** será executado, ocorrendo um erro ou não. Ideal para fechar conexões com bancos de dados ou arquivos.

```java
public class ExemploTryCatch {
    public static void main(String[] args) {
        try {
            int resultado = 10 / 0; // Provoca uma Unchecked Exception
            System.out.println("Resultado: " + resultado);
        } catch (ArithmeticException e) {
            System.err.println("Erro matemático: Não é possível dividir um número por zero!");
        } finally {
            System.out.println("Encerrando a tentativa de divisão.");
        }
    }
}
```

---

#### 🚨 Palavra-chave `throw`

Utilizada para **lançar manualmente** uma exceção no sistema. É muito útil para aplicar regras de negócio e impedir que dados inválidos avancem na aplicação.

```java
public class ExemploThrow {
    public static void validarIdade(int idade) {
        if (idade < 18) {
            // Lançando manualmente uma exceção de argumento inválido
            throw new IllegalArgumentException("Acesso negado: Usuário menor de idade.");
        }
        System.out.println("Acesso liberado!");
    }

    public static void main(String[] args) {
        try {
            validarIdade(15);
        } catch (IllegalArgumentException e) {
            System.out.println("Capturado no main: " + e.getMessage());
        }
    }
}
```

---

#### ⚠️ Palavra-chave `throws`

Utilizada na assinatura de um método para indicar que ele **pode disparar** uma ou mais exceções que ele mesmo não vai tratar. A responsabilidade do tratamento é transferida para quem chamar esse método.

```java
import java.io.FileReader;
import java.io.FileNotFoundException;

public class ExemploThrows {
    // O método avisa que pode lançar um erro de arquivo não encontrado
    public static void abrirArquivo() throws FileNotFoundException {
        FileReader arquivo = new FileReader("contrato_inexistente.txt");
    }

    public static void main(String[] args) {
        try {
            abrirArquivo(); // Quem chama é obrigado a tratar ou relançar (por ser Checked)
        } catch (FileNotFoundException e) {
            System.err.println("Erro: O arquivo solicitado não foi encontrado no sistema.");
        }
    }
}
```

---

### 🛸 Criando Exceções Personalizadas (Custom Exceptions)

Em sistemas profissionais, muitas vezes precisamos criar nossas próprias exceções para representar erros específicos do negócio (ex: `SaldoInsuficienteException`). Para isso, basta criar uma classe que herde de `Exception` (para criar uma Checked) ou de `RuntimeException` (para criar uma Unchecked).

#### 1. Criando a Classe de Exceção

```java
// Criando uma exceção personalizada do tipo Checked
public class SaldoInsuficienteException extends Exception {
    public SaldoInsuficienteException(String mensagem) {
        super(mensagem);
    }
}
```

#### 2. Aplicando e Capturando a Exceção Customizada

```java
public class CaixaEletronico {
    private static double saldo = 100.00;

    public static void sacar(double valor) throws SaldoInsuficienteException {
        if (valor > saldo) {
            throw new SaldoInsuficienteException("Você tentou sacar R$" + valor + ", mas seu saldo é de apenas R$" + saldo);
        }
        saldo -= valor;
        System.out.println("Saque realizado com sucesso! Novo saldo: R$" + saldo);
    }

    public static void main(String[] args) {
        try {
            sacar(150.00); // Forçando o estouro da exceção personalizada
        } catch (SaldoInsuficienteException e) {
            System.out.printf("Alerta do Sistema -> %s\n", e.getMessage());
        }
    }
}
```

---

### 🎯 Conclusão

O domínio do tratamento de exceções em Java separa programadores iniciantes de profissionais. Utilizando corretamente as ferramentas apresentadas (`try-catch-finally`, `throw`, `throws` e customizações), criamos aplicações robustas que não travam na mão do cliente final e geram logs limpos e fáceis de monitorar.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 16: Interfaces e Modularidade em Java](../Aula_16/README.md)
* ➡️ **Próxima Aula:** [Aula 18: Framework de Coleções (Collections Framework)](../Aula_18/README.md)