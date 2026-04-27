Antes de manejar a ferramenta, convém compreender o caminho que uma consulta percorre. O DNS não é um único servidor, mas uma hierarquia — quase como uma cadeia de guardiões, cada qual responsável por uma parte do saber.

---

## 🌍 Tipos de servidores DNS

Quando você faz uma consulta, ela pode passar por diferentes tipos de servidores:

### 🌐 DNS Raiz (Root Server)

* É o ponto inicial da busca
* Não sabe o IP final, mas sabe **para onde direcionar**
* Indica os servidores responsáveis pelos domínios de nível superior (como `.com`, `.org`, `.br`)

---

### 🏷️ DNS de Nível Superior (TLD – Top-Level Domain)

* Responsável por domínios como `.com`, `.edu`, `.br`
* Indica quais servidores são responsáveis por um domínio específico
* Exemplo: para `mit.edu`, aponta os servidores do MIT

---

### 🏛️ DNS Autoritativo

* É o servidor que **tem a resposta definitiva**
* Contém os registros oficiais do domínio
* Responde com o IP correto do site

---

### 🔁 DNS Intermediário (Recursivo / Cache)

* Geralmente é o DNS do seu provedor ou da sua rede
* Recebe sua solicitação e faz todo o trabalho por você
* Pode armazenar respostas em cache para acelerar futuras consultas

---

### ⚡ Cache DNS (Complemento importante)

* Não é um servidor em si, mas um **mecanismo presente nos servidores**
* Guarda respostas já consultadas
* Reduz tempo de resposta e tráfego na rede

---

## 🧭 O que é o nslookup

O **nslookup** é uma ferramenta de linha de comando usada para consultar servidores DNS.

Na prática, ele responde perguntas como:
“Qual é o endereço IP deste site?”

* Está disponível em **Linux, Unix e Windows**
* Funciona diretamente no terminal ou prompt de comando
* Permite consultar diferentes tipos de informações DNS

---

## ⚙️ Como o nslookup funciona

Quando você executa um comando com **nslookup**, acontece o seguinte:

1. Seu computador envia uma consulta para um servidor DNS
2. O servidor DNS processa essa consulta
3. Ele retorna a resposta com as informações solicitadas

Se você **não especificar um servidor DNS**, será usado o servidor padrão da sua rede.

Esse servidor pode:

* Responder diretamente (se tiver a informação)
* Ou consultar outros servidores DNS (raiz → TLD → autoritativo) até encontrar a resposta

---

## 🔍 Consulta básica (Registro A)

Exemplo:

```bash id="i3y0xb"
nslookup www.mit.edu
```

Esse comando pede:

👉 “Qual é o IP do site [www.mit.edu?”](http://www.mit.edu?”)

A resposta inclui:

* O servidor DNS que respondeu
* O endereço IP do site

Esse tipo de consulta usa, por padrão, o **registro A**.

---

## 🏛️ Consulta de servidores DNS (Registro NS)

Exemplo:

```bash id="lq6eqc"
nslookup -type=NS mit.edu
```

Esse comando pede:

👉 “Quais são os servidores DNS responsáveis pelo domínio mit.edu?”

A resposta mostra:

* Os servidores DNS autoritativos do domínio
* Seus respectivos endereços IP

💡 Observação importante:
Se aparecer “**resposta não autoritativa**”, significa que:

* A resposta veio de um **cache**
* E não diretamente do servidor oficial do domínio

---

## 📡 Consulta usando um servidor DNS específico

Exemplo:

```bash id="pbgk06"
nslookup www.aiit.or.kr bitsy.mit.edu
```

Aqui você está dizendo:

👉 “Pergunte diretamente ao servidor bitsy.mit.edu qual é o IP desse site”

Isso ignora o DNS padrão e consulta um servidor específico.

---

## 🧱 Tipos principais de registros DNS

O DNS funciona com diferentes tipos de registros. Os principais são:

### 🌐 Registro A (Address)

* Liga um domínio a um **endereço IPv4**
* Exemplo: site → 192.168.1.1

---

### 🔗 Registro CNAME (Alias)

* Faz um domínio apontar para outro domínio
* Exemplo:
  `www.site.com` → `site.com`

---

### 📧 Registro MX (E-mail)

Define quais servidores recebem e-mails do domínio (com prioridade).

**Exemplo:**

```bash
nslookup -type=MX gmail.com
```

Resposta indica servidores como `gmail-smtp-in.l.google.com`
👉 Menor número = maior prioridade

---

### 🏷️ Registro NS (Name Server)

Indica os servidores DNS responsáveis pelo domínio.

**Exemplo:**

```bash
nslookup -type=NS google.com
```

Resposta mostra servidores como `ns1.google.com`
👉 São os responsáveis oficiais pelas informações do domínio

---

## 🧾 Sintaxe geral do nslookup

A estrutura do comando é:

```bash id="h01gbd"
nslookup -opção host servidor_dns
```

Onde:

* **-opção** → tipo de consulta (ex: `-type=NS`)
* **host** → domínio que você quer consultar
* **servidor_dns** → opcional (se não informar, usa o padrão)

---

## 🧠 Conclusão prática

O **nslookup** é uma ferramenta essencial para entender como a internet “resolve nomes”.

Com ele, você pode:

* Descobrir IPs de sites
* Identificar servidores DNS
* Analisar configurações de rede
* Investigar problemas de conexão

Dominar essa ferramenta é como aprender a ler os bastidores da internet —
onde nomes se transformam em números, e cada consulta encontra seu destino por caminhos bem definidos.

---

*Organizado por [João Victor Labre/LabreCoder](https://github.com/LabreCoder)*