"""
BLOCO D — Prioridade nas filas (priority queue).

Uma fila comum é FIFO: sai na ordem em que chegou. Declarando a fila com o argumento
`x-max-priority`, cada mensagem pode levar uma prioridade (0 = menor ... N = maior) e o
broker entrega as de MAIOR prioridade primeiro. Mensagens da mesma prioridade continuam FIFO.

Atenção (pegadinha de prova): a prioridade só faz diferença quando HÁ FILA, isto é, quando as
mensagens estão acumuladas esperando. Se o consumidor é mais rápido que o produtor, a fila
fica vazia e a ordem de chegada prevalece. Por isso aqui publicamos TUDO antes de consumir.
Dica prática: use poucos níveis (até ~10); cada nível extra custa memória/CPU no broker.
"""
import pika

from common import conectar, drenar, titulo

MENSAGENS = [   # (texto, prioridade) — na ORDEM em que o produtor envia
    ("relatório mensal", 1),
    ("boleto a vencer", 5),
    ("PAGAMENTO URGENTE", 9),
    ("newsletter", 0),
    ("estoque crítico", 8),
    ("backup noturno", 2),
    ("FRAUDE DETECTADA", 10),
    ("notificação push", 3),
]

if __name__ == "__main__":
    titulo("BLOCO D — Prioridade nas filas")
    conexao = conectar()
    ch = conexao.channel()

    for fila in ("q_fifo", "q_prioridade"):
        ch.queue_delete(fila)
    ch.queue_declare("q_fifo")                                              # fila comum (FIFO)
    ch.queue_declare("q_prioridade", arguments={"x-max-priority": 10})      # fila COM prioridade (0..10)
    print("  q_fifo       : fila comum")
    print("  q_prioridade : declarada com x-max-priority=10")

    print("\n  Ordem de ENVIO (mesma lista nas duas filas):")
    for texto, prio in MENSAGENS:
        print(f"    prioridade {prio:>2}  {texto}")
        ch.basic_publish("", "q_fifo", texto.encode(), properties=pika.BasicProperties(priority=prio))
        ch.basic_publish("", "q_prioridade", texto.encode(), properties=pika.BasicProperties(priority=prio))

    print("\n  Ordem de ENTREGA ao consumidor:")
    print("    q_fifo (ignora a prioridade):")
    for i, t in enumerate(drenar(ch, "q_fifo"), 1):
        print(f"      {i}. {t}")
    print("    q_prioridade (maior prioridade primeiro):")
    prios = {t: p for t, p in MENSAGENS}
    for i, t in enumerate(drenar(ch, "q_prioridade"), 1):
        print(f"      {i}. [prio {prios[t]:>2}] {t}")
    conexao.close()
    print("\n\033[1;32mBloco D terminou: a fila com x-max-priority reordenou a entrega.\033[0m")
