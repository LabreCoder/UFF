# 🧭 PLANO DE EXECUÇÃO — Trabalho de Sistemas Distribuídos

> **Arquivo de controle.** Serve para retomar o trabalho de onde parou (inclusive em outra sessão do Claude).
> Ao retomar: leia este arquivo, ache o primeiro item `[ ]` e continue dali. Marque `[x]` ao concluir.

## 1. Contexto

- **Disciplina:** TCC00362 — Sistemas Distribuídos (UFF). Professor: Raphael Guerra. Aluno: João Victor Labre.
- **Enunciado:** [Trabalho.md](./Trabalho.md). 4 protocolos: **REST, gRPC, RabbitMQ, Apache Kafka**.
- **Entrega:** domingo, **29/11/2026**, pelo Classroom. **1 vídeo (≤ 5 min) + 1 `.zip` com o código por protocolo.** Vídeos sem compactar, sem links.
- **Nota:** 50% domínio da teoria + 50% demonstrar **todas** as características do protocolo.
- **Objetivo pedagógico do aluno:** *entender* cada passo, não só entregar. Por isso cada pasta tem um `GUIA.md` (teoria, código explicado, perguntas de prova, roteiro do vídeo).
- **Base teórica no repositório:** `../Aula_5` (arquiteturas, REST como estilo), `../Aula_6` (RPC, MOM, AMQP, RabbitMQ) e `../Aula_7` (replicação, relevante p/ Kafka).

## 2. Decisões já tomadas

| Decisão | Escolha | Motivo |
|---|---|---|
| Linguagem principal (servidores) | **Python 3.12** | Já instalado; legível |
| Segunda linguagem (interoperabilidade) | **Node.js 20** (JavaScript) | Escolha do aluno |
| Execução | **Docker Compose** (nada instalado no host além do Docker) | Zip roda com um comando; o host não tem Node/Java/protoc |
| Portas das demos | faixa **81xx** (REST 8101, gRPC 8102, RabbitMQ painel 8103 + AMQP 8113, Kafka 8104) | 8080 e 8443 ocupadas pelo projeto "cofre" do aluno |
| Cenário de domínio (comum a todos) | **Loja online**: produtos, pedidos, estoque, notificações | Uma história só facilita a explicação nos 4 vídeos |
| Gravação/narração | **Fica para depois** de construir tudo (ffmpeg x11grab disponível; sessão X11) | Pedido do aluno |
| Git | **Não fazer commit** sem o aluno pedir | — |

## 3. Estrutura final

```
Trabalho/
├── Trabalho.md            (enunciado)
├── PLANO.md               (este arquivo)
├── 01-rest/               docker-compose.yml, api/, gateway/, clientes/, demo.sh, GUIA.md
├── 02-grpc/               idem (proto/, server Python, client Node + Python)
├── 03-rabbitmq/           idem (4 sub-demos)
├── 04-kafka/              idem
└── entrega/               (por último) zips: rest.zip, grpc.zip, rabbitmq.zip, kafka.zip
```

Cada pasta de protocolo deve ser **autossuficiente**: `docker compose up` sobe tudo; `./demo.sh` roda a demonstração narrável passo a passo, com pausas (`read`) entre etapas para dar tempo de falar no vídeo.

## 4. Checklists

### 4.1 REST  `01-rest/`   — status: [x] CONCLUÍDO (2026-11-25)
Características a demonstrar (cada uma = um trecho do `demo.sh` + uma seção do GUIA):
- [x] Cliente-servidor (separação de responsabilidades)
- [x] **Sem estado (stateless)**: toda requisição leva sua autenticação (header), servidor não guarda sessão
- [x] **Recursos e URIs** (`/produtos`, `/produtos/{id}`, `/pedidos`)
- [x] **Verbos HTTP**: GET, POST, PUT, PATCH, DELETE, HEAD, OPTIONS (+ **idempotência**/segurança de cada um)
- [x] **Códigos de status**: 200, 201, 204, 304, 400, 401, 404, 409, 422
- [x] **Representações / negociação de conteúdo** (`Accept`: JSON e XML)
- [x] **Cache** (ETag + `If-None-Match` → 304, `Cache-Control`)
- [x] **Sistema em camadas** (gateway nginx na frente da API)
- [x] **HATEOAS** (links na resposta) / interface uniforme
- [x] Paginação e filtros por query string
- [x] **Interoperabilidade**: mesma API consumida por curl, Node.js e Python
- [x] Documentação OpenAPI (`/docs`)
- [x] `GUIA.md` (teoria, código, perguntas, roteiro de vídeo 5 min)
- [x] Testado do zero (`docker compose down -v && up --build`)

### 4.2 gRPC  `02-grpc/`   — status: [x] CONCLUÍDO (2026-11-25)
- [x] IDL **Protocol Buffers** (`.proto`) e **geração de stubs** (Python e Node)
- [x] **4 tipos de chamada**: unária, server streaming, client streaming, bidirecional
- [x] Servidor Python ↔ cliente **Node.js** (e cliente Python) — **interoperabilidade**
- [x] **HTTP/2** (multiplexação) — mostrar em tráfego/log
- [x] **Deadlines/timeouts** e **cancelamento**
- [x] **Metadata** (headers/trailers) e **interceptors** (ex.: auth/log)
- [x] **Códigos de status gRPC** (NOT_FOUND, DEADLINE_EXCEEDED, INVALID_ARGUMENT…) e tratamento de erro
- [x] Comparação de tamanho **Protobuf × JSON** (binário × texto)
- [ ] (extra, opcional, NÃO feito) TLS
- [x] `GUIA.md` + teste do zero

### 4.3 RabbitMQ  `03-rabbitmq/`   — status: [x] CONCLUÍDO (2026-11-25)
Sub-demos (4 blocos, cada um com script próprio):
- [x] **A. Roteamento — todos os tipos de exchange**: default, **direct**, **fanout**, **topic** (`*` e `#`), **headers**
- [x] **B. Balanceamento de carga**: **round-robin** (vários consumidores na mesma fila) e **round-robin ponderado** (pesos 3:1 via nº de consumidores por worker; explicar que o RabbitMQ não tem peso nativo) + `prefetch`/fair dispatch
- [x] **C. Persistente × transiente**, **com e sem confirmação**: fila durável + `delivery_mode=2` × não durável; `auto_ack` × ACK manual × `nack/requeue`; **publisher confirms**; provar reiniciando o broker (`docker restart`)
- [x] **D. Prioridade nas filas**: `x-max-priority`, mensagens de prioridades diferentes saindo em ordem
- [x] Produtores/consumidores em **Python e Node.js** (interoperabilidade via AMQP)
- [x] Painel de gerenciamento (15672) usado no vídeo
- [ ] (extras, NÃO feitos; só citados no GUIA) TTL e dead-letter exchange, RPC sobre RabbitMQ
- [x] `GUIA.md` + teste do zero

### 4.4 Kafka  `04-kafka/`   — status: [x] CONCLUÍDO (2026-11-25)
- [x] Broker Kafka (modo **KRaft**, sem Zookeeper) via Docker
- [x] Tópico com **partições**, produtor com **chave** (mesma chave → mesma partição, ordem preservada)
- [x] **Consumer groups**: dois consumidores do mesmo grupo dividem partições; grupos diferentes recebem tudo
- [x] **Retenção e replay**: ler de novo desde o início/offset (o que o RabbitMQ não faz)
- [x] Produtor Python + consumidor Node.js
- [x] **Explicação da diferença Kafka × RabbitMQ** (tabela + falar no vídeo): log distribuído com retenção × broker/fila com roteamento; pull × push; offset × ACK; ordem por partição; escala; casos de uso
- [x] `GUIA.md` + teste do zero

### 4.5 Fechamento
- [ ] (ideia do aluno, opcional) **Compose geral** na raiz de `Trabalho/` com `include:` dos 4 composes, só como atalho para subir tudo junto (as portas já não conflitam). Cada zip continua autossuficiente.
- [ ] (ideia do aluno, futura) Uma demo de **concorrência** (ex.: vários clientes/consumidores disputando, interrupção de processos)
- [ ] `README.md` na raiz de `Trabalho/` (como rodar cada demo, mapa das pastas)
- [ ] Gerar os 4 zips em `entrega/` (sem `node_modules`, `__pycache__`, volumes) — **o aluno pediu para NÃO gerar por enquanto** (decidir quando)
- [ ] Atualizar o README principal do repositório (seção Tecnologias; seção Trabalho)
- [ ] **Depois:** plano de gravação (ffmpeg), roteiro de narração, ensaio

## 5. Padrão de cada `GUIA.md`
1. O que é o protocolo (em 5 linhas) e **onde se liga à aula** (links `../Aula_X`).
2. Tabela **característica → onde está demonstrada no código/`demo.sh`**.
3. Código explicado **trecho a trecho**.
4. **Perguntas que o professor pode fazer** + respostas.
5. **Roteiro do vídeo, minuto a minuto** (≤ 5 min).
6. Como rodar e como resolver problemas comuns.

## 6. Diário de progresso
> Acrescente uma linha a cada marco (data, o que foi feito, o que falta).

- 2026-11-25 — READMEs das Aulas 1–8 atualizados (agentes). Plano criado. Docker OK (imagens python:3.12-slim, node:20-alpine, nginx:1.27-alpine baixadas).
- 2026-11-25 — **REST concluído e testado do zero** (11 códigos de status exibidos; clientes Node e Python OK; GUIA.md pronto). Próximo: **gRPC** (`02-grpc/`). Observação: `docker compose down -v` já foi executado; para ver rodando: `cd 01-rest && docker compose up -d --build && ./demo.sh`.
- 2026-11-25 — **gRPC concluído e testado do zero** (4 tipos de chamada, deadline/cancelamento, metadata, interceptor, status codes, HTTP/2 via curl, Protobuf×JSON, clientes Python e Node; GUIA.md pronto). TLS ficou de fora (opcional). Próximo: **RabbitMQ** (`03-rabbitmq/`), o maior: 4 sub-demos (A roteamento, B balanceamento, C persistência/ACK, D prioridade).
- 2026-11-25 — Revisão rápida de REST e gRPC OK (sintaxe, composes válidos, sem lixo para o zip). Pequenos ajustes feitos (mktemp no demo do gRPC; nota sobre as etiquetas R1–R9 no GUIA do REST). Próximo: RabbitMQ.
- 2026-11-25 — **RabbitMQ concluído e testado do zero** (blocos A–E: 5 exchanges; round-robin, fair dispatch e ponderado 9×3; reinício real do broker; ack/nack/publisher confirms; prioridade; Node↔Python). Painel em :8103 (loja/loja123), AMQP em :8113. GUIA.md pronto. Próximo: **Kafka** (`04-kafka/`, porta 8104), depois fechamento (README de Trabalho/, zips em entrega/, README principal).
- 2026-11-25 — **Kafka concluído e testado do zero** (KRaft; K1 partições/chave/ordem, K2 consumer groups+rebalanceamento, K3 retenção/replay/seek, K4 Node↔Python com murmur2, K5 tabela Kafka×RabbitMQ; GUIA.md com a explicação da diferença). Corrigido: scripts standalone criam o tópico (auto-create desligado). **Os 4 protocolos estão prontos.** Pendente: fechamento (README em Trabalho/, README principal do repo, zips — NÃO gerar sem o aluno pedir), compose geral opcional, depois gravação dos vídeos.
