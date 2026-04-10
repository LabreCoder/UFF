# 4. HTTP COM OBJETOS EMBUTIDOS

## Orientações para responder a questão

### 1. Acessar o Wireshark

Basta acessar o aplicativo e selecionar sua conexão com a internet, seja ela via wlan ou pelo cabo ethernet.

<hr>

### 2. Realizar a captura

Primeiro eu realizei um filtro para <b>*'http'*</b>:

- Assim como aparece na imagem: [filtro http](/Redes/Labs/Wireshark_HTTP/imagem_filtro.png)

Após isso, basta colar o link abaixo no navegador:
> <b>*http://gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file4.html*</b> 

Ou o comando abaixo no terminal:

``` 
curl http://gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file4.html
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

> Você pode acessar o [Request 1](/Redes/Labs/Wireshark_HTTP/Question_4/Request_1.txt), [Request 2](/Redes/Labs/Wireshark_HTTP/Question_4/Request_2.txt) ou [Request 3](/Redes/Labs/Wireshark_HTTP/Question_4/Request_3.txt).

> Você pode acessar o [Response 1](/Redes/Labs/Wireshark_HTTP/Question_4/Response_1.txt), [Response 2](/Redes/Labs/Wireshark_HTTP/Question_4/Response_2.txt) ou [Response 3](/Redes/Labs/Wireshark_HTTP/Question_4/Response_3.txt).

<hr>

## Respostas

#### 1. *Quantas mensagens de solicitação HTTP GET seu navegador enviou? Para quais endereços da Internet essas solicitações GET foram enviadas?* 

R: Foi enviadas 3 mensagens HTTP GET.

As duas primeiras foram para o mesmo servidor [128.119.245.12] enquanto a última foi para um outro endereço [2.56.99.24].

#### 2. *Você sabe se o seu navegador baixou as duas imagens em série ou se elas foram baixadas dos dois sites em paralelo?*

R: Verifiquei como podemos ver se foram baixadas em paralelo, e um dos indicativos é quando temos duas requisições quase simultâneas e também em portas diferentes. Essas duas requisições atendem isso:

```
GET 1:
Time: 2.48 s
Src Port: 34736
Destino: 128.119.245.12

GET 2:
Time: 2.86 s
Src Port: 59704
Destino: 2.56.99.24
```