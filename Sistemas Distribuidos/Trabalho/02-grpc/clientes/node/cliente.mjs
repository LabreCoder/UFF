// Cliente gRPC em JavaScript (Node.js) — OUTRA linguagem, MESMO contrato (.proto).
// O servidor é Python; este cliente nunca viu o código dele: só o loja.proto.
// Interoperabilidade = a IDL é a única coisa compartilhada.
//
// Uso: node cliente.mjs <demo>
//      demos: unaria | erros | servidor | cliente | bidi | deadline | todos
import grpc from "@grpc/grpc-js";
import protoLoader from "@grpc/proto-loader";

const ALVO = process.env.ALVO ?? "localhost:8102";

// O proto-loader lê o .proto e monta o stub dinamicamente (em Python usamos o protoc).
const definicao = protoLoader.loadSync("proto/loja.proto", {
  keepCase: true, longs: String, enums: String, defaults: true,
});
const pacote = grpc.loadPackageDefinition(definicao).loja;
const cliente = new pacote.Catalogo(ALVO, grpc.credentials.createInsecure());

const AUTH = new grpc.Metadata();
AUTH.set("authorization", "Bearer segredo-da-loja");

const titulo = (t) => console.log(`\n\x1b[1;36m=== ${t} ===\x1b[0m`);
const dormir = (ms) => new Promise((r) => setTimeout(r, ms));
const comPrazo = (seg) => ({ deadline: new Date(Date.now() + seg * 1000) });

// ---------------------------------------------------------------------------
async function unaria() {
  titulo("1) UNÁRIA: 1 requisição -> 1 resposta (+ metadata)");
  await new Promise((resolve, reject) => {
    const call = cliente.ObterProduto({ id: 1 }, AUTH, comPrazo(5), (err, resp) => {
      if (err) return reject(err);
      console.log("resposta :", resp.nome, "| R$", resp.preco, "| estoque", resp.estoque);
    });
    call.on("metadata", (m) => console.log("metadata inicial (headers):", m.getMap()));
    call.on("status", (s) => { console.log("metadata final   (trailers):", s.metadata.getMap()); resolve(); });
  });
}

async function erros() {
  titulo("2) CÓDIGOS DE STATUS gRPC");
  const casos = [
    ["produto inexistente (id=999)", { id: 999 }, AUTH],
    ["id inválido (id=-5)", { id: -5 }, AUTH],
    ["sem token (metadata ausente)", { id: 1 }, new grpc.Metadata()],
  ];
  for (const [nome, req, md] of casos) {
    await new Promise((resolve) => {
      cliente.ObterProduto(req, md, comPrazo(5), (err) => {
        console.log(`${nome.padEnd(32)} -> ${grpc.status[err.code].padEnd(16)} | ${err.details}`);
        resolve();
      });
    });
  }
}

async function servidorStreaming() {
  titulo("3) SERVER STREAMING: 1 requisição -> N respostas (chegam uma a uma)");
  const t0 = Date.now();
  await new Promise((resolve) => {
    const fluxo = cliente.ListarProdutos({ categoria: "informatica", atraso_ms: 600 }, AUTH);
    fluxo.on("data", (p) => console.log(`  +${((Date.now() - t0) / 1000).toFixed(1)}s  recebido: ${p.nome}`));
    fluxo.on("end", resolve);
  });
}

async function clienteStreaming() {
  titulo("4) CLIENT STREAMING: N requisições -> 1 resposta");
  await new Promise(async (resolve) => {
    const chamada = cliente.FecharCarrinho(AUTH, (err, r) => {
      console.log(`  resumo: ${r.itens} itens, ${r.unidades} unidades, total R$ ${r.total} | avisos: ${JSON.stringify(r.avisos)}`);
      resolve();
    });
    for (const [produto_id, quantidade] of [[1, 1], [2, 3], [5, 2], [777, 1]]) {
      console.log(`  enviando produto=${produto_id} qtd=${quantidade}`);
      chamada.write({ produto_id, quantidade });
      await dormir(400);
    }
    chamada.end();                       // avisa "terminei de enviar"
  });
}

async function bidirecional() {
  titulo("5) BIDIRECIONAL: os dois lados falam ao mesmo tempo");
  await new Promise(async (resolve) => {
    const chamada = cliente.Conversar(AUTH);
    chamada.on("data", (m) => console.log(`  [servidor] <- ${m.autor}: ${m.texto}`));
    chamada.on("end", resolve);
    for (const texto of ["Meu pedido atrasou", "Quero trocar o produto", "Obrigado!"]) {
      await dormir(800);
      console.log(`  [cliente] -> ${texto}`);
      chamada.write({ autor: "Cliente", texto, timestamp: Math.floor(Date.now() / 1000) });
    }
    await dormir(400);
    chamada.end();
  });
}

async function deadline() {
  titulo("6) DEADLINE (prazo) e CANCELAMENTO");
  await new Promise((resolve) => cliente.GerarRelatorio({ duracao_ms: 500 }, AUTH, comPrazo(2), (e, r) => {
    console.log("dentro do prazo      :", r.conteudo); resolve();
  }));
  await new Promise((resolve) => cliente.GerarRelatorio({ duracao_ms: 3000 }, AUTH, comPrazo(1), (e) => {
    console.log("prazo de 1s estourou :", grpc.status[e.code], "| o servidor foi avisado e parou o trabalho"); resolve();
  }));
  const chamada = cliente.GerarRelatorio({ duracao_ms: 5000 }, AUTH, () => {});
  chamada.on("error", () => {});
  await dormir(500);
  chamada.cancel();                      // o cliente desiste
  await dormir(400);
  console.log("cancelamento         : chamada cancelada pelo cliente");
}

const DEMOS = { unaria, erros, servidor: servidorStreaming, cliente: clienteStreaming, bidi: bidirecional, deadline };
const escolha = process.argv[2] ?? "todos";
for (const nome of escolha === "todos" ? Object.keys(DEMOS) : [escolha]) await DEMOS[nome]();
console.log("\n\x1b[1;32mCliente gRPC Node.js terminou (stub montado a partir do mesmo .proto).\x1b[0m");
cliente.close();
