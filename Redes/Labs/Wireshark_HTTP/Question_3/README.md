# 3. RESGATANDO DOCUMENTOS LONGOS

## Orientações para responder a questão

### 1. Acessar o Wireshark

Basta acessar o aplicativo e selecionar sua conexão com a internet, seja ela via wlan ou pelo cabo ethernet.

<hr>

### 2. Realizar a captura

Primeiro eu realizei um filtro para <b>*'http'*</b>:

- Assim como aparece na imagem: [filtro http](/Redes/Labs/Wireshark_HTTP/imagem_filtro.png)

Após isso, basta colar o link abaixo no navegador:
> <b>*http://gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file3.html*</b> 

Ou o comando abaixo no terminal:

``` 
curl http://gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file3.html
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

> Você pode acessar o [Request](/Redes/Labs/Wireshark_HTTP/Question_3/Request.txt).

> Você pode acessar o [Response](/Redes/Labs/Wireshark_HTTP/Question_3/Response.txt).

<hr>

## Respostas

#### 1. *Quantas mensagens de solicitação HTTP GET seu navegador enviou? Qual número de pacote no rastreamento contém a mensagem GET para a conta ou direitos?* 

R: Foi enviada 1 mensagem HTTP GET, no pacote 2704.

#### 2. *Qual número de pacote no rastreio contém o código de status e a frase associados à resposta à solicitação HTTP GET?*

R: No. 2734 -> [Response in frame: 2734]

#### 3. *Qual é o código de status e frase na resposta?*

R: 200 OK

#### 4. *Quantos segmentos TCP contendo dados eram necessários para transmitir a única resposta HTTP e o texto da Declaração de Direitos?*

R: A resposta HTTP foi dividida em 4 segmentos TCP

[4 Reassembled TCP Segments (4864 bytes): 
 #2728(1388), 
 #2730(1388), 
 #2732(1388), 
 #2734(700)]
