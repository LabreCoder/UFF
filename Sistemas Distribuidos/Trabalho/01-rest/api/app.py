"""
API REST da "Loja Online" — Trabalho de Sistemas Distribuídos (UFF)

Este arquivo é PROPOSITALMENTE didático: cada bloco indica qual característica
do estilo REST ele demonstra. Os números entre colchetes [R1], [R2]... são as
mesmas referências usadas no GUIA.md e no demo.sh.

  [R1] Cliente-servidor      -> a API só expõe dados; quem desenha a tela é o cliente
  [R2] Sem estado (stateless)-> cada requisição traz o token; o servidor não guarda sessão
  [R3] Recursos e URIs       -> /produtos, /produtos/{id}, /pedidos/{id}
  [R4] Verbos HTTP           -> GET, HEAD, POST, PUT, PATCH, DELETE, OPTIONS
  [R5] Códigos de status     -> 200, 201, 204, 304, 400, 401, 404, 406, 409, 412, 422
  [R6] Representações        -> o mesmo recurso em JSON ou XML (cabeçalho Accept)
  [R7] Cache                 -> ETag + Cache-Control (+ 304 Not Modified)
  [R8] Sistema em camadas    -> o cliente fala com um gateway nginx, não com a API
  [R9] Interface uniforme    -> HATEOAS: respostas trazem links (_links)
"""
import hashlib
import json
import os
import socket
from datetime import datetime, timezone
from typing import Optional
from xml.etree import ElementTree as ET

from fastapi import Depends, FastAPI, Header, HTTPException, Request, Response
from pydantic import BaseModel, Field

# Token fixo só para a demonstração (em produção: JWT/OAuth2).
TOKEN = os.getenv("API_TOKEN", "segredo-da-loja")

app = FastAPI(
    title="API da Loja Online (REST)",
    description="Demonstração das características do estilo arquitetural REST.",
    version="1.0.0",
)

# --------------------------------------------------------------------------
# "Banco de dados" em memória. O ESTADO DO RECURSO vive aqui (no servidor),
# mas o ESTADO DA CONVERSA (sessão) NÃO: isso é o stateless [R2].
# --------------------------------------------------------------------------
produtos: dict[int, dict] = {
    1: {"id": 1, "nome": "Notebook Gamer", "preco": 5999.90, "categoria": "informatica", "estoque": 10},
    2: {"id": 2, "nome": "Mouse Sem Fio", "preco": 89.90, "categoria": "informatica", "estoque": 50},
    3: {"id": 3, "nome": "Cafeteira Expresso", "preco": 349.00, "categoria": "casa", "estoque": 8},
    4: {"id": 4, "nome": "Liquidificador", "preco": 199.90, "categoria": "casa", "estoque": 15},
    5: {"id": 5, "nome": "Camiseta UFF", "preco": 59.90, "categoria": "vestuario", "estoque": 100},
    6: {"id": 6, "nome": "Teclado Mecânico", "preco": 429.90, "categoria": "informatica", "estoque": 20},
}
pedidos: dict[int, dict] = {}
_proximo = {"produto": 7, "pedido": 1}


# --------------------------------------------------------------------------
# Modelos de entrada (validação automática -> 422 quando inválido) [R5]
# --------------------------------------------------------------------------
class ProdutoIn(BaseModel):
    nome: str = Field(min_length=2, max_length=80)
    preco: float = Field(gt=0)
    categoria: str = Field(min_length=2, max_length=40)
    estoque: int = Field(ge=0)


class ProdutoPatch(BaseModel):
    """PATCH = atualização PARCIAL: todos os campos são opcionais."""
    nome: Optional[str] = Field(None, min_length=2, max_length=80)
    preco: Optional[float] = Field(None, gt=0)
    categoria: Optional[str] = Field(None, min_length=2, max_length=40)
    estoque: Optional[int] = Field(None, ge=0)


class PedidoIn(BaseModel):
    produto_id: int
    quantidade: int = Field(gt=0)


# --------------------------------------------------------------------------
# [R2] Autenticação SEM ESTADO: o servidor não lembra quem você é entre
# requisições. Todo pedido de escrita precisa trazer o token de novo.
# --------------------------------------------------------------------------
def exigir_token(authorization: Optional[str] = Header(None)):
    if authorization != f"Bearer {TOKEN}":
        raise HTTPException(
            status_code=401,
            detail="Token ausente ou inválido. Envie o header 'Authorization: Bearer <token>'.",
            headers={"WWW-Authenticate": "Bearer"},
        )


# --------------------------------------------------------------------------
# Cabeçalhos que ajudam a PROVAR a arquitetura em camadas [R8] e o cache [R7]:
#   X-Servidor  = quem realmente processou (container da API)
#   X-Gerado-Em = horário em que a API montou a resposta. Se uma resposta
#                 vier do cache do gateway, este horário NÃO muda.
# --------------------------------------------------------------------------
@app.middleware("http")
async def cabecalhos_comuns(request: Request, call_next):
    resposta = await call_next(request)
    resposta.headers["X-Servidor"] = socket.gethostname()
    resposta.headers["X-Gerado-Em"] = datetime.now(timezone.utc).strftime("%H:%M:%S")
    return resposta


# --------------------------------------------------------------------------
# [R6] Negociação de conteúdo: o MESMO recurso, REPRESENTAÇÕES diferentes.
# --------------------------------------------------------------------------
def _para_xml(tag: str, valor) -> ET.Element:
    el = ET.Element(tag)
    if isinstance(valor, dict):
        for k, v in valor.items():
            if isinstance(v, list):
                lista = ET.SubElement(el, k)
                for item in v:
                    lista.append(_para_xml("item", item))
            else:
                el.append(_para_xml(k, v))
    else:
        el.text = str(valor)
    return el


def responder(request: Request, dados: dict, raiz: str, status: int = 200, headers: Optional[dict] = None) -> Response:
    accept = request.headers.get("accept", "*/*").lower()
    headers = dict(headers or {})
    if "json" in accept or "*/*" in accept:
        return Response(json.dumps(dados, ensure_ascii=False), status_code=status,
                        media_type="application/json", headers=headers)
    if "xml" in accept:
        corpo = ET.tostring(_para_xml(raiz, dados), encoding="unicode")
        return Response('<?xml version="1.0" encoding="UTF-8"?>' + corpo, status_code=status,
                        media_type="application/xml", headers=headers)
    raise HTTPException(406, "Representação não suportada. Use Accept: application/json ou application/xml.")


def _etag(p: dict) -> str:
    """ETag = 'impressão digital' do estado atual do recurso [R7]."""
    return '"' + hashlib.md5(json.dumps(p, sort_keys=True).encode()).hexdigest()[:16] + '"'


def _achar(pid: int) -> dict:
    if pid not in produtos:
        raise HTTPException(404, f"Produto {pid} não encontrado.")
    return produtos[pid]


def _com_links(p: dict) -> dict:
    """[R9] HATEOAS: a resposta diz ao cliente o que ele pode fazer a seguir."""
    return {
        **p,
        "_links": {
            "self": {"href": f"/produtos/{p['id']}", "method": "GET"},
            "atualizar": {"href": f"/produtos/{p['id']}", "method": "PUT"},
            "remover": {"href": f"/produtos/{p['id']}", "method": "DELETE"},
            "colecao": {"href": "/produtos", "method": "GET"},
            "comprar": {"href": "/pedidos", "method": "POST"},
        },
    }


# ==========================================================================
# ENDPOINTS
# ==========================================================================
@app.get("/", summary="Ponto de entrada (HATEOAS)")
def raiz(request: Request):
    """O cliente só precisa conhecer ESTA URL; o resto ele descobre pelos links [R9]."""
    dados = {
        "nome": "API da Loja Online",
        "versao": "1.0.0",
        "_links": {
            "produtos": {"href": "/produtos", "method": "GET"},
            "pedidos": {"href": "/pedidos", "method": "POST"},
            "documentacao": {"href": "/docs", "method": "GET"},
        },
    }
    return responder(request, dados, "loja")


# ---------------- COLEÇÃO /produtos ----------------
@app.get("/produtos", summary="Listar produtos (filtro + paginação)")
def listar(
    request: Request,
    categoria: Optional[str] = None,
    preco_max: Optional[float] = None,
    pagina: int = 1,
    tamanho: int = 3,
):
    # [R3] Filtro e paginação vão na QUERY STRING; o recurso continua sendo /produtos.
    if pagina < 1 or not (1 <= tamanho <= 50):
        raise HTTPException(400, "Parâmetros inválidos: pagina >= 1 e 1 <= tamanho <= 50.")  # [R5] 400
    itens = list(produtos.values())
    if categoria:
        itens = [p for p in itens if p["categoria"] == categoria]
    if preco_max is not None:
        itens = [p for p in itens if p["preco"] <= preco_max]
    total = len(itens)
    inicio = (pagina - 1) * tamanho
    fatia = itens[inicio:inicio + tamanho]

    links = {"self": {"href": f"/produtos?pagina={pagina}&tamanho={tamanho}"}}
    cab = {"X-Total-Count": str(total), "Cache-Control": "no-store"}
    if inicio + tamanho < total:
        prox = f"/produtos?pagina={pagina + 1}&tamanho={tamanho}"
        links["proxima"] = {"href": prox}
        cab["Link"] = f'<{prox}>; rel="next"'  # padrão HTTP para paginação
    if pagina > 1:
        links["anterior"] = {"href": f"/produtos?pagina={pagina - 1}&tamanho={tamanho}"}

    dados = {"total": total, "pagina": pagina, "itens": [_com_links(p) for p in fatia], "_links": links}
    return responder(request, dados, "produtos", headers=cab)


@app.post("/produtos", status_code=201, dependencies=[Depends(exigir_token)], summary="Criar produto")
def criar(novo: ProdutoIn, request: Request):
    # POST NÃO é idempotente em geral. Aqui impedimos nomes duplicados -> 409 Conflict.
    if any(p["nome"].lower() == novo.nome.lower() for p in produtos.values()):
        raise HTTPException(409, f"Já existe um produto chamado '{novo.nome}'.")
    pid = _proximo["produto"]
    _proximo["produto"] += 1
    produtos[pid] = {"id": pid, **novo.model_dump()}
    # [R5] 201 Created + header Location apontando para o NOVO recurso.
    return responder(request, _com_links(produtos[pid]), "produto", status=201,
                     headers={"Location": f"/produtos/{pid}", "Cache-Control": "no-store"})


@app.api_route("/produtos", methods=["OPTIONS"], include_in_schema=False)
def opcoes_colecao():
    # OPTIONS: "o que eu posso fazer neste recurso?"
    return Response(status_code=204, headers={"Allow": "GET, POST, HEAD, OPTIONS"})


# ---------------- ITEM /produtos/{id} ----------------
@app.api_route("/produtos/{pid}", methods=["GET", "HEAD"], summary="Obter produto (com cache)")
def obter(pid: int, request: Request):
    p = _achar(pid)
    etag = _etag(p)
    # [R7] max-age=10: caches (gateway/navegador) podem reutilizar por 10 s sem perguntar à API.
    cab = {"ETag": etag, "Cache-Control": "public, max-age=10"}
    # [R7] GET condicional: se o cliente já tem esta versão, respondemos 304 SEM corpo.
    if request.headers.get("if-none-match") == etag:
        return Response(status_code=304, headers=cab)
    return responder(request, _com_links(p), "produto", headers=cab)


@app.put("/produtos/{pid}", dependencies=[Depends(exigir_token)], summary="Substituir produto (idempotente)")
def substituir(pid: int, novo: ProdutoIn, request: Request, if_match: Optional[str] = Header(None)):
    atual = _achar(pid)
    # Controle de concorrência OTIMISTA: só altera se o cliente viu a versão atual.
    if if_match is not None and if_match != _etag(atual):
        raise HTTPException(412, "Precondition Failed: o produto mudou desde que você o leu (ETag diferente).")
    produtos[pid] = {"id": pid, **novo.model_dump()}
    return responder(request, _com_links(produtos[pid]), "produto",
                     headers={"ETag": _etag(produtos[pid]), "Cache-Control": "no-store"})


@app.patch("/produtos/{pid}", dependencies=[Depends(exigir_token)], summary="Atualizar parcialmente")
def atualizar(pid: int, mudancas: ProdutoPatch, request: Request):
    p = _achar(pid)
    p.update(mudancas.model_dump(exclude_unset=True))  # só os campos enviados
    return responder(request, _com_links(p), "produto",
                     headers={"ETag": _etag(p), "Cache-Control": "no-store"})


@app.delete("/produtos/{pid}", status_code=204, dependencies=[Depends(exigir_token)], summary="Remover produto")
def remover(pid: int):
    _achar(pid)
    del produtos[pid]
    # [R5] 204 No Content: deu certo e não há corpo. Repetir o DELETE dá 404
    # (o ESTADO FINAL do servidor é o mesmo => DELETE é idempotente).
    return Response(status_code=204)


@app.api_route("/produtos/{pid}", methods=["OPTIONS"], include_in_schema=False)
def opcoes_item(pid: int):
    return Response(status_code=204, headers={"Allow": "GET, HEAD, PUT, PATCH, DELETE, OPTIONS"})


# ---------------- PEDIDOS ----------------
@app.post("/pedidos", status_code=201, dependencies=[Depends(exigir_token)], summary="Criar pedido")
def criar_pedido(novo: PedidoIn, request: Request):
    """POST repetido cria pedidos DIFERENTES -> POST não é idempotente."""
    p = produtos.get(novo.produto_id)
    if p is None:
        raise HTTPException(404, f"Produto {novo.produto_id} não encontrado.")
    if p["estoque"] < novo.quantidade:
        raise HTTPException(409, f"Estoque insuficiente: pedido de {novo.quantidade}, disponível {p['estoque']}.")
    p["estoque"] -= novo.quantidade
    oid = _proximo["pedido"]
    _proximo["pedido"] += 1
    pedidos[oid] = {
        "id": oid, "produto_id": p["id"], "quantidade": novo.quantidade,
        "total": round(p["preco"] * novo.quantidade, 2), "status": "confirmado",
    }
    dados = {**pedidos[oid], "_links": {"self": {"href": f"/pedidos/{oid}"}, "produto": {"href": f"/produtos/{p['id']}"}}}
    return responder(request, dados, "pedido", status=201,
                     headers={"Location": f"/pedidos/{oid}", "Cache-Control": "no-store"})


@app.get("/pedidos/{oid}", dependencies=[Depends(exigir_token)], summary="Consultar pedido")
def obter_pedido(oid: int, request: Request):
    if oid not in pedidos:
        raise HTTPException(404, f"Pedido {oid} não encontrado.")
    return responder(request, pedidos[oid], "pedido", headers={"Cache-Control": "no-store"})
