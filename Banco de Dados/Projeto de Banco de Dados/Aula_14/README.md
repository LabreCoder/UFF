# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 30/09/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 14: Catálogo e Metadados

### 📝 Introdução

Esta aula abordou o papel estratégico do **Catálogo de Dados e Metadados** nos Sistemas Gerenciadores de Bancos de Dados Relacionais (SGBD). O catálogo funciona como um repositório interno que armazena informações descritivas sobre o próprio sistema e suas estruturas físicas e lógicas. Ele serve como base para o pipeline de processamento de consultas, fornecendo os metadados e as métricas estatísticas indispensáveis para as etapas de parsing, validação semântica e, principalmente, para a **estimativa de custos e seleção do plano de execução físico (QEP)** pelo otimizador.

---

### 💡 Conceitos Chave

* **Catálogo e Metadados:** Coleção de informações mantidas pelo SGBD sobre suas próprias estruturas (dados sobre dados).
* **Tabelas de Catálogo:** Tabelas especiais do sistema organizadas para armazenar os metadados de forma estruturada e relacional.
* **Metadados de Tabelas:** Mapeiam o nome de cada tabela, o nome e tipo de cada atributo, as restrições de integridade, os índices associados e a estrutura dos arquivos de armazenamento em disco.
* **Metadados de Índices:** Registram o nome e tipo de cada índice (B-Tree, Hash, etc.), os atributos da chave de busca e os arquivos físicos em disco onde os dados do índice estão salvos.
* **Acesso e Consulta via SQL:** Uma das principais vantagens da arquitetura de catálogo é ser composta por tabelas, permitindo que administradores (DBA) e o próprio sistema realizem consultas aos metadados utilizando comandos SQL convencionais.

#### 🔍 Tópico em Destaque: Estatísticas Mantidas pelo Catálogo

Para permitir a avaliação precisa de custos dos planos físicos de execução (QEP), o SGBD calcula e mantém estatísticas sobre tabelas e índices:
* **\\(n_r\\) (Cardinalidade da relação \\(r\\)):** Número total de tuplas contidas na tabela \\(r\\).
* **\\(p_r\\) (Páginas físicas):** Número de páginas/blocos em disco utilizados para armazenar as tuplas de \\(r\\).
* **\\(s_r\\) (Tamanho da tupla):** Tamanho médio em bytes de cada registro de \\(r\\).
* **\\(f_r\\) (Fator de bloco/página):** Quantidade de tuplas de \\(r\\) que cabem em uma única página.
* **\\(V(A, r)\\) (Valores distintos):** Número de valores distintos presentes no atributo \\(A\\) da tabela \\(r\\) (se \\(A\\) for chave primária ou única, \\(V(A, r) = n_r\\)).
* **\\(HT_i\\) (Altura do índice):** Número de níveis de altura na estrutura física do índice \\(i\\).
* **\\(FS(A, r)\\) (Fator de Seleção):** Número estimado de tuplas que satisfazem a uma condição de igualdade sobre o atributo \\(A\\) (\\(A = k\\)). Se \\(A\\) for chave, \\(FS = 1\\); caso contrário, utiliza-se a análise por **Histogramas**.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Estatísticas Desatualizadas e a Regra *Garbage In, Garbage Out*:**
> As estatísticas do catálogo são atualizadas periodicamente para evitar o overhead de recalculá-las a cada operação de inserção ou exclusão. No entanto, manter estatísticas desatualizadas pode fazer com que o otimizador calcule custos com base em premissas falsas, levando à escolha de um QEP ineficiente (*Garbage in, Garbage out*).

> 💡 **Consultando o Catálogo no PostgreSQL:**
> No PostgreSQL, o catálogo do sistema pode ser inspecionado por meio de tabelas e visões do esquema `pg_catalog`:
> * **Listar tabelas públicas:** `SELECT tablename FROM pg_tables WHERE schemaname LIKE 'public';`
> * **Inspecionar classe/tabela:** `SELECT * FROM pg_class WHERE relname = 'lineitem';`
> * **Listar índices de uma tabela:** `SELECT indexname FROM pg_indexes WHERE schemaname LIKE 'public' AND tablename LIKE 'lineitem';`

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 16: *System Catalogs and Cost Estimation*.
* 📖 *PostgreSQL Documentation* — [System Catalogs (`pg_catalog`)](https://www.postgresql.org/docs/current/catalogs.html).

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 13: Execução do QEP (Query Execution Plan)](../Aula_13/README.md)
* ➡️ **Próxima Aula:** [Aula 15: ...](../Aula_15/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)