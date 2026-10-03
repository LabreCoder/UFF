# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 14/09/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍‍🏫 Aluno: João Victor Labre

# ☕ Aula 09: Processamento de Consultas

### 📝 Introdução

Esta aula abordou o conceito fundamental de **Processamento de Consultas** em Sistemas Gerenciadores de Bancos de Dados Relacionais (SGBD). Compreendemos como uma consulta expressa em uma linguagem declarativa de alto nível (como SQL) é recebida pelo sistema e transformada passo a passo em um plano executável de baixo nível. Foram apresentados a arquitetura do **Query Engine**, as formas de representação intermediárias (como Árvores de Parsing e Álgebra Relacional) e o pipeline de execução composto por parsing, reescrita lógica, otimização baseada em custos e geração de planos físicos.

---

### 💡 Conceitos Chave

* **Processamento de Consulta:** Conjunto sequencial de atividades e transformações envolvidas na recuperação eficiente dos dados requisitados por uma consulta expressa em linguagem de alto nível.
* **Linguagens de Consulta de Alto Nível:** Interface próxima da linguagem natural que permite especificar **quais** dados recuperar e manipular (SQL, QUEL, QBE). Além do DML (manipulação) e DDL (definição de estruturas), abrange a especificação de restrições de integridade (`NOT NULL`, `CHECK`) e controle de acesso e segurança (`GRANT`, `REVOKE`).
* **Formas de Representação Intermediárias:** Como computadores não executam expressões declarativas diretas, as consultas SQL de alto nível precisam ser traduzidas para modelos matemáticos e abstratos operacionais. As principais formas incluem:
  * **Álgebra Relacional** e **Cálculo Relacional**.
  * **Grafos de Operadores** e **Left Deep Trees**.
  * **Tableaus** e **Grafos de Objetos**.
* **Pipeline e Componentes do Query Engine:**
  * **Compilador DML e Parser:** Executam a análise sintática e semântica sobre a consulta para construir a **Parse Tree**.
  * **Mapeador e Padronização:** Convertem a *Parse Tree* em um plano lógico inicial (*Query Logical Plan*), frequentemente estruturado como uma *Left Deep Tree*.
  * **Otimizador e Reescrita:** Realizam simplificações lógicas, reescritas e reordenações de operadores para melhorar o plano lógico.
  * **Gerenciador de Estatísticas e Catálogo:** Fornecem métricas (tamanho das tabelas, seletividade, cardinalidade e índices disponíveis) indispensáveis para a **Avaliação de Custos**.
  * **Seletor e Executor de QEP (*Query Execution Plan*):** Escolhem o plano físico de menor custo estimado (*Query Physical Plan*) e o enviam para execução no motor de armazenamento.

---

### ⚠️️ Pontos de Atenção & Dicas

> 💡 **Da Declaração à Execução Operacional:**
> A linguagem SQL é estritamente **declarativa** (o usuário especifica *o que* deseja obter, sem ditar *como* a busca deve ser feita em disco). A grande responsabilidade do SGBD no processamento de consultas é justamente traduzir essa intenção em uma sequência **procedural e física** otimizada de operadores de I/O de baixo nível.

> 💡 **Estruturação da Left Deep Tree:**
> Durante o mapeamento do plano lógico, o SGBD padroniza e transforma a *Parse Tree* em uma **Left Deep Tree**. Essa estrutura de árvore de operadores prioriza ter como filho direito apenas relações base (tabelas), facilitando o pipelining (encadeamento de memória) entre as operações sem a necessidade de materializar tabelas intermediárias temporárias em disco.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 15: *Query Execution* e Capítulo 16: *The Query Compiler*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 19: *Strategies for Query Processing and Optimization*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 08: Particionamento e Fragmentação Horizontal Avançada](../Aula_8/README.md)
* ➡️️ **Próxima Aula:** [Aula 10: Parsing e Reescrita de Consultas](../Aula_10/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)