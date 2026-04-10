# 2. HTTP CONDICIONAL

## Orientações para responder a questão

### 1. Acessar o Wireshark

Basta acessar o aplicativo e selecionar sua conexão com a internet, seja ela via wlan ou pelo cabo ethernet.

<hr>

### 2. Realizar a captura

Primeiro eu realizei um filtro para <b>*'http'*</b>:

- Assim como aparece na imagem: [filtro http](/Redes/Labs/Wireshark_HTTP/Question_1/imagem_filtro.png)

Após isso, basta colar o link abaixo no navegador:
> <b>*http://gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file2.html*</b> 

**Obs.:** para esse exercício será necessário recarregar a página.

<hr>

### 3. Salvar resultados HTTP

Se quiser orientações sobre como fazer isso, basta clicar *[aqui](/Redes/Labs/Wireshark_HTTP/README.md)*.

<hr>

### 4. Acessar meus arquivos

> Você pode acessar o [Request](/Redes/Labs/Wireshark_HTTP/Question_2/Request_1.txt).

> Você pode acessar o [Response 1](/Redes/Labs/Wireshark_HTTP/Question_2/Response_1.txt) ou [Response 2](/Redes/Labs/Wireshark_HTTP/Question_2/Response_2.txt).

<hr>

## Respostas

#### 1. *Inspecione o conteúdo da primeira solicitação HTTP GET do seu navegador para o servidor. Você vê uma linha “IF-MODIFIED-SINCE” no HTTP GET?* 

R: Não, consigo ver apenas dentro da minha segunda requisição.

#### 2. *Inspecione o conteúdo da resposta do servidor. O servidor retornou explicitamente o conteúdo do arquivo? Como você sabe?*

R: Se for a primeira resposta → o servidor retorna o conteúdo completo (200 OK)

#### 3. *Agora inspecione o conteúdo da segunda solicitação HTTP GET do seu navegador para o servidor. Você vê uma linha “IF-MODIFIED-SINCE:” no HTTP GET? Em caso afirmativo, quais informações seguem o cabeçalho“IF-MODIFIED-SINCE:”?*

R: Sim, as informações são: Tue, 28 Oct 2025 05:59:01 GMT\r\n

#### 4. *Qual é o código de status HTTP e a frase retornada do servidor em resposta a este segundo HTTP GET? O servidor retornou explicitamente o conteúdo do arquivo? Explicar.*

R: Não, o servidor não retornou o conteúdo do arquivo.
Sabemos disso porque o código de status foi '304 Not Modified', que indica que o arquivo não foi alterado desde a última requisição, então o navegador deve usar a versão armazenada em cache.

