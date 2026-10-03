# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 28/09/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 13: Execução do QEP (Query Execution Plan)

### 📝 Introdução

Esta aula consolida a etapa final do pipeline de processamento de consultas em um SGBD: a **Execução do QEP (Query Physical Execution Plan)**. A partir do plano de execução físico escolhido na fase de otimização (entrada), o motor de execução (*Query Engine*) interpreta os operadores e algoritmos físicos selecionados para recuperar os dados e retornar o conjunto final de tuplas resultantes ao usuário (saída). Foram analisadas as duas estratégias fundamentais para a transmissão de dados intermediários entre operadores: a **Materialização** e o **Pipelining**.

---

### 💡 Conceitos Chave

* **Execução do QEP:** Fase operacional final do processamento de consultas que interpreta o plano físico e executa a busca e manipulação de dados no banco.
* **Entrada e Saída da Execução:** Recebe como entrada o *Query Physical Execution Plan* selecionado pelo otimizador e entrega como saída a relação final de tuplas para a aplicação.
* **Operadores Físicos de Acesso:** Métodos concretos para leitura de dados em disco, incluindo *Table Scan* (varredura completa), *Index Scan* e *Index Seek* (navegação por índices).
* **Operadores Físicos de Junção:** Algoritmos executáveis para implementar junções, tais como *Nested Loops* (laços aninhados), *Merge Join* (junção por intercalação ordenada) e *Hash Match / Hash Join* (junção baseada em tabela hash).

#### 🔍 Tópico em Destaque: Estratégias de Execução (Materialização vs. Pipelining)

* **Materialização (Estratégia 1):** O plano físico é processado de baixo para cima (*bottom-up*). Cada operação é executada por completo e seu resultado intermediário é salvo em tabelas temporárias em disco antes que o próximo operador possa iniciar. A principal desvantagem é a degradação de desempenho gerada pelo I/O excessivo em disco.
* **Pipelining (Estratégia 2):** Várias operações físicas são executadas simultaneamente em fluxo contínuo (*Non stop-and-go physical operations*). O resultado de um operador é repassado diretamente na memória RAM para o operador pai conforme as tuplas são produzidas, eliminando a gravação de arquivos temporários em disco.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Impacto do Pipelining na Latência:**
> A utilização do *pipelining* evita que o SGBD precise escrever e re-ler gigabytes de resultados intermediários em disco. Mantendo o fluxo de tuplas diretamente na memória RAM, a resposta da consulta é iniciada e entregue de forma significativamente mais rápida.

> 💡 **Operadores "Blocking" e Necessidade de Ordenação:**
> Algoritmos como o *Merge Join* exigem que os dados de entrada estejam ordenados. Caso as tuplas não venham ordenadas por um índice (*Index Seek*), o SGBD é obrigado a introduzir um operador físico de ordenação (*Sort*). Operadores como o *Sort* funcionam como bloqueadores (*blocking*), pois precisam acumular e materializar todo o conjunto de dados antes de entregar a primeira tupla ordenada para o nível superior.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 15: *Query Execution (Pipelining vs. Materialization)*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 19: *Algorithms for Query Processing and Optimization*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 12: Seleção do QEP (Query Physical Execution Plan)](../Aula_12/README.md)
* ➡️️ **Próxima Aula:** [Aula 14: Catálogo e Metadados](../Aula_14/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)