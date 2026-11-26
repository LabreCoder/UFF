// BLOCO K4 — o lado Node.js da interoperabilidade (biblioteca kafkajs).
// Uso: node interop.mjs produzir | consumir
// Mesmo broker, mesmo tópico, mesmo JSON do interop.py. O kafkajs usa por padrão o particionador
// murmur2 (compatível com Java e com o murmur2_random do Python): a mesma chave cai na mesma partição.
import { Kafka, logLevel } from "kafkajs";

const TOPICO = "interop";
const kafka = new Kafka({
  clientId: "loja-node",
  brokers: [process.env.KAFKA_BOOTSTRAP ?? "localhost:8104"],
  logLevel: logLevel.NOTHING,
});
const titulo = (t) => console.log(`\n\x1b[1;36m=== ${t} ===\x1b[0m`);
const modo = process.argv[2] ?? "consumir";

// O auto-create de tópicos está desligado no broker: cria (3 partições) só se ainda não existir.
const admin = kafka.admin();
await admin.connect();
await admin.createTopics({ topics: [{ topic: TOPICO, numPartitions: 3, replicationFactor: 1 }] });
await admin.disconnect();

if (modo === "produzir") {
  titulo("K4 — Node.js PRODUZ (o consumidor será em Python)");
  const produtor = kafka.producer();
  await produtor.connect();
  const eventos = [["ana", "pedido.criado"], ["iris", "pedido.pago"], ["bruno", "pedido.enviado"]];
  let id = 0;
  for (const [cliente, evento] of eventos) {
    const corpo = JSON.stringify({ origem: "node", id: ++id, cliente, evento });
    const [meta] = await produtor.send({ topic: TOPICO, messages: [{ key: cliente, value: corpo }] });
    console.log(`  gravado: chave=${cliente.padEnd(6)} → partição ${meta.partition} offset ${meta.baseOffset}`);
  }
  await produtor.disconnect();
} else {
  titulo("K4 — Node.js CONSOME o que o Python produziu (e tudo que já estava no log)");
  const consumidor = kafka.consumer({ groupId: `node-${Date.now()}` });
  await consumidor.connect();
  await consumidor.subscribe({ topic: TOPICO, fromBeginning: true });   // grupo novo: lê desde o início
  await consumidor.run({
    eachMessage: async ({ partition, message }) =>
      console.log(`  lido: partição ${partition} offset ${message.offset}  chave=${message.key.toString().padEnd(6)} ${message.value.toString()}`),
  });
  await new Promise((r) => setTimeout(r, 9000));                          // escuta por 9 s e encerra
  await consumidor.disconnect();
}
