# 1. HTTP GET/RESPONSE

## Orientações para responder a questão

1. Primeiro passo será configurar o wireshark

Eu tive uma certa dificuldade com o meu primeiro contato com o Wireshark, pois eu não havia habilitado a opção que permite captar os pacotes sem ser o sudo. A solução inicial seria de iniciar o Wireshark através do terminal com o comando:

```
sudo wireshark
```

ou realizar uma reconfiguração do Wireshark com 

```
sudo dpkg-reconfigure wireshark-common
```

Clicar em 'YES' e depois adicionar o seu usuário ao grupo do wireshark

```
sudo usermod -aG wireshark SEU_USUARIO
```

Após esses passo, será possível executar o wireshark com acesso a captura dos pacotes.

2. Acessar o Wireshark

Basta acessar o aplicativo e selecionar sua conexão com a internet, seja ela via wlan ou pelo cabo eternet.

3. Realizar a captura

Primeiro eu realizei um filtro para <b>*'http'*</b>:

- Assim como aparece na imagem: [filtro http](../imagem_filtro.png)

Após isso, basta colar o link abaixo no navegador:
> <b>*http://gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file1.html*</b> 

Ou o comando abaixo no terminal:

``` 
curl http://gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file1.html
```

**Obs.:** caso você já tenha acessado o link pelo navegador, o próprio navegador irá guardar esse acesso na memória cache do navegador, com isso o wireshark não irá capturar como se fosse uma nova requisição. Para resolver esse problema, é necessário resetar o cache do navegador, utilizando:

```
Ctrl + Shift + R
```

4. Salvar resultados HTTP

Após realizar as capturas, o wireshark irá retornar com dois resultados:

- A requisição feita pelo sua máquina para o site;
- A resposta do site para sua máquina;

Você pode salvar o resultado HTTP selecionando <b>*Hypertext Transfer Protocol-> File -> Export Packets Dissections -> As Plain Text -> Selected packets only*</b>.

Após realizar esse caminho, coloque o nome do arquivo e salve.

5. Acessar as respostas que obtive

> Você pode acessar o [Request](../Request.txt).

> Você pode acessar o [Response](../Response.txt).

## Respostas

1. *O seu navegador está executando a versão 1.0 ou 1.1 do HTTP? Qual versão do HTTP o servidor está executando?* 

R: Navegador: HTTP/1.1 e Servidor: HTTP/1.1

2. *Que idiomas (se algum) seu navegador indica que pode aceitar para o servidor?*

R: pt-BR, en-US

3. *Qual é o endereço IP do seu computador? Do servidor gaia.cs.umass.edu?*

R: Meu IP: 192.168.X.X. Gaia IP: 128.119.245.12

4. *Qual é o código de status retornado do servidor para o seu navegador?*

R: 200 OK

5. *Quando o arquivo HTML que você está recuperando foi modificado pela última vez no servidor?*

R: Tue, 28 Oct 2025 05:59:01

6. *Quantos bytes de conteúdo estão sendo retornados ao seu navegador?*

R: 128 bytes

7. *Ao inspecionar os dados brutos na janela de conteúdo do pacote, você vê algum cabeçalho dentro dos dados que não são exibidos na janela de listagem de pacotes? Se sim, nomeie um.*

R: Sim. Nos dados brutos é possível observar cabeçalhos como Connection: Keep-Alive e Keep-Alive: timeout=5, max=100, além da formatação completa da mensagem HTTP que não aparece da mesma forma na visualização resumida.