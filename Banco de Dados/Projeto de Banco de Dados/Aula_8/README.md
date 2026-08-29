# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 26/08/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 08: Particionamento e Fragmentação Horizontal Avançada

### 📝 Introdução

Esta aula aprofunda a implementação física e as estratégias avançadas de **particionamento horizontal** em Sistemas Gerenciadores de Bancos de Dados (SGBDs) distribuídos e relacionais de grande porte. Deixando para trás a derivação analítica de predicados mintermos vista na teoria de FHP/FHD, o foco aqui recai sobre mecanismos arquiteturais de distribuição: particionamento por **Hash**, particionamento **Composto (Multi-nível)** e particionamento por **Referência (REF Partitioning)**. Analisamos como essas estratégias viabilizam a **Poda de Partições (*Partition Pruning*)**, a co-localização física de dados relacionados e a execução eficiente de junções locais (*Partition-wise Joins*) sem sobrecarga de tráfego de rede.

---

### 💡 Estratégias Avançadas de Particionamento

#### 1. Particionamento por Hash (Hash Partitioning)

Técnica de particionamento físico baseada na aplicação de uma função hash determinística sobre a chave de particionamento ($h(K) \pmod N$), distribuindo os registros de maneira pseudoaleatória e uniforme entre $N$ partições ou nós.

* **Objetivo Principal:** Eliminar assimetrias de carga (*data skew*) e gargalos de I/O (*hotspots* de escrita/leitura).
* **Características Arquiteturais:**
* Não guarda relação direta com predicados semânticos de negócio (ex.: intervalos de datas ou categorias).
* O projetista não tem controle semântico sobre em qual partição uma linha específica ficará alocada.
* Consultas pontuais por chave exata (`WHERE id = 1234`) executam com acesso direto a uma partição específica (*single partition scan*).


* **Limitação Operacional:** Ineficiente para consultas por intervalo (`WHERE valor BETWEEN 10 AND 50`), exigindo varredura de todas as partições em modo *scatter-gather* (espalha-e-reúne).

---

#### 2. Particionamento Composto (Composite Partitioning / Subparticionamento)

Aplica uma estrutura hierárquica de particionamento de **dois níveis** sobre a mesma tabela lógica, combinando métodos ortogonais para atender a múltiplos padrões de acesso e estratégias de retenção de dados.

* **Combinações Clássicas:**
* **Range – List:** Nível 1 particiona por intervalos contínuos (ex.: `data_venda`); Nível 2 subparticiona por conjuntos discretos (ex.: `regiao_uf` ou `pais`).
* **Range – Hash:** Nível 1 particiona por intervalo temporal; Nível 2 distribui as tuplas daquele período por hash de um identificador (ex.: `cliente_id` ou `loja_id`) para balancear I/O.
* **List – Hash:** Nível 1 particiona por domínios categóricos (ex.: tipo de operação ou filial); Nível 2 subparticiona por hash da chave primária.


* **Benefício de Manutenção (*Data Lifecycle Management*):** Permite arquivamento ou descarte rápido de dados legados no nível 1 (desacoplando ou expurgando uma partição por data inteira via `DROP/DETACH PARTITION`) mantendo a concorrência balanceada no nível 2.

---

#### 3. Particionamento por Referência (REF Partitioning)

Mecanismo no qual uma tabela dependente/filha herda e replica automaticamente a estratégia e o chaveamento de partição da tabela pai com a qual mantém um relacionamento de chave primária e estrangeira (`PK` $\to$ `FK`).

* **Mecanismo de Propagação:**
* Não exige desnormalização ou duplicação manual da coluna de partição na tabela filha.
* As partições da tabela membro são geradas em correspondência biunívoca ($1:1$) com as partições da tabela dona.


* **Vantagem de Desempenho (*Partition-wise Joins*):**
* Quando duas tabelas relacionadas compartilham o mesmo esquema de particionamento e estão co-localizadas no mesmo nó/disco, operações de junção ($R \bowtie S$) são executadas exclusivamente dentro de cada partição local, eliminando o custo de transferência de dados (*shuffle/repartition*) pela rede do cluster.


* **Propagação de Manutenção (DDL Cascading):** Operações como divisão de partição (*split*), mesclagem (*merge*) ou expurgo (*drop*) na tabela dona são propagadas automaticamente para as partições correspondentes da tabela dependente.

---

### 🔍 Comparativo Técnico das Estratégias

| Estratégia | Critério de Divisão | Suporte a Poda (*Pruning*) | Caso de Uso Primário | Principal Trade-off |
| --- | --- | --- | --- | --- |
| **Range** | Intervalos contínuos e ordenados (datas, valores) | Excelente para ranges e filtros escalares | Séries temporais, logs de auditoria e auditoria financeira | Risco alto de *data skew* nas partições mais recentes |
| **List** | Listas explícitas de valores discretos | Excelente para filtros de igualdade categórica | Segmentação por filial, região, estado ou status | Requer manutenção quando novos domínios surgem |
| **Hash** | Função hash matemática $h(K)$ | Apenas buscas exatas por igualdade (`=`, `IN`) | Distribuição uniforme de carga e prevenção de *hotspots* | Consultas por intervalo exigem varredura completa (*all partitions scan*) |
| **Composite** | Combinação hierárquica de 2 métodos | Híbrido (podas em múltiplos níveis) | Tabelas massivas com ciclos de vida temporais e alto volume de escrita | Maior complexidade operacional e overhead de metadados |
| **REF Partitioning** | Herança automática via vínculo PK-FK | Otimizado via chave de partição da tabela pai | Relacionamentos 1:N frequentes (ex.: Pedido $\to$ Itens_Pedido) | Dependência estrita de integridade referencial ativa e indexada |

---

### ⚙️ Mecanismos de Otimização e Execução

#### Poda de Partições (*Partition Pruning*)

Capacidade do otimizador de consultas de analisar a cláusula `WHERE` da instrução SQL antes da execução e restringir a leitura exclusivamente às partições físicas que contêm tuplas compatíveis, ignorando completamente as demais:

* **Poda Estática:** Determinada em tempo de compilação quando os predicados utilizam constantes literais (ex.: `WHERE data_venda >= '2026-01-01'`).
* **Poda Dinâmica:** Determinada durante a execução quando os predicados dependem de subconsultas, variáveis vinculadas (*bind variables*) ou parâmetros de junção.

#### Co-localização e *Partition-wise Joins*

* **Full Partition-wise Join:** Ocorre quando ambas as tabelas estão particionadas na mesma chave (ou vinculadas por REF) com o mesmo número de partições, permitindo que o SGBD execute a junção partição a partição em paralelo sem comunicação entre nós.
* **Partial Partition-wise Join:** Ocorre quando apenas uma das tabelas está particionada; o SGBD particiona dinamicamente a relação não particionada em tempo de execução para casar com as partições da primeira.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Escolha da Chave de Particionamento:**
> A chave de partição deve ser escolhida com base no predicado mais frequente nas consultas críticas (`WHERE`) ou na coluna de junção mais custosa (`JOIN`). Uma escolha incorreta pode forçar o otimizador a executar *Full Partition Scans* em todo o banco.
> ---
> 💡 **Indexação Local vs. Global:**
> * **Índices Locais:** O índice é particionado de forma alinhada com a própria tabela (cada partição possui seu índice isolado). Favorece a manutenção e a poda.
> * **Índices Globais:** Um único índice cobre a tabela inteira, atravessando as partições. Acelera consultas pontuais que não usam a chave de partição, mas onera operações de manutenção (ex.: um `DROP PARTITION` pode invalidar o índice global).
> ---
> 💡 **Integridade Referencial no REF Partitioning:**
> A chave estrangeira que dá suporte ao particionamento por referência deve ser explicitamente declarada com restrição `NOT NULL` e `FOREIGN KEY` habilitada para que o otimizador possa garantir matematicamente a corretude da poda.

---

### 📚 Links & Leituras Complementares

* 📖 *Principles of Distributed Database Systems* — M. Tamer Özsu e Patrick Valduriez (Springer, 3ª Edição) — Capítulo 3 e 4: *Physical Database Design and Advanced Partitioning*.
* 📖 *Oracle Database VLDB and Partitioning Guide* — Documentação oficial sobre *Partitioning Strategies, Composite Partitioning, and Reference Partitioning*.
* 📖 *Designing Data-Intensive Applications* — Martin Kleppmann (O'Reilly) — Capítulo 6: *Partitioning / Sharding*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 07: Fragmentação Horizontal (Teoria, FHP, FHD e Corretude)](../Aula_7/README.md)
* ➡️ **Próxima Aula:** [Aula 09: ](../Aula_9/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)