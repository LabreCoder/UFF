// Cliente REST em JavaScript (Node.js 20).
// Mesma API, OUTRA linguagem: isso é a interoperabilidade do REST.
// Só usamos HTTP + JSON; o Node não sabe nada sobre Python/FastAPI.
// `fetch` já vem embutido no Node 20, não precisa instalar nada.

const BASE = process.env.API_URL ?? "http://localhost:8101";
const AUTH = { Authorization: "Bearer segredo-da-loja" };

const titulo = (t) => console.log(`\n\x1b[1;36m=== ${t} ===\x1b[0m`);

async function chamar(metodo, caminho, { corpo, headers = {} } = {}) {
  const resp = await fetch(BASE + caminho, {
    method: metodo,
    headers: { "Content-Type": "application/json", ...headers },
    body: corpo ? JSON.stringify(corpo) : undefined,
  });
  const texto = await resp.text();
  const dados = texto && resp.headers.get("content-type")?.includes("json") ? JSON.parse(texto) : texto;
  console.log(`${metodo} ${caminho} -> ${resp.status} ${resp.statusText}`);
  return { status: resp.status, dados, headers: resp.headers };
}

titulo("1) Descobrindo a API pela raiz (HATEOAS)");
const raiz = await chamar("GET", "/");
console.log("links recebidos:", Object.keys(raiz.dados._links).join(", "));

titulo("2) Seguindo o link 'produtos' (o cliente não 'decorou' a URL)");
const lista = await chamar("GET", raiz.dados._links.produtos.href + "?categoria=informatica&tamanho=2");
console.log("total:", lista.dados.total, "| nesta página:", lista.dados.itens.map((p) => p.nome));

titulo("3) Criando um produto (POST com token)");
const nome = `Produto do Node ${Date.now() % 100000}`;
const criado = await chamar("POST", "/produtos", {
  headers: AUTH,
  corpo: { nome, preco: 42.5, categoria: "javascript", estoque: 7 },
});
console.log("Location:", criado.headers.get("location"));

titulo("4) Cache: 2ª leitura com ETag volta 304 sem corpo");
const id = criado.dados.id;
const primeira = await chamar("GET", `/produtos/${id}`);
const etag = primeira.headers.get("etag");
console.log("ETag:", etag, "| X-Servidor (container da API):", primeira.headers.get("x-servidor"));
await chamar("GET", `/produtos/${id}`, { headers: { "If-None-Match": etag } });

titulo("5) Tratando erros pelos códigos de status");
await chamar("GET", "/produtos/9999"); // 404
await chamar("POST", "/produtos", { corpo: { nome: "x", preco: 1, categoria: "x", estoque: 1 } }); // 401
await chamar("POST", "/pedidos", { headers: AUTH, corpo: { produto_id: id, quantidade: 999 } }); // 409

titulo("6) Limpeza (DELETE)");
await chamar("DELETE", `/produtos/${id}`, { headers: AUTH });

console.log("\n\x1b[1;32mCliente Node.js terminou: mesma API, linguagem diferente.\x1b[0m");
