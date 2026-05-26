## 📆 Data: 27/04/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 🧩 Aula 11: Introdução Prática à Orientação a Objetos

### 📝 Introdução
Esta aula marcou o início da nossa visão prática sobre o paradigma de **Programação Orientada a Objetos (POO)**. Compreendemos como transformar conceitos do mundo real em estruturas de código eficientes e organizadas.

---

### 📑 Conteúdo da Aula

#### 1. Pilares e Conceitos Abordados
* **Classificação:** O ato de organizar os elements do sistema em classes, agrupando objetos que compartilham características e comportamentos em comum. É como separar o mundo em categorias bem definidas, trazendo ordem e reutilização ao desenvolvimento.
* **Abstração:** A capacidade de simplificar a realidade, destacando apenas o que é essencial para o problema e ocultando detalhes desnecessários. O desenvolvedor trabalha focado no que importa, evitando complexidade excessiva.
* **Encapsulamento:** O princípio de proteger os dados de um objeto, controlando o acesso a eles por meio de métodos. Garante a integridade e segurança, permitindo que o objeto governe seu próprio estado.

#### 2. O Fluxo de Desenvolvimento em POO
Vimos que a aplicação real da orientação a objetos segue três etapas fundamentais:
1. **Análise O.O (O que resolve?):** Entendimento do problema e identificação do que fará parte do sistema.
2. **Projeto O.O (Como resolve?):** Modelagem das classes, definição de como elas vão interagir e estruturação dos dados.
3. **Programação O.O (Código):** A tradução do projeto para a linguagem de programação (Java).

---

### 🔀 Paradigma Estruturado vs. Orientado a Objetos

Abaixo, analisamos como cada abordagem lida com o fluxo de informações no desenvolvimento:

> **No paradigma estruturado**, a lógica é conduzida de forma sequencial, organizada em funções e procedimentos. O foco está nas etapas do processo — como um roteiro bem definido, onde os dados são manipulados ao longo do caminho. É uma abordagem direta, eficiente para problemas mais simples, porém tende a se tornar difícil de manter à medida que o sistema cresce.
>
> **Já no paradigma orientado a objetos**, o olhar se volta para a modelagem do mundo real. O sistema é estruturado em objetos que possuem responsabilidades próprias, reuniindo dados e comportamentos. Em vez de apenas executar passos, o programa passa a representar entidades que interagem entre si, tornando o código mais modular, reutilizável e próximo da realidade do problema.

#### 🏦 Exemplo Prático: Sistema Bancário

* **No modelo estruturado:** Haveria funções soltas e globais como `criarConta()`, `depositar(int contaId, double valor)` e `sacar(int contaId, double valor)`, manipulando variáveis ou arrays globais de forma desvinculada.
* **No modelo O.O:** Existiria uma classe `Conta`, onde cada objeto gerado possui seus próprios atributos privados (`saldo`, `titular`) e seus próprios métodos (`depositar()`, `sacar()`), centralizando e protegendo a responsabilidade sobre aqueles dados.

---

### 🔑 Definições Fundamentais

#### 🔮 Objetos
* **O que é:** São as entidades fundamentais da POO. Representam elementos do mundo real (ou conceitual), reunindo em si características e comportamentos. Um objeto é uma instância prática e concreta de uma classe.
* **Como aplicar:** Utilizamos para mapear as entidades do negócio. Em um sistema escolar, criamos objetos como *Aluno*, *Professor* ou *Turma*.
* **Lógica de identificação:** Identificamos os objetos observando o problema e destacando os **substantivos** relevantes que possuem identidade própria no contexto.

#### 📊 Características (Atributos)
* **O que é:** São os dados que descrevem o estado de um objeto. Representam suas propriedades, aquilo que o define e o diferencia dos outros.
* **Como aplicar:** Atribuímos variáveis de instância aos objetos. Um objeto `Aluno` possui os atributos `nome`, `idade` e `matricula`.
* **Lógica de identificação:** Identificamos os atributos observando os dados necessários para caracterizar os objetos — geralmente associados a **informações descritivas**.

#### ⚙️ Comportamentos (Métodos)
* **O que é:** São as funções/ações que um objeto pode realizar. Representam como ele interage com seus próprios dados e com outros objetos do sistema.
* **Como aplicar:** Definimos blocos de código para executar as operações do objeto. O `Aluno` pode ter métodos como `estudar()`, `realizarProva()` ou `consultarNota()`.
* **Lógica de identificação:** Identificamos os behaviors observando os **verbos** associados aos objetos dentro do contexto do sistema.

---

### 💻 Representação em Código (Java)

Para consolidar o que foi discutido sobre **Objetos, Atributos e Métodos**, veja a implementação da entidade `Aluno` mapeada durante a aula:

```java
package br.com.escola;

public class Aluno {
    // 1. ATRIBUTOS (Características / Propriedades)
    public String nome;
    public String matricula;
    public double nota;

    // 2. MÉTODOS (Comportamentos / Ações)
    public void estudar() {
        System.out.println(nome + " está estudando os conceitos de O.O...");
    }

    public void consultarNota() {
        System.out.println("A nota atual do aluno " + nome + " é: " + nota);
    }
}
```

#### Instanciando o Objeto na Classe Principal:

```java
package br.com.escola;

public class Main {
    public static void main(String[] args) {
        // Materializando a ideia abstrata em um objeto concreto (Instanciação)
        Aluno aluno1 = new Aluno();
        
        // Atribuindo valores às características
        aluno1.nome = "João Victor Labre";
        aluno1.matricula = "20261105";
        aluno1.nota = 9.5;

        // Invocando os comportamentos do objeto
        aluno1.estudar();
        aluno1.consultarNota();
    }
}
```

---

### 🎯 Conclusão

A transição do pensamento estruturado para o orientado a objetos exige uma mudança na forma de enxergar o problema. Ao focar em "quem faz a ação" (Entidades/Objetos) in vez de apenas "como a ação é feita" (Procedimentos), conseguimos construir softwares muito mais organizados, escaláveis e alinhados com as regras do mundo real.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 10: Apresentação de Pesquisa e Revisão](../Aula_10/README.md)
* ➡️ **Próxima Aula:** [Aula 12: Laboratório Prático — Lista 05](../Aula_12/README.md)