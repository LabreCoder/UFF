"""
BLOCO E — Interoperabilidade: Python e Node.js conversando pelo RabbitMQ.

AMQP é um protocolo ABERTO (Aula 6: surgiu justamente para evitar ficar preso a um fabricante).
Por isso um produtor em uma linguagem e um consumidor em outra se entendem sem saber nada um
do outro: só combinam a exchange, a fila, a routing key e o formato do corpo (aqui, JSON).

Uso:  python e_interop.py publicar | consumir
"""
import json
import sys
import time

import pika

from common import conectar, drenar, titulo

EXCHANGE, FILA, PADRAO = "ex_interop", "q_interop", "loja.#"


def preparar(ch):
    # Mesmos parâmetros no Node e no Python (se divergirem, o broker recusa a redeclaração).
    ch.exchange_declare(EXCHANGE, "topic", durable=False)
    ch.queue_declare(FILA, durable=False)
    ch.queue_bind(FILA, EXCHANGE, PADRAO)


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else "consumir"
    conexao = conectar()
    ch = conexao.channel()
    preparar(ch)
    if modo == "publicar":
        titulo("E — Python PUBLICA (o consumidor será em Node.js)")
        for i, evento in enumerate(["loja.pedido.criado", "loja.pedido.pago", "loja.estoque.baixo"], 1):
            corpo = {"origem": "python", "id": i, "evento": evento, "ts": int(time.time())}
            ch.basic_publish(EXCHANGE, evento, json.dumps(corpo).encode(),
                             properties=pika.BasicProperties(content_type="application/json"))
            print(f"  publicado [{evento}] {corpo}")
    else:
        titulo("E — Python CONSOME o que o Node.js publicou")
        for m in drenar(ch, FILA):
            print(f"  recebido: {json.loads(m)}")
    conexao.close()
