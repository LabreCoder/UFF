"""
BLOCO K4 — Interoperabilidade: Python e Node.js trocando eventos pelo Kafka.

Uso: python interop.py reset | produzir | consumir
Os dois lados só combinam o NOME DO TÓPICO e o FORMATO do corpo (JSON). Como configuramos o
mesmo algoritmo de partição (murmur2), a MESMA CHAVE cai na MESMA PARTIÇÃO nas duas linguagens.
"""
import json
import sys
import time

from confluent_kafka import Consumer

from common import BOOTSTRAP, garantir_topico, novo_produtor, recriar_topico, titulo

TOPICO_INTEROP = "interop"
EVENTOS = [("ana", "pedido.criado"), ("iris", "pedido.pago"), ("bruno", "pedido.enviado")]

if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else "consumir"
    if modo == "reset":
        recriar_topico(TOPICO_INTEROP, 3)
        print("  tópico 'interop' recriado")
    elif modo == "produzir":
        titulo("K4 — Python PRODUZ (o consumidor será em Node.js)")
        garantir_topico(TOPICO_INTEROP, 3)
        p = novo_produtor()

        def ao_entregar(erro, msg):
            print(f"  gravado: chave={msg.key().decode():<6} → partição {msg.partition()} offset {msg.offset()}")

        for i, (cliente, tipo) in enumerate(EVENTOS, 1):
            corpo = json.dumps({"origem": "python", "id": i, "cliente": cliente, "evento": tipo})
            p.produce(TOPICO_INTEROP, key=cliente, value=corpo, callback=ao_entregar)
        p.flush()
    else:
        titulo("K4 — Python CONSOME o que o Node.js produziu (e tudo que já estava no log)")
        garantir_topico(TOPICO_INTEROP, 3)
        c = Consumer({"bootstrap.servers": BOOTSTRAP, "group.id": f"py-{time.time_ns()}",
                      "auto.offset.reset": "earliest"})
        c.subscribe([TOPICO_INTEROP])
        vazios = 0
        while vazios < 3:
            m = c.poll(1.0)
            if m is None:
                vazios += 1
            elif not m.error():
                vazios = 0
                print(f"  lido: partição {m.partition()} offset {m.offset()}  chave={m.key().decode():<6} {m.value().decode()}")
        c.close()
