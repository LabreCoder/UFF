"""
BLOCO B — Balanceamento de carga entre consumidores ("competing consumers").

Quando VÁRIOS consumidores ouvem a MESMA fila, o RabbitMQ entrega cada mensagem a UM deles:
os consumidores "competem" pelo trabalho e a carga se divide. É o padrão "work queue".

  Cenário 1 — ROUND-ROBIN: o broker entrega em rodízio (A, B, C, A, B, C...), ignorando
              quem está mais lento. (Aula 2: balanceamento ESTÁTICO.)
  Cenário 2 — O PROBLEMA do round-robin com um consumidor lento, e a solução PREFETCH=1
              (só entrega a próxima quando a anterior foi confirmada = "fair dispatch";
              fica parecido com o balanceamento DINÂMICO por "menor carga").
  Cenário 3 — ROUND-ROBIN PONDERADO: o RabbitMQ NÃO tem peso nativo. Emulamos dando mais
              CONSUMIDORES ao worker mais forte: peso 3 = 3 consumidores; peso 1 = 1 consumidor.
              Como o rodízio é por consumidor, o worker A recebe 3 de cada 4 mensagens.
"""
import threading
import time

from common import conectar, subtitulo, titulo


def consumidor(nome, fila, prefetch, tempo, eventos, pronto, parar):
    """Uma thread = uma conexão AMQP = um consumidor (pika não é thread-safe)."""
    conexao = conectar()
    canal = conexao.channel()
    canal.basic_qos(prefetch_count=prefetch)          # 0 = sem limite (round-robin "puro")

    def ao_receber(ch, metodo, props, corpo):
        eventos.append((corpo.decode(), nome))
        time.sleep(tempo)                              # simula o tempo de processamento
        ch.basic_ack(metodo.delivery_tag)              # confirma: "terminei, pode me mandar outra"

    canal.basic_consume(fila, ao_receber)
    pronto.release()
    while not parar.is_set():
        conexao.process_data_events(time_limit=0.1)
    conexao.close()


def cenario(descricao, fila, grupos, n_tarefas, prefetch):
    """grupos = {worker: (qtd_consumidores, segundos_por_tarefa)}"""
    subtitulo(descricao)
    pub = conectar()
    ch = pub.channel()
    ch.queue_delete(fila)
    ch.queue_declare(fila)

    eventos, parar, pronto = [], threading.Event(), threading.Semaphore(0)
    threads, total = [], 0
    for worker, (qtd, tempo) in grupos.items():
        print(f"  worker {worker}: {qtd} consumidor(es), {tempo * 1000:.0f} ms por tarefa")
        for i in range(1, qtd + 1):
            nome = f"{worker}{i}" if qtd > 1 else worker
            t = threading.Thread(target=consumidor, args=(nome, fila, prefetch, tempo, eventos, pronto, parar))
            t.start()
            threads.append(t)
            total += 1
    for _ in range(total):
        pronto.acquire()                               # espera todos os consumidores estarem prontos

    inicio = time.time()
    print(f"  → publicando {n_tarefas} tarefas (T01..T{n_tarefas:02d}) | prefetch={prefetch or 'ilimitado'}")
    for i in range(1, n_tarefas + 1):
        ch.basic_publish("", fila, f"T{i:02d}".encode())
    while len(eventos) < n_tarefas and time.time() - inicio < 40:
        time.sleep(0.05)
    duracao = time.time() - inicio
    parar.set()
    for t in threads:
        t.join()
    pub.close()

    sequencia = sorted(eventos)
    print("  quem pegou cada tarefa: " + " ".join(f"{t}→{w}" for t, w in sequencia))
    print("  RESULTADO por worker:")
    for worker in grupos:
        qtd = sum(1 for _, w in eventos if w.startswith(worker))
        print(f"    {worker}: {'█' * qtd:<14} {qtd} tarefas")
    print(f"  tempo total: {duracao:.1f} s")


def rr():
    cenario("1) ROUND-ROBIN: 3 workers iguais (rodízio A,B,C,A,B,C...)",
            "tarefas_rr", {"W1": (1, 0.05), "W2": (1, 0.05), "W3": (1, 0.05)}, 12, prefetch=0)


def lento():
    cenario("2a) Round-robin PURO com um worker LENTO (W3 = 10x mais lento): divide igual mesmo assim",
            "tarefas_lento", {"W1": (1, 0.05), "W2": (1, 0.05), "W3": (1, 0.5)}, 12, prefetch=0)
    cenario("2b) Mesmo cenário com PREFETCH=1 (fair dispatch): o lento recebe MENOS",
            "tarefas_justo", {"W1": (1, 0.05), "W2": (1, 0.05), "W3": (1, 0.5)}, 12, prefetch=1)


def ponderado():
    cenario("3) ROUND-ROBIN PONDERADO: worker A (peso 3) e worker B (peso 1)",
            "tarefas_pond", {"A": (3, 0.05), "B": (1, 0.05)}, 12, prefetch=0)


DEMOS = {"rr": rr, "lento": lento, "ponderado": ponderado}

if __name__ == "__main__":      # uso: python b_balanceamento.py [rr|lento|ponderado]  (sem argumento = todos)
    import sys
    titulo("BLOCO B — Balanceamento de carga")
    for nome in (sys.argv[1:] or DEMOS):
        DEMOS[nome]()
    if len(sys.argv) == 1:     # só quando o bloco inteiro rodou
        print("\n\033[1;32mBloco B terminou: round-robin, fair dispatch e round-robin ponderado.\033[0m")
