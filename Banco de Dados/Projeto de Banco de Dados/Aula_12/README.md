# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 23/09/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 12: Seleção do QEP (Query Physical Execution Plan)

### 📝 Introdução

Esta aula abordou a fase final da compilação de consultas no *Query Engine*: a **Seleção do Plano de Execução Físico (QEP)**. Após a consulta passar pelas etapas de *parsing* e reescrita lógica, o SGBD precisa mapear os operadores lógicos para algoritmos físicos concretos de acesso e manipulação de dados em disco. O objetivo central dessa fase é navegar pelo espaço de busca e selecionar o **QEP de menor custo estimado** ou que apresente um desempenho aceitável de execução.

---

### 💡 Conceitos Chave

* **Plano de Execução de Consulta (QEP — *Query Physical Execution Plan*):** Estrutura em formato de grafo de operadores anotado que descreve a sequência exata de operações físicas e procedimentos executados pelo motor de armazenamento. Ele mapeia o caminho desde a leitura das tabelas existentes até a entrega do resultado final ao usuário.
* **Entrada e Saída do Otimizador:** O processo de seleção recebe como entrada o *Query Logical Execution Plan* reescrito e produz como saída o *Query Physical Execution Plan* (QEP).
* **Espaço de Busca (*Search Space*):** Representa o conjunto de todos os planos de execução físicos equivalentes e possíveis para resolver uma determinada consulta.
* **Métrica de Desempenho e Custo:** A estimativa de custo de um QEP é calculada prioritariamente com base na **quantidade de acessos a disco (E/S ou I/O de páginas/blocos)** necessários para processar a consulta.

#### 🔍 Tópico em Destaque: Abordagens para Seleção do QEP

* **Otimização Baseada em Custo (*Cost-Based Optimization* — CBO):**
  * **Funcionamento:** O otimizador gera os planos físicos possíveis dentro do espaço de busca, calcula a estimativa de custo para cada um utilizando dados estatísticos do Catálogo e escolhe o QEP com a menor estimativa.
  * **Vantagens & Desvantagens:** Tende a sempre encontrar o QEP ótimo, mas o tempo de busca pode ser elevado devido à exploração combinatória de múltiplos caminhos e estruturas de índices.
* **Otimização Baseada em Heurísticas (*Heuristic-Based Optimization*):**
  * **Funcionamento:** Seleciona o plano aplicando um conjunto pré-definido de regras empíricas e heurísticas diretas de transformação.
  * **Vantagens & Desvantagens:** O processo de escolha é executado de forma extremamente rápida, mas não há garantia matemática de que o QEP selecionado seja o ótimo.
* **Abordagens Híbridas:** Combinam regras heurísticas para podar caminhos inviáveis do espaço de busca e, em seguida, aplicam estimativas de custo apenas sobre os planos remanescentes.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **O Trade-off entre Tempo de Otimização e Tempo de Execução:**
> A otimização baseada em custo pura pode sofrer de uma explosão combinatória no espaço de busca em consultas complexas que envolvem muitas junções (`JOINs`) e múltiplos índices disponíveis. Nesses cenários, explorar 100% dos planos possíveis pode custar mais tempo de processamento do CPU do que o próprio tempo necessário para executar a consulta em disco. Por isso, os SGBDs comerciais utilizam abordagens híbridas ou algoritmos de programação dinâmica para podar o espaço de busca.

> 💡 **I/O de Páginas como Métrica Dominante:**
> Como o acesso ao disco possui uma latência ordens de grandeza superior ao acesso à memória RAM e registradores do processador, a métrica primária considerada na avaliação de custo de um QEP é o número estimado de páginas/blocos físicos lidos do disco.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 16: *Completing the Physical-Query-Plan Selection*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 19: *Cost Estimation in Query Optimization*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 11: Reescrita da Consulta (Padronização, Simplificação e Melhoria)](../Aula_11/README.md)
* ➡️ **Próxima Aula:** [Aula 13: Execução do QEP (Query Execution Plan)](../Aula_13/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)