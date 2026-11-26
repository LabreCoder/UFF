# 🌐 REST — Guia de Estudo e Roteiro do Vídeo

> **Cenário:** API de uma *Loja Online* (produtos e pedidos).
> **Stack:** servidor Python (FastAPI) atrás de um gateway nginx; clientes em curl, **Node.js** e **Python**. Tudo em Docker.

---

## 1. O que é REST (em 5 linhas)

**REST (Representational State Transfer)** não é um protocolo, é um **estilo arquitetural** (Aula 5, "estilo baseado em recursos"). Ele usa o próprio HTTP: tudo é um **recurso** identificado por uma **URI**, e o cliente o manipula trocando **representações** (JSON, XML...) com um conjunto pequeno de **verbos** padronizados. O servidor **não guarda estado da conversa**: cada requisição é independente. Isso o torna simples, escalável e interoperável: qualquer linguagem que fale HTTP consegue usá-lo.

**Onde se liga às aulas:** `../../Aula_5` (estilos arquiteturais: cliente-servidor, camadas, baseado em recursos/REST), `../../Aula_6` (RPC × REST: *"em aplicações Web, RPC perdeu espaço para REST"*), `../../Aula_1` (transparência, abertura/interoperabilidade).

---

## 2. As 6 restrições do REST e onde cada uma aparece

| # | Restrição REST | O que significa | Onde está na demo |
|---|---|---|---|
| R1 | **Cliente-servidor** | Separação de responsabilidades: a API entrega dados, o cliente decide a apresentação | Três clientes diferentes usam a mesma API |
| R2 | **Sem estado (stateless)** | Cada requisição carrega tudo o que o servidor precisa (inclusive o token) | Etapa 7: sem token → 401; token vai em **toda** escrita |
| R3 | **Recursos e URIs** | Substantivos, não verbos: `/produtos/3`, não `/obterProduto?id=3` | Etapa 2 (coleção, item, filtro, paginação) |
| R4 | **Verbos HTTP / interface uniforme** | Poucos verbos com semântica fixa | Etapas 8, 10, 11, 12, 14, 15 |
| R6 | **Representações** | O mesmo recurso em formatos diferentes (negociação com `Accept`) | Etapa 6 (JSON, XML, 406) |
| R7 | **Cache** | Respostas rotuladas como cacheáveis podem ser reutilizadas | Etapas 4, 5, 13 (ETag, max-age, 304, 412) |
| R8 | **Sistema em camadas** | O cliente não sabe se fala com o servidor final ou com um intermediário | Etapa 3 (gateway nginx) |
| R9 | **HATEOAS** (interface uniforme) | A resposta traz *links* do que fazer a seguir | Etapa 1 (`_links`) e Node etapa 2 |
| — | *Código sob demanda* (opcional) | Servidor envia código executável (ex.: JavaScript) | Não usado; é a única restrição opcional |

> **Sobre a numeração [R1]…[R9]:** são só *etiquetas* minhas, usadas nos comentários do código e no `demo.sh` para você achar cada ponto. **[R5] = códigos de status** (item de HTTP, não uma restrição do REST, por isso não está nesta tabela). Já [R3], [R4], [R6] e [R9] são aspectos da **interface uniforme** (recursos, verbos, representações, HATEOAS).
>
> **Dica de prova:** são 5 restrições obrigatórias (cliente-servidor, stateless, cache, interface uniforme, camadas) + 1 opcional (código sob demanda).

---

## 3. Verbos HTTP: propriedades que o professor adora perguntar

| Verbo | Uso | Seguro? (não altera) | Idempotente? (repetir = mesmo estado final) | Na demo |
|---|---|---|---|---|
| **GET** | ler | ✅ | ✅ | etapas 1–6 |
| **HEAD** | ler só cabeçalhos | ✅ | ✅ | etapa 14 |
| **OPTIONS** | descobrir o que é permitido (`Allow`) | ✅ | ✅ | etapa 14 |
| **POST** | criar / ação | ❌ | ❌ | etapa 8 e **12** (dois pedidos) |
| **PUT** | substituir por completo | ❌ | ✅ | etapa 10 (ETag igual nas duas) |
| **PATCH** | alterar parcialmente | ❌ | (depende) | etapa 11 |
| **DELETE** | remover | ❌ | ✅ | etapa 15 (204 e depois 404) |

**Idempotente** não quer dizer "mesma resposta", e sim **mesmo estado no servidor**. Por isso o 2º `DELETE` devolve 404 e continua sendo idempotente.

## 4. Códigos de status usados

| Código | Quando | Etapa |
|---|---|---|
| **200 OK** | leitura/atualização bem-sucedida | várias |
| **201 Created** + `Location` | recurso criado | 8, 12 |
| **204 No Content** | sucesso sem corpo (DELETE, OPTIONS) | 14, 15 |
| **304 Not Modified** | o cliente já tem a versão atual (cache) | 5 |
| **400 Bad Request** | requisição malformada (`pagina=0`) | 9 |
| **401 Unauthorized** | sem/errado token | 7 |
| **404 Not Found** | recurso não existe | 9, 15 |
| **406 Not Acceptable** | não há representação no formato pedido | 6 |
| **409 Conflict** | conflito com o estado atual (nome duplicado, estoque insuficiente) | 9, 12 |
| **412 Precondition Failed** | `If-Match` com ETag velha | 13 |
| **422 Unprocessable Entity** | dados semanticamente inválidos (preço negativo) | 9 |

Famílias: **2xx** sucesso, **3xx** redirecionamento/cache, **4xx** erro do **cliente**, **5xx** erro do **servidor**.

---

## 5. Código explicado

### 5.1 Arquitetura
```
 curl / Node.js / Python           nginx (gateway)                 FastAPI (api)
 ───────────────────────►  porta 8101 ──► cache + proxy ──►  porta 8000 (interna)
        HTTP/JSON                R8: camada intermediária          dados em memória
```
Só o gateway publica porta. A API não é alcançável de fora: o cliente **não sabe** que ela existe (R8).

### 5.2 `api/app.py` (trechos-chave)

**Recursos e rotas (R3/R4)** — cada decorador liga *verbo + URI* a uma função:
```python
@app.get("/produtos")            # listar (com filtro e paginação na query string)
@app.post("/produtos", status_code=201, ...)   # criar -> 201 + Location
@app.api_route("/produtos/{pid}", methods=["GET","HEAD"])  # ler um
@app.put("/produtos/{pid}")      # substituir (idempotente)
@app.patch("/produtos/{pid}")    # alterar parcialmente (exclude_unset=True)
@app.delete("/produtos/{pid}", status_code=204)
```

**Stateless (R2)** — a função `exigir_token` é executada em *cada* requisição de escrita. Não existe `login`, cookie nem sessão no servidor:
```python
def exigir_token(authorization: Optional[str] = Header(None)):
    if authorization != f"Bearer {TOKEN}":
        raise HTTPException(401, ...)
```

**Cache (R7)** — o servidor dá uma *impressão digital* (ETag) do recurso e diz por quanto tempo vale:
```python
cab = {"ETag": etag, "Cache-Control": "public, max-age=10"}
if request.headers.get("if-none-match") == etag:
    return Response(status_code=304, headers=cab)   # sem corpo!
```
- `max-age=10`: durante 10 s o gateway/navegador reaproveita a resposta **sem perguntar à API**.
- Depois disso, o cliente pode **revalidar** com `If-None-Match`: se nada mudou → **304** (economiza banda).
- No `PUT`, o `If-Match` faz o inverso: **só grava se a versão ainda é a que o cliente viu** → senão **412** (controle de concorrência otimista, evita "perder atualizações").

**Negociação de conteúdo (R6)** — o cliente diz o que aceita, o servidor escolhe:
```python
if "json" in accept or "*/*" in accept: ... JSON
if "xml" in accept: ... XML
else: raise HTTPException(406, ...)
```

**HATEOAS (R9)** — cada recurso vem com `_links` dizendo o que é possível fazer. O cliente Node, por exemplo, **segue o link `produtos` da raiz** em vez de ter a URL escrita no código.

### 5.3 `gateway/nginx.conf`
- `proxy_pass http://api:8000` → camada intermediária (R8).
- `proxy_cache` + `proxy_cache_key "$request_uri|$http_accept"` → o gateway guarda as respostas cacheáveis; a chave inclui o `Accept` porque JSON e XML são representações diferentes.
- `add_header X-Cache-Status` → torna visível **MISS / HIT / EXPIRED**.

### 5.4 Clientes (interoperabilidade)
`clientes/node/cliente.mjs` (JavaScript, `fetch` nativo do Node 20) e `clientes/python/cliente.py` (só `urllib`). **Nenhum conhece o código da API**: só sabem HTTP + JSON. Isso demonstra a vantagem central pedida no enunciado: **interoperabilidade entre linguagens**, sem stubs, sem geração de código, sem biblioteca específica.

---

## 6. Perguntas que o professor pode fazer (e respostas)

1. **REST é um protocolo?** Não. É um estilo arquitetural que usa o protocolo HTTP.
2. **O que significa "sem estado"? Isso quer dizer que o servidor não guarda dados?** Não: o servidor guarda o *estado dos recursos* (produtos, pedidos). O que ele **não** guarda é o *estado da sessão/conversa*. Cada requisição é autossuficiente. Vantagem: qualquer instância pode atender qualquer requisição → **escalabilidade horizontal** e tolerância a falhas (Aula 1/5).
3. **Diferença entre PUT e PATCH?** PUT substitui o recurso inteiro (idempotente); PATCH altera só os campos enviados.
4. **POST é idempotente?** Não: repetir cria outro recurso (etapa 12 cria 2 pedidos).
5. **O que é idempotência e por que importa?** Repetir a operação deixa o servidor no mesmo estado. Importa para **retentativas seguras** quando a rede falha (Aula 8, tolerância a falhas).
6. **Para que serve o ETag?** Identifica a versão do recurso: permite cache condicional (304) e controle de concorrência (If-Match → 412).
7. **Qual a diferença entre 401 e 403? E 404 e 410?** 401 = não autenticado; 403 = autenticado mas sem permissão. 404 = não existe (ou não quero revelar); 410 = existiu e foi removido de vez.
8. **REST × RPC (gRPC)?** REST é orientado a **recursos** (substantivos + verbos fixos), texto (JSON), sobre HTTP/1.1, fácil de depurar e cachear. RPC é orientado a **ações** (chamar função remota), com IDL e stubs (Aula 6). Em contrapartida o gRPC é binário e mais rápido, com streaming (vídeo 2).
9. **Vantagens e desvantagens do REST?** + simples, interoperável, cacheável, escalável. − *over/under-fetching* (resposta com mais/menos dados que o necessário), JSON verboso, sem tipagem forte nem streaming nativo, vários *round-trips*.
10. **Qual a vantagem de ter o gateway na frente?** Cache, balanceamento, TLS, autenticação central, esconder a topologia; o cliente nunca muda quando o back-end muda (transparência de localização/migração).
11. **O que é HATEOAS?** O cliente navega pela API seguindo links devolvidos pelo servidor, como um usuário clica em links numa página web. Desacopla o cliente das URLs.
12. **Limitação do cache nesta demo?** O gateway pode servir uma versão **desatualizada** por até 10 s após um PATCH (o nginx OSS não invalida). Essa é a troca clássica **desempenho × consistência** (Aula 7: consistência eventual).

---

## 7. Roteiro do vídeo (≤ 5 min)

> Dica: deixe a janela do terminal grande, fonte legível. Rode `./demo.sh` com pausas e fale durante cada pausa. Se passar de 5 min, corte as etapas marcadas ✂️.

| Tempo | Tela | O que falar |
|---|---|---|
| 0:00–0:30 | Slide/README + `docker compose ps` | "REST é um estilo arquitetural sobre HTTP. Aqui: loja online, API em Python atrás de um gateway nginx; clientes em curl, Node e Python." Mostrar que só a porta 8101 está exposta. |
| 0:30–1:15 | Etapas 1–2 | Recursos e URIs; HATEOAS (`_links`); filtro e paginação na query string. |
| 1:15–2:00 | Etapas 3–5 | **Camadas** (X-Gateway/X-Servidor), **cache** MISS→HIT com mesmo X-Gerado-Em, **304** com ETag. |
| 2:00–2:30 | Etapa 6 ✂️ | Negociação de conteúdo: JSON, XML, 406. |
| 2:30–3:30 | Etapas 7–9 | **Stateless** (401 sem token), POST → 201 + Location, erros 409/422/404/400. |
| 3:30–4:15 | Etapas 10–12, 15 | PUT/PATCH/DELETE; **idempotência** (PUT e DELETE sim, POST não). |
| 4:15–4:50 | Etapa 16 | **Interoperabilidade**: clientes Node.js e Python rodando contra a mesma API. |
| 4:50–5:00 | Fecho | "Vantagens: simples, cacheável, escalável, interoperável. Limitações: sem streaming nativo, JSON verboso — por isso o gRPC, no próximo vídeo." |

*(Etapas 13–14 — If-Match/412, HEAD/OPTIONS — são extras; cite-as só se sobrar tempo, ou faça-as sem pausa.)*

---

## 8. Como rodar

```bash
cd Trabalho/01-rest
docker compose up -d --build       # sobe API + gateway (porta 8101)
./demo.sh                          # demonstração narrável (ENTER avança)
PAUSA=0 ./demo.sh                  # sem pausas
docker compose run --rm cliente-node      # só o cliente Node.js
docker compose run --rm cliente-python    # só o cliente Python
docker compose restart api         # zera os dados em memória (repetir a demo)
docker compose down                # desliga e remove
```
Documentação interativa gerada automaticamente (OpenAPI/Swagger): **http://localhost:8101/docs**

**Problemas comuns**
- *Porta 8101 ocupada:* mude `"8101:80"` no `docker-compose.yml` e use `BASE=http://localhost:NOVA ./demo.sh`.
- *Demo repetida dá 409 em "Monitor 4K":* o produto já foi criado → `docker compose restart api`.
- *X-Cache-Status aparece EXPIRED em vez de MISS:* normal se a mesma URL foi pedida há menos de 60 s; o importante é a 2ª chamada ser HIT.
