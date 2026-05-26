## 📆 Data: 04/05/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 📦 Aula 13: Encapsulamento, Pacotes e Construtores em Java

### 📝 Introdução
Esta aula teve como objetivo aprofundar os conceitos de **Encapsulamento** dentro da Programação Orientada a Objetos (POO), explorando a organização do código por meio de **Pacotes (Packages)**, os níveis de **Modificadores de Acesso** (Visibilidade) e a correta utilização de **Construtores**.

---

### 📂 Pacotes (Packages)
Os pacotes em Java servem para organizar as classes de forma lógica e hierárquica, funcionando como "pastas" no sistema de arquivos. Eles ajudam a evitar conflitos de nomes (ex: duas classes chamadas `Usuario` em pacotes diferentes) e controlam o acesso à visibilidade dos membros da classe.

---

### 🔒 Modificadores de Acesso (Visibilidade)
Os modificadores de acesso definem quem pode visualizar e interagir com as classes, atributos e métodos. Em Java, temos **4 níveis de visibilidade**:

| Modificador | Dentro da própria Classe | No mesmo Pacote (Package) | Por herança (Subclasses) | Em qualquer lugar (Global) |
| :--- | :---: | :---: | :---: | :---: |
| **`public`** |  Sim |  Sim |  Sim |  Sim |
| **`protected`** |  Sim |  Sim |  Sim | ❌ Não |
| **`default`** *(package-private)* |  Sim |  Sim | ❌ Não | ❌ Não |
| **`private`** |  Sim | ❌ Não | ❌ Não | ❌ Não |

#### 🔍 Detalhes de cada visibilidade:
* **`public`:** O membro é acessível por qualquer outra classe em qualquer pacote.
* **`protected`:** O membro é acessível por classes do mesmo pacote e por subclasses (classes que herdam da classe original), mesmo que estejam em pacotes diferentes.
* **`default` (ou package-private):** É a visibilidade padrão quando **nenhum** modificador é escrito. O membro só fica visível para classes que estão exatamente dentro do mesmo pacote.
* **`private`:** O nível mais restrito. O membro só pode ser acessado e modificado por métodos de dentro da própria classe. É a base do encapsulamento.

---

### 🏗️ Construtores
O construtor é um bloco de código especial executado no momento em que um objeto da classe é instanciado (usando a palavra-chave `new`). Ele serve principalmente para inicializar os atributos do objeto com valores válidos.

#### 📐 Regras obrigatórias dos Construtores:
1. **Nome idêntico à Classe:** O construtor deve ter exatamente o mesmo nome da classe em que foi criado (incluindo letras maiúsculas e minúsculas).
2. **Sem tipo de retorno:** Construtores **não possuem** tipo de retorno (nem mesmo `void`). Se você colocar um tipo de retorno, o Java entenderá que é um método comum e não um construtor.
3. **Construtor Padrão:** Se você não escrever nenhum construtor, o Java criará automaticamente um construtor padrão vazio implicitamente. Porém, se você criar qualquer construtor com parâmetros, o construtor padrão deixa de existir automaticamente, a menos que você o escreva explicitamente.
4. **Sobrecarga:** Uma classe pode ter múltiplos construtores (sobrecarga), desde que eles recebam parâmetros diferentes.

---

### 💻 Exemplo Prático de Código

Abaixo está um exemplo demonstrando o encapsulamento (atributos privados com métodos públicos de acesso `get`/`set`) e o uso de construtores sobrecarregados.

```java
package br.com.escola.modelo;

public class Aluno {
    // Atributos privados do exemplo inicial
    private String nome;
    private int idade;

    // --- Atributos de teste para cada Modificador de Acesso ---
    
    // 1. Private: Visível apenas dentro desta própria classe
    private String segredoPrivate = "Diário Oculto";

    // 2. Default ou Package-Private: Visível apenas por classes no mesmo pacote (br.com.escola.modelo)
    String registroDefault = "Dado Escolar";

    // 3. Protected: Visível no mesmo pacote e por herança (subclasses) em outros pacotes
    protected String herancaProtected = "Segredo de Família";

    // 4. Public: Visível em qualquer lugar do projeto
    public String nomePublico = "Nome Global";


    // 1. Construtor Padrão (Sem parâmetros)
    public Aluno() {
    }

    // 2. Construtor com Parâmetros (Sobrecarga)
    public Aluno(String nome, int idade) {
        this.nome = nome;
        this.idade = idade;
    }

    // Métodos Getters e Setters para o encapsulamento
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getIdade() {
        return idade;
    }

    public void setIdade(int idade) {
        // Validação de segurança graças ao encapsulamento
        if (idade >= 0) {
            this.idade = idade;
        } else {
            System.out.println("Idade inválida!");
        }
    }
}
```

#### Testando a Instanciação:

```java
package br.com.escola;

import br.com.escola.modelo.Aluno;

// Criando uma classe filha em pacote diferente para testar o 'protected'
class AlunoBolsista extends Aluno {
    public void testarAcessoHeranca() {
        // ✅ PERMITIDO: Atributo 'protected' é acessível via herança mesmo em pacotes diferentes
        System.out.println(this.herancaProtected); 
    }
}

public class Main {
    public static void main(String[] args) {
        // Criando o objeto aluno (utilizando o pacote br.com.escola.modelo)
        Aluno aluno = new Aluno("João Victor", 20);

        // 1. Testando o modificador PUBLIC
        // ✅ PERMITIDO: Visível em qualquer parte do projeto
        System.out.println(aluno.nomePublico);

        // 2. Testando o modificador PROTECTED
        // ❌ ERRO DE COMPILAÇÃO: Main não herda de Aluno e está em outro pacote (br.com.escola)
        // System.out.println(aluno.herancaProtected);

        // 3. Testando o modificador DEFAULT (Package-private)
        // ❌ ERRO DE COMPILAÇÃO: Main está no pacote 'br.com.escola' e Aluno no 'br.com.escola.modelo'
        // System.out.println(aluno.registroDefault);

        // 4. Testando o modificador PRIVATE
        // ❌ ERRO DE COMPILAÇÃO: Atributos privados são completamente invisíveis fora da classe Aluno
        // System.out.println(aluno.segredoPrivate);
    }
}
```

---

### 🎯 Conclusão

O encapsulamento protege os dados internos de um objeto contra modificações indevidas ou acidentais de outras partes do sistema. Associado aos pacotes e construtores bem definidos, conseguimos criar sistemas em Java muito mais modulares, organizados, fáceis de dar manutenção e seguros.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 12: Laboratório Prático — Lista de Exercícios 05](../Aula_12/README.md)
* ➡️ **Próxima Aula:** [Aula 14: Apresentação DOJO](../Aula_14/README.md)