"""Funções comuns às demonstrações de RabbitMQ (Python + biblioteca pika)."""
import os
import time

import pika

HOST = os.getenv("RABBIT_HOST", "rabbitmq")
CREDENCIAIS = pika.PlainCredentials("loja", "loja123")


def conectar():
    """Abre uma conexão AMQP (TCP). Tenta por até 30 s caso o broker ainda esteja subindo."""
    params = pika.ConnectionParameters(host=HOST, credentials=CREDENCIAIS, heartbeat=30)
    for _ in range(30):
        try:
            return pika.BlockingConnection(params)
        except pika.exceptions.AMQPConnectionError:
            time.sleep(1)
    raise RuntimeError("Não consegui conectar ao RabbitMQ")


def titulo(t):
    print(f"\n\033[1;36m=== {t} ===\033[0m", flush=True)


def subtitulo(t):
    print(f"\n\033[1;33m--- {t} ---\033[0m", flush=True)


def drenar(ch, fila):
    """Lê TODAS as mensagens que estão na fila (basic_get) e devolve a lista de textos."""
    msgs = []
    while True:
        metodo, _props, corpo = ch.basic_get(fila, auto_ack=True)
        if metodo is None:
            return msgs
        msgs.append(corpo.decode())


def contar(ch, fila):
    """Quantas mensagens PRONTAS há na fila; None se a fila não existe."""
    try:
        return ch.queue_declare(fila, passive=True).method.message_count
    except pika.exceptions.ChannelClosedByBroker:   # 404: fila inexistente (o broker fecha o canal)
        return None
