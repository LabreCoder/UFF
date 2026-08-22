# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 19/08/2026 | 📚 Professor: Marcos Bedo | 👨🏾🏫 Aluno: João Victor Labre

# ☕ Aula 06: Índices no PostgreSQL

### 📝 Introdução

Esta aula abordou os aspectos práticos da **implementação e gerenciamento de índices no PostgreSQL**. Vimos como criar índices utilizando a sintaxe nativa do SQL, explorando parâmetros de controle físico (como `FILLFACTOR` e concorrência). Também analisamos o conjunto diversificado de índices nativos do SGBD (B-Tree, Hash, GIN, GiST, SP-GiST), a aplicação de estratégias de otimização física fina (Índices de Expressão e Índices Parciais) e comandos fundamentais de manutenção de arquivos físicos do banco de dados (`CLUSTER`, `REINDEX` e `VACUUM`).

---

### 💡 Conceitos Chave

* **Sintaxe Geral de Criação:** No PostgreSQL, os índices são criados através do comando:
  ```sql
  CREATE [UNIQUE] INDEX [CONCURRENTLY] nome_indice ON nome_tabela 
  USING tipo_indice (nome_coluna [ASC | DESC]) 
  [WITH (FILLFACTOR = taxa_preenchimento)] [TABLESPACE nome_tablespace];
  ```
* **Tipos de Índices Suportados:**
  * **B+ (B-Tree):** O padrão geral para buscas ordenadas e de intervalo.
  * **Hash:** Utilizado para buscas exatas de igualdade.
  * **GIN (*Generalized Inverted Index*):** Índice invertido, altamente eficiente para indexação de textos complexos e documentos semiestruturados (como JSONB).
  * **GiST (*Generalized Search Tree*):** Funciona como um template para estruturar índices especializados customizados, amplamente adotado em visão computacional, dados espaciais e bioinformática.
  * **SP-GiST (*Space-Partitioned GiST*):** Suporta árvores de pesquisa particionadas no espaço (como Quad-Trees e KD-Trees), simplificando a construção de tipos de dados complexos.
* **Índices de Expressão (*Expression Index*):** Úteis para acelerar consultas cujos predicados da cláusula `WHERE` utilizam funções no atributo indexado. Em vez de indexar o valor puro do campo, o SGBD armazena o resultado da expressão pré-computado.
  * **Exemplo:** `CREATE INDEX idx_lower_nome ON pokemon (LOWER(nome));`
* **Índices Parciais:** Índices que abrangem e organizam apenas um subconjunto de tuplas da tabela que satisfazem um predicado lógico. Isso economiza muito espaço físico e reduz o custo de atualização do índice.
  * **Exemplo:** `CREATE INDEX idx_poke_fogo ON pokemon USING btree(codigo) WHERE tipo = 'fogo';`

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Criação Segura com `CONCURRENTLY`:**
> Por padrão, a criação de um índice bloqueia escritas na tabela associada. Ao utilizar a cláusula `CONCURRENTLY`, o PostgreSQL cria o índice sem bloquear leituras ou escritas concorrentes. O ponto de atenção é que **a criação concorrente consome significativamente mais tempo** e exige duas varreduras completas sobre a tabela.
>
> ---
>
> 💡 **O Equilíbrio Fino do `FILLFACTOR`:**
> Este parâmetro define o percentual de espaço que será preenchido em cada nó de índice em disco. As árvores B+ do PostgreSQL usam por padrão um fator de **90**.
>
> * **FILLFACTOR alto (próximo de 100):** O índice fica menor e a altura da árvore diminui, otimizando leituras, mas aumenta severamente o risco de **splits de nós** em updates frequentes.
> * **FILLFACTOR baixo (ex: 70):** Deixa espaço de reserva nas páginas, o que previne splits de nós e melhora o desempenho das operações de atualização (`UPDATE`/`INSERT`), à custa de um índice mais espalhado fisicamente em disco.
>
> ---
>
> 💡 **Índices Secundários e o Comando `CLUSTER`:**
> Todos os índices criados no PostgreSQL são **secundários por padrão** (os dados lógicos na tabela não são fisicamente ordenados de forma sequencial pelo índice). Para reordenar fisicamente a tabela de dados com base na ordem sequencial de um índice específico, usa-se o comando:
> `CLUSTER nome_tabela USING nome_indice;`
> *Lembre-se: o agrupamento do CLUSTER não é mantido de forma automática; novas inserções continuarão sem ordenação física, exigindo nova execução futura do comando.*
>
> ---
>
> 💡 **Manutenção Preventiva de Performance (VACUUM vs. VACUUM FULL):**
> Devido ao mecanismo MVCC do PostgreSQL, atualizações e exclusões não removem fisicamente os dados antigos imediatamente.
>
> * **`VACUUM`:** Libera as tuplas marcadas como mortas/inúteis para reutilização pelo SGBD. Pode rodar em background **sem bloquear a tabela**.
> * **`VACUUM FULL`:** Libera o espaço de dados mortos de volta ao Sistema Operacional e reconstrói as tabelas fisicamente, eliminando qualquer espaço vazio. É um processo **altamente demorado que bloqueia totalmente a tabela**, impedindo leituras e escritas durante a execução.

---

### 📚 Links & Leituras Complementares

* 📖 *PostgreSQL Documentation* — Capítulo Oficial de *Indexes*: [Types of Indexes in Postgres](https://www.postgresql.org/docs/current/indexes-types.html)
* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo sobre *Physical Storage Management*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 05: Estruturas de Índices Baseadas em Árvores (Árvores B e B+)](../Aula_5/README.md)
* ➡️ **Próxima Aula:** [Aula 07: ](../Aula_7/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)