# Respostas das Perguntas

O código do servidor TCP começa informando que recebeu a conexão do cliente, com o seu IP e porta origem, após qualquer mensagem do cliente, temos uma saída no terminal do servidor com o IP e porta de origem do cliente que enviou. 

No caso do UDP, não temos nenhuma mensagem informando que realizamos uma conexão com o cliente, ele apenas envia a mensagem e o servidor imprime com o IP e porta de origem desse cliente.

### Pergunta 1:

- **Diferente do UDP, o TCP você precisa primeiro executar o programa do lado servidor e depois o programa do lado cliente. Por quê?**

**Resposta:** Isso ocorre, pois o Cliente inicia tentando se conectar com o servidor, como o servidor ainda não existe, o programa do cliente se encerra.

---

### Pergunta 2:

- **É possível melhorar o programa TCP do lado servidor de modo aceitar múltiplas conexões? De que forma você faria utilizando threads? Mostrar a implementação.**

**Resposta:** Sim é possível. A princípio eu irei disponibilizar mais threads para o servidor e sempre que o cliente tentar se conectar com o servidor, ele irá criar uma nova thread para aquele cliente.
---

### Pergunta 3:

- **Deseja-se implementar um serviço de eco usando a conexão TCP. É possível adaptar os códigos do servidor TCP e do cliente TCP para responder a mensagem do cliente com a mesma mensagem? Mostrar a implementação do servidor TCP e do cliente TCP.**

**Resposta:** Sim, é possível.
Basta fazer o servidor TCP reenviar ao cliente a mesma mensagem recebida. Visualizar o código nas linhas: [56 - 59] Cliente e [84 -85] Servidor.
---

### Pergunta 4:

- **Deseja-se implementar um servidor Web. É possível adaptar o código do servidor TCP para responder a uma requisição HTTP simples com algum conteúdo HTML?**

Mostrar a implementação do servidor TCP. 

**Dica**: lembre-se de ajustar o número da porta do servidor para 80 (porta onde o serviço Web responde).

**Resposta:** Sim, é possível.
Como o protocolo HTTP utiliza TCP, o servidor TCP pode ser adaptado para responder requisições HTTP enviando:

- Cabeçalhos HTTP
- Conteúdo HTML

O navegador interpreta essa resposta e exibe a página Web.

Não consegui utilizar a porta 80, provavelmente estava ocupada, então teste com a própria 8080 e apliquei no navegador. Teste com a 3000 para poder ver estava funcionando também.