# ⚡ gRPC — Guia de Estudo e Roteiro do Vídeo

> **Cenário:** o catálogo da *Loja Online* (mesmo domínio do REST, para comparar).
> **Stack:** servidor **Python**; clientes **Python** (stubs gerados pelo `protoc`) e **Node.js** (stub montado a partir do mesmo `.proto`). Tudo em Docker.

---

## 1. O que é gRPC (em 5 linhas)

**gRPC** é um framework de **RPC (Remote Procedure Call)** criado pelo Google. Você descreve o serviço em um arquivo **`.proto`** (a **IDL**), o compilador gera os **stubs** para cada linguagem, e chamar um método remoto passa a parecer chamar uma função local. Por baixo, usa **HTTP/2** como transporte e **Protocol Buffers (Protobuf)** como formato binário de mensagens.

**Onde se liga à Aula 6** (`../../Aula_6/README.md`): é a implementação moderna de tudo o que a aula ensina sobre RPC. Os slides citam: *"Novos frameworks de RPC (e.g. gRPC) disputam espaço com REST"*.

| Conceito da Aula 6 | No gRPC (nesta demo) |
|---|---|
| **Stub de cliente** (empacota parâmetros, envia, espera resposta) | `CatalogoStub` em `loja_pb2_grpc.py` (gerado) |
| **Stub de servidor** (desempacota, chama o serviço) | `CatalogoServicer` — herdamos dele em `server.py` |
| **IDL** → compilada gera os stubs; cliente e servidor em **linguagens diferentes** | `loja.proto` → `protoc` → Python e Node.js |
| **Marshalling** (empacotar parâmetros em mensagem) | Serialização Protobuf |
| **RPC síncrona × assíncrona** | `stub.Metodo(...)` bloqueia; `stub.Metodo.future(...)` não bloqueia (etapa 9) |
| **Passagem por referência é problema** (endereços diferentes) | gRPC passa **por valor**: a mensagem é copiada/serializada |
| **Heterogeneidade** (endianness, tamanho de int...) | Protobuf define a representação binária; vale para qualquer arquitetura |

As **10 etapas da RPC** (Aula 6) acontecem em cada chamada: o *cliente chama o stub* → o stub monta a mensagem → o SO envia → o SO do servidor entrega ao stub → desempacota e chama o serviço → resposta volta pelo caminho inverso.

---

## 2. Características do gRPC e onde cada uma aparece

| # | Característica | Em que consiste | Onde está na demo |
|---|---|---|---|
| G1 | **IDL (.proto) e geração de stubs** | Contrato único; código de cliente/servidor gerado | Etapas 1 e 2; `proto/loja.proto`; `Dockerfile.python` (passo `protoc`) |
| G2 | **4 tipos de comunicação** | Unária, server streaming, client streaming, bidirecional | Etapas 4, 6, 7, 8 |
| G3 | **Códigos de status** | 17 códigos próprios (`OK`, `NOT_FOUND`, `INVALID_ARGUMENT`, `DEADLINE_EXCEEDED`, `UNAUTHENTICATED`...) | Etapa 5 |
| G4 | **Metadata** | Pares chave/valor: **headers** (antes) e **trailers** (depois) | Etapas 4 e 5 (`x-servidor`, `x-tempo-us`, `authorization`) |
| G5 | **Interceptors** | Código que envolve toda chamada (auth, log, métricas) | `AuthInterceptor` em `server.py`; etapa 5 |
| G6 | **Deadline e cancelamento** | Cliente impõe prazo; o servidor é avisado e para | Etapa 9 |
| G7 | **HTTP/2** | Binário, multiplexado, headers comprimidos, full-duplex | Etapa 3 (curl `--http2-prior-knowledge`) |
| G8 | **Protobuf (binário e compacto)** | ~44% do tamanho do JSON nesta mensagem | Etapa 10 |
| G9 | **Interoperabilidade** | Servidor Python ↔ clientes Python e Node.js com o mesmo contrato | Etapas 11 e 12 |

---

## 3. Os 4 tipos de chamada

```
UNÁRIA            cliente ──req──►  servidor           ObterProduto(id)  → Produto
                  cliente ◄──resp── servidor

SERVER STREAMING  cliente ──req──►  servidor           ListarProdutos(filtro) → stream Produto
                  cliente ◄─r1─r2─r3─ servidor         (servidor envia vários, ao longo do tempo)

CLIENT STREAMING  cliente ─i1─i2─i3─► servidor         FecharCarrinho(stream Item) → Resumo
                  cliente ◄──resp──── servidor         (uma resposta só, no fim)

BIDIRECIONAL      cliente ─m1────m2──►  servidor       Conversar(stream Msg) ↔ stream Msg
                  cliente ◄──r1────r2── servidor       (independentes, ao mesmo tempo)
```
**Como reconhecer no `.proto`:** a palavra `stream` antes do tipo da requisição e/ou da resposta.
**Quando usar:** server streaming = feed/notificações/download grande; client streaming = upload/telemetria; bidirecional = chat/jogos/colaboração em tempo real.

---

## 4. Código explicado

### 4.1 `proto/loja.proto`
- `service Catalogo { rpc ... }` declara os métodos remotos.
- `message Produto { int32 id = 1; ... }`: os **números (tags)** — e não os nomes — são o que viaja pela rede. Por isso é compacto e permite **evoluir o contrato** (adicionar campos novos com tags novas) sem quebrar clientes antigos.
- `repeated string avisos = 4;` = lista.

### 4.2 `servidor/server.py`
```python
class Catalogo(loja_pb2_grpc.CatalogoServicer):      # herda a "casca" gerada
    def ObterProduto(self, request, context): ...    # unária: retorna uma mensagem
    def ListarProdutos(self, request, context): ...  # server streaming: usa `yield`
    def FecharCarrinho(self, request_iterator, context): ...  # client streaming: itera os pedidos
    def Conversar(self, request_iterator, context): ...       # bidirecional: itera E usa `yield`
```
- **Erros:** `context.abort(grpc.StatusCode.NOT_FOUND, "...")` — vira o código de status no cliente.
- **Metadata:** `context.send_initial_metadata(...)` (headers) e `context.set_trailing_metadata(...)` (trailers).
- **Cancelamento:** `context.is_active()` fica `False` quando o cliente desiste ou o prazo vence; o laço de `GerarRelatorio` para.
- **Interceptor:** `AuthInterceptor.intercept_service` roda **antes** de qualquer método: confere o token e, se faltar, devolve `UNAUTHENTICATED` sem chamar o método. Também registra no log *quem* chamou (`grpc-python` / `grpc-node-js`).
- `add_insecure_port` = HTTP/2 sem TLS (para a demo). Com TLS seria `add_secure_port` + certificados.

### 4.3 Clientes
- **Python** (`cliente.py`): `loja_pb2_grpc.CatalogoStub(canal)` e depois `stub.ObterProduto(loja_pb2.ProdutoRequest(id=1))`. Erros chegam como `grpc.RpcError` com `.code()` e `.details()`. `timeout=` define o **deadline**.
- **Node.js** (`cliente.mjs`): `@grpc/proto-loader` lê o **mesmo** `loja.proto` e monta o stub em tempo de execução; chamadas com *callbacks* e *eventos* (`on('data')`), `deadline` como data-limite, `call.cancel()`.
- **Detalhe para a prova:** Python usa stubs **gerados em tempo de build** (`protoc`); Node, neste exemplo, usa **carga dinâmica** do `.proto`. Em ambos o contrato é o `.proto`. (O Node também poderia gerar código estático.)

---

## 5. gRPC × REST (o professor pergunta!)

| | **REST** | **gRPC** |
|---|---|---|
| Paradigma | Recursos + verbos HTTP | **Chamada de procedimento remoto** (métodos) |
| Contrato | Informal (OpenAPI opcional) | **Obrigatório e tipado** (`.proto`) |
| Formato | JSON/XML (texto) | **Protobuf (binário)** |
| Transporte | HTTP/1.1 (ou 2) | **HTTP/2** obrigatório |
| Streaming | Não nativo (SSE, WebSocket à parte) | **Nativo, 4 tipos** |
| Geração de código | Opcional | **Central** (stubs em várias linguagens) |
| Desempenho | Mais verboso | Mais rápido e compacto |
| Depuração | Fácil (curl, navegador) | Mais difícil (binário; precisa de ferramenta) |
| Cache HTTP | Sim (GET, ETag) | **Não** (tudo é POST) |
| Navegador | Direto | Precisa de **gRPC-Web** |
| Acoplamento | Baixo (cliente genérico) | Maior (cliente depende do `.proto`) |
| Melhor uso | APIs públicas, web | **Microsserviços internos**, baixa latência, streaming |

---

## 6. Perguntas que o professor pode fazer (e respostas)

1. **O que é uma RPC e qual a ideia central?** Chamar um procedimento em outra máquina como se fosse local (**transparência de acesso**), escondendo a comunicação nos *stubs*.
2. **O que é uma IDL e por que o gRPC precisa dela?** É a linguagem que descreve a interface (serviços e tipos). O compilador gera os stubs de cliente e servidor, permitindo **linguagens diferentes** dos dois lados.
3. **Por que o gRPC usa HTTP/2?** Multiplexação (várias chamadas na mesma conexão TCP, sem bloquear umas às outras), **streaming bidirecional**, compressão de cabeçalhos (HPACK), controle de fluxo. Em HTTP/1.1 não existe full-duplex nem multiplexação reais.
4. **Por que Protobuf é menor que JSON?** Não envia nomes de campos (só o número da tag), usa inteiros de tamanho variável (*varint*) e não tem pontuação/aspas. Na etapa 10: 42 bytes × 95 bytes.
5. **Diferença entre os 4 tipos de chamada?** Ver seção 3.
6. **O que é deadline e por que é importante em sistemas distribuídos?** O prazo máximo que o cliente espera. Evita esperar para sempre por um servidor lento/falho (Aula 8: **falha de temporização**) e libera recursos: o servidor é avisado e **cancela** o trabalho.
7. **Para que serve metadata?** Informação "fora do corpo" da chamada (token, id de rastreio...), equivalente aos headers HTTP.
8. **O que é um interceptor?** Middleware que envolve toda chamada. Centraliza autenticação, log, métricas sem repetir código nos métodos.
9. **O gRPC é síncrono ou assíncrono?** Os dois: a chamada pode ser bloqueante (padrão) ou assíncrona (futures/callbacks) — Aula 6, RPC síncrona × assíncrona.
10. **Como o gRPC trata parâmetros por referência?** Não trata: tudo é **por valor** (a mensagem é serializada). Ponteiros não fazem sentido entre espaços de endereçamento diferentes (Aula 6, Q9).
11. **gRPC garante entrega exatamente uma vez?** Não. Uma falha de rede pode deixar o cliente sem saber se o servidor executou. Para repetir com segurança, os métodos devem ser **idempotentes** (Aula 8; REST, vídeo 1).
12. **Quando NÃO usar gRPC?** API pública consumida por navegadores/terceiros, quando precisa de cache HTTP, ou quando a facilidade de depuração importa mais que o desempenho.
13. **Como evoluir o contrato sem quebrar clientes?** Adicionando campos com **novas tags**, nunca reaproveitando/mudando o número de um campo existente.
14. **Limitação de balanceamento?** Conexões HTTP/2 são longas e multiplexadas; um balanceador L4 "gruda" o cliente num servidor. Usa-se balanceamento no cliente ou proxy L7 (ex.: Envoy).

---

## 7. Roteiro do vídeo (≤ 5 min)

| Tempo | Etapa do `demo.sh` | O que falar |
|---|---|---|
| 0:00–0:40 | 1 e 2 | "gRPC é RPC moderno (Aula 6). O contrato é o `.proto`; o `protoc` **gera os stubs**." Mostrar o service com as 4 formas de `rpc`. |
| 0:40–1:15 | 3 | **HTTP/2 no fio:** `HTTP/2 200`, corpo binário, `grpc-status` no trailer; HTTP/1.1 falha. |
| 1:15–2:00 | 4 e 5 | Chamada unária; **metadata** (headers/trailers); **status codes**; interceptor barrando sem token. |
| 2:00–3:20 | 6, 7 e 8 | Os 3 tipos de **streaming** (note os tempos +0.6s…; no bidi as mensagens se intercalam). |
| 3:20–3:50 | 9 | **Deadline** estourando e **cancelamento**; servidor para o trabalho. |
| 3:50–4:10 | 10 | **Protobuf × JSON**: 42 × 95 bytes. |
| 4:10–5:00 | 11 e 12 | **Cliente Node.js** no servidor Python, mesmo `.proto`; log do servidor com `grpc-python` e `grpc-node-js`. Fechar: vantagens (rápido, tipado, streaming, multilíngue) e limitações (binário, sem cache HTTP, navegador). |

> Dicas: rode as etapas 11 e 12 sem pausa (o cliente Node leva ~14 s). Se estourar o tempo, corte a 10 ou resuma a 5.

---

## 8. Como rodar

```bash
cd Trabalho/02-grpc
docker compose up -d --build servidor     # compila o .proto, sobe o servidor (porta 8102 no host)
./demo.sh                                 # demonstração narrável (ENTER avança)
PAUSA=0 ./demo.sh                         # sem pausas
docker compose run --rm cliente-python    # tour completo em Python
docker compose run --rm cliente-node      # tour completo em Node.js
docker compose run --rm cliente-python python -u cliente.py bidi   # só uma demo
docker compose logs servidor              # o que o servidor registrou
docker compose down -v                    # desliga
```
**Problemas comuns**
- *Porta 8102 ocupada:* mude `"8102:50051"` no compose (só o `curl` da etapa 3 usa a porta do host).
- *Mudou o `.proto`:* rode `docker compose build` — os stubs são gerados no build.
- *Cliente falha logo ao iniciar:* o servidor ainda está subindo; o compose espera o *healthcheck*, mas na 1ª vez o build demora.
