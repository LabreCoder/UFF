# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 05/08/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 02: Revisão de Arquitetura Física e Armazenamento

### 📝 Introdução

Esta aula foca na transição do modelo lógico de banco de dados (estudado em Banco de Dados I) para o **projeto físico**, detalhando como os Sistemas Gerenciadores de Bancos de Dados Relacionais (SGBD) monolíticos estruturam o armazenamento e a memória sob as restrições do hardware e do Sistema Operacional. Foi apresentada a estrutura física de arquivos (Heap Files, páginas físico-lógicas, tuplas), o gerenciamento de fragmentação concorrente (através de mapas auxiliares) e o papel crucial do Buffer Pool na mitigação de latência de disco.

---

### 💡 Conceitos Chave

* **Arquitetura de Armazenamento Físico:** Uma tabela no banco de dados não é um arquivo de texto contínuo, mas um conjunto estruturado onde um arquivo do SO armazena segmentos físicos (como o *relfilenode* de até 1GB). Estes segmentos são compostos por **páginas físico-lógicas de tamanho fixo (normalmente 8KB)** que contêm as tuplas gravadas em disco.
* **Heap Files (Arquivos Não-Ordenados):** As tabelas no PostgreSQL utilizam o formato Heap File, o que significa que os dados não têm uma ordenação física intrínseca. As tuplas novas são inseridas sequencialmente onde houver espaço livre em disco, priorizando a velocidade de escrita em detrimento da ordenação.
* **Buffer Pool:** Atua como um cache persistente e uma **ponte de paginação** entre a memória RAM e o armazenamento em disco. As consultas nunca acessam diretamente os arquivos do Sistema Operacional; em vez disso, as páginas requisitadas são carregadas do disco para o Buffer Pool na RAM para manipulação rápida.

---

#### 🔍 Tópico em Destaque

Níveis de abstração do projeto de banco de dados e seus focos fundamentais:

* **Projeto Conceitual:** Foco em *estar completo* (mapeando todas as regras de negócio do minimundo).
* **Projeto Lógico:** Foco em *estar correto* (mapeamento do MER para tabelas lógicas relacionais).
* **Projeto Físico:** Foco em *ser o mais eficiente* (estruturação interna, índices, particionamento e alocação física de páginas).

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Como podemos otimizar o SGBD?**
> A otimização física ocorre ao organizar índices e estruturas de dados adequadamente, minimizando o custo das operações de E/S (I/O) no disco através de um bom gerenciamento de páginas no Buffer Pool e controlando a fragmentação decorrente das atualizações.

--

> 💡 **Como conciliar as múltiplas threads que estão executando em paralelo?**
> O PostgreSQL utiliza uma arquitetura baseada em processos controlada pelo **postmaster** (Daemon Supervisor), que gera processos filhos independentes (**postgres** de backend) para cada aplicação cliente. A sincronização de acesso concorrente ao disco ocorre por meio de uma **Memória Global Compartilhada** (composta por `shared_buffers`, `WAL buffers` e `Commit Log`) associada a **Memórias Locais Privadas** (`work_mem`) para a execução individual de cada consulta dos usuários. Além disso, o **Mapa de Visualização (VM)** previne conflitos de transação ao mapear o estado de visibilidade de milhares de páginas em disco.

--

> 💡 **O que são SGBD monolíticos?**
> São sistemas que realizam uma "ponte" lógica para implementar operadores e propriedades de banco de dados rodando diretamente sobre os registros físicos e a pilha de chamadas disponibilizadas pelo próprio Sistema Operacional de base.

--

> 💡 **OLTP, o que é?**
> Sistemas transacionais (como PostgreSQL) orientados a linha (*row-oriented*), projetados para cargas de trabalho de alta concorrência compostas de leituras e escritas pontuais focadas em **tuplas ou registros individuais**.

--

> 💡 **Relfilenode:**
> É a representação do segmento de arquivo físico de 1GB correspondente a uma tabela. Cada tabela tem seu Object ID (OID) no catálogo do SGBD diretamente mapeado para o seu respectivo arquivo *relfilenode* por meio do sistema de arquivos FAT ou i-Node do SO.

--

> 💡 **Para buscar uma tupla é necessário apenas saber o offset dela: Tuple ID - TID (page_id, item_id):**
> O **TID** fornece a coordenada física exata de uma tupla no disco utilizando o identificador da página e o índice do item dentro dela. Como o Heap File não é ordenado, os índices primários e secundários guardam esses TIDs apontando direto para essas coordenadas. Isso permite que operações de offset tenham custo constante de tempo $O(1)$, além de possibilitar otimizações físicas (como particionamento e controle de concorrência) sem precisar desfragmentar ou reconstruir os índices globais constantemente.

--

> 💡 **Lembrar que as escritas são feitas em bloco:**
> Devido às severas diferenças de velocidade entre a CPU e os discos físicos, o banco de dados **nunca realiza leitura ou escrita de bytes individuais**. Toda transferência física ocorre em blocos ou páginas físico-lógicas completas de tamanho fixo (8KB no PostgreSQL).

--

> 💡 **Por que o swap de disco é prejudicial à performance?**
> O acesso ao disco possui uma latência extremamente alta se comparado ao acesso de memória RAM e registradores da CPU. Se a aplicação de banco de dados precisar realizar paginação constante com o disco (*swap* / paginação clássica) para ler informações que não cabem no cache, ela se torna dependente do gargalo de I/O (*I/O Bound*), degradando significativamente a performance e destruindo a velocidade de processamento das queries.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 1: Apresentação da Disciplina e Introdução ao Curso](../Aula_1/README.md)
* ➡️ **Próxima Aula:** [Aula 3: Índices e Estruturas de Índices](../Aula_3/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)