# 5. HTTP COM AUTENTICAÇÃO

## Orientações para responder a questão

### 1. Acessar o Wireshark

Basta acessar o aplicativo e selecionar sua conexão com a internet, seja ela via wlan ou pelo cabo ethernet.

<hr>

### 2. Realizar a captura

Primeiro eu realizei um filtro para <b>*'http'*</b>:

- Assim como aparece na imagem: [filtro http](/Redes/Labs/Wireshark_HTTP/imagem_filtro.png)

Após isso, basta colar o link abaixo no navegador:
> <b>*http://gaia.cs.umass.edu/wireshark-labs/protected_pages/HTTP-wireshark-file5.html*</b> 

Ou o comando abaixo no terminal:

``` 
curl http://gaia.cs.umass.edu/wireshark-labs/protected_pages/HTTP-wireshark-file5.html
```

**Obs.:** caso você já tenha acessado o link pelo navegador, o próprio navegador irá guardar esse acesso na memória cache do navegador, com isso o wireshark não irá capturar como se fosse uma nova requisição. Para resolver esse problema, é necessário resetar o cache do navegador, utilizando:

```
Ctrl + Shift + R
```
<hr>

### 3. Salvar resultados HTTP

Se quiser orientações sobre como fazer isso, basta clicar *[aqui](/Redes/Labs/Wireshark_HTTP/README.md)*.

<hr>

### 4. Acessar meus arquivos

> Você pode acessar o [Request 1](/Redes/Labs/Wireshark_HTTP/Question_5/Request_1.txt) ou [Request 2](/Redes/Labs/Wireshark_HTTP/Question_5/Request_2.txt).

> Você pode acessar o [Response 1](/Redes/Labs/Wireshark_HTTP/Question_5/Response_1.txt) ou [Response 2](/Redes/Labs/Wireshark_HTTP/Question_5/Response_2.txt).
<hr>

## Respostas

#### 1. *Qual é a resposta do servidor (código de status e frase) em resposta à mensagem HTTP GET inicial do seu navegador?* 

R: 401 Unauthorized.

#### 2. *Quando o seu navegador envia a mensagem HTTP GET pela segunda vez, que novo campo está incluído na mensagem HTTP GET?*

R: Authorization: Basic d2lyZXNoYXJrLXN0dWRlbnRzOm5ldHdvcms=\r\n -> Credentials: wireshark-students:network