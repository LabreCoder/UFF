"""
BLOCO C1 — Comunicação PERSISTENTE × TRANSIENTE (sobrevive à queda do broker?)

Aula 6: na comunicação PERSISTENTE o middleware guarda a mensagem o tempo que for preciso
até entregá-la; na TRANSIENTE ela só existe enquanto as aplicações/middleware estão no ar.

No RabbitMQ, "persistente" exige DUAS coisas ao mesmo tempo:
   1) a FILA ser durável   -> queue_declare(durable=True)        (a fila sobrevive ao reinício)
   2) a MENSAGEM ser persistente -> delivery_mode=2              (o conteúdo vai para o disco)

  fila                       | fila durável? | mensagem persistente? | depois do reinício do broker
  ---------------------------|---------------|-----------------------|------------------------------
  q_transiente               | não           | não                   | fila some (e as mensagens)
  q_duravel_msg_transiente   | SIM           | não                   | fila existe, mas VAZIA
  q_duravel_persistente      | SIM           | SIM                   | fila existe COM as mensagens

Uso:  python c_persistencia.py publicar     (cria filas e publica 5 mensagens em cada)
      python c_persistencia.py contar       (mostra quantas mensagens há em cada fila)
O demo.sh reinicia o broker (docker compose restart) ENTRE os dois comandos.
"""
import sys

import pika

from common import conectar, contar, titulo

FILAS = [
    # (nome, fila durável?, mensagem persistente?)
    ("q_transiente", False, False),
    ("q_duravel_msg_transiente", True, False),
    ("q_duravel_persistente", True, True),
]


def publicar():
    titulo("C1 — Publicando 5 mensagens em 3 tipos de fila")
    conexao = conectar()
    ch = conexao.channel()
    for nome, duravel, persistente in FILAS:
        ch.queue_delete(nome)
        ch.queue_declare(nome, durable=duravel)
        props = pika.BasicProperties(delivery_mode=2 if persistente else 1)   # 2 = persistent, 1 = transient
        for i in range(1, 6):
            ch.basic_publish("", nome, f"msg {i}".encode(), properties=props)
        print(f"  {nome:<26} durable={str(duravel):<5} delivery_mode={2 if persistente else 1}  → 5 mensagens publicadas")
    conexao.close()
    mostrar("ANTES do reinício")


def mostrar(rotulo):
    conexao = conectar()
    print(f"\n  Mensagens em cada fila — {rotulo}:")
    for nome, _d, _p in FILAS:
        ch = conexao.channel()                     # 1 canal novo por consulta (404 fecha o canal)
        n = contar(ch, nome)
        estado = "a FILA NÃO EXISTE MAIS" if n is None else f"{n} mensagem(ns)"
        print(f"    {nome:<26} {estado}")
    conexao.close()


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "publicar":
        publicar()
    else:
        titulo("C1 — Conferindo as filas DEPOIS do reinício do broker")
        mostrar("DEPOIS do reinício")
