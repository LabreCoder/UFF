"""
BLOCO A — Roteamento de mensagens: TODOS os tipos de exchange do RabbitMQ.

Lembrete (Aula 6): o produtor NUNCA fala direto com a fila. Ele entrega a mensagem a uma
EXCHANGE, que decide para quais filas ela vai, de acordo com os BINDINGS (ligações).
A exchange não guarda mensagens: quem guarda é a fila.

     produtor ──msg(routing key)──► [EXCHANGE] ──binding──► [FILA] ──► consumidor

  tipo     | como decide
  ---------|--------------------------------------------------------------------
  default  | ("" = sem nome) entrega na fila cujo NOME é igual à routing key
  direct   | routing key IGUAL à chave do binding
  fanout   | ignora a chave: copia para TODAS as filas ligadas (broadcast)
  topic    | chave com padrão: `*` = exatamente 1 palavra, `#` = 0 ou mais palavras
  headers  | ignora a chave: compara CABEÇALHOS da mensagem (x-match = all | any)
"""
import pika

from common import conectar, drenar, subtitulo, titulo


def montar(ch, exchange, tipo, ligacoes):
    """(Re)cria a exchange, as filas e os bindings. `ligacoes` = {fila: [chave ou dict de headers]}."""
    ch.exchange_delete(exchange)
    ch.exchange_declare(exchange=exchange, exchange_type=tipo)
    for fila, chaves in ligacoes.items():
        ch.queue_delete(fila)
        ch.queue_declare(fila)
        for c in chaves:
            if isinstance(c, dict):                      # exchange headers
                ch.queue_bind(fila, exchange, arguments=c)
                print(f"  binding: fila {fila:<12} <- headers {c}")
            else:                                        # direct / topic / fanout
                ch.queue_bind(fila, exchange, routing_key=c)
                print(f"  binding: fila {fila:<12} <- chave '{c}'")


def resultado(ch, filas):
    print("  RESULTADO (o que cada fila recebeu):")
    for f in filas:
        print(f"    {f:<12}: {drenar(ch, f)}")


def default(ch):
    subtitulo("1) EXCHANGE PADRÃO (default, nome vazio): chave = NOME DA FILA")
    ch.queue_delete("fila_padrao")
    ch.queue_declare("fila_padrao")
    print("  toda fila é ligada automaticamente à exchange '' usando o próprio nome como chave")
    print("  → publicando com exchange='' e routing_key='fila_padrao'")
    ch.basic_publish(exchange="", routing_key="fila_padrao", body=b"ola, direto na fila")
    resultado(ch, ["fila_padrao"])


def direct(ch):
    subtitulo("2) DIRECT: a chave da mensagem tem que ser IGUAL à do binding")
    filas = {"q_erros": ["error"], "q_avisos": ["warning"], "q_tudo": ["error", "warning", "info"]}
    montar(ch, "ex_direct", "direct", filas)
    for chave, texto in [("error", "disco cheio"), ("warning", "memória alta"), ("info", "usuário logou")]:
        print(f"  → publicando chave='{chave}': {texto}")
        ch.basic_publish("ex_direct", chave, texto.encode())
    resultado(ch, filas)
    print("  Note: 'q_tudo' tem 3 bindings, então recebeu as 3 mensagens.")


def fanout(ch):
    subtitulo("3) FANOUT: broadcast, a chave é IGNORADA")
    filas = {"q_email": [""], "q_sms": [""], "q_push": [""]}
    montar(ch, "ex_fanout", "fanout", filas)
    print("  → publicando UMA mensagem com chave 'qualquer-coisa' (será ignorada)")
    ch.basic_publish("ex_fanout", "qualquer-coisa", "Promoção relâmpago!".encode())
    resultado(ch, filas)


def topic(ch):
    subtitulo("4) TOPIC: padrões  *  (1 palavra)   e   #  (0 ou mais palavras)")
    filas = {
        "q_sp":      ["*.*.sp"],          # qualquer evento de SP (exatamente 3 palavras, termina em sp)
        "q_pedidos": ["pedido.#"],        # tudo que começa com 'pedido'
        "q_estoque": ["estoque.#"],
        "q_todos":   ["#"],               # tudo (equivale a fanout)
    }
    montar(ch, "ex_topic", "topic", filas)
    for chave in ["pedido.criado.sp", "pedido.pago.rj", "estoque.baixo.sp", "pedido.cancelado"]:
        print(f"  → publicando chave='{chave}'")
        ch.basic_publish("ex_topic", chave, chave.encode())
    resultado(ch, filas)
    print("  Note: 'pedido.cancelado' NÃO casa com '*.*.sp' (só 2 palavras), mas casa com 'pedido.#'.")


def headers(ch):
    subtitulo("5) HEADERS: decide pelos CABEÇALHOS (x-match: all = todos, any = qualquer um)")
    filas = {
        "q_pdf_fin": [{"x-match": "all", "formato": "pdf", "tipo": "financeiro"}],
        "q_pdf_ou_fin": [{"x-match": "any", "formato": "pdf", "tipo": "financeiro"}],
    }
    montar(ch, "ex_headers", "headers", filas)
    for h in [{"formato": "pdf", "tipo": "financeiro"}, {"formato": "pdf", "tipo": "vendas"},
              {"formato": "xls", "tipo": "financeiro"}, {"formato": "xls", "tipo": "vendas"}]:
        print(f"  → publicando com headers {h}")
        ch.basic_publish("ex_headers", "", str(h).encode(), properties=pika.BasicProperties(headers=h))
    resultado(ch, filas)
    print("  Note: 'all' exige pdf E financeiro (1 mensagem); 'any' aceita pdf OU financeiro (3 mensagens).")


DEMOS = {"default": default, "direct": direct, "fanout": fanout, "topic": topic, "headers": headers}

if __name__ == "__main__":      # uso: python a_roteamento.py [default|direct|fanout|topic|headers]  (sem argumento = todos)
    import sys
    conexao = conectar()
    canal = conexao.channel()
    titulo("BLOCO A — Tipos de exchange / roteamento")
    for nome in (sys.argv[1:] or DEMOS):
        DEMOS[nome](canal)
    conexao.close()
    if len(sys.argv) == 1:     # só quando o bloco inteiro rodou
        print("\n\033[1;32mBloco A terminou: 5 formas de roteamento demonstradas.\033[0m")
