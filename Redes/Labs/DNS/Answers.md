# 📡 Exercícios com nslookup — Perguntas e Respostas

Agora que fornecemos uma visão geral do nslookup, é hora de testar na prática:

---

## 🌏 1. Executar o nslookup para obter o endereço IP de um servidor da Web na Ásia

**Pergunta:**  
Qual é o endereço IP de um servidor web localizado na Ásia?

**Procedimento adotado:**
```bash
nslookup www.naver.com
````

**Resposta:**
O comando retorna o endereço IP associado ao domínio consultado.

Exemplo de resultado:

```
Name:   www.naver.com
Address: 23.xxx.xxx.xxx
```

👉 Assim, o IP do servidor web é identificado diretamente na resposta.

---

## 🎓 2. Determinar os servidores DNS autoritativos de uma universidade na Europa

**Pergunta:**
Quais são os servidores DNS autoritativos de uma universidade europeia? (Escolhi a Universidade de Oxford)

**Procedimento adotado:**

```bash
nslookup -type=NS ox.ac.uk
```

**Resposta:**
O comando lista os servidores DNS responsáveis pelo domínio.

Exemplo de resultado:

```
ox.ac.uk     nameserver = dns0.ox.ac.uk
ox.ac.uk     nameserver = dns1.ox.ac.uk
```

👉 Portanto, os servidores autoritativos incluem:

* dns0.ox.ac.uk
* dns1.ox.ac.uk

---

## 📧 3. Consultar os servidores de correio do Yahoo usando um DNS específico

**Pergunta:**
Utilizando um dos servidores DNS obtidos anteriormente, quais são os servidores de e-mail do Yahoo e qual o IP de um deles?

**Procedimento adotado:**

Consulta MX usando um DNS específico:

```bash
nslookup -type=MX yahoo.com dns0.ox.ac.uk
```

**Resultado obtido:**

```
Server:     dns0.ox.ac.uk
Address:    129.67.1.190#53

** server can't find yahoo.com: REFUSED
```

👉 Interpretação:
O servidor DNS recusou a consulta. Isso pode ocorrer por restrições de configuração — um comportamento esperado em muitos servidores autoritativos.

Podemos tentar com o DNS do Google:

```bash
nslookup -type=MX yahoo.com 8.8.8.8
```

**Resultado obtido:**

```
Server:		8.8.8.8
Address:	8.8.8.8#53

Non-authoritative answer:
yahoo.com	mail exchanger = 1 mta7.am0.yahoodns.net.
yahoo.com	mail exchanger = 1 mta5.am0.yahoodns.net.
yahoo.com	mail exchanger = 1 mta6.am0.yahoodns.net.
```

---

**Etapa alternativa (continuação):**

Consulta direta a um servidor MX conhecido do Yahoo:

```bash
nslookup mta5.am0.yahoodns.net
```

**Resposta obtida:**

```
Non-authoritative answer:
Name:   mta5.am0.yahoodns.net
Address: 98.136.96.91
Address: 98.136.96.76
Address: 67.195.204.73
Address: 98.136.96.77
Address: 67.195.204.72
Address: 67.195.228.94
Address: 98.136.96.75
Address: 67.195.228.106
```

👉 Assim, alguns dos IPs associados ao servidor de e-mail são:

* 98.136.96.91
* 67.195.204.73
* 67.195.228.94
  *(entre outros retornados)*

---

## 🧭 Conclusão

Nem toda resposta vem pronta — algumas são negadas, outras fragmentadas.
Ainda assim, cada tentativa revela o comportamento dos servidores e fortalece o entendimento.

Quando uma consulta falhar:

* experimente outro servidor DNS
* teste outro domínio
* observe as diferenças nas respostas

É nesse processo que se forma o olhar atento de quem compreende a rede além da superfície.