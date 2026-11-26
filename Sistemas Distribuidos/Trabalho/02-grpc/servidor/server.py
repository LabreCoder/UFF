"""
Servidor gRPC da Loja (Python).

Características do gRPC demonstradas aqui:
  [G1] Stubs gerados a partir do .proto  -> `loja_pb2` e `loja_pb2_grpc` (gerados no build)
  [G2] 4 tipos de chamada                -> ObterProduto / ListarProdutos / FecharCarrinho / Conversar
  [G3] Códigos de status gRPC            -> NOT_FOUND, INVALID_ARGUMENT, UNAUTHENTICATED...
  [G4] Metadata                          -> headers (inicial) e trailers (final) da chamada
  [G5] Interceptor                       -> AuthInterceptor: roda ANTES de qualquer método
  [G6] Deadline e cancelamento           -> GerarRelatorio percebe quando o cliente desistiu
  [G7] HTTP/2                            -> o servidor é um servidor HTTP/2 (porta 50051)
"""
import socket
import time
from concurrent import futures

import grpc

import loja_pb2          # classes das MENSAGENS (Produto, FiltroRequest...)  [G1]
import loja_pb2_grpc     # classes do SERVIÇO (CatalogoServicer, stub)        [G1]

TOKEN = "segredo-da-loja"

PRODUTOS = {
    1: {"id": 1, "nome": "Notebook Gamer", "preco": 5999.90, "categoria": "informatica", "estoque": 10},
    2: {"id": 2, "nome": "Mouse Sem Fio", "preco": 89.90, "categoria": "informatica", "estoque": 50},
    3: {"id": 3, "nome": "Cafeteira Expresso", "preco": 349.00, "categoria": "casa", "estoque": 8},
    4: {"id": 4, "nome": "Liquidificador", "preco": 199.90, "categoria": "casa", "estoque": 15},
    5: {"id": 5, "nome": "Camiseta UFF", "preco": 59.90, "categoria": "vestuario", "estoque": 100},
    6: {"id": 6, "nome": "Teclado Mecânico", "preco": 429.90, "categoria": "informatica", "estoque": 20},
}


# ---------------------------------------------------------------------------
# [G5] INTERCEPTOR: código que "intercepta" TODA chamada antes do método rodar.
# Serve para autenticação, log, métricas, etc. sem poluir cada método.
# ---------------------------------------------------------------------------
class AuthInterceptor(grpc.ServerInterceptor):
    def intercept_service(self, continuation, handler_call_details):
        md = dict(handler_call_details.invocation_metadata)      # [G4] metadata recebida
        agente = md.get("user-agent", "?").split(" ")[0]         # ex.: grpc-python/1.68.1
        autorizado = md.get("authorization") == f"Bearer {TOKEN}"
        print(f"[servidor] {handler_call_details.method}  cliente={agente}  "
              f"auth={'OK' if autorizado else 'NEGADA'}", flush=True)
        if autorizado:
            return continuation(handler_call_details)            # segue para o método

        def negar(request, context):
            context.abort(grpc.StatusCode.UNAUTHENTICATED,       # [G3]
                          "Token ausente ou inválido (metadata 'authorization').")
        return grpc.unary_unary_rpc_method_handler(negar)


class Catalogo(loja_pb2_grpc.CatalogoServicer):
    """Implementa os métodos declarados no `service Catalogo` do .proto."""

    # ---- 1) UNÁRIA -------------------------------------------------------
    def ObterProduto(self, request, context):
        inicio = time.perf_counter()
        # [G4] metadata INICIAL: enviada antes da resposta (como headers HTTP)
        context.send_initial_metadata((("x-servidor", socket.gethostname()),))
        if request.id <= 0:
            context.abort(grpc.StatusCode.INVALID_ARGUMENT, "O id deve ser positivo.")      # [G3]
        produto = PRODUTOS.get(request.id)
        if produto is None:
            context.abort(grpc.StatusCode.NOT_FOUND, f"Produto {request.id} não existe.")   # [G3]
        # [G4] metadata FINAL (trailers): enviada depois da resposta
        micros = int((time.perf_counter() - inicio) * 1_000_000)
        context.set_trailing_metadata((("x-tempo-us", str(micros)),))
        return loja_pb2.Produto(**produto)

    # ---- 2) SERVER STREAMING --------------------------------------------
    def ListarProdutos(self, request, context):
        """É um GERADOR: cada `yield` envia uma mensagem imediatamente."""
        for p in PRODUTOS.values():
            if request.categoria and p["categoria"] != request.categoria:
                continue
            if not context.is_active():          # cliente cancelou/estourou o prazo?
                return
            time.sleep(request.atraso_ms / 1000)
            yield loja_pb2.Produto(**p)

    # ---- 3) CLIENT STREAMING --------------------------------------------
    def FecharCarrinho(self, request_iterator, context):
        """Recebe um FLUXO de itens (iterador) e devolve UMA resposta no fim."""
        itens = unidades = 0
        total = 0.0
        avisos = []
        for item in request_iterator:            # bloqueia até o próximo item chegar
            print(f"[servidor]   item recebido: produto={item.produto_id} qtd={item.quantidade}", flush=True)
            if item.quantidade <= 0:
                context.abort(grpc.StatusCode.INVALID_ARGUMENT, "quantidade deve ser > 0")
            p = PRODUTOS.get(item.produto_id)
            if p is None:
                avisos.append(f"produto {item.produto_id} não existe (ignorado)")
                continue
            itens += 1
            unidades += item.quantidade
            total += p["preco"] * item.quantidade
        return loja_pb2.ResumoCompra(itens=itens, unidades=unidades, total=round(total, 2), avisos=avisos)

    # ---- 4) BIDIRECIONAL -------------------------------------------------
    def Conversar(self, request_iterator, context):
        """Os dois lados enviam quando quiserem, de forma independente."""
        yield loja_pb2.Mensagem(autor="Atendente", texto="Olá! Como posso ajudar?",
                                timestamp=int(time.time()))       # servidor fala PRIMEIRO
        for msg in request_iterator:
            print(f"[servidor]   {msg.autor}: {msg.texto}", flush=True)
            yield loja_pb2.Mensagem(autor="Atendente", timestamp=int(time.time()),
                                    texto=f"Recebi '{msg.texto}'. Vou verificar!")

    # ---- [G6] DEADLINE / CANCELAMENTO -----------------------------------
    def GerarRelatorio(self, request, context):
        decorrido = 0
        while decorrido < request.duracao_ms:
            if not context.is_active():          # o cliente desistiu ou o prazo venceu
                print(f"[servidor]   relatório ABORTADO aos {decorrido} ms "
                      "(deadline estourado ou cancelado pelo cliente)", flush=True)
                return loja_pb2.Relatorio()
            time.sleep(0.1)
            decorrido += 100
        return loja_pb2.Relatorio(conteudo=f"Relatório pronto após {decorrido} ms")


def main():
    servidor = grpc.server(futures.ThreadPoolExecutor(max_workers=10), interceptors=[AuthInterceptor()])
    loja_pb2_grpc.add_CatalogoServicer_to_server(Catalogo(), servidor)
    servidor.add_insecure_port("[::]:50051")     # HTTP/2 em texto claro (h2c); TLS seria add_secure_port
    servidor.start()
    print("[servidor] gRPC no ar na porta 50051 (HTTP/2)", flush=True)
    servidor.wait_for_termination()


if __name__ == "__main__":
    main()
