"""Sonda: chama o servidor gRPC 1x por segundo e mostra o que o CLIENTE enxerga quando a rede/servidor falha.
Uso (dentro do container cliente):  ALVO=192.168.56.10:8102 python -u sonda.py [segundos]"""
import os, sys, time
import grpc
import loja_pb2, loja_pb2_grpc

ALVO = os.environ["ALVO"]
SEGUNDOS = int(sys.argv[1]) if len(sys.argv) > 1 else 20
AUTH = (("authorization", "Bearer segredo-da-loja"),)
# Opções do canal (o padrão do gRPC é conservador demais para uma demo curta):
#  - reconnect_backoff: o gRPC reconecta com espera crescente (1 s, 1,6 s, 2,6 s... até 120 s). Limitamos a 1,5 s.
#  - keepalive: pings HTTP/2 periódicos. Sem eles, se a rede some SEM aviso, a conexão TCP "morta" só é
#    percebida muito depois. Com keepalive o cliente detecta em ~4 s e abre outra conexão.
OPCOES = [
    ("grpc.initial_reconnect_backoff_ms", 500),
    ("grpc.max_reconnect_backoff_ms", 1500),
    ("grpc.keepalive_time_ms", 3000),
    ("grpc.keepalive_timeout_ms", 1000),
    ("grpc.keepalive_permit_without_calls", 1),
    ("grpc.http2.max_pings_without_data", 0),
]
canal = grpc.insecure_channel(ALVO, options=OPCOES)
# subscribe(..., try_to_connect=True) mantém o canal TENTANDO reconectar em segundo plano e nos avisa das
# transições de estado: READY -> IDLE/CONNECTING -> TRANSIENT_FAILURE -> ... -> READY.
# (Sem isso, o canal Python não reconecta sozinho com a rapidez que esperamos depois de uma queda.)
canal.subscribe(lambda e: print(f"{time.strftime('%H:%M:%S')}  \033[1;33m~ canal: {e.name}\033[0m", flush=True), try_to_connect=True)
stub = loja_pb2_grpc.CatalogoStub(canal)

fim = time.time() + SEGUNDOS
while time.time() < fim:
    t0 = time.time()
    try:
        r = stub.ObterProduto(loja_pb2.ProdutoRequest(id=1), metadata=AUTH, timeout=2)   # prazo de 2 s
        print(f"{time.strftime('%H:%M:%S')}  OK                {r.nome}  ({(time.time()-t0)*1000:.0f} ms)", flush=True)
    except grpc.RpcError as e:
        print(f"{time.strftime('%H:%M:%S')}  \033[1;31m{e.code().name:<17}\033[0m (levou {time.time()-t0:.1f} s) {(e.details() or '')[:70]}", flush=True)
    time.sleep(max(0, 1 - (time.time() - t0)))
