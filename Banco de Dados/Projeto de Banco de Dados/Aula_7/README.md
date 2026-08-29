# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 24/08/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 07: Fragmentação Horizontal (Teoria, FHP, FHD e Corretude)

### 📝 Introdução

Esta aula abordou os conceitos teóricos fundamentais do **particionamento e fragmentação de dados** no contexto de Bancos de Dados Distribuídos. O objetivo principal da fragmentação é dividir as tabelas lógicas em unidades menores (fragmentos) para aproximar fisicamente os dados de onde eles são mais frequentemente processados, reduzindo custos de comunicação e latência na rede. Focamos nos tipos de **Fragmentação Horizontal Primária (FHP)** e **Fragmentação Horizontal Derivada (FHD)**, detalhando os seus algoritmos de geração (como o **COM_MIN**), a formalização de predicados simples e mintermos, e as três regras matemáticas de corretude necessárias para garantir a integridade dos dados distribuídos.

---

### 💡 Conceitos Chave

* **Fragmentação:** Divisão de uma relação ou base de dados em partes lógicas e físicas menores, distribuídas pelos nós do sistema.
* **Classificações Gerais de Fragmentação:**

  * **Fragmentação Horizontal (FH):** Divisão da relação por linhas/tuplas com base em operadores de seleção algébrica ($\sigma$).
  * **Fragmentação Horizontal Primária (FHP):** Particionamento realizado por meio de predicados de seleção aplicados diretamente sobre os atributos da própria tabela que está sendo fragmentada (relação "Dono").
  * **Fragmentação Horizontal Derivada (FHD):** Particionamento aplicado sobre uma tabela "Membro" (filha) com base nos predicados de partição definidos em outra relação "Dono" (pai), utilizando semi-junções ($\ltimes$).
  * **Fragmentação Vertical (FV):** Particionamento da relação por colunas/atributos através de projeções ($\pi$).
  * **Fragmentação Híbrida (FH):** Combinação estruturada entre fragmentações horizontal e vertical.
* **Frequência de Acesso ($\text{acc}(q_i)$):** Métrica que quantifica a frequência com a qual a consulta $q_i$ acessa uma relação/fragmento, usada para ponderar a relevância dos predicados no projeto de fragmentação.
* **Predicados Simples ($p_j$):** Expressões de comparação atômicas no formato $A_i\ \theta\ \text{Val}$, onde $\theta \in \{=, <, \le, >, \ge, \neq\}$:

  * Exemplo 1: $p_1: \text{PNOME} = \text{"Manutenção"}$
  * Exemplo 2: $p_2: \text{ORCAMENTO} \le 200000$
* **Predicados Mintermo ($m_i$):** Conjunções completas baseadas em predicados simples diretos ou negados ($p_j$ ou $\neg p_j$). São mutuamente exclusivos e definem os fragmentos finais da tabela ($R_i = \sigma_{m_i}(R)$):

  * $m_1: \text{PNOME} = \text{"Manutenção"} \land \text{ORCAMENTO} \le 200000$
  * $m_2: \neg(\text{PNOME} = \text{"Manutenção"}) \land \text{ORCAMENTO} \le 200000$
  * $m_3: \text{PNOME} = \text{"Manutenção"} \land \neg(\text{ORCAMENTO} \le 200000)$
  * $m_4: \neg(\text{PNOME} = \text{"Manutenção"}) \land \neg(\text{ORCAMENTO} \le 200000)$
* **Seletividade do Mintermo ($\text{sel}(m_i)$):** Quantidade de tuplas da relação $R$ que satisfazem e são acessadas de acordo com a condição do predicado mintermo $m_i$.

---

#### 🔍 Tópico em Destaque: Algoritmo COM_MIN e Minimalidade de Predicados

O **Algoritmo COM_MIN** tem como objetivo gerar um conjunto completo e mínimo de predicados simples $P_r'$ para derivar os fragmentos mintermos de uma relação $R$:

* **Regra Fundamental (Regra 1):** Uma relação ou fragmento é particionado em pelo menos duas partes que são acessadas de formas distintas por pelo menos uma consulta do conjunto de aplicações.
* **Minimalidade:** Um conjunto $P_r'$ deve ser estritamente mínimo. Se um predicado não contribui para dividir tuplas em blocos acessados diferentemente por consultas reais, ele é irrelevante e deve ser descartado.
* **Passos de Execução:**

1. **Inicialização:**

* Encontre um predicado simples $p_i \in P_r$ de forma que $p_i$ fragmente $R$ de acordo com a Regra 1.
* Defina $P_r' = \{p_i\}$, $P_r \leftarrow P_r - \{p_i\}$ e $F \leftarrow \{f_i\}$.

2. **Iteração:** Adicione iterativamente predicados em $P_r'$ até torná-lo completo:

* Encontre um predicado $p_j \in P_r$ que fragmente algum fragmento $f_k$ (definido sobre os mintermos de $P_r'$) conforme a Regra 1.
* Atualize $P_r' = P_r' \cup \{p_j\}$, $P_r \leftarrow P_r - \{p_j\}$ e $F \leftarrow F \cup \{f_j\}$.
* Identifique e elimine qualquer $p_k \in P_r'$ redundante que não afete a partição final.

---

#### 🔍 Tópico em Destaque: Fragmentação Horizontal Derivada (FHD) e Corretude

* **Definição por Semi-Junção:**
  Em um link de junção $L$ onde $\text{dono}(L) = S$ e $\text{membro}(L) = R$, os fragmentos derivados da tabela membro $R$ são obtidos através de:

$$
R_i = R \ltimes_F S_i \quad (1 \le i \le w)
$$

onde $S_i = \sigma_{F_i}(S)$ representa o fragmento primário correspondente na tabela dona e $w$ é o total de fragmentos.

* **Exemplo Clássico:**
  Dado o link $L_1$ com $\text{dono}(L_1) = \text{SALARIO}$ e $\text{membro}(L_1) = \text{EMPREGADO}$:

  * $\text{SALARIO}_1 = \sigma_{\text{VALOR} \le 30000}(\text{SALARIO})$
  * $\text{SALARIO}_2 = \sigma_{\text{VALOR} > 30000}(\text{SALARIO})$
  * $\text{EMPREGADO}_1 = \text{EMPREGADO} \ltimes \text{SALARIO}_1$
  * $\text{EMPREGADO}_2 = \text{EMPREGADO} \ltimes \text{SALARIO}_2$
* **As 3 Regras de Corretude:**

1. **Completude (Completeness):** Se uma relação $R$ é decomposta em fragmentos $F_R = \{R_1, R_2, \dots, R_n\}$, cada item de dado em $R$ deve pertencer a pelo menos um fragmento $R_i$. Na **FHD**, a completude depende diretamente da garantia de **Integridade Referencial** (ausência de chaves estrangeiras nulas/órfãs).
2. **Reconstrução (Reconstruction):** Deve ser possível reconstruir a relação original $R$ aplicando um operador relacional adequado sobre os fragmentos. Para fragmentação horizontal, utiliza-se a **União**:

$$
R = \bigcup_{i=1}^n R_i
$$

3. **Disjunção (Disjointness):** Garante que não haja tuplas duplicadas entre fragmentos distintos. Se $R$ foi decomposta em $R_1, \dots, R_n$ através de FHP sobre predicados mintermo, então para todo $i \neq j$:

$$
R_i \cap R_j = \emptyset
$$

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Operador de Reconstrução por Tipo de Fragmentação:**
> Na fragmentação **horizontal**, a relação original é reconstruída exclusivamente por **União** ($R = \bigcup R_i$). Na fragmentação **vertical**, o operador mandatório de reconstrução é a **Junção Natural** ($R = \bowtie R_i$) sobre a chave primária.
>
> ---
>
> 💡 **Integridade Referencial na FHD:**
> Na FHD, tuplas da tabela membro sem chave correspondente na tabela dona são descartadas na semi-junção, provocando perda de dados e violando a regra de **Completude**.
>
> ---
>
> 💡 **Eliminação de Mintermos Vazio / Contraditórios:**
> A construção de tabelas-verdade ajuda a identificar predicados mintermos logicamente contraditórios (ex.: $\text{ORCAMENTO} \le 100000 \land \text{ORCAMENTO} > 200000$), permitindo descartá-los antes de gerar os fragmentos físicos.

---

### 📚 Links & Leituras Complementares

* 📖 *Principles of Distributed Database Systems* — M. Tamer Özsu e Patrick Valduriez (Springer, 3ª Edição) — Capítulo 3: *Distributed Database Design* (Algoritmo COM_MIN, FHD e Regras de Corretude).
* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo sobre *Distributed Databases and Fragmentation*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 06: Índices no PostgreSQL](../Aula_6/README.md)
* ➡️ **Próxima Aula:** [Aula 08: Particionamento e Fragmentação Horizontal Avançada](../Aula_8/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
