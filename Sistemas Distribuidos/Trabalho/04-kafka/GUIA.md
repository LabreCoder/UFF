# 🪵 Apache Kafka — Guia de Estudo e Roteiro do Vídeo

> **Exigência do enunciado:** *"Apache Kafka — explique a diferença em relação ao RabbitMQ."*
> **Cenário:** fluxo de eventos de pedidos da *Loja Online*.
> **Stack:** broker **Kafka 3.8 em modo KRaft** (sem Zookeeper); clientes **Python (confluent-kafka)** e **Node.js (kafkajs)**. Tudo em Docker.

---

## 1. O que é Kafka (em 5 linhas)

**Apache Kafka** é uma plataforma de **streaming de eventos**. Em vez de uma "fila" onde a mensagem some ao ser lida, o Kafka é um **log distribuído**: um arquivo em que os eventos são **apenas acrescentados no fim**, ficam **guardados** por um tempo de retenção e podem ser **lidos por muitos consumidores, quantas vezes quiserem**. Cada consumidor só guarda **até onde já leu** (o *offset*).

**Onde se liga às aulas**
| Aula | Ligação |
|---|---|
| **Aula 5** (`../../Aula_5`) | Estilo **baseado em eventos / publish-subscribe**: Kafka é a infraestrutura clássica desse estilo. |
| **Aula 6** (`../../Aula_6`) | É um **MOM** (middleware orientado a mensagens), como o RabbitMQ, mas com outro modelo. Também vimos **pub/sub** no ZeroMQ. |
| **Aula 7** (`../../Aula_7`) | **Replicação**: cada partição tem um **líder** e **seguidores** (protocolo de **backup primário**); o conjunto **ISR** (*in-sync replicas*) lembra o **quórum**. Consistência × desempenho aparece em `acks`. |
| **Aula 8** (`../../Aula_8`) | **Recuperação retroativa**: o offset funciona como um *checkpoint*; após uma falha o consumidor retoma de onde parou (ou reprocessa). |

---

## 2. Vocabulário

```
 produtor ──► TÓPICO "pedidos" ─────────────────────────────────────────────► consumidores
              ├─ partição 0: [0][1][2][3][4][5] ──►  (só cresce no fim; cada posição = OFFSET)
              ├─ partição 1: [0][1][2][3][4][5] ──►
              └─ partição 2: [0][1][2][3][4][5] ──►
                                                       grupo "faturamento": F1 lê [0,1]   F2 lê [2]
                                                       grupo "estoque":     E1 lê [0,1,2]   (independente)
```
| Termo | Significado |
|---|---|
| **Broker** | Servidor Kafka que guarda os logs. Um **cluster** tem vários. |
| **Tópico** | "Assunto" (categoria de eventos), ex.: `pedidos`. |
| **Partição** | Pedaço ordenado e imutável do tópico. É a **unidade de paralelismo, ordem e replicação**. |
| **Offset** | Posição de uma mensagem **dentro de uma partição** (0, 1, 2…). |
| **Chave (key)** | Define a partição (hash). **Mesma chave ⇒ mesma partição ⇒ ordem preservada.** |
| **Consumer group** | Conjunto de consumidores que **dividem** as partições de um tópico. |
| **Retenção** | Por quanto tempo/quanto espaço o log guarda mensagens (padrão: 7 dias). |
| **KRaft** | O próprio Kafka gerencia os metadados do cluster (consenso Raft), dispensando o Zookeeper. |

---

## 3. O que cada bloco da demo mostra

| Bloco | Arquivo | Característica | O que observar |
|---|---|---|---|
| **K1** | `python/produtor.py` | Tópico, **partições**, **chave**, **offset**, **ordem** | 12 mensagens → 4 por partição; cada cliente (chave) cai em **uma** partição só |
| **K2** | `python/grupos.py` | **Consumer groups**, **rebalanceamento**, **pub/sub entre grupos** | F1+F2 dividem as partições; grupo `estoque` lê tudo; ao F2 sair, F1 assume as 3 partições |
| **K3** | `python/replay.py` | **Retenção** e **replay** (seek) | 18 mensagens ainda no log depois de lidas; grupo novo relê tudo; volta ao offset 2 |
| **K4** | `python/interop.py`, `node/interop.mjs` | **Interoperabilidade** | Node ↔ Python; **mesma chave = mesma partição** nas duas linguagens |
| **K5** | `demo.sh` | **Kafka × RabbitMQ** | Tabela comparativa |

> **Observação honesta:** a demo usa **1 broker**, então o **fator de replicação é 1**. Replicação (líder/seguidor, ISR, `acks=all`) é explicada na teoria; para demonstrá-la seriam necessários 3 brokers.
> **Detalhe de execução:** quem fica com 2 partições (F1 ou F2) **muda de uma execução para outra**: depende de quem entra primeiro. O importante é que **cada partição vai para um único consumidor do grupo**.

---

## 4. Kafka × RabbitMQ — a diferença (o ponto central do vídeo)

### 4.1 A ideia em uma frase
- **RabbitMQ** é uma **caixa de correio inteligente**: o broker **roteia** a mensagem, **entrega** ao consumidor e **esquece** depois do ACK. ("*smart broker, dumb consumer*")
- **Kafka** é um **livro-razão**: o broker **só grava** na ordem; **cada leitor marca onde parou** e pode voltar atrás. ("*dumb broker, smart consumer*")

### 4.2 Tabela comparativa

| Aspecto | **RabbitMQ** | **Apache Kafka** | Evidência na demo |
|---|---|---|---|
| **Modelo** | Broker de **filas** (exchange → fila) | **Log distribuído** (tópico → partições) | — |
| **Após a leitura** | Mensagem **removida** (ACK) | Mensagem **permanece** (retenção) | K3 |
| **Replay do histórico** | ❌ não | ✅ sim (offset, seek, grupo novo) | K3 |
| **Entrega** | Broker **empurra** (*push*) | Consumidor **puxa** (*pull*) | `poll()` |
| **Quem sabe a posição** | O broker (controla ACK/entrega) | O **consumidor/grupo** (offset) | K2 |
| **Vários assinantes** | *fanout* + **1 fila por assinante** | Cada **grupo** lê tudo, sem custo extra | K2 (`estoque`) |
| **Dividir o trabalho** | Vários consumidores na **mesma fila** (round-robin) | Consumidores do grupo × **partições** | K2 |
| **Limite de paralelismo** | Quantos consumidores quiser | **nº de partições** por grupo | K2 |
| **Roteamento** | **Rico**: direct, topic, fanout, headers | **Simples**: tópico + chave | RabbitMQ vídeo A |
| **Ordem** | Por fila (com 1 consumidor) | Por **partição** (garantida pela chave) | K1 |
| **Prioridade** | ✅ (`x-max-priority`) | ❌ | RabbitMQ vídeo D |
| **Confirmação** | ACK/NACK **por mensagem** | **Commit de offset** (posição do grupo) | K2 |
| **Desempenho** | Alta velocidade por mensagem, baixa latência | **Altíssima vazão** (milhões msg/s): escrita sequencial, lotes, *zero-copy* | — |
| **Replicação** | Cluster + *quorum queues* | **Réplicas por partição** (líder/seguidor, ISR) | (teoria) |
| **Melhor para** | Tarefas em segundo plano, RPC, roteamento complexo, filas de trabalho | **Streaming de eventos**, logs/métricas, *event sourcing*, integração em larga escala, reprocessamento | — |

### 4.3 Como a **mesma situação** se comporta nos dois
> *"Três sistemas (faturamento, estoque, auditoria) precisam receber cada pedido."*
- **RabbitMQ:** uma exchange **fanout** e **uma fila para cada sistema**. Se um novo sistema surgir **depois**, só recebe pedidos **dali em diante** (o passado já foi consumido e apagado).
- **Kafka:** um tópico; cada sistema é um **grupo** com seu offset. Um sistema **novo** entra e pode **ler desde o começo** do log (replay) — foi o que o grupo `auditoria` fez na K3.

### 4.4 Quando escolher qual
- **RabbitMQ**: distribuir **tarefas** a workers, **roteamento sofisticado**, **prioridades**, **RPC**, mensagens que **devem sumir** depois de processadas, latência baixa por mensagem.
- **Kafka**: **fluxo contínuo e massivo de eventos**, **múltiplos consumidores independentes** dos mesmos dados, **histórico/auditoria/reprocessamento**, **ordem por chave**, analytics em tempo real.
- Podem **coexistir**: Kafka como "espinha dorsal" de eventos e RabbitMQ para as filas de trabalho de cada serviço.

### 4.5 Nuances (para mostrar domínio)
- **Não é "o Kafka é mais rápido"**: são ferramentas para problemas diferentes. O RabbitMQ pode ter **menor latência por mensagem**; o Kafka vence em **vazão agregada**.
- O RabbitMQ também tem **Streams** (desde a 3.9): um log de retenção parecido com o do Kafka — mas o modelo principal e o que usamos aqui são as **filas**.
- Ordem no Kafka é **só por partição**; não existe ordem global se houver mais de uma partição.

---

## 5. Conceitos que o professor pode explorar

**Garantias de entrega**
| Semântica | Como acontece | Risco |
|---|---|---|
| **No máximo uma vez** | Commit do offset **antes** de processar | Pode **perder** |
| **Pelo menos uma vez** (comum) | Commit **depois** de processar | Pode **duplicar** → consumidor idempotente |
| **Exatamente uma vez** | Produtor idempotente + transações | Mais caro/complexo |

**Produtor e `acks`** (Aula 7 — consistência × desempenho)
- `acks=0`: não espera ninguém (mais rápido, pode perder).
- `acks=1`: espera o **líder** gravar.
- `acks=all`: espera **todas as réplicas em sincronia (ISR)** (mais seguro).

**Retenção e compactação:** o log apaga por **tempo/tamanho**; a **compactação** mantém só o **último valor de cada chave** (útil para "estado atual").

**Por que é rápido:** escrita **sequencial** em disco, **cache de página** do SO, **lotes** (batching), **compressão** e **zero-copy** (`sendfile`).

**Rebalanceamento:** quando um consumidor entra/sai/cai, o grupo redistribui as partições (K2, etapa 3). Durante o rebalanceamento clássico (*eager*) o consumo pausa brevemente; existe o modo *cooperative* para reduzir isso.

---

## 6. Perguntas que o professor pode fazer (e respostas)

1. **Qual a diferença fundamental entre Kafka e RabbitMQ?** Seção 4.1: RabbitMQ é **fila com roteamento** (mensagem some ao ser confirmada); Kafka é **log distribuído** (mensagem fica; o consumidor controla o offset).
2. **O que é uma partição? Por que existe?** Divisão ordenada do tópico; permite **paralelismo** e **escala horizontal**, e é a unidade de **ordem** e **replicação**.
3. **O que garante a ordem no Kafka?** Dentro de **uma partição**. Para manter a ordem de um cliente, usa-se a **mesma chave** (mesma partição). Não há ordem global entre partições.
4. **O que é um offset?** A posição da mensagem na partição. Cada grupo guarda o **seu** (no tópico interno `__consumer_offsets`).
5. **O que é um consumer group?** Consumidores que **dividem** as partições; **cada partição é lida por só um consumidor do grupo**. Grupos diferentes são **independentes** (cada um lê tudo).
6. **Posso ter mais consumidores que partições em um grupo?** Pode, mas os **excedentes ficam ociosos**: o paralelismo máximo é o nº de partições.
7. **O que é rebalanceamento?** Redistribuição das partições quando o grupo muda (entra/sai/cai alguém).
8. **Por que o Kafka consegue "replay" e o RabbitMQ não?** Porque o Kafka **não apaga ao ler**: só avança o offset; a retenção é por tempo/tamanho. No RabbitMQ a leitura (ACK) remove a mensagem.
9. **Kafka é push ou pull?** **Pull**: o consumidor pede (`poll`) no seu ritmo, o que dá *backpressure* natural.
10. **Como o Kafka tolera falhas de um broker?** **Replicação** por partição: um **líder** e **seguidores** (ISR). Se o líder cai, um seguidor em sincronia é eleito (Aula 7: backup primário e quórum).
11. **O que é KRaft?** O modo em que o Kafka gerencia os **metadados do cluster sozinho** (protocolo Raft), sem Zookeeper.
12. **O que o `acks` controla?** Quantas confirmações o produtor espera antes de considerar a mensagem gravada (0, 1 ou all): **desempenho × durabilidade**.
13. **Kafka entrega "exatamente uma vez"?** Por padrão **"pelo menos uma vez"**; "exatamente uma vez" exige produtor idempotente + transações.
14. **O Kafka substitui o RabbitMQ?** Não necessariamente. Resolvem problemas diferentes; muitas arquiteturas usam os dois.
15. **Quando NÃO usar Kafka?** Poucas mensagens com roteamento complexo, prioridades, RPC ou necessidade de apagar a mensagem após o uso: o RabbitMQ é mais natural. Também há **custo operacional** maior.
16. **Cada cliente cai sempre na mesma partição?** Sim, enquanto o **número de partições não mudar** (o hash é módulo nº de partições). Mudar isso quebra a correspondência chave→partição.

---

## 7. Roteiro do vídeo (≤ 5 min)

> Como o enunciado pede *explicar a diferença*, reserve **o último minuto e meio** para isso. Use `PAUSA=0 ./demo.sh` e narre por cima (a execução completa leva ~50 s); a etapa K5 (tabela) pode ficar na tela enquanto você explica.

| Tempo | Etapa | O que falar |
|---|---|---|
| 0:00–0:30 | Intro | "Kafka é um **log distribuído de eventos**, não uma fila. Vou mostrar como funciona e depois a diferença para o RabbitMQ." Desenho do tópico/partições. |
| 0:30–1:30 | K1 | Tópico com 3 partições; **chave → partição**; **offsets**; **ordem por partição**. |
| 1:30–2:30 | K2 | **Consumer group** dividindo partições; outro grupo lendo tudo (pub/sub); **rebalanceamento** quando F2 sai. |
| 2:30–3:15 | K3 | **Replay**: log retém 18 mensagens depois de lidas; grupo novo relê tudo; volta ao offset 2. *"No RabbitMQ isso já teria sumido."* |
| 3:15–3:40 | K4 | Node ↔ Python; mesma chave, mesma partição. |
| 3:40–5:00 | K5 | **A diferença**: tabela na tela. Falar: log × fila; reter × apagar; pull × push; offset × ACK; grupos × fanout; ordem por partição; roteamento e prioridade só no RabbitMQ; quando usar cada um. |

---

## 8. Como rodar

```bash
cd Trabalho/04-kafka
docker compose up -d --build --wait kafka     # sobe o broker KRaft (leva ~15 s)
./demo.sh                                     # demonstração completa (ENTER avança)
PAUSA=0 ./demo.sh                             # sem pausas (~50 s)

# Partes isoladas:
docker compose run --rm cliente-python python -u produtor.py
docker compose run --rm cliente-python python -u grupos.py
docker compose run --rm cliente-python python -u replay.py
docker compose exec kafka /opt/kafka/bin/kafka-topics.sh --bootstrap-server kafka:9092 --list
docker compose exec kafka /opt/kafka/bin/kafka-consumer-groups.sh --bootstrap-server kafka:9092 --describe --group faturamento
docker compose down -v                        # desliga e apaga os dados
```
**Problemas comuns**
- *O broker demora a ficar "healthy":* é normal na 1ª vez (até ~30 s); o `--wait` aguarda.
- *Porta 8104 ocupada:* mude `"8104:9094"` e o `EXTERNAL://localhost:8104` no compose (só importa para clientes **fora** do Docker).
- *`replay.py` mostra "tópico vazio":* ele mesmo produz 12 mensagens; para ver o cenário completo rode antes `grupos.py`.
- *Tópico não existe:* `AUTO_CREATE_TOPICS` está desligado de propósito; os scripts criam o tópico com 3 partições.
