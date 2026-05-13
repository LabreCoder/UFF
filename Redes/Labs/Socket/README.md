# README — Laboratório de Programação com Sockets TCP/UDP em Python

## Objetivo

Este laboratório teve como objetivo estudar conceitos fundamentais de redes de computadores utilizando programação com sockets em Python.

Foram implementados:

* Cliente e servidor UDP
* Cliente e servidor TCP
* Servidor TCP com múltiplas conexões utilizando threads
* Serviço Echo TCP
* Servidor HTTP simples utilizando sockets TCP

---

# Tecnologias utilizadas

* Python 3
* Biblioteca `socket`
* Biblioteca `threading`

---

# Conceitos estudados

Durante o laboratório foram praticados conceitos importantes de redes:

* Comunicação cliente-servidor
* Protocolo TCP
* Protocolo UDP
* Portas TCP/UDP
* Endereçamento IP
* Sockets
* Threads
* Conexões simultâneas
* Requisições HTTP
* Respostas HTTP
* HTML básico
* Modelo cliente-servidor

---

# Estrutura do laboratório

## 1. Comunicação UDP

Implementação de:

* Cliente UDP
* Servidor UDP

### Características

* Não orientado à conexão
* Sem garantia de entrega
* Mais leve e rápido

### Métodos utilizados

```python
socket()
bind()
sendto()
recvfrom()
```

---

# 2. Comunicação TCP

Implementação de:

* Cliente TCP
* Servidor TCP

### Características

* Orientado à conexão
* Comunicação confiável
* Controle de entrega de pacotes

### Métodos utilizados

```python
socket()
bind()
listen()
accept()
connect()
send()
recv()
```

---

# 3. Servidor TCP com múltiplas conexões

O servidor foi adaptado para suportar múltiplos clientes simultaneamente utilizando threads.

## Funcionamento

* O servidor principal aceita conexões
* Cada cliente é tratado em uma thread separada

### Biblioteca utilizada

```python
from threading import Thread
```

---

# 4. Serviço Echo TCP

Foi implementado um serviço Echo utilizando TCP.

## Funcionamento

O servidor:

1. Recebe a mensagem do cliente
2. Reenvia exatamente a mesma mensagem

O cliente:

1. Envia uma mensagem
2. Recebe a resposta do servidor

---

# 5. Servidor HTTP simples

Foi implementado um servidor Web simples utilizando sockets TCP.

## Funcionamento

O servidor:

* Recebe uma requisição HTTP
* Envia cabeçalhos HTTP
* Envia uma página HTML simples

O navegador interpreta a resposta e renderiza a página.

---

# Exemplo de resposta HTTP enviada

```http
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: ...
Connection: close
```

---

# Conceitos importantes aprendidos

## TCP x UDP

| TCP                         | UDP                     |
| --------------------------- | ----------------------- |
| Orientado à conexão         | Não orientado à conexão |
| Confiável                   | Não confiável           |
| Mais lento                  | Mais rápido             |
| Usa `listen()` e `accept()` | Não utiliza conexão     |

---

# Conexões TCP

Uma conexão TCP é identificada por:

```text
(IP origem, porta origem, IP destino, porta destino)
```

Isso permite múltiplos clientes conectados simultaneamente na mesma porta do servidor.

---

# Threads

As threads permitiram que:

* múltiplos clientes fossem atendidos ao mesmo tempo
* o servidor permanecesse aceitando novas conexões

---

# Como executar

## Executar servidor TCP

```bash
python servidor.py
```

---

## Executar cliente TCP

```bash
python cliente.py
```

---

## Executar servidor HTTP

```bash
python servidor_http.py
```

Acessar no navegador:

```text
http://127.0.0.1:8080
```

---

# Resultados obtidos

Ao final do laboratório foi possível:

* compreender o funcionamento de sockets
* implementar comunicação TCP e UDP
* criar aplicações cliente-servidor
* entender múltiplas conexões TCP
* implementar um serviço Echo
* desenvolver um servidor HTTP simples

---

*Organizado por [João Victor Labre/LabreCoder](https://github.com/LabreCoder)*