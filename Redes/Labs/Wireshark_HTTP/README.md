# Orientações utilizar o Wireshark

### 1. Primeiro passo será configurar o wireshark

Eu tive uma certa dificuldade com o meu primeiro contato com o Wireshark, pois eu não havia habilitado a opção que permite captar os pacotes sem ser o sudo. A solução inicial seria de iniciar o Wireshark através do terminal com o comando:

```
sudo wireshark
```

ou realizar uma reconfiguração do Wireshark com 

```
sudo dpkg-reconfigure wireshark-common
```

Clicar em **'YES'** e depois adicionar o seu usuário ao grupo do wireshark

```
sudo usermod -aG wireshark SEU_USUARIO
```

Após esses passo, será possível executar o wireshark com acesso a captura dos pacotes.

<hr>

### 2. Acessar o Wireshark

Basta acessar o aplicativo e selecionar sua conexão com a internet, seja ela via wlan ou pelo cabo ethernet.

<hr>

### 3. Salvar resultados HTTP

Após realizar as capturas, o wireshark irá retornar com dois resultados:

- A requisição feita pelo sua máquina para o site;
- A resposta do site para sua máquina;

Você pode salvar o resultado HTTP selecionando <b>*Hypertext Transfer Protocol-> File -> Export Packets Dissections -> As Plain Text -> Selected packets only*</b>.

Após realizar esse caminho, coloque o nome do arquivo e salve.

---

*Organizado por [João Victor Labre/LabreCoder](https://github.com/LabreCoder)*