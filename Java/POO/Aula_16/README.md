## 📆 Data: 18/05/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 🔌 Aula 16: Interfaces e Modularidade em Java

### 📝 Introdução
Esta aula teve como objetivo apresentar os conceitos de **Interfaces** e **Modularidade** no Java. Esses conceitos são os pilares para a criação de sistemas flexíveis, de fácil manutenção e com baixo acoplamento (onde as classes não dependem rigidamente umas das outras).

---

### 🏛️ O que é uma Interface?
Uma interface em Java é um **contrato** que define o comportamento que uma classe deve implementar. Ela não diz *como* fazer, apenas *o que* deve ser feito. 

#### 📐 Regras de Ouro das Interfaces:
1. **Abstração Total:** Por padrão, todos os métodos de uma interface são `public` e `abstract` (não possuem corpo/código), a menos que utilizem a palavra-chave `default` (introduzida no Java 8).
2. **Constantes:** Qualquer atributo declarado dentro de uma interface é automaticamente `public static final` (uma constante).
3. **Múltiplas Implementações:** Diferente das classes (onde o Java permite herdar de apenas uma classe mãe), uma classe pode implementar **várias interfaces** ao mesmo tempo.
4. **Instanciação:** Você **não pode** dar `new` em uma interface diretamente. Ela serve para ser implementada por outras classes usando a palavra-chave `implements`.

---

### 📦 O que é Modularidade?
Modularidade é a prática de dividir um sistema em partes independentes (módulos). Cada módulo possui uma responsabilidade bem definida. As interfaces são as ferramentas perfeitas para a modularidade, pois funcionam como "tomadas" ou "conectores" entre esses diferentes módulos.

---

### 💻 Exemplo Prático: Sistema de Pagamentos

Para exemplificar como a Interface gera Modularidade, vamos criar um contrato de pagamento. O nosso sistema principal não precisa saber se o pagamento é via Pix ou Cartão, ele só precisa saber que o objeto "sabe pagar".

#### 1. Criando a Interface (O Contrato)
```java
package br.com.escola.pagamento;

public interface FormaPagamento {
    // Método abstrato (toda classe que assinar este contrato deverá implementar)
    void processarPagamento(double valor);
}
```

#### 2. Criando os Módulos de Pagamento (As Implementações)

```java
package br.com.escola.pagamento.modulos;

import br.com.escola.pagamento.FormaPagamento;

// Módulo 1: Cartão de Crédito
public class CartaoCredito implements FormaPagamento {
    @Override
    public void processarPagamento(double valor) {
        System.out.println("Conectando com a operadora de cartão...");
        System.out.printf("Pagamento de R$ %.2f realizado no Crédito com sucesso!\n", valor);
    }
}
```

```java
package br.com.escola.pagamento.modulos;

import br.com.escola.pagamento.FormaPagamento;

// Módulo 2: Pix
public class Pix implements FormaPagamento {
    @Override
    public void processarPagamento(double valor) {
        System.out.println("Gerando QR Code do Pix...");
        System.out.printf("Pagamento de R$ %.2f recebido instantaneamente via Pix!\n", valor);
    }
}
```

#### 3. Testando a Modularidade (A Aplicação Principal)

Repare que a classe `Loja` consegue aceitar qualquer novo método de pagamento no futuro sem precisar mudar o seu código fonte, graças ao polimorfismo da interface.

```java
package br.com.escola;

import br.com.escola.pagamento.FormaPagamento;
import br.com.escola.pagamento.modulos.CartaoCredito;
import br.com.escola.pagamento.modulos.Pix;

public class Main {
    public static void main(String[] args) {
        // Criando a nossa "venda"
        double valorDaCompra = 250.50;

        // O cliente escolhe pagar com Pix
        FormaPagamento pagamentoEscolhido = new Pix();
        
        // Executando o pagamento de forma modular
        pagamentoEscolhido.processarPagamento(valorDaCompra);

        System.out.println("----------------------------------------");

        // Se o cliente mudasse de ideia para Cartão, bastaria trocar o objeto:
        pagamentoEscolhido = new CartaoCredito();
        pagamentoEscolhido.processarPagamento(valorDaCompra);
    }
}
```

---

### 🎯 Conclusão

O uso de interfaces permite que o código seja **modular**. Se amanhã o sistema precisar aceitar um novo método de pagamento (como "Boleto" ou "Criptomoedas"), basta criar uma nova classe que implemente `FormaPagamento`. O restante do sistema continuará funcionando perfeitamente sem precisar alterar uma única linha da classe `Main`.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 15: Relacionamentos, Herança e Polimorfismo em POO](../Aula_15/README.md)
* ➡️ **Próxima Aula:** [Aula 17: Tratamento de Exceções em Java](../Aula_17/README.md)