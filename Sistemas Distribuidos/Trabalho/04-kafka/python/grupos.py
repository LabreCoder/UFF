"""
BLOCO K2 — Consumer groups (grupos de consumidores), rebalanceamento e PUB/SUB.

Regra de ouro do Kafka:
   • DENTRO de um grupo : cada PARTIÇÃO é lida por UM consumidor só  → o grupo DIVIDE o trabalho
                          (parecido com o "competing consumers" / round-robin do RabbitMQ).
   • ENTRE grupos       : cada grupo recebe TODAS as mensagens, de forma independente
                          → é o publish/subscribe (no RabbitMQ seria preciso um fanout + 1 fila por assinante).
   • Cada grupo guarda o seu OFFSET (quanto já leu) no próprio Kafka.
   • Se um consumidor entra ou sai, o grupo faz REBALANCEAMENTO e redistribui as partições.
   • Máximo de consumidores ATIVOS num grupo = número de partições.

Cenário desta demo (tópico `pedidos`, 3 partições, 12 mensagens já gravadas):
   1) grupo `faturamento` com 2 consumidores (F1, F2)  -> dividem as 3 partições
   2) grupo `estoque`     com 1 consumidor  (E1)       -> recebe as 12 mensagens SOZINHO (broadcast entre grupos)
   3) F2 sai do grupo -> REBALANCEAMENTO: F1 assume todas as partições e lê as novas mensagens
"""
import threading
import time
from collections import defaultdict

from confluent_kafka import Consumer

from common import BOOTSTRAP, TOPICO, recriar_topico, subtitulo, titulo
from produtor import produzir


class Worker:
    """Um consumidor Kafka rodando em sua própria thread."""

    def __init__(self, nome, grupo, eventos):
        self.nome, self.grupo, self.eventos = nome, grupo, eventos
        self.partes = set()                                  # partições que este consumidor possui AGORA
        self.parar = threading.Event()
        self.thread = threading.Thread(target=self.rodar)
        self.thread.start()

    def rodar(self):
        c = Consumer({"bootstrap.servers": BOOTSTRAP, "group.id": self.grupo,
                      "auto.offset.reset": "earliest",       # grupo novo começa do INÍCIO do log
                      "session.timeout.ms": 6000})

        def ao_atribuir(_c, parts):                          # chamado a cada rebalanceamento
            self.partes = {p.partition for p in parts}
            print(f"    [{self.nome}] passou a ler as partições {sorted(self.partes)}", flush=True)

        def ao_revogar(_c, _parts):                          # as partições foram retiradas (alguém entrou/saiu)
            self.partes = set()

        c.subscribe([TOPICO], on_assign=ao_atribuir, on_revoke=ao_revogar)
        while not self.parar.is_set():
            m = c.poll(0.2)
            if m is not None and not m.error():
                self.eventos.append((self.nome, m.partition(), m.offset(), m.key().decode()))
        c.close()                                            # sai do grupo (e confirma os offsets)

    def encerrar(self):
        self.parar.set()
        self.thread.join()


def esperar(eventos, quantidade, limite=30):
    inicio = time.time()
    while len(eventos) < quantidade and time.time() - inicio < limite:
        time.sleep(0.2)


def esperar_grupo(workers, limite=40):
    """Espera todos os consumidores do grupo terem partições (e a união ser as 3 partições)."""
    inicio = time.time()
    while time.time() - inicio < limite:
        if all(w.partes for w in workers) and set().union(*(w.partes for w in workers)) == {0, 1, 2}:
            return
        time.sleep(0.2)


def resumo(eventos, nomes):
    for n in nomes:
        parts = sorted({p for nome, p, _o, _c in eventos if nome == n})
        qtd = sum(1 for nome, *_ in eventos if nome == n)
        print(f"    {n}: {qtd:>2} mensagens | partições {parts}")


if __name__ == "__main__":
    titulo("K2 — Consumer groups e rebalanceamento")
    recriar_topico(TOPICO, 3)

    subtitulo("1) Grupo 'faturamento' com 2 consumidores: DIVIDEM as partições")
    print("    consumidores entrando no grupo...")
    ev1 = []
    f1 = Worker("F1", "faturamento", ev1)
    esperar_grupo([f1])
    f2 = Worker("F2", "faturamento", ev1)
    esperar_grupo([f1, f2])                                  # rebalanceamento: as 3 partições se dividem
    time.sleep(1)
    produzir(12)
    print("    12 mensagens gravadas no tópico (4 por partição)")
    esperar(ev1, 12)
    time.sleep(1)
    resumo(ev1, ["F1", "F2"])
    print("    → cada partição foi lida por UM consumidor só (sem repetição entre F1 e F2).")

    subtitulo("2) Outro grupo, 'estoque', com 1 consumidor: recebe TODAS as 12 (pub/sub entre grupos)")
    ev2 = []
    e1 = Worker("E1", "estoque", ev2)
    esperar(ev2, 12)
    resumo(ev2, ["E1"])
    print("    → o grupo 'estoque' leu tudo de novo: grupos são INDEPENDENTES (cada um tem seu offset).")

    subtitulo("3) F2 sai do grupo → REBALANCEAMENTO: F1 assume tudo e lê as novas mensagens")
    f2.encerrar()
    print("    F2 saiu. Produzindo mais 6 mensagens...")
    ev3_inicio = len(ev1)
    esperar_grupo([f1])                                      # espera o REBALANCEAMENTO: F1 com as 3 partições
    produzir(6, inicio=13)
    esperar(ev1, ev3_inicio + 6, 20)
    novos = ev1[ev3_inicio:]
    print(f"    as 6 novas mensagens foram lidas por: {sorted({n for n, *_ in novos})} "
          f"(partições {sorted({p for _n, p, *_ in novos})})")

    for w in (f1, e1):
        w.encerrar()
    print("\n\033[1;32mK2 terminou: divisão dentro do grupo, broadcast entre grupos e rebalanceamento.\033[0m")
