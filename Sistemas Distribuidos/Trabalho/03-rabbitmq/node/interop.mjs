// BLOCO E — o lado Node.js da interoperabilidade (biblioteca amqplib).
// Uso: node interop.mjs publicar | consumir
// Fala AMQP com o MESMO broker e as MESMAS exchange/fila/chaves do e_interop.py.
import amqp from "amqplib";

const EXCHANGE = "ex_interop", FILA = "q_interop", PADRAO = "loja.#";
const titulo = (t) => console.log(`\n\x1b[1;36m=== ${t} ===\x1b[0m`);

const conexao = await amqp.connect(process.env.RABBIT_URL ?? "amqp://loja:loja123@localhost:8113");
const canal = await conexao.createChannel();
// Mesmos parâmetros do Python (durable=false), senão o broker recusa a redeclaração.
await canal.assertExchange(EXCHANGE, "topic", { durable: false });
await canal.assertQueue(FILA, { durable: false });
await canal.bindQueue(FILA, EXCHANGE, PADRAO);

const modo = process.argv[2] ?? "consumir";
if (modo === "publicar") {
  titulo("E — Node.js PUBLICA (o consumidor será em Python)");
  let id = 0;
  for (const evento of ["loja.pedido.criado", "loja.pedido.pago", "loja.estoque.baixo"]) {
    const corpo = { origem: "node", id: ++id, evento, ts: Math.floor(Date.now() / 1000) };
    canal.publish(EXCHANGE, evento, Buffer.from(JSON.stringify(corpo)), { contentType: "application/json" });
    console.log(`  publicado [${evento}]`, corpo);
  }
} else {
  titulo("E — Node.js CONSOME o que o Python publicou");
  for (;;) {
    const msg = await canal.get(FILA, { noAck: true });
    if (!msg) break;
    console.log("  recebido:", msg.content.toString());   // já é JSON (texto): mesmo formato do Python
  }
}
await canal.close();
await conexao.close();
