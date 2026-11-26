"""
BLOCO C2 — Confirmação de recebimento (acknowledgement), COM e SEM.

Existem DUAS confirmações diferentes:

  (1) Do CONSUMIDOR para o broker  ("já processei, pode apagar"): ACK
        auto_ack=True  -> o broker apaga a mensagem NO MOMENTO da entrega (SEM confirmação real)
        ACK manual     -> o broker só apaga quando o consumidor chama basic_ack (COM confirmação)
        basic_nack(requeue=True/False) / basic_reject -> "não consegui": devolve ou descarta

  (2) Do BROKER para o PRODUTOR ("recebi e guardei"): PUBLISHER CONFIRMS
        sem confirms -> o produtor publica e NÃO sabe se o broker recebeu
        com confirms -> o broker responde ack (ou nack); mandatory=True devolve mensagem sem rota

Isso é a "confiabilidade ponta a ponta" do AMQP da Aula 6 (estados não resolvido -> resolvido).
"""
import time

import pika

from common import conectar, contar, subtitulo, titulo

FILA = "q_ack"


def preparar(ch):
    ch.queue_delete(FILA)
    ch.queue_declare(FILA)


def sem_confirmacao():
    subtitulo("1) SEM confirmação (auto_ack=True): o consumidor 'cai' → mensagem PERDIDA")
    pub = conectar(); ch = pub.channel(); preparar(ch)
    ch.basic_publish("", FILA, b"pedido-123")
    print("  produtor publicou 'pedido-123'")

    a = conectar(); cha = a.channel()
    _m, _p, corpo = cha.basic_get(FILA, auto_ack=True)             # auto_ack: broker JÁ apagou
    print(f"  consumidor A recebeu {corpo.decode()!r} (auto_ack=True: o broker já apagou a mensagem)")
    print("  💥 consumidor A cai ANTES de processar (fecha a conexão)")
    a.close()

    print(f"  mensagens restantes na fila: {contar(ch, FILA)}  ← a mensagem foi PERDIDA")
    pub.close()


def com_confirmacao():
    subtitulo("2) COM confirmação (ACK manual): o consumidor cai → mensagem REENTREGUE")
    pub = conectar(); ch = pub.channel(); preparar(ch)
    ch.basic_publish("", FILA, b"pedido-456")
    print("  produtor publicou 'pedido-456'")

    a = conectar(); cha = a.channel()
    m, _p, corpo = cha.basic_get(FILA, auto_ack=False)             # recebe, mas NÃO confirma
    print(f"  consumidor A recebeu {corpo.decode()!r} (sem ack ainda: o broker guarda como 'não confirmada')")
    print(f"  mensagens PRONTAS na fila agora: {contar(ch, FILA)} (a de A está 'em andamento')")
    print("  💥 consumidor A cai SEM dar ack")
    a.close()
    time.sleep(0.5)                                       # o broker devolve a mensagem à fila (assíncrono)

    b = conectar(); chb = b.channel()
    m, _p, corpo = chb.basic_get(FILA, auto_ack=False)
    print(f"  consumidor B recebeu {corpo.decode()!r}  redelivered={m.redelivered}  ← o broker REENTREGOU")
    chb.basic_ack(m.delivery_tag)
    print(f"  B processou e deu ACK → mensagens restantes: {contar(chb, FILA)}")
    b.close(); pub.close()


def nack_e_reject():
    subtitulo("3) Consumidor RECUSA: nack(requeue=True) devolve; nack(requeue=False) descarta")
    pub = conectar(); ch = pub.channel(); preparar(ch)
    ch.basic_publish("", FILA, b"pedido-789")
    c = conectar(); chc = c.channel()

    m, _p, corpo = chc.basic_get(FILA)
    print(f"  recebeu {corpo.decode()!r} → falhou temporariamente → basic_nack(requeue=True)")
    chc.basic_nack(m.delivery_tag, requeue=True)
    m, _p, corpo = chc.basic_get(FILA)
    print(f"  recebeu DE NOVO {corpo.decode()!r}  redelivered={m.redelivered}")

    print("  mensagem 'envenenada' (sempre falha) → basic_nack(requeue=False) → descartada")
    chc.basic_nack(m.delivery_tag, requeue=False)
    print(f"  mensagens restantes na fila: {contar(chc, FILA)}  (num sistema real iria para uma Dead Letter Queue)")
    c.close(); pub.close()


def publisher_confirms():
    subtitulo("4) PUBLISHER CONFIRMS: o broker confirma ao PRODUTOR que recebeu")
    conexao = conectar(); ch = conexao.channel(); preparar(ch)
    ch.exchange_delete("ex_confirma"); ch.exchange_declare("ex_confirma", "direct")
    ch.confirm_delivery()                                  # liga o modo "confirmação do broker"

    ch.basic_publish("", FILA, b"com confirmacao", mandatory=True)
    print("  publicou na fila existente  → broker CONFIRMOU (basic_publish retornou sem erro)")

    try:
        ch.basic_publish("ex_confirma", "chave-sem-binding", b"orfa", mandatory=True)
    except pika.exceptions.UnroutableError:
        print("  publicou com chave SEM binding e mandatory=True → broker DEVOLVEU a mensagem (UnroutableError)")
        print("  → sem confirms/mandatory o produtor nem ficaria sabendo que a mensagem foi descartada")
    conexao.close()


if __name__ == "__main__":
    titulo("BLOCO C2 — Confirmação de recebimento: com e sem")
    sem_confirmacao()
    com_confirmacao()
    nack_e_reject()
    publisher_confirms()
    print("\n\033[1;32mBloco C2 terminou: ack automático x manual, nack e publisher confirms.\033[0m")
