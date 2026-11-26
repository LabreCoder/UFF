"""
Cliente gRPC em Python — usa os STUBS GERADOS pelo protoc (loja_pb2 / loja_pb2_grpc).

Uso:  python cliente.py <demo>
      demos: unaria | erros | servidor | cliente | bidi | deadline | tamanho | todos
Note como chamar um método remoto parece chamar uma função local:
      stub.ObterProduto(ProdutoRequest(id=1))     <- transparência de acesso (Aula 1/6)
"""
import json
import os
import sys
import threading
import time

import grpc
from google.protobuf.json_format import MessageToDict

import loja_pb2
import loja_pb2_grpc

ALVO = os.getenv("ALVO", "localhost:8102")
AUTH = (("authorization", "Bearer segredo-da-loja"),)   # metadata enviada em toda chamada


def titulo(t):
    print(f"\n\033[1;36m=== {t} ===\033[0m", flush=True)


def stub_novo():
    canal = grpc.insecure_channel(ALVO)                 # 1 canal HTTP/2, várias chamadas multiplexadas
    return loja_pb2_grpc.CatalogoStub(canal)


# ---------------------------------------------------------------------------
def unaria(stub):
    titulo("1) UNÁRIA: 1 requisição -> 1 resposta (+ metadata)")
    resp, call = stub.ObterProduto.with_call(loja_pb2.ProdutoRequest(id=1), metadata=AUTH, timeout=5)
    print("resposta :", resp.nome, "| R$", resp.preco, "| estoque", resp.estoque)
    print("metadata inicial (headers):", dict(call.initial_metadata()))
    print("metadata final   (trailers):", dict(call.trailing_metadata()))


def erros(stub):
    titulo("2) CÓDIGOS DE STATUS gRPC")
    casos = [
        ("produto inexistente (id=999)", dict(request=loja_pb2.ProdutoRequest(id=999), metadata=AUTH)),
        ("id inválido (id=-5)", dict(request=loja_pb2.ProdutoRequest(id=-5), metadata=AUTH)),
        ("sem token (metadata ausente)", dict(request=loja_pb2.ProdutoRequest(id=1), metadata=None)),
    ]
    for nome, kw in casos:
        try:
            stub.ObterProduto(kw["request"], metadata=kw["metadata"], timeout=5)
        except grpc.RpcError as e:                      # todo erro vira RpcError com code() + details()
            print(f"{nome:32} -> {e.code().name:16} | {e.details()}")


def servidor_streaming(stub):
    titulo("3) SERVER STREAMING: 1 requisição -> N respostas (chegam uma a uma)")
    t0 = time.time()
    for p in stub.ListarProdutos(loja_pb2.FiltroRequest(categoria="informatica", atraso_ms=600), metadata=AUTH):
        print(f"  +{time.time() - t0:3.1f}s  recebido: {p.nome}", flush=True)


def cliente_streaming(stub):
    titulo("4) CLIENT STREAMING: N requisições -> 1 resposta")

    def itens():                                        # gerador: cada yield = 1 mensagem enviada
        for pid, qtd in [(1, 1), (2, 3), (5, 2), (777, 1)]:
            print(f"  enviando produto={pid} qtd={qtd}", flush=True)
            yield loja_pb2.ItemCarrinho(produto_id=pid, quantidade=qtd)
            time.sleep(0.4)

    r = stub.FecharCarrinho(itens(), metadata=AUTH)
    print(f"  resumo: {r.itens} itens, {r.unidades} unidades, total R$ {r.total} | avisos: {list(r.avisos)}")


def bidirecional(stub):
    titulo("5) BIDIRECIONAL: os dois lados falam ao mesmo tempo")

    def falas():
        for texto in ["Meu pedido atrasou", "Quero trocar o produto", "Obrigado!"]:
            time.sleep(0.8)
            print(f"  [cliente] -> {texto}", flush=True)
            yield loja_pb2.Mensagem(autor="Cliente", texto=texto, timestamp=int(time.time()))

    for m in stub.Conversar(falas(), metadata=AUTH):    # respostas chegam ENQUANTO enviamos
        print(f"  [servidor] <- {m.autor}: {m.texto}", flush=True)


def deadline(stub):
    titulo("6) DEADLINE (prazo) e CANCELAMENTO")
    r = stub.GerarRelatorio(loja_pb2.RelatorioRequest(duracao_ms=500), metadata=AUTH, timeout=2)
    print("dentro do prazo      :", r.conteudo)
    try:
        stub.GerarRelatorio(loja_pb2.RelatorioRequest(duracao_ms=3000), metadata=AUTH, timeout=1)
    except grpc.RpcError as e:
        print("prazo de 1s estourou :", e.code().name, "| o servidor foi avisado e parou o trabalho")
    futuro = stub.GerarRelatorio.future(loja_pb2.RelatorioRequest(duracao_ms=5000), metadata=AUTH)
    time.sleep(0.5)
    futuro.cancel()                                     # o cliente desiste
    time.sleep(0.4)
    print("cancelamento         : cancelado =", futuro.cancelled())


def tamanho(_stub):
    titulo("7) PROTOBUF (binário) x JSON (texto)")
    p = loja_pb2.Produto(id=1, nome="Notebook Gamer", preco=5999.90, categoria="informatica", estoque=10)
    pb = p.SerializeToString()
    js = json.dumps(MessageToDict(p, preserving_proto_field_name=True), ensure_ascii=False).encode()
    print("JSON     :", js.decode(), f"  -> {len(js)} bytes")
    print("Protobuf :", pb.hex(" "), f"  -> {len(pb)} bytes")
    print(f"Protobuf ocupa {100 * len(pb) / len(js):.0f}% do JSON (campos viajam como números de tag, sem nomes).")
    lista = [loja_pb2.Produto(id=i, nome=f"Produto {i}", preco=i * 1.5, categoria="geral", estoque=i) for i in range(1, 101)]
    pb_total = sum(len(x.SerializeToString()) for x in lista)
    js_total = len(json.dumps([MessageToDict(x, preserving_proto_field_name=True) for x in lista]).encode())
    print(f"100 produtos: JSON {js_total} bytes | Protobuf {pb_total} bytes (+ delimitadores de 5 bytes por mensagem no gRPC)")


DEMOS = {"unaria": unaria, "erros": erros, "servidor": servidor_streaming, "cliente": cliente_streaming,
         "bidi": bidirecional, "deadline": deadline, "tamanho": tamanho}

if __name__ == "__main__":
    escolha = sys.argv[1] if len(sys.argv) > 1 else "todos"
    stub = stub_novo()
    for nome in (DEMOS if escolha == "todos" else [escolha]):
        DEMOS[nome](stub)
    print("\n\033[1;32mCliente gRPC Python terminou (stubs gerados pelo protoc).\033[0m")
