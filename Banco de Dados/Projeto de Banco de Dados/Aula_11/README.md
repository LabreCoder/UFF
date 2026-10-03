# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 21/09/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 11: Reescrita da Consulta (Padronização, Simplificação e Melhoria)

### 📝 Introdução

Esta aula aprofundou a fase de **Reescrita de Consultas** dentro do *Query Engine*, processo encarregado de transformar a *Parse Tree* gerada na fase de parsing em um **Plano de Execução Lógico (*Query Logical Execution Plan*)**. Embora a *Parse Tree* inicial já seja teoricamente capaz de recuperar os dados solicitados, existem múltiplos grafos de operadores semanticamente equivalentes que produzem o mesmo resultado, mas com desempenhos drasticamente diferentes. O objetivo da reescrita é reestruturar a consulta por meio de regras de equivalência e heurísticas lógicas para minimizar o volume de dados intermediários processados antes da avaliação física de custos.

---

### 💡 Conceitos Chave

* **Entrada e Saída da Reescrita:** A fase de reescrita recebe como entrada a *Parse Tree* (ou grafo de operadores inicial) e entrega como saída o *Query Logical Execution Plan* reescrito e otimizado.
* **As Três Etapas da Reescrita:**
  1. **Padronização:** Converte a *Parse Tree* em uma estrutura lógica padronizada (*Left Deep Tree*) para servir de base uniforme ao processo de otimização.
  2. **Simplificação:** Elimina redundâncias lógicas aplicando leis da álgebra booleana e regras de idempotência.
  3. **Melhoria (Otimização Lógica):** Aplica regras de transformação algébrica e heurísticas para construir expressões mais eficientes do ponto de vista de desempenho de execução.
* **Simplificação por Idempotência e Leis Lógicas:** Processo que reduz predicados desnecessários através de identidades booleanas:
  * \\(A \lor A \to A\\) e \\(A \land A \to A\\)
  * \\(A \lor \neg A \to \text{True}\\) e \\(A \land \neg A \to \text{False}\\)
  * \\(A \land (A \lor B) \to A\\) e \\(A \lor (A \land B) \to A\\)
  * \\(A \land \text{TRUE} \to A\\), \\(A \lor \text{FALSE} \to A\\), \\(A \lor \text{TRUE} \to \text{True}\\) e \\(A \land \text{FALSE} \to \text{False}\\)

#### 🔍 Tópico em Destaque: Regras de Transformação e Heurísticas de Otimização Lógica

* **Empurrar Seleções para Baixo (*Pushdown Select*):** Heurística fundamental que consiste em mover as operações seletivas (\\(\sigma\\)) para baixo no grafo de consulta, executando os filtros **antes** de operações construtivas e custosas como Junções (\\(\bowtie\\)) e Produtos Cartesianos (\\(\times\\)).
  * *Cascata de Seleções:* \\(\sigma_{\theta_1 \land \theta_2}(R) \to \sigma_{\theta_1}(\sigma_{\theta_2}(R))\\)
  * *Comutatividade de Seleções:* \\(\sigma_{\theta_1}(\sigma_{\theta_2}(R)) \to \sigma_{\theta_2}(\sigma_{\theta_1}(R))\\)
  * *Empurrar Seleção através da Junção:* \\(\sigma_{\theta_1}(R \bowtie_{\theta_2} S) \to (\sigma_{\theta_1}(R)) \bowtie_{\theta_2} S\\) (válido quando o predicado \\(\theta_1\\) envolve apenas atributos da relação \\(R\\)).
* **Empurrar Projeções para Baixo (*Pushdown Project*):** Eliminar colunas e atributos irrelevantes o mais cedo possível para reduzir a largura das tuplas e economizar memória RAM intermediária.
  * *Cascata de Projeções:* \\(\Pi_{A_1}(\Pi_{A_2}(...(\Pi_{A_n}(R))...)) \to \Pi_{A_1}(R)\\).

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **A Regra de Ouro das Heurísticas:**
> Executar operações **seletivas** (filtros \\(\sigma\\) e projeções \\(\Pi\\)) **antes** de operações **construtivas** (junções \\(\bowtie\\) e produtos cartesianos \\(\times\\)). Mover a seleção para baixo diminui a cardinalidade (número de linhas) das tabelas envolvidas antes de realizar o `JOIN`, reduzindo exponencialmente o custo de processamento em memória.

> 💡 **Exemplo Prático de Transformação de Plano:**
> Em uma consulta entre as tabelas `Empregado` e `Departamento` com o filtro `nome_dep = 'DC' AND salário > 8000`:
> 1. Na *Left Deep Tree* inicial, a seleção é aplicada **depois** de realizar a junção de todas as linhas de `Empregado` com `Departamento`.
> 2. No *Query Logical Execution Plan* reescrito, o filtro `salário > 8000` é empurrado diretamente para a tabela `Empregado` e o filtro `nome_dep = 'DC'` para a tabela `Departamento`.
> 3. Em seguida, aplica-se a projeção dos campos estritamente necessários antes de efetuar a junção (\\(\bowtie_{\text{cod\_dep}=\text{lotação}}\\)), resultando em um ganho massivo de performance.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 16: *Algebraic Laws for Transforming Logical Query Plans*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 19: *Heuristics in Query Optimization*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 10: Parsing e Reescrita de Consultas](../Aula_10/README.md)
* ➡️ **Próxima Aula:** [Aula 12: Seleção do QEP (Query Physical Execution Plan)](../Aula_12/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)