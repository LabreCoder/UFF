# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 17/08/2026 | 📚 Professora: Rebeca Motta | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 03: Modelos de Ciclo de Vida — RUP e Métodos Ágeis

### 📝 Introdução

A terceira aula presencial da disciplina **TCC00225 — Engenharia de Software**, ministrada pela **Profª. Rebeca Motta**, deu continuidade ao estudo dos modelos de ciclo de vida de desenvolvimento, concentrando-se nas abordagens modernas voltadas para o desenvolvimento iterativo, incremental e ágil. O curso aprofundou-se no **Processo Unificado da Rational (RUP)** — analisando suas fases focadas em mitigação de riscos de engenharia baseadas em casos de uso e de arquitetura, bem como sua distribuição de disciplinas de engenharia e apoio ao longo das iterações — e, em seguida, explorou o paradigma ágil através do **Manifesto Ágil**, do framework **Scrum** (com suas cerimônias, papéis e artefatos) e das práticas técnicas do **Extreme Programming (XP)**. Ao final da aula, foram discutidos os critérios de decisão multidimensionais para a seleção do modelo de ciclo de vida ideal, avaliando características do problema, da equipe e do produto.

---

### 💡 Conceitos Chave

* **Rational Unified Process (RUP):** É um processo de desenvolvimento de software moderno caracterizado por ser **centrado na arquitetura**, **guiado por casos de uso** e **iterativo e incremental**. O RUP equilibra as fases e disciplinas de desenvolvimento dividindo o ciclo de vida em 4 fases sequenciais bem demarcadas por marcos (*milestones*):

  * *Concepção (Inception):* Estabelece o caso de negócio e o escopo do projeto, identificando os atores e casos de uso essenciais.
  * *Elaboração (Elaboration):* Foco no detalhamento dos requisitos e na definição/validação de uma arquitetura executável robusta para mitigar riscos técnicos.
  * *Construção (Construction):* Codificação e integração em massa do sistema baseado na arquitetura validada.
  * *Transição (Transition):* Implantação do software, testes no ambiente de homologação dos usuários, treinamento e conversão de dados.
  * *Fluxos de Trabalho (Disciplinas):* O RUP define 9 fluxos que permeiam as fases (6 básicos de engenharia: Modelagem do Negócio, Requisitos, Análise & Projeto, Implementação, Testes, Implantação; e 3 de apoio: Gerenciamento, Gerência de Configuração e Mudanças, Ambiente). O esforço dedicado a cada disciplina varia conforme a fase e a iteração corrente.
* **Manifesto Ágil:** Surgiu na década de 1990 em oposição aos processos tradicionais rígidos e excessivamente focados em documentação. Baseia-se em 4 valores centrais:

  * *Indivíduos e interações* mais que processos e ferramentas.
  * *Software em funcionamento* mais que documentação abrangente.
  * *Colaboração com o cliente* mais que negociação de contratos.
  * *Responder a mudanças* mais que seguir um plano.
* **Scrum (Framework Ágil):** Framework iterativo e incremental projetado para o gerenciamento ágil de equipes de desenvolvimento. Organiza-se em:

  * *Papéis:* **Product Owner (PO)** (define requisitos, prioriza o Backlog e gerencia o ROI), **Scrum Master** (garante as práticas do Scrum e remove impedimentos) e o **Time de Desenvolvimento** autogerenciado.
  * *Cerimônias:* Reuniões de **Planejamento da Sprint** (criação do Sprint Backlog), **Daily Scrum** (reuniões diárias rápidas), **Sprint Review** (demonstração de funcionalidades prontas) e **Sprint Retrospective** (melhoria contínua de processos).
  * *Artefatos:* **Product Backlog** (lista dinâmica de requisitos prioritários), **Sprint Backlog** (tarefas da iteração atual), **Quadro Scrum** (Kanban de progresso visual) e **Gráficos Burndown** (horas restantes estimadas vs. consumidas).
* **Extreme Programming (XP):** Método ágil que foca em altíssima disciplina técnica e feedback rápido. Divide suas práticas em:

  * *Programação:* **Programação em Pares** (dois desenvolvedores no mesmo computador reduzem erros e estimulam ideias), **Design Incremental** (solução mais simples e refatoração constante), além de Integração Contínua e TDD.
  * *Desenvolvimento:* **Histórias de Usuário** descritas em pequenos cartões, estimadas em **Story Points** (usando *Planning Poker*) em **Ciclos Semanais e Trimestrais**.
  * *Gerenciamento:* **Sentar-se Junto** (sala aberta para comunicação ágil), **Trabalho Energizado** (horas sustentáveis evitando esgotamento mental) e **Ambiente Informativo**.

#### 🔍 Tópico em Destaque

**Processo Unificado (RUP) × Métodos Ágeis (Scrum / XP)**

* **RUP:** Focado em arquitetura e mitigação de riscos estruturais nas fases iniciais (Elaboração), utiliza formalidade intermediária/alta e é guiado por Casos de Uso com disciplinas explícitas de engenharia.
* **Métodos Ágeis:** Focados em ciclos muito curtos de entrega contínua, colaboração intensa, resposta rápida a mudanças e código executável sobre documentação extensiva, priorizando simplicidade técnica e autorregulação do time.

---

### ⚠️ Pontos de Atenção & Dicas

> 📌 **A Tríade de Critérios para Escolha de Modelo de Ciclo de Vida:**
> A decisão por um ciclo de vida tradicional, incremental ou ágil deve ser respaldada por critérios formais:
>
> * **Relacionados ao Problema:** Complexidade, grau de maturidade do domínio de aplicação e frequência esperada de mudanças nos requisitos.
> * **Relacionados às Pessoas:** Experiência da equipe no domínio e em Engenharia de Software, disponibilidade e facilidade de expressão dos usuários.
> * **Relacionados ao Produto:** Tamanho total do sistema e complexidade técnica da aplicação.
>
> ---
>
> 💡 **O Paradoxo da Documentação Ágil:**
> Um dos principais erros de equipes iniciantes em métodos ágeis é negligenciar completamente a modelagem e a documentação técnica. O RUP e os Métodos Ágeis não são mutuamente exclusivos na prática; ambos buscam reduzir riscos por meio de iterações constantes, porém com diferentes níveis de formalidade exigidos.

---

### 📚 Links & Leituras Complementares

* 📖 **The Scrum Guide:** [Guia Oficial do Framework Scrum](https://scrumguides.org/)
* 📖 **Manifesto Ágil:** [Valores e Princípios Originais](https://agilemanifesto.org/iso/ptbr/manifesto.html)
* 📖 **Extreme Programming Práticas:** [Filosofia XP por Kent Beck](http://www.extremeprogramming.org/)
* 📖 **UML Distilled (Martin Fowler):** Livro de referência sobre a modelagem visual usada no RUP e nas Histórias de Usuário.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 2: Modelos de Ciclo de Vida — Métodos Tradicionais](../Aula_2/README.md)
* ➡️ **Próxima Aula:** [Aula 4: Introdução à Engenharia de Requisitos](../Aula_4/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
