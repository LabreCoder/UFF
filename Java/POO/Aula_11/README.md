## 📆 Data - 27/04/2026    |  📚 Professora: Rebeca    |   👨🏾‍🏫 Aluno: João Victor Labre

### Introdução

- Nesta aula tivemos visão mais prática sobre a programação com o paradigma O.O.

### Conteúdo da aula

- Primeiro separamos os conceitos de O.O que seriam abordados nessa aula:

    1. **Classificação** -> É o ato de organizar os elementos do sistema em classes, agrupando objetos que compartilham características e comportamentos em comum.

    - Em termos práticos, é como separar o mundo em categorias bem definidas, permitindo reutilização e ordem no desenvolvimento.

    2. **Abstração** -> É a capacidade de simplificar a realidade, destacando apenas o que é essencial para o problema e ocultando detalhes desnecessários.

    - Assim, o desenvolvedor trabalha com o que importa, mantendo o foco e evitando complexidade excessiva.

    3. **Encapsulamento** -> É o princípio de proteger os dados de um objeto, controlando o acesso a eles por meio de métodos.

    - Dessa forma, garante-se integridade, organização e segurança, permitindo que o objeto governe seu próprio estado com disciplina.

- Segundo separamos a aplicação de fato que ocorre com O.O:

    1. **Análise O.O** -> O que resolve?

    2. **Projeto O.O** -> Como resolve?

    3. **Programar** -> Código (java)

---

- Abordamos algumas diferenças entre os paradigmas O.O e Estruturados, sobre como cada um agiria em uma determinada situação.

```
No paradigma estruturado, a lógica é conduzida de forma sequencial, organizada em funções e procedimentos. O foco está nas etapas do processo — como um roteiro bem definido, onde os dados são manipulados ao longo do caminho. É uma abordagem direta, eficiente para problemas mais simples, porém tende a se tornar difícil de manter à medida que o sistema cresce.

Já no paradigma orientado a objetos, o olhar se volta para a modelagem do mundo real. O sistema é estruturado em objetos que possuem responsabilidades próprias, reunindo dados e comportamentos. Em vez de apenas executar passos, o programa passa a representar entidades que interagem entre si, tornando o código mais modular, reutilizável e próximo da realidade do problema.

Em uma situação prática, como o desenvolvimento de um sistema bancário:

No modelo estruturado, haveria funções separadas como criarConta, depositar e sacar, manipulando dados globais.
No modelo O.O, existiria um objeto Conta, que já possui seus próprios atributos (saldo, titular) e métodos (depositar, sacar), centralizando responsabilidades.

Assim, enquanto o paradigma estruturado organiza ações, o orientado a objetos organiza entidades e suas interações, oferecendo maior clareza e escalabilidade em sistemas mais complexos.
```

---

### Definições

#### Objetos

* **O que é:**
  São as entidades fundamentais da programação orientada a objetos. Representam elementos do mundo real (ou conceitual), reunindo em si **características (atributos)** e **comportamentos (métodos)**. Um objeto é, em essência, uma instância de uma classe — uma materialização concreta de uma ideia abstrata.

* **Como podemos aplicar:**
  Utilizamos objetos para modelar problemas reais dentro do sistema. Por exemplo, em um sistema escolar, podemos ter objetos como *Aluno*, *Professor* ou *Turma*, cada um contendo seus próprios dados e ações.

* **Qual a lógica de identificação:**
  Identificamos objetos observando o problema e destacando os “substantivos” relevantes — tudo aquilo que possui identidade própria dentro do contexto analisado.

---

#### Características (Atributos)

* **O que é:**
  São os dados que descrevem o estado de um objeto. Representam suas propriedades, aquilo que o define e o diferencia dos demais.

* **Como podemos aplicar:**
  Atribuímos características aos objetos para armazenar informações. Por exemplo, um objeto *Aluno* pode possuir atributos como *nome*, *idade* e *matrícula*.

* **Qual a lógica de identificação:**
  Identificamos atributos observando as qualidades e propriedades dos objetos — geralmente associadas a adjetivos ou informações descritivas que complementam o substantivo.

---

#### Comportamentos (Métodos)

* **O que é:**
  São as ações que um objeto pode realizar. Representam seu comportamento, ou seja, como ele interage consigo mesmo e com outros objetos.

* **Como podemos aplicar:**
  Definimos métodos para executar operações. Por exemplo, um objeto *Aluno* pode ter métodos como *estudar()*, *realizarProva()* ou *consultarNotas()*.

* **Qual a lógica de identificação:**
  Identificamos comportamentos observando os “verbos” associados aos objetos — ações que fazem sentido dentro do contexto do sistema.