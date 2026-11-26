"""Funções comuns às demonstrações de Kafka (Python + biblioteca confluent-kafka)."""
import json
import os
import time

from confluent_kafka import Producer
from confluent_kafka.admin import AdminClient, NewTopic

BOOTSTRAP = os.getenv("KAFKA_BOOTSTRAP", "kafka:9092")
TOPICO = "pedidos"


def titulo(t):
    print(f"\n\033[1;36m=== {t} ===\033[0m", flush=True)


def subtitulo(t):
    print(f"\n\033[1;33m--- {t} ---\033[0m", flush=True)


def admin():
    return AdminClient({"bootstrap.servers": BOOTSTRAP})


def recriar_topico(nome, particoes=3):
    """Apaga (se existir) e recria o tópico: deixa a demonstração sempre no mesmo ponto de partida."""
    a = admin()
    if nome in a.list_topics(timeout=10).topics:
        a.delete_topics([nome])[nome].result()
        for _ in range(30):                       # a exclusão é assíncrona no broker
            if nome not in a.list_topics(timeout=10).topics:
                break
            time.sleep(0.5)
    for _ in range(20):
        try:
            a.create_topics([NewTopic(nome, num_partitions=particoes, replication_factor=1)])[nome].result()
            return
        except Exception:
            time.sleep(1)
    raise RuntimeError(f"não consegui criar o tópico {nome}")


def garantir_topico(nome, particoes=3):
    """Cria o tópico SOMENTE se ainda não existir (não apaga nada)."""
    if nome not in admin().list_topics(timeout=10).topics:
        recriar_topico(nome, particoes)


def novo_produtor():
    # murmur2_random = MESMO algoritmo de partição do cliente Java e do kafkajs.
    # Sem isso, a mesma chave cairia em partições diferentes conforme a linguagem do produtor!
    return Producer({"bootstrap.servers": BOOTSTRAP, "partitioner": "murmur2_random", "client.id": "loja-python"})


def evento(i, cliente):
    return json.dumps({"pedido": i, "cliente": cliente, "origem": "python", "ts": int(time.time())})
