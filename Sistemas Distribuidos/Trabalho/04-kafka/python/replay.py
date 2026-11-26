"""
BLOCO K3 — Retenção e REPLAY: a diferença mais importante entre Kafka e RabbitMQ.

  RabbitMQ: a mensagem SAI da fila quando o consumidor confirma (ACK). Depois disso, acabou.
  Kafka   : a mensagem FICA no log pelo tempo de retenção (padrão 7 dias) ou até um tamanho máximo,
            TENHA SIDO LIDA OU NÃO. Ler não apaga nada: o consumidor só avança o seu OFFSET.

Consequências:
   • Dá para RELER o histórico (replay): novo consumidor, correção de bug, reprocessamento.
   • Vários grupos leem os mesmos dados sem interferir (cada um com seu offset).
   • Dá para voltar a um offset específico (seek).
"""
import time

from confluent_kafka import Consumer, TopicPartition

from common import BOOTSTRAP, TOPICO, garantir_topico, subtitulo, titulo
from produtor import produzir


def novo_consumidor():
    return Consumer({"bootstrap.servers": BOOTSTRAP, "group.id": f"replay-{time.time_ns()}",
                     "auto.offset.reset": "earliest", "enable.auto.commit": False})


def ler_ate_ficar_parado(c, silencios=2):
    msgs, vazios = [], 0
    while vazios < silencios:
        m = c.poll(1.0)
        if m is None:
            vazios += 1
        elif not m.error():
            vazios = 0
            msgs.append(m)
    return msgs


if __name__ == "__main__":
    titulo("K3 — Retenção e replay (as mensagens continuam no log depois de lidas)")
    garantir_topico(TOPICO, 3)
    sonda = novo_consumidor()
    total ={p: sonda.get_watermark_offsets(TopicPartition(TOPICO, p), timeout=10) for p in range(3)}
    if sum(alto - baixo for baixo, alto in total.values()) == 0:
        print("  (tópico vazio: produzindo 12 mensagens para a demonstração)")
        produzir(12)
        total = {p: sonda.get_watermark_offsets(TopicPartition(TOPICO, p), timeout=10) for p in range(3)}
    sonda.close()

    subtitulo("1) O que o log guarda (offset mais antigo → offset do próximo)")
    for p, (baixo, alto) in total.items():
        print(f"    partição {p}: offsets {baixo}..{alto - 1}  ({alto - baixo} mensagens retidas)")
    n = sum(alto - baixo for baixo, alto in total.values())
    print(f"    TOTAL: {n} mensagens guardadas — ler NÃO apaga (quem leu só avançou o seu offset).")

    subtitulo("2) REPLAY: um grupo NOVO ('auditoria') lê TODO o histórico desde o início")
    c = novo_consumidor()
    c.subscribe([TOPICO])
    todas = ler_ate_ficar_parado(c)
    c.close()
    print(f"    o grupo novo leu {len(todas)} mensagens. As 3 primeiras de cada partição:")
    vistas = {}
    for m in todas:
        vistas.setdefault(m.partition(), []).append(m)
    for p in sorted(vistas):
        for m in vistas[p][:3]:
            print(f"      partição {p} offset {m.offset()}  chave={m.key().decode():<6} {m.value().decode()[:48]}")

    subtitulo("3) SEEK: voltar a um offset específico (partição 0, a partir do offset 2)")
    c = novo_consumidor()
    c.assign([TopicPartition(TOPICO, 0, 2)])             # sem grupo/assinatura: posição manual
    lidas = ler_ate_ficar_parado(c)
    c.close()
    for m in lidas:
        print(f"      partição {m.partition()} offset {m.offset()}  chave={m.key().decode()}")
    print("    → o consumidor controla a posição: pode reler, pular ou reprocessar quando quiser.")
    print("\n  \033[1;33mNo RabbitMQ essas mensagens já teriam sumido da fila após o ACK.\033[0m")
