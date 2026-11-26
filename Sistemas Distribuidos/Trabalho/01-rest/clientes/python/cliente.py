"""Cliente REST em Python puro (só biblioteca padrão: urllib).

Terceira forma de consumir a mesma API (curl, Node.js e agora Python):
o contrato é o PROTOCOLO (HTTP + JSON), não a linguagem.
"""
import json
import os
import time
import urllib.error
import urllib.request

BASE = os.getenv("API_URL", "http://localhost:8101")
AUTH = {"Authorization": "Bearer segredo-da-loja"}


def titulo(t):
    print(f"\n\033[1;36m=== {t} ===\033[0m")


def chamar(metodo, caminho, corpo=None, headers=None):
    h = {"Content-Type": "application/json", **(headers or {})}
    dados = json.dumps(corpo).encode() if corpo is not None else None
    req = urllib.request.Request(BASE + caminho, data=dados, headers=h, method=metodo)
    try:
        resp = urllib.request.urlopen(req)
    except urllib.error.HTTPError as e:  # 4xx/5xx/304 viram exceção no urllib
        resp = e
    texto = resp.read().decode()
    print(f"{metodo} {caminho} -> {resp.status}")
    ct = resp.headers.get("Content-Type", "")
    return resp.status, (json.loads(texto) if texto and "json" in ct else texto), resp.headers


titulo("1) Raiz da API (HATEOAS)")
_, raiz, _ = chamar("GET", "/")
print("links:", list(raiz["_links"]))

titulo("2) Listagem com filtro e paginação")
_, lista, h = chamar("GET", "/produtos?categoria=casa&tamanho=1")
print("X-Total-Count:", h["X-Total-Count"], "| Link:", h.get("Link"))

titulo("3) POST + PUT + PATCH + DELETE")
nome = f"Produto do Python {int(time.time()) % 100000}"
_, p, _ = chamar("POST", "/produtos", {"nome": nome, "preco": 10, "categoria": "python", "estoque": 3}, AUTH)
pid = p["id"]
chamar("PUT", f"/produtos/{pid}", {"nome": nome, "preco": 20, "categoria": "python", "estoque": 3}, AUTH)
_, p2, _ = chamar("PATCH", f"/produtos/{pid}", {"estoque": 99}, AUTH)
print("estoque após PATCH:", p2["estoque"], "| preço continua:", p2["preco"])
chamar("DELETE", f"/produtos/{pid}", headers=AUTH)
chamar("DELETE", f"/produtos/{pid}", headers=AUTH)  # 2º DELETE -> 404 (estado final igual)

titulo("4) Negociação de conteúdo: pedindo XML")
req = urllib.request.Request(BASE + "/produtos/2", headers={"Accept": "application/xml"})
print(urllib.request.urlopen(req).read().decode()[:160], "...")

print("\n\033[1;32mCliente Python terminou: mesma API, linguagem diferente.\033[0m")
