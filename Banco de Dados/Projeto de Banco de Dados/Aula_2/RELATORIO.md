### 1. O que é o VACUUM na prática? O que aconteceria sem ele?

* **O que é:** É o "lixeiro" do PostgreSQL. No modelo MVCC, um `DELETE` ou `UPDATE` não apaga o registro do disco de imediato; ele apenas marca a versão antiga como morta (*dead tuple*). O `VACUUM` varre a página, limpa essas tuplas mortas e avisa ao **Free Space Map (FSM)** que aqueles bytes podem ser reutilizados por novos `INSERT`s.
* **Sem ele:** Ocorre o fenômeno do **Bloat** (inchaço). A tabela cresceria infinitamente em disco a cada atualização/deleção, e as consultas ficariam progressivamente lentas, pois o banco precisaria ler milhares de páginas cheias de "lixo" invisível.

---

### 2. O tamanho cresceu de forma proporcional? Para onde foram as novas tuplas?

* **Inserção inicial (+50.000 linhas):** O arquivo cresceu de forma **exatamente proporcional** (+25% em `relpages`), e essas linhas foram anexadas ao final do Heap File, pois não havia espaço livre nas páginas anteriores.
* **Após o DELETE + VACUUM (+5.000 linhas):** As novas tuplas **preencheram os buracos** deixados no início da tabela (páginas 0 em diante) em vez de irem para o final. O tamanho do arquivo (`relpages`) **não aumentou**, porque o PostgreSQL consultou o FSM e reaproveitou o espaço liberado pelo `VACUUM`.

---

### 3. Por que o SGBD lê/escreve apenas páginas inteiras (8 KB) e nunca bytes individuais?

* **Motivo físico e arquitetural:** Discos rígidos, SSDs e o próprio kernel do Sistema Operacional operam em blocos/setores (geralmente 4 KB ou 8 KB). Buscar 1 único byte exigiria a mesma operação de I/O de trazer o bloco inteiro. Além disso, gerenciar ponteiros de bytes avulsos na memória causaria uma sobrecarga inviável.
* **Relação com o Passo 3:** Quando você buscou um único registro (`WHERE id = 150000`), o Postgres não leu apenas os 20 bytes daquela linha. Ele leu **4 páginas inteiras (32 KB)** de Buffer (`shared hit=4` / `read=4`) — 3 do índice e 1 do heap — trazendo dezenas de outras linhas vizinhas para a memória RAM junto com a linha desejada.

---

### 4. Em um SSD NVMe ultrarrápido, o Buffer Pool ainda é relevante?

**Sim, totalmente indispensável.**

* **Latência:** Acesso à memória RAM ocorre na escala de **nanossegundos** (~10 a 100 ns). Acesso a um SSD NVMe de ponta ocorre na escala de **microssegundos** (~10 a 50 µs). A RAM ainda é de **100 a 1.000 vezes mais rápida** que o melhor SSD do mercado.
* **Concorrência e CPU:** Toda manipulação de dados pelo motor SQL (filtros, ordenações, joins, locks) só pode ser processada diretamente pela CPU se os dados estiverem na memória RAM. Sem o Buffer Pool, a CPU ficaria constantemente ociosa esperando chamadas de barramento PCIe/disco.