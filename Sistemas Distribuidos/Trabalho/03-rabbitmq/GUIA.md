# 🐇 RabbitMQ — Guia de Estudo e Roteiro do Vídeo

> **Cenário:** mensageria da *Loja Online* (eventos de pedido/estoque, tarefas, notificações).
> **Stack:** broker **RabbitMQ 3.13** (com painel web); produtores/consumidores em **Python (pika)** e **Node.js (amqplib)**. Tudo em Docker.

---

## 1. O que é (e onde se liga à Aula 6)

**RabbitMQ** é um **message broker**: um servidor intermediário que recebe mensagens de **produtores**, guarda em **filas** e entrega a **consumidores**. É uma implementação do **AMQP** (Advanced Message Queuing Protocol), padrão **aberto** criado para que sistemas de filas de fabricantes diferentes conversem entre si (Aula 6: *"soluções de fila de mensagens são, em grande parte, proprietárias"* → AMQP).

Em `../../Aula_6/README.md` ele é o exemplo de **Middleware Orientado a Mensagens (MOM)**: comunicação **assíncrona** e **persistente**, em que *"o receptor não precisa estar em execução quando uma mensagem é enviada"*.

| Conceito da Aula 6 | No RabbitMQ / nesta demo |
|---|---|
| Fila de fonte / destino, gerenciador de filas | Filas dentro do broker; o broker é o gerenciador de filas |
| **Message broker** como intermediário | O próprio RabbitMQ |
| **Conexão** como "contêiner de canais" | `BlockingConnection` (TCP) → vários `channel()` |
| **Exchange**: o produtor fala com ela, não com a fila; *"nunca armazena mensagens"* | Blocos A (5 tipos) |
| Tipos de exchange **fanout / direct / topic** (slides) | Bloco A (+ default e headers, **complementos**) |
| Mensagem **durável**; nó que não garante durabilidade **rejeita** | Bloco C1 |
| Estados **não resolvido → resolvido** (receptor "concluiu") = ACK | Bloco C2 |
| Comunicação **persistente × transiente** | Bloco C1 |
| **Round-robin** (aparece no PUSH/PULL do ZeroMQ) | Bloco B |
| Acoplamento fraco no tempo e no espaço | Produtor e consumidor nunca se conhecem nem precisam estar online juntos |

**Vocabulário rápido**
```
produtor ──mensagem(routing key)──► [EXCHANGE] ──binding──► [FILA] ──► consumidor
              (publish)              roteia e              guarda        (consume + ACK)
                                     NÃO guarda
```
- **Binding** = regra que liga exchange → fila (com uma chave ou cabeçalhos).
- **Routing key** = "endereço" que o produtor coloca na mensagem.
- **Canal (channel)** = conexão lógica leve dentro de uma conexão TCP.

---

## 2. O que o enunciado pede → onde está

| Exigência do `Trabalho.md` | Bloco | Arquivo | Etapa do `demo.sh` |
|---|---|---|---|
| Todos os tipos de roteamento | **A** | `python/a_roteamento.py` | A1–A5 |
| Round-robin | **B** | `python/b_balanceamento.py` | B1, B2 |
| Round-robin **ponderado** | **B** | `python/b_balanceamento.py` | B3 |
| Comunicação **persistente × transiente** | **C1** | `python/c_persistencia.py` | C1 (com reinício do broker) |
| **Com e sem confirmação** de recebimento | **C2** | `python/c_ack.py` | C2 |
| **Prioridade** nas filas | **D** | `python/d_prioridade.py` | D |
| Interoperabilidade de linguagens | **E** | `node/interop.mjs` + `python/e_interop.py` | E |

---

## 3. Bloco A — Tipos de exchange (roteamento)

| Tipo | Como decide | Quando usar | Resultado na demo |
|---|---|---|---|
| **default** (`""`) | Chave = **nome da fila** | Enviar direto a uma fila (atalho) | `fila_padrao` recebe a mensagem |
| **direct** | Chave **igual** à do binding | Rotear por categoria exata (`error`, `info`) | `q_erros` só recebe `error`; `q_tudo` (3 bindings) recebe as 3 |
| **fanout** | **Ignora** a chave; copia para **todas** as filas ligadas | Broadcast (notificar e-mail + SMS + push) | As 3 filas recebem a mesma mensagem |
| **topic** | Chave com **padrão**: `*` = 1 palavra, `#` = 0 ou mais | Eventos hierárquicos (`pedido.criado.sp`) | `*.*.sp` pega SP; `pedido.#` pega todos de pedido; `#` pega tudo |
| **headers** | **Ignora** a chave; compara **cabeçalhos** (`x-match` = `all`/`any`) | Roteamento por vários atributos | `all`: 1 mensagem; `any`: 3 mensagens |

**Pontos de prova**
- O produtor **nunca** publica "na fila": publica numa **exchange**. (O default é uma exchange especial que dá a *impressão* de ir direto à fila.)
- **Uma mensagem pode ir para várias filas** (copiada) e **uma fila pode ter vários bindings**.
- *Se várias filas se ligam à mesma chave num direct, ele funciona como fanout* (slide da Aula 6).
- Uma mensagem **sem nenhuma fila correspondente é descartada** (a menos que o produtor use `mandatory=True` — bloco C2).

---

## 4. Bloco B — Balanceamento de carga

Vários consumidores na **mesma fila** = *competing consumers*: cada mensagem vai para **um só** deles.

| Cenário | Resultado | O que mostra |
|---|---|---|
| **B1** Round-robin, 3 workers iguais | `W1,W2,W3,W1…` → **4/4/4** | O broker distribui em **rodízio** |
| **B2a** Round-robin com worker **10× mais lento** | Ainda 4/4/4 → tempo **1,5 s** | Round-robin é **estático**: não olha a carga (Aula 2) |
| **B2b** Mesmo caso com `prefetch=1` | 5/6/**1** → tempo **0,3 s** | *Fair dispatch*: só manda outra mensagem quando a anterior foi confirmada (parecido com "menor carga", **dinâmico**) |
| **B3** Ponderado: A (3 consumidores), B (1) | **9 × 3** | Peso 3:1 |

**⚠️ O RabbitMQ não tem round-robin ponderado nativo.** O que fizemos: o rodízio é **por consumidor**, então um worker com **3 consumidores** recebe **3 vezes mais** que um com 1. O "peso" é o **número de consumidores** (ou, na prática, mais instâncias do worker mais forte).
Alternativas reais: (a) o plugin *Consistent Hash Exchange*, que aceita pesos no binding — mas distribui por **hash**, não por rodízio; (b) uma fila por faixa de peso. Seja honesto no vídeo: *"o RabbitMQ não oferece peso nativo; emulamos com o número de consumidores"* — o professor tende a valorizar a precisão.

**`prefetch_count` (QoS):** quantas mensagens o broker pode entregar a um consumidor **sem confirmação**. `0` = ilimitado (rodízio puro); `1` = justo.

---

## 5. Bloco C — Persistência e confirmação

### C1. Comunicação persistente × transiente
Na **Aula 6**: *persistente* = o middleware guarda a mensagem pelo tempo necessário até entregar; *transiente* = só enquanto emissor e receptor estão em execução.

No RabbitMQ **"persistente" exige DUAS coisas juntas**:
1. **fila durável** (`durable=True`) → a fila sobrevive ao reinício;
2. **mensagem persistente** (`delivery_mode=2`) → o conteúdo vai ao disco.

| Fila | Durável? | Mensagem persistente? | Após reiniciar o broker (demo) |
|---|---|---|---|
| `q_transiente` | não | não | **fila sumiu** |
| `q_duravel_msg_transiente` | **sim** | não | fila existe, **0 mensagens** |
| `q_duravel_persistente` | **sim** | **sim** | fila existe, **5 mensagens** ✅ |

Na demo o broker é **derrubado de verdade** (`docker compose restart rabbitmq`) e as filas são conferidas antes e depois. Os dados persistentes ficam no **volume** `rabbit-data`.

### C2. Com e sem confirmação de recebimento
Há **duas** confirmações, em sentidos opostos:

| | Quem confirma a quem | Sem | Com |
|---|---|---|---|
| **ACK do consumidor** | consumidor → broker ("já processei") | `auto_ack=True`: o broker apaga na **entrega**; se o consumidor cai, a mensagem é **perdida** | **ACK manual**: o broker só apaga após `basic_ack`; se o consumidor cai, **reentrega** (`redelivered=True`) |
| **Recusa** | consumidor → broker ("não consegui") | — | `basic_nack(requeue=True)` devolve à fila; `requeue=False` **descarta** (ou envia à *Dead Letter Queue*) |
| **Publisher confirms** | broker → produtor ("recebi e guardei") | O produtor publica "no escuro" | `confirm_delivery()`; com `mandatory=True` o broker **devolve** mensagens sem rota (`UnroutableError`) |

Ligação com a Aula 6 (AMQP): a mensagem fica **"não resolvida"** até o receptor informar que **concluiu**; só então vira **"resolvida"** e pode ser esquecida. Isso dá *confiabilidade real de ponta a ponta*. **Garantia resultante: "pelo menos uma vez"** — uma mensagem pode chegar **duplicada** (reentrega), então os consumidores devem ser **idempotentes** (ver REST, vídeo 1).

---

## 6. Bloco D — Prioridade

Fila declarada com `arguments={"x-max-priority": 10}`; cada mensagem leva `priority` (0–10). O broker entrega **maior prioridade primeiro**; **mesma prioridade = FIFO**.

Na demo as mesmas 8 mensagens vão para uma fila comum e para uma fila com prioridade: a comum entrega na ordem de chegada; a outra entrega `FRAUDE DETECTADA (10)` primeiro e `newsletter (0)` por último.

**Pegadinhas**
- Só faz diferença quando **há fila acumulada**. Se o consumidor é mais rápido que o produtor, a ordem de chegada prevalece (por isso publicamos tudo antes de consumir).
- Use **poucos níveis** (≈ até 10): cada nível extra custa recursos.
- Vale para **filas clássicas** (as *quorum queues* tratam prioridade de forma limitada).

---

## 7. Bloco E — Interoperabilidade

Node publica → Python consome, e Python publica → Node consome, no mesmo broker. Eles só combinam **exchange, fila, routing key e formato do corpo (JSON)**. Nenhum conhece o código do outro. É a vantagem do **AMQP aberto** (Aula 6) e do **desacoplamento** da mensageria.

---

## 8. Perguntas que o professor pode fazer (e respostas)

1. **Por que usar mensageria em vez de chamar a API direto?** **Desacoplamento** (tempo, espaço, tecnologia), **absorve picos** (a fila amortece), **tolerância a falhas** (o consumidor pode estar fora do ar), **escala** (mais consumidores) e **entrega confiável**.
2. **Qual a diferença entre comunicação síncrona e assíncrona aqui?** O produtor **não espera** o consumidor processar; só entrega ao broker (Aula 6).
3. **O que é uma exchange e por que ela existe?** Camada que **roteia** mensagens às filas conforme bindings; separa *quem produz* de *quem consome*. Nunca armazena mensagens.
4. **Diferença entre direct, fanout, topic e headers?** Ver seção 3.
5. **O que significam `*` e `#`?** `*` = exatamente **uma** palavra; `#` = **zero ou mais** palavras.
6. **O que é round-robin? E o ponderado?** Rodízio entre consumidores; no ponderado, consumidores mais fortes recebem mais. **No RabbitMQ não é nativo**: emulamos com mais consumidores.
7. **Para que serve o `prefetch`?** Limita mensagens sem ACK por consumidor; com `1` obtém-se *fair dispatch* e evita-se que um worker lento acumule trabalho.
8. **Diferença entre fila durável e mensagem persistente?** A **fila** sobrevive ao reinício; a **mensagem** só sobrevive se também for persistente **e** a fila for durável. Precisa das **duas**.
9. **O que acontece com `auto_ack=True` se o consumidor falha?** A mensagem **se perde** (já foi apagada). Com ACK manual é **reentregue**.
10. **Para que servem os publisher confirms?** O broker confirma ao produtor que **recebeu** a mensagem (e `mandatory` avisa se não havia rota). Sem isso, o produtor não sabe se a mensagem se perdeu.
11. **RabbitMQ garante entrega "exatamente uma vez"?** Não: **"pelo menos uma vez"** (com ACK + persistência). Pode haver duplicata → consumidor idempotente.
12. **Garante ordem?** Dentro de **uma fila com um consumidor**, FIFO. Com vários consumidores ou reentregas, a **ordem pode se perder**.
13. **Como funciona a prioridade?** `x-max-priority` na fila + `priority` na mensagem; só importa com fila acumulada.
14. **O que é uma Dead Letter Queue?** Fila para onde vão mensagens **rejeitadas**, **expiradas (TTL)** ou que estouraram o limite — para análise posterior. *(Além do enunciado; citada em C2.)*
15. **O que acontece se o broker cair?** Depende: filas/mensagens **não duráveis** somem; **duráveis+persistentes** voltam (demo C1). Para **alta disponibilidade** usa-se **cluster** com **quorum queues** (replicação — Aula 7).
16. **RabbitMQ × Kafka?** Resumo (detalhes no vídeo 4): RabbitMQ é **broker de filas com roteamento flexível** (a mensagem **sai** da fila ao ser confirmada); Kafka é **log distribuído** com retenção (a mensagem **fica**; consumidores controlam seu *offset*).

---

## 9. Roteiro do vídeo (≤ 5 min)

> Este é o vídeo mais denso. Dicas: use `PAUSA=0 ./demo.sh` e **narre por cima** da saída, ou grave por blocos e una depois; deixe o painel web aberto numa aba para mostrar exchanges/filas rapidamente. Se estourar o tempo: resuma A2–A3 e corte B2a.

| Tempo | Etapa | O que falar |
|---|---|---|
| 0:00–0:25 | Intro | "RabbitMQ = broker AMQP, MOM (Aula 6): assíncrono, persistente, desacoplado." Mostrar o desenho produtor → exchange → fila → consumidor. |
| 0:25–1:25 | A1–A5 | Os **5 tipos de exchange**. Destacar topic (`*` × `#`) e fanout. |
| 1:25–2:25 | B1–B3 | **Round-robin 4/4/4**; lento × `prefetch=1` (1,5 s → 0,3 s); **ponderado 9×3** *(avisar: peso não é nativo)*. |
| 2:25–3:45 | C1, C2 | **Reinício do broker**: transiente some, persistente fica. **ACK**: `auto_ack` perde, manual reentrega; publisher confirms. |
| 3:45–4:15 | D | Fila comum × com prioridade. |
| 4:15–4:40 | E | Node ↔ Python pelo mesmo broker. |
| 4:40–5:00 | Fecho | Vantagens (desacoplamento, confiabilidade, roteamento flexível) e limites (broker é ponto central; "pelo menos uma vez"; ordem não garantida). Apontar o Kafka como contraste. |

---

## 10. Como rodar

```bash
cd Trabalho/03-rabbitmq
docker compose up -d --build --wait rabbitmq    # sobe o broker
./demo.sh                                       # demonstração completa (ENTER avança)
PAUSA=0 ./demo.sh                               # sem pausas
# Painel web: http://localhost:8103  (usuário loja / senha loja123)

# Partes isoladas:
docker compose run --rm cliente-python python -u a_roteamento.py topic
docker compose run --rm cliente-python python -u b_balanceamento.py ponderado
docker compose run --rm cliente-python python -u d_prioridade.py
docker compose exec rabbitmq rabbitmqctl list_queues name durable messages
docker compose down -v                          # desliga e apaga os dados
```
**Problemas comuns**
- *Porta 8103/8113 ocupada:* mude no `docker-compose.yml`.
- *`PRECONDITION_FAILED` ao redeclarar:* uma fila/exchange já existe com parâmetros diferentes → `docker compose down -v` (apaga o volume).
- *Após mudar um script:* o `demo.sh` reconstrói as imagens dos clientes sozinho; manualmente: `docker compose --profile clientes build`.
