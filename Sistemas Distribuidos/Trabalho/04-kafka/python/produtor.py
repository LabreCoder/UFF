"""
BLOCO K1 — Tópico, partições, chave e ORDEM.

Kafka não é uma "fila": é um LOG distribuído (um arquivo onde só se acrescenta no fim).
  - TÓPICO    : um "assunto" (aqui: `pedidos`). É dividido em PARTIÇÕES.
  - PARTIÇÃO  : um log ordenado e imutável. Cada mensagem recebe um OFFSET (0, 1, 2...) dentro dela.
  - CHAVE     : o produtor escolhe a partição pelo hash da chave -> MESMA CHAVE = MESMA PARTIÇÃO.

  tópico `pedidos`
   partição 0: [off0][off1][off2][off3] ──►  (só cresce no fim)
   partição 1: [off0][off1][off2]       ──►
   partição 2: [off0][off1][off2][off3] ──►

GARANTIA DE ORDEM: só dentro de UMA partição. Como todos os pedidos de um mesmo cliente têm a
mesma chave, eles ficam na mesma partição e são lidos NA ORDEM em que foram produzidos.
Entre partições diferentes NÃO há ordem global.
"""
import sys
from collections import defaultdict

from common import TOPICO, evento, novo_produtor, recriar_topico, subtitulo, titulo

# Nomes escolhidos (calculando o hash murmur2 do Kafka) para se espalharem 2 por partição.
CLIENTES = ["ana", "bruno", "diego", "iris", "carla", "gabi"]


def produzir(qtd, inicio=1):
    """Produz `qtd` eventos, cada um com a chave = cliente. Devolve onde cada mensagem caiu."""
    destino = []

    def ao_entregar(erro, msg):          # chamado quando o broker CONFIRMA a gravação (ack do produtor)
        if erro:
            print("  erro:", erro)
        else:
            destino.append((msg.partition(), msg.offset(), msg.key().decode(), msg.value().decode()))

    p = novo_produtor()
    for i in range(inicio, inicio + qtd):
        cliente = CLIENTES[(i - 1) % len(CLIENTES)]
        p.produce(TOPICO, key=cliente, value=evento(i, cliente), callback=ao_entregar)
        p.poll(0)
    p.flush()                            # espera todas as confirmações
    return destino


if __name__ == "__main__":
    qtd = int(sys.argv[1]) if len(sys.argv) > 1 else 12
    titulo("K1 — Produtor Python: eventos com CHAVE = cliente")
    recriar_topico(TOPICO, 3)
    print(f"  tópico '{TOPICO}' recriado com 3 partições")
    entregues = produzir(qtd)

    subtitulo("Onde cada mensagem foi gravada (partição, offset)")
    por_particao = defaultdict(list)
    for part, off, chave, _v in sorted(entregues):
        por_particao[part].append((off, chave))
    for part in sorted(por_particao):
        itens = "  ".join(f"[off{o}:{c}]" for o, c in por_particao[part])
        print(f"  partição {part}: {itens}")
    chaves_por_part = {}
    for part, itens in por_particao.items():
        for _o, c in itens:
            chaves_por_part.setdefault(c, set()).add(part)
    print("\n  cada cliente (chave) caiu em UMA partição só:",
          {c: sorted(p)[0] for c, p in sorted(chaves_por_part.items())})
    assert all(len(p) == 1 for p in chaves_por_part.values()), "mesma chave em partições diferentes!"
    print("  → mesma chave = mesma partição ⇒ a ORDEM dos pedidos de cada cliente é preservada.")
