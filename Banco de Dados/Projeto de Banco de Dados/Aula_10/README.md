# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 16/09/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 10: Parsing e Reescrita de Consultas

### 📝 Introdução

Esta aula detalhou a primeira grande etapa do **Query Engine**: a fase de **Parsing** (Análise Gramatical) e **Reescrita de Consultas**. Vimos como a instrução SQL em texto enviada pelo usuário é recebida pelo SGBD e submetida a verificações sintáticas e semânticas antes de ser mapeada para uma estrutura interna denominada *Parse Tree*. Essa representação estruturada é convertida em um **Grafo de Operadores** da álgebra relacional e padronizada (geralmente como uma *Left Deep Tree*), servindo de entrada para os módulos de simplificação, avaliação de custos e geração do plano de execução físico (QEP).

---

### 💡 Conceitos Chave

* **Parsing:** Fase inicial do processamento de consultas encarregada de analisar a instrução SQL declarativa do usuário e transformá-la em uma árvore de análise (*Parse Tree*).
* **Analisador Sintático e Semântico:** Componentes que validam se a consulta obedece às regras gramaticais do SQL (sintaxe) e se os elementos citados (tabelas, colunas e tipos de dados) existem e são acessíveis conforme o Catálogo do banco (semântica).
* **Mapeador (*Mapper*):** Módulo que traduz a *Parse Tree* em uma forma interna de representação baseada em operadores da álgebra relacional.
* **Grafo de Operadores (*Operator Graph* — \\(OG(Q) = (V,E)\\)):** Estrutura de grafo direcionado na qual cada vértice \\(v \in V\\) representa um operador relacional (como Projeção \\(\Pi\\), Seleção \\(\sigma\\) e Junção \\(\bowtie\\)) ou uma tabela de dados, e cada aresta \\(e \in E\\) representa o fluxo de dados (*dataflow*) entre eles.
* **Padronização (*Left Deep Tree*):** Etapa que reorganiza o grafo de operadores em uma estrutura de árvore padronizada para facilitar a fase posterior de reescrita, simplificação e otimização lógica.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Grafo de Operadores e Fluxo de Dados (*Dataflow*):**
> No Grafo de Operadores \\(OG(Q) = (V,E)\\), a direção das arestas indica exatamente o fluxo de dados intermediários. A leitura inicia-se nos nós folha (tabelas base) e os dados fluem para cima através de filtros de Seleção (\\(\sigma\\)) e junções (\\(\bowtie\\)), culminando na projeção final (\\(\Pi\\)) na raiz.

> 💡 **Simplificação e Otimização Lógica Antes do Custo:**
> A fase de reescrita aplica regras de equivalência algébrica para simplificar e melhorar o plano lógico antes de consultar o Catálogo e o Gerenciador de Estatísticas. Isso reduz a busca por planos físicos, eliminando redundâncias e reordenando seleções antecipadamente.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 16: *The Query Compiler (Parsing & Expression Trees)*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 19: *Query Processing and Optimization (Parsing and Syntax Trees)*.

---

### 🧭 Navegação

* ⬅️️ **Aula Anterior:** [Aula 09: Processamento de Consultas](../Aula_9/README.md)
* ➡️ **Próxima Aula:** [Aula 11: Reescrita da Consulta (Padronização, Simplificação e Melhoria)](../Aula_11/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)