# 🧪 Exercício Prático — Aula 02: Arquitetura Física e Buffer Pool

> **Aula de referência:** [`README.md`](./README.md) — Revisão de Arquitetura Física e Armazenamento

## 🎯 Objetivo

Tirar a "arquitetura física" do papel: enxergar o *relfilenode*, o crescimento do Heap File em disco e a diferença entre um acesso "frio" (disco) e um acesso "quente" (Buffer Pool) usando ferramentas nativas do PostgreSQL.

## ⚙️ Preparação

```bash
docker compose up -d
docker exec -i pbd_postgres psql -U aluno -d projeto_bd < Aula_2/scripts/setup.sql
docker exec -it pbd_postgres psql -U aluno -d projeto_bd
```

O `setup.sql` cria a tabela `pedidos` (sem índices) e popula com 200.000 linhas via `generate_series`.

## 📋 Tarefas

1. **Encontre o arquivo físico da tabela**

   ```sql
   SELECT pg_relation_filepath('pedidos');
   SELECT relfilenode, relpages, reltuples FROM pg_class WHERE relname = 'pedidos';
   ```

   Rode `docker exec -it pbd_postgres bash -c "ls -lh $(caminho retornado acima)*"` (ajuste o caminho para dentro do container: `/var/lib/postgresql/data/<caminho>`) e observe: a tabela virou **um ou mais arquivos de até 1GB**? Quantas páginas (`relpages`) isso representa, sabendo que cada página tem 8KB?

   Ex.: `docker exec -it pbd_postgres bash -c "ls -lh /var/lib/postgresql/data/base/16384/16388*"`
2. **Inspecione uma página crua com `pageinspect`**

   ```sql
   SELECT * FROM heap_page_items(get_raw_page('pedidos', 0)) LIMIT 10;
   ```

   Identifique nas colunas `lp`, `t_ctid` e `t_data` como cada tupla ocupa um slot dentro da página. As tuplas estão em ordem pelo `id`? Isso confirma ou contradiz a definição de Heap File (não ordenado) da aula?
3. **Cold start vs Buffer Pool aquecido**

   ```sql
   -- reinicia as estatísticas de buffer da sessão
   DISCARD ALL;
   EXPLAIN (ANALYZE, BUFFERS) SELECT * FROM pedidos WHERE id = 150000;
   -- rode a MESMA query de novo, sem fechar a sessão
   EXPLAIN (ANALYZE, BUFFERS) SELECT * FROM pedidos WHERE id = 150000;
   ```

   > ⚠️ **Nota Prática sobre o `shared read` no Cold Start:**
   > Se a 1ª execução já retornar `shared hit` em vez de `shared read`, isso ocorre porque o comando `DISCARD ALL` limpa apenas o cache da sessão, mas os blocos da tabela/índice já foram carregados no **Buffer Pool compartilhado** durante a execução do `setup.sql` ou da Tarefa 2.
   > Para forçar um **Cold Start real** (leituras físicas em disco):
   > ---
   > 1. **Reinicie o container** no terminal: `docker restart pbd_postgres` e reconecte.
   > 2. Execute a consulta imediatamente: você verá `Buffers: shared read=4` (3 páginas do índice B-Tree + 1 do Heap).
   > 3. Na segunda execução consecutiva, observe a transição para `Buffers: shared hit=4` (`read=0`).
   >

   Compare `shared hit` (páginas já no Buffer Pool) contra `shared read` (páginas lidas do disco) nas duas execuções. Explique a diferença citando o papel do Buffer Pool como "ponte de paginação" descrito na aula.
4. **Crescimento do arquivo e reuso de espaço (FSM & VACUUM)**

* **Parte A — Inserção sequencial e crescimento proporcional:**
  ```sql
  -- Anote o relpages antes:
  SELECT relpages, reltuples FROM pg_class WHERE relname = 'pedidos';

  -- Insira mais 50.000 linhas:
  INSERT INTO pedidos (id, cliente_id, valor)
  SELECT gs,
        (random() * 5000)::INT,
        (random() * 1000)::NUMERIC(10,2)
  FROM generate_series(200001, 250000) AS gs;

  ANALYZE pedidos;

  -- Verifique o novo tamanho:
  SELECT relpages, reltuples FROM pg_class WHERE relname = 'pedidos';
  ```

*O tamanho (`relpages`) cresceu de forma proporcional (+25%)?*

* **Parte B — Deleção, VACUUM e preenchimento de buracos:**
  ```sql
  -- 1. Delete as primeiras 10.000 linhas
  DELETE FROM pedidos WHERE id BETWEEN 1 AND 10000;

  -- 2. Limpe o espaço morto e atualize o Free Space Map (execute individualmente)
  VACUUM pedidos;

  -- 3. Insira 5.000 novas linhas
  INSERT INTO pedidos (id, cliente_id, valor)
  SELECT gs,
        (random() * 5000)::INT,
        (random() * 1000)::NUMERIC(10,2)
  FROM generate_series(300001, 305000) AS gs;

  ANALYZE pedidos;

  -- 4. Inspecione se o arquivo expandiu ou se reaproveitou páginas existentes
  SELECT relpages, reltuples FROM pg_class WHERE relname = 'pedidos';

  -- 5. (Opcional) Verifique se a página 0 recebeu as novas tuplas (IDs 300001+)
  SELECT lp, t_ctid, t_data 
  FROM heap_page_items(get_raw_page('pedidos', 0)) 
  LIMIT 10;
  ```

---

## ❓ Perguntas de reflexão (entregar por escrito)

1. **Qual é o papel prático do `VACUUM` no MVCC do PostgreSQL e o que aconteceria com o arquivo físico da tabela ao longo do tempo se ele nunca fosse executado?**
2. **Na Tarefa 4, após deletar 10.000 linhas e rodar o `VACUUM`, por que a inserção de 5.000 novos registros não aumentou o número de `relpages` do arquivo?**
3. **Por que o SGBD nunca lê ou escreve bytes individuais no disco, operando sempre em blocos inteiros de 8KB? Relacione com o resultado de `Buffers` obtido na Tarefa 3.**
4. **Se essa tabela estivesse armazenada em um SSD NVMe de altíssima velocidade, o conceito de Buffer Pool ainda seria relevante? Justifique comparando ordens de grandeza de latência e concorrência.**

## ✅ Entregável

Um `RELATORIO.md` (ou print/notebook) com as saídas dos comandos acima e as respostas das perguntas de reflexão.

### 🧭 Navegação

* ⬅️ **Aula 2:** [Aula 2: Revisão de Arquitetura Física e Armazenamento](./README.md)
