# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: [DD/MM/AAAA] | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 06: Comunicação entre Processos — RPC, Mensagens, Filas (MOM), AMQP e RabbitMQ

### 📝 Introdução

A sexta aula trata do **coração de qualquer sistema distribuído (SD): a comunicação entre processos** que rodam em máquinas diferentes. Toda comunicação em SD é baseada em **troca de mensagens**, o que é mais difícil de programar do que a memória compartilhada. Por isso o desejável é obter modelos em que a **complexidade da comunicação fique transparente** para o desenvolvedor.

A aula percorre três grandes blocos:

1. **Fundamentos:** camadas e protocolos, e os "eixos" de classificação da comunicação (persistente x transiente, síncrona x assíncrona, confiável x não-confiável, discreta x fluxo).
2. **Chamada de Procedimento Remoto (RPC):** como chamar uma função em outra máquina como se fosse local (stubs, etapas, RPC síncrona/assíncrona, passagem de parâmetros, IDL).
3. **Comunicação Orientada a Mensagem:** sockets (TCP/UDP), ZeroMQ, MPI e, principalmente, o **Middleware Orientado a Mensagens (MOM)** com filas, gerenciadores de fila, repassadores, **message brokers**, o protocolo **AMQP** e o **RabbitMQ** (exchanges *fanout*, *direct* e *topic*).

> 🎯 **Por que esta aula é a mais importante para o Trabalho Final:** o trabalho pede demonstrar **gRPC, REST, RabbitMQ e Apache Kafka**. Esta aula é a base teórica de tudo isso: gRPC é uma **RPC** (stubs + IDL), RabbitMQ é um **MOM** que implementa **AMQP** com **exchanges**, e Kafka será comparado ao RabbitMQ. Veja a seção **🔗 Conexão com o Trabalho Final** ao final.

> 📌 **Data:** os slides não trazem a data da aula, por isso o placeholder `[DD/MM/AAAA]` foi mantido.

> 🏷️ **Convenção deste documento:** tudo que for explicação própria e **não estiver nos slides** está marcado com **(complemento)**. O restante é fiel ao material (`Aula06-sd-comunicacao.pdf` e `Aula06-gab.md`).

---

### 💡 Conceitos Chave

#### 1. Fundamentos: camadas, protocolos e a necessidade de transparência

* **Troca de mensagens:** processos em máquinas diferentes só conseguem se comunicar enviando mensagens pela rede. É mais difícil do que usar primitivas de memória compartilhada.
* **Protocolos em camadas:** em muitos protocolos em camadas, **cada camada tem seu próprio cabeçalho** (header). Os dados que descem da camada *k+1* para a camada *k* contêm cabeçalho + dados, mas a camada *k* **não consegue distinguir** o que é um e o que é outro.
  * **Por que não um cabeçalho único com todo o controle?** (gabarito, Q1) Porque **cada camada precisa ser independente das outras**. Um cabeçalho único, lido e escrito por todas as camadas, destruiria essa transparência e faria com que **mudanças no protocolo de uma camada ficassem visíveis para as demais**, o que é indesejável.
* **Serviços da camada de transporte são inadequados para construir aplicações distribuídas** (gabarito, Q2): eles **mal oferecem transparência de distribuição**. O desenvolvedor precisa dar muita atenção à comunicação, o que leva a **soluções proprietárias**. O efeito é que aplicações construídas direto sobre *sockets* são **difíceis de portar e de interoperar** com outras aplicações. É daí que nascem RPC, MOM, etc.: modelos de mais alto nível.

```
(complemento) Visão simplificada em camadas — cada camada só "enxerga" a de cima e a de baixo

 Aplicação ──────────────► [ dados ]
 Transporte (TCP/UDP) ───► [ H-transp | dados ]
 Rede (IP) ──────────────► [ H-rede | H-transp | dados ]
 Enlace ─────────────────► [ H-enlace | H-rede | H-transp | dados ]
 (cada camada ACRESCENTA o seu cabeçalho e trata o restante como "dados" opacos)
```

* **Tipos de comunicação (eixos de classificação):**
  * Persistente x Transiente
  * Síncrona x Assíncrona
  * Confiável x Não-confiável
  * Discreta x Fluxo

---

#### 2. Comunicação Persistente x Transiente

* **Persistente:** a mensagem é **armazenada pelo middleware** de comunicação durante o tempo que for necessário para entregá-la ao receptor.
  * O remetente **não precisa continuar em execução** após apresentar a mensagem.
  * O receptor **não precisa estar em execução** no momento em que a mensagem é apresentada.
  * Exemplo dos slides: **sistema de caixa de correio (mailbox)**.
* **Transiente:** a mensagem é armazenada pelo middleware **somente enquanto remetente e receptor estiverem ambos em execução**. Se o middleware não puder entregar, **a mensagem é descartada**.
  * Normalmente os serviços de comunicação do **nível de transporte** (ex.: TCP/UDP, sockets) oferecem comunicação transiente.

```
PERSISTENTE (middleware guarda)                 TRANSIENTE (sem guarda)
Remetente ──► [ Middleware: guarda a msg ] ──►  Remetente ──► (rede) ──► Receptor
   (pode terminar)         │      Receptor            Receptor fora do ar?  ➜ mensagem DESCARTADA
                           └────► (pode estar desligado agora, recebe depois)
```

#### 3. Comunicação Síncrona x Assíncrona

* **Síncrona:**
  * Remetente usa **chamada bloqueante** para enviar: fica bloqueado até o receptor **confirmar o recebimento**.
  * Receptor usa chamada bloqueante para receber: fica bloqueado até a mensagem chegar.
  * Remetente e receptor devem estar **ativos ao mesmo tempo e sincronizados**.
  * No modelo **requisição-resposta**: o cliente usa chamada bloqueante para **enviar** a requisição **e** chamada bloqueante para **receber** a resposta.
* **Assíncrona:**
  * Remetente **continua a execução imediatamente** após apresentar a mensagem (envio **não bloqueante**).
  * A mensagem fica armazenada (temporariamente) até o envio concluir; o tempo de armazenamento **depende de a comunicação ser persistente ou transiente**.
  * O receptor **não fica bloqueado** esperando: faz trabalho útil e processa a mensagem quando ela chegar.
  * No modelo requisição-resposta: cliente usa chamada bloqueante **ou** não-bloqueante para enviar e chamada **não-bloqueante** para receber a resposta.
  * **Vantagem:** **oculta a latência de comunicação** intrínseca dos SDs.
* Os slides destacam que **há várias formas de combinar sincronismo e persistência**.

```
SÍNCRONA (cliente bloqueado esperando)            ASSÍNCRONA (cliente segue trabalhando)
Cliente:  ──envia──┐        ┌─recebe──►           Cliente:  ──envia──►(continua trabalhando)──►(trata resposta quando chegar)
                   │ bloq.  │                                  │                                   ▲
Servidor:          └─processa┘                    Servidor:      └────────processa────────────────────┘
```

#### 4. Confiável x Não-confiável e Discreta x Fluxo

* **Confiável:** há **garantia de entrega** e os dados **não chegam corrompidos**.
* **Não-confiável:** **sem garantia de entrega**; dados podem chegar corrompidos.
* **Discreta:** as partes se comunicam por mensagens e **cada mensagem forma uma unidade de informação completa**.
* **Fluxo (stream):** são enviadas **várias mensagens relacionadas entre si pela ordem ou pela relação temporal**.
  * Podem ter **restrição temporal** (ex.: áudio e vídeo) ou **não** (ex.: transferência de arquivo).

#### 📊 Tabela comparativa: Transiente x Persistente x Síncrona x Assíncrona

| Critério | Transiente | Persistente | Síncrona | Assíncrona |
|---|---|---|---|---|
| **O que significa** | Mensagem existe só enquanto remetente **e** receptor executam | Middleware guarda a mensagem até entregá-la | Remetente bloqueia até receptor confirmar | Remetente segue executando após enviar |
| **Quem guarda a mensagem** | Ninguém além do tempo de entrega (descarta se falhar) | O middleware (ex.: fila / mailbox) | Depende (tipicamente transiente) | Armazenada temporariamente; **tempo depende** de ser persistente ou transiente |
| **Receptor precisa estar ativo?** | **Sim** | **Não** | **Sim** (ao mesmo tempo, sincronizados) | Não precisa ficar bloqueado esperando |
| **Remetente precisa continuar ativo?** | Sim, até a entrega | **Não** | Sim (bloqueado) | Não bloqueia (persistente: pode até terminar) |
| **Acoplamento no tempo** | Forte | **Fraco** | Forte | Fraco/médio |
| **Se a entrega falha** | Mensagem é descartada | Fica guardada até conseguir entregar | Remetente continua bloqueado/aguardando | Depende do armazenamento |
| **Exemplo nos slides** | Sockets TCP/UDP, ZeroMQ, MPI | Caixa de correio (mailbox), MOM/filas (RabbitMQ) | Chamada bloqueante; RPC síncrona | RPC assíncrona (callback); MOM |
| **Efeito principal** | Simples e rápido, mas frágil | Robusto, desacopla remetente e receptor | Escalabilidade geográfica limitada (veja Q4 abaixo) | Oculta a latência |

> 🧠 **Como ler a tabela:** persistente/transiente fala de **quem guarda a mensagem e por quanto tempo**; síncrona/assíncrona fala de **quem fica esperando (bloqueado)**. São eixos **independentes**, por isso dá para combiná-los. O **MOM** (filas) é, nos slides, **assíncrono + persistente**.

```
(complemento) Quadro das combinações

                      │  TRANSIENTE                     │  PERSISTENTE
──────────────────────┼─────────────────────────────────┼──────────────────────────────────
 SÍNCRONA             │ Sockets com send/recv bloqueante│ Remetente espera o aceite da fila
                      │ RPC síncrona                    │ (ex.: confirmação do broker)
 ASSÍNCRONA           │ Datagrama UDP, RPC assíncrona   │ MOM / filas / e-mail (mailbox)
                      │ de uma via                      │ ← caso típico de RabbitMQ
```

##### As 4 combinações de comunicação fracamente acoplada com filas (Figura 4.15 dos slides)

```
 (a)                (b)                 (c)                 (d)
Remetente EXEC.    Remetente EXEC.     Remetente PASSIVO   Remetente PASSIVO
     │                  │                    ┊                   ┊
     ▼                  ▼                    ┊ (msg já na fila)  ┊ (fila guarda)
   [fila]             [fila]               [fila]              [fila]
     │                  ┊                    │                   ┊
     ▼                  ┊                    ▼                   ┊
Receptor EXEC.     Receptor PASSIVO    Receptor EXEC.      Receptor PASSIVO
```

* **(a)** remetente e destinatário em execução durante toda a transmissão.
* **(b)** só o remetente executa; o destinatário está passivo (entrega impossível agora), mas o remetente **ainda pode enviar**.
* **(c)** o destinatário pode ler mensagens que lhe foram enviadas, **sem que os remetentes precisem estar em execução**.
* **(d)** o sistema **armazena (e possivelmente transmite) mensagens** mesmo com remetente e destinatário passivos.

---

#### 5. Chamada de Procedimento Remoto (RPC)

* **Definição** (Birrell e Nelson, 1984): "permite a processos **chamar procedimentos localizados em outras máquinas**".
* **Motivação:** obter **transparência de acesso** em SDs, o que **não** ocorre com o uso das primitivas `send` e `receive`.
  * Um processo da máquina A chama um procedimento da máquina B.
  * O processo A é **suspenso** e o procedimento é executado em B.
  * Informação viaja nos **parâmetros** e no **resultado**.
  * **Nenhum aspecto da troca de mensagens é visível** para o programador!

##### Stubs (a "mágica" da transparência)

* **Stub do cliente:** versão "falsa" do procedimento que fica na biblioteca do cliente. Em um sistema tradicional, `read` é um procedimento que faz uma chamada de sistema ao SO; com RPC, uma **versão diferente do `read`** é colocada na biblioteca. Ela **empacota (marshalling) os parâmetros** em uma mensagem, pede o envio ao servidor, faz o `send` e o `receive`, e **bloqueia até a resposta voltar**. Ao chegar, copia o resultado e devolve o controle ao cliente.
* **Stub do servidor:** quando a mensagem chega, o SO do servidor a repassa ao stub do servidor, que **transforma requisições vindas da rede em chamadas de procedimento locais**: **desempacota** os parâmetros, executa o procedimento do servidor e, ao receber o resultado, **empacota** os dados e envia ao stub do cliente.

##### As 10 etapas do RPC

```
 CLIENTE                                                        SERVIDOR
┌──────────────────┐                                      ┌──────────────────┐
│ 1. Procedimento  │                                      │ 5. Stub servidor │
│    cliente chama │                                      │    desempacota   │
│    o stub        │                                      │    parâmetros e  │
│ 2. Stub cliente  │                                      │    chama serviço │
│    monta msg e   │                                      │ 6. Servidor faz  │
│    chama SO      │                                      │    o serviço e   │
│ 3. SO cliente ───┼──────── mensagem (requisição) ─────► │    devolve ao stub│
│    envia ao SO   │            4. SO remoto entrega      │ 7. Stub empacota │
│    remoto        │               ao stub do servidor    │    resultado e   │
│ 9. SO cliente    │ ◄─────── mensagem (resposta) ─────── │    chama SO      │
│    entrega ao    │            8. SO servidor envia      │                  │
│    stub          │               ao SO do cliente       │                  │
│10. Stub          │                                      │                  │
│    desempacota e │                                      │                  │
│    retorna ao    │                                      │                  │
│    cliente       │                                      │                  │
└──────────────────┘                                      └──────────────────┘
```

1. O procedimento do cliente chama o stub do cliente do modo normal.
2. O stub do cliente constrói uma mensagem e chama o SO local.
3. O SO do cliente envia a mensagem para o SO remoto.
4. O SO remoto dá a mensagem ao stub do servidor.
5. O stub do servidor desempacota os parâmetros e chama o serviço.
6. O servidor faz o serviço e retorna o resultado para o stub.
7. O stub do servidor empacota o resultado em uma mensagem e chama o SO local para solicitar envio ao SO do cliente.
8. O SO do servidor envia a mensagem ao SO do cliente.
9. O SO do cliente dá a mensagem ao stub do cliente.
10. O stub desempacota o resultado e retorna ao cliente.

##### RPC síncrona x assíncrona

* **RPC síncrona:** **bloqueia o cliente** até o servidor terminar de processar e retornar a resposta.

```
Cliente  ━━━━━━━━┓- - - Wait for result - - - ┏━━━━━━━━►
          Call remote  │ Request      Reply │  Return
          procedure    ▼              ▲     │  from call
Servidor - - - - - - - ┗━━━━━━━━━━━━━┛ - - - - - - - ► tempo
                       Call local procedure and return results
```

* **RPC assíncrona:** **não bloqueia o cliente** enquanto o servidor processa. O cliente aguarda apenas a **confirmação de que o servidor recebeu** a requisição e pode fazer trabalho útil nesse ínterim. Ao receber a resposta, o cliente executa uma **rotina de callback** (pós-processamento).
  * **Exemplo dos slides (e-commerce):** o serviço de compra pede ao serviço da instituição financeira do cartão a transação de pagamento; enquanto a financeira processa, o serviço de compra **trata outras compras concorrentes**; a financeira responde se o pagamento foi autorizado ou não; então o serviço de compra **conclui a compra ou informa o usuário que o pagamento foi recusado** (pós-processamento via callback).
  * **RPC de uma via (one-way):** o cliente **nem espera a confirmação** de recebimento. Quando a confiabilidade não é garantida, o cliente **não sabe se a requisição será processada**.
* **Onde difere nas 10 etapas?** (gabarito, Q8) Na RPC **síncrona** o SO do cliente **bloqueia o cliente na etapa 3 até a resposta chegar na etapa 9**. Na **assíncrona** o cliente **não é bloqueado** e o stub do cliente **retorna para uma rotina de callback na etapa 10**.

##### Dificuldades em RPC

* Chamador e procedimento rodam em **máquinas diferentes**, em **espaços de endereço diferentes**.
* Passar parâmetros e resultados é complicado entre máquinas diferentes (**big endian x little endian**, arquiteturas 32/64 bits etc.). **Solução dos slides:** o cliente **informa seu tipo** e a **conversão é feita pelo servidor** se os tipos forem diferentes.
* **Qualquer uma das duas máquinas pode falhar**, e cada falha causa problemas diferentes.
* Mesmo assim, RPC é amplamente usada em SD. **Em aplicações Web, RPC perdeu espaço para REST**; **novos frameworks de RPC (ex.: gRPC) disputam espaço com REST**.

##### Passagem de parâmetros por referência

* **Problema:** um **ponteiro só faz sentido dentro do espaço de endereço do processo** que o usa. Com memória distribuída, cada nó tem espaço de endereçamento diferente.
* **Solução:** **copiar o conteúdo apontado** e enviá-lo ao servidor; quando o servidor retorna, o conteúdo original no cliente é **substituído** (**copiar/restaurar**). Tem o mesmo efeito da chamada por referência (o parâmetro é modificado ao fim).
* **Complicação:** é difícil quando o parâmetro é o endereço do início de um vetor ou de uma estrutura complexa (lista encadeada, árvore, grafo...). Uma saída é **gerar código especial no servidor que resolve ponteiros fazendo requisições ao cliente**, com **impacto no desempenho**.

##### Especificação de parâmetros, protocolos e IDL

* É preciso **definir o formato da mensagem** para que chamador e chamado sigam as mesmas etapas, e **ambos devem concordar nas definições de tipo** (ex. dos slides: `char` = Unicode 16 bits; `int` = complemento de dois; `float` = IEEE 754; *little endian*...). Também é preciso definir o **protocolo de comunicação**. Só depois se implementam os stubs.
* **IDL (Interface Definition Language):** linguagem usada para **especificar a interface** (o que o cliente chama e o servidor implementa). A interface escrita em IDL é **compilada** para gerar o **stub do cliente** e o **stub do servidor**.
  * Suporta **geração de stubs para várias linguagens**: cliente e servidor podem ser escritos em **linguagens diferentes**.
  * Simplifica as aplicações cliente-servidor baseadas em RPC; middlewares baseados em RPC **oferecem uma IDL**.
  * (gabarito, Q10) Os stubs gerados tratam **a conversão de dados e a comunicação** entre cliente e servidor.

```
Fluxo de geração (figura do slide 24)

      [ Arquivo de definição de interface (IDL) ]
                          │
                   [ Compilador IDL ]
        ┌───────────┬─────┴──────┬────────────┐
   Stub cliente   Header      Stub servidor    (o Header é incluído - #include -
        │        (compartilhado)     │          tanto pelo código do cliente
 Código cliente ─┘                   └─ Código servidor     quanto pelo do servidor)
        │  compilador C                     │  compilador C
        ▼                                   ▼
 obj. cliente + obj. stub cliente    obj. servidor + obj. stub servidor
        │  + biblioteca de runtime          │  + biblioteca de runtime
        ▼  (linker)                         ▼  (linker)
   Binário do CLIENTE                 Binário do SERVIDOR
```

---

#### 6. Comunicação Orientada a Mensagem

* **Pergunta-guia dos slides:** o que fazer quando **não se pode supor que o receptor esteja em execução** quando a requisição é emitida? Resposta: usar modelos em que mensagens possam ser trocadas **estando ou não os processos em funcionamento**, com **armazenamento para tratamento posterior**.
* Muitos SDs são construídos sobre o modelo simples orientado a mensagem **da camada de transporte**; algumas interfaces de transporte foram padronizadas (ex.: **Berkeley Sockets**).

##### 6.1 Sockets (Berkeley Sockets)

* **Socket:** terminal de comunicação no qual a aplicação lê/escreve dados que serão recebidos/enviados pela rede subjacente. É uma abstração de ponto de comunicação.
* **Orientado a conexão:** **TCP**. **Sem conexão:** **UDP**.
* Adotam o paradigma **cliente-servidor** e oferecem comunicação **transiente**.

| Operação (TCP) | Descrição (slides) |
|---|---|
| `socket` | Cria um novo ponto de comunicação |
| `bind` | Associa um endereço local ao socket |
| `listen` | Informa ao SO o número máximo de requisições de conexão pendentes |
| `accept` | Bloqueia o chamador até chegar uma requisição de conexão |
| `connect` | Tenta ativamente estabelecer uma conexão |
| `send` | Envia dados pela conexão |
| `receive` | Recebe dados pela conexão |
| `close` | Libera a conexão |

```
        SERVIDOR TCP                                   CLIENTE TCP
 socket() ─► bind() ─► listen() ─► accept()  ◄─────── socket() ─► connect()
                                      │  (conexão estabelecida)         │
                         recv() ◄─────┼─────────── send() ◄─────────────┤
                         send() ──────┼──────────► recv()               │
                         close() ◄────┴──────────► close()
```

* **Exemplo dos slides (Python, TCP):** o servidor cria o socket, faz `bind`, `listen(1)`, `accept`, e em loop `recv(1024)` e devolve os dados com um `"*"` anexado; o cliente faz `connect`, `send('Hello, world')`, `recv`, imprime e fecha.
* O exemplo **aceita uma única conexão**. Para várias, `accept()` deve ficar **dentro de um loop**.
  * **Servidor iterativo:** trata **uma conexão por vez**; as demais ficam pendentes aguardando o próximo `accept()`.
  * **Servidor concorrente:** aceita novas conexões sem terminar a anterior, **delegando a troca de mensagens a uma thread separada** e chamando `accept()` para os pedidos pendentes.
* **UDP:** `socket()` (cria e aloca recursos), `bind()` (associa a IP local + porta), `sendto()` e `recvfrom()` (enviam/recebem dados) e `close()` (libera recursos). Não há `listen`/`accept`/`connect`: cada datagrama é enviado com o endereço de destino.

##### 6.2 ZeroMQ

* Como em Berkeley, o ZeroMQ fornece **sockets** pelos quais toda a comunicação ocorre, mas **a configuração e manutenção das conexões são em grande parte gerenciadas internamente**: um socket pode ser **vinculado a vários endereços**, permitindo que um servidor lide com mensagens de fontes muito diferentes por uma única interface.
  * Ex.: um servidor escuta em várias portas com **uma única operação de recebimento bloqueante** → comunicação **muitos-para-um** (não só um-para-um, como em Berkeley).
  * Também suporta **um-para-muitos (multicasting)**.
* **Nível mais alto de abstração:** os sockets **não precisam chamar `listen` nem `accept`**; há **sockets específicos para cada padrão de comunicação**.
* **Importante (gabarito, Q12):** o ZeroMQ **só suporta mensagens transientes e não possui broker**.
* **Os 4 padrões mais importantes:** **par**, **requisição-resposta**, **publica-subscreve** e **pipeline**.

```
 PAR (PAIR-PAIR)          REQ-REP                 PUB-SUB                  PIPELINE (PUSH-PULL)
 ┌──────┐   ┌──────┐   ┌─────┐    ┌─────┐      ┌─────┐   ┌─────┐       ┌────────┐  ┌───────┐
 │ PAIR │◄─►│ PAIR │   │ REQ │───►│ REP │      │ PUB │──►│ SUB │       │Produtor│  │Consum.│  ┌────────┐
 └──────┘   └──────┘   │     │◄───│     │      │     │──►│ SUB │       │  PUSH  ├─►│PULL PUSH├─►│ PULL   │
 bidirecional,         └─────┘    └─────┘      │     │──►│ SUB │       │        ├─►│PULL PUSH├─►│(coletor│
 só 1 par conectado    1 req → 1 resp          └─────┘   └─────┘       └────────┘  └───────┘     │de result.)
                       alternado               1 → N (só quem assinou)   round-robin ──► downstream
```

* **Par (PAIR):** comunicação **bidirecional**; **nenhum estado específico** armazenado no socket; **apenas um par conectado**; o servidor escuta em uma porta e um cliente se conecta; cada lado pode enviar **qualquer número de mensagens** ao outro.
* **Requisição/Resposta (REQ/REP):**
  * Sockets `REQ` podem se conectar a **vários servidores**; as requisições são **intercaladas/distribuídas** entre eles.
  * Quando o cliente chama `recv` após enviar, o ZeroMQ assume que ele aguarda a resposta **do destinatário original**.
  * Tentar enviar **outra** mensagem sem ter recebido a resposta da anterior **gera erro**.
  * `REQ` **bloqueia ao enviar** a menos que tenha recebido resposta com sucesso; `REP` **bloqueia ao receber** a menos que tenha recebido uma requisição.
  * Exemplo dos slides: o servidor (`REP`, `bind` em `tcp://*:12345`) responde acrescentando `*` e para ao receber "STOP"; o cliente (`REQ`, `connect` em `tcp://localhost:12345`) envia "Hello world", recebe a resposta e depois envia "STOP".
  * *Obs.:* o slide cita `zmq.PAIR` dentro dessa seção; trata-se do padrão PAIR já visto, não do REQ/REP.
* **Publica/Subscreve (PUB/SUB):**
  * O servidor usa socket **PUB**; cada cliente usa socket **SUB**.
  * Os clientes **se inscrevem em mensagens específicas** e **só recebem o que assinaram**.
  * Se o servidor publica mensagens que **ninguém assinou, elas são perdidas**.
  * **Por padrão, o cliente não se inscreve em nada**: sem assinatura explícita, **não recebe nada**.
  * Exemplo dos slides: o servidor publica `"TIME " + hora` a cada 5 s; o cliente `SUB` faz `setsockopt(zmq.SUBSCRIBE, b"TIME")` e recebe 5 mensagens.
* **Pipeline (PUSH/PULL):**
  * Distribui mensagens para **vários trabalhadores organizados em pipeline**.
  * O socket **Push distribui as mensagens aos clientes Pull de forma equilibrada (round-robin)**.
  * Os resultados calculados **não voltam para cima**, e sim **para baixo**, para outro socket Pull (o coletor de resultados).
  * Exemplo dos slides (produtor-trabalhador): o produtor gera cargas aleatórias e as envia por `PUSH`; cada worker (`PULL`) recebe o trabalho e "finge" executá-lo.

##### 6.3 MPI (Message-Passing Interface)

* **Origem:** sockets são **insuficientes para escrever com facilidade aplicações de alto desempenho**: só oferecem primitivas simples (`send`/`receive`), geram código mais complexo, pedem abstração mais alta e são inadequados para os **protocolos proprietários de redes de alta velocidade** (como em **clusters**). Era preciso lidar com formas de **bufferização e sincronização** e criar um **padrão para compatibilidade entre fabricantes**.
* **Características:** padrão de comunicação para **aplicações paralelas de alto desempenho em memória distribuída**; **portabilidade**; comunicação **transiente**; **não tolera falhas** (falha de rede ou término incorreto de processo é **fatal**); abstrações de alto nível e eficientes; é **a biblioteca mais popular** para programas paralelos de alto desempenho com troca de mensagens.
* **Grupos e identificadores:** a comunicação ocorre dentro de um **grupo conhecido de processos**; cada grupo tem um `groupID` e cada processo um `processID`; o par `(groupID, processID)` identifica **fonte ou destinatário**. Vários grupos podem executar ao mesmo tempo.
* **As 6 funções principais:**

| Função | O que faz |
|---|---|
| `MPI_Init(&argc,&argv)` | Inicializa os processos MPI; **primeira** função MPI chamada por cada processo (não precisa ser o primeiro comando) |
| `MPI_Finalize()` | Finaliza a computação; **última** função MPI de cada processo; o sistema libera as estruturas MPI |
| `MPI_Comm_Size(MPI_COMM_WORLD,&p)` | Retorna o **número de processos** |
| `MPI_Comm_Rank(MPI_COMM_WORLD,&pid)` | Retorna o **identificador (rank)** do processo |
| `MPI_Send(dado, cont, tipo, destino, tag, comm)` | Envia mensagem |
| `MPI_Recv(dado, cont, tipo, origem, tag, comm, status)` | Recebe mensagem |

* **Comunicador:** universo de processos envolvidos em uma comunicação. O padrão é `MPI_COMM_WORLD`; novos comunicadores são definidos por **grupo** (conjunto ordenado de processos) e **contexto** (tag da mensagem). Só processos do **mesmo grupo e contexto** se comunicam.
* **Parâmetros de send/recv:** `dado` (ponteiro p/ início do dado), `cont` (nº de elementos), `tipo` (`MPI_Datatype`: `MPI_CHAR`, `MPI_INT`, `MPI_LONG`, `MPI_FLOAT`, `MPI_DOUBLE`), `destino/origem` (rank), `tag` (etiqueta da mensagem), `comm` (comunicador), `status` (verifica o estado da mensagem). Curingas: `MPI_ANY_SOURCE` e `MPI_ANY_TAG`.
* **Exemplo dos slides:** `MPI_Send(&dado,1,MPI_INT,i,1,MPI_COMM_WORLD);` e `MPI_Recv(&dado,1,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,&status);`
* **Várias opções de envio/recebimento (slide 52):** `MPI_bsend` (anexa a mensagem a um buffer local de envio), `MPI_send` (envia e espera cópia para buffer local ou remoto), `MPI_ssend` (envia e espera a transmissão começar), `MPI_sendrecv` (envia e espera resposta), `MPI_isend` (passa referência da mensagem e continua), `MPI_issend` (passa referência e espera o recebimento começar), `MPI_recv` (recebe; bloqueia se não houver) e `MPI_irecv` (verifica se há mensagem, **sem bloquear**). O MPI tem **mais de 600 operações**; é importante entender a diversidade para **escolher a mais eficiente** em cada cenário.

---

#### 7. Middleware Orientado a Mensagens (MOM) / Sistemas de Enfileiramento

* **MOM** (*Message-Oriented Middleware*) = **sistema de enfileiramento de mensagens** (*message-queuing systems*). Proporciona **comunicação assíncrona persistente**.
* Oferece **armazenamento de médio prazo** das mensagens, sem exigir que remetente ou receptor estejam ativos durante a transmissão. A tolerância para envio e recepção pode ser de **minutos** em vez de segundos ou milissegundos.
* **Como funciona:** aplicações se comunicam **inserindo mensagens em filas específicas**; as mensagens são **repassadas por uma série de servidores de comunicação** e **entregues ao destinatário mesmo que ele não estivesse ativo no envio**. **Cada aplicação tem sua fila particular** onde outras aplicações depositam mensagens; uma vez depositada, **a mensagem permanece na fila até ser removida**, independentemente de remetente ou receptor estarem em execução.
* **Garantia (e limite):** o remetente só tem a garantia de que, em algum momento, **a mensagem será inserida na fila do receptor**. **Não há garantia de QUANDO ou SE será lida**; isso depende do destinatário. É uma comunicação **fracamente acoplada no tempo**.
* **Mensagens e endereçamento:** podem conter **qualquer tipo de dado** e devem ser **adequadamente endereçadas**, com o **nome exclusivo da fila de destino** no âmbito do sistema.
* **Interface básica (muito simples):**

| Primitiva | Comportamento |
|---|---|
| `put` | Anexa uma mensagem à fila especificada |
| `get` | **Bloqueia** até a fila ficar não vazia e **retira a primeira** mensagem |
| `poll` | Verifica a fila e retira a primeira mensagem, **se houver; nunca bloqueia** |
| `notify` | Instala um **manipulador (callback)** chamado quando uma mensagem é colocada em uma fila |

##### Arquitetura geral de um sistema de filas (gabarito, Q13)

```
 Remetente A                                                       Receptor B
┌────────────────┐        ┌────────┐     ┌────────┐        ┌────────────────┐
│  Aplicação     │        │ Repass.│     │ Repass.│        │  Aplicação     │
│  [fila receb.] │◄──────►│   R1   │────►│   R2   │◄──────►│  [fila receb.] │
│  [fila envio ]─┼───────►│ (filas)│     │ (filas)│        │  [fila envio ] │
└────────────────┘        └───┬────┘     └────────┘        └────────────────┘
      ▲ gerenciador de fila   │  repassadores = "roteadores" de mensagens
      │ (processo separado ou biblioteca)  └──────► outros gerenciadores de fila
```

* **Fila de fonte:** fila **local do remetente**, na qual ele envia a mensagem.
* **Fila de destino:** a mensagem colocada em uma fila contém a **especificação da fila de destino** para a qual deve ser transferida.
* **Gerenciadores de fila:** interagem **diretamente com a aplicação** que envia/recebe a mensagem. Podem ser um **processo separado** ou uma **biblioteca vinculada à aplicação**. (Slide 62: o gerenciador de fila de origem consulta um **banco de endereços** para achar o **endereço de contato** do gerenciador de destino e envia pela rede ao endereço lógico/nome da fila.)
* **Repassadores (relays):** repassam mensagens que chegam a outros gerenciadores de fila (**roteadores**).
* **Para que servem os repassadores:**
  * ajudam a construir sistemas de filas **escaláveis**;
  * permitem **processamento secundário** da mensagem (registrar mensagens por **segurança e tolerância a falhas**);
  * podem ser usados para **multicasting**;
  * em muitos sistemas **não há serviço de nomes** para mapear dinamicamente fila→localização. Solução: alguns repassadores **conhecem a topologia**; **atualizações de remoção/adição de filas são feitas só nos repassadores**, e os outros gerenciadores só precisam saber **onde está o repassador mais próximo**.

##### Message Broker

* Problema: aplicações de um SD podem ser muito **diversas**; mensagens entre remetente e receptor podem ter **formatos diferentes**.
* O **message broker** é o **intermediário entre produtores e consumidores** (gabarito, Q17): **gerencia o roteamento, o armazenamento temporário e a entrega** das mensagens e **converte mensagens**, permitindo que serviços interdependentes "conversem" diretamente, usando um **repositório de regras e plugins** de conversão.

```
 FONTE                 MESSAGE BROKER                     DESTINO
┌──────────┐     ┌──────────────────────────┐     ┌──────────────┐
│Aplicação │     │ [plugins] ...  [Regras]  │     │ Aplicação    │
│ Interface│     │        conversão         │     │  Interface   │
│  [fila]──┼────►│ camada de filas ──[fila]─┼────►│   [fila]     │
│ SO local │     │       SO local           │     │  SO local    │
└──────────┘     └──────────────────────────┘     └──────────────┘
                      (figura 4.28 do slide 66)
```

---

#### 8. AMQP (Advanced Message Queuing Protocol)

* **Por que surgiu:** sistemas de fila foram criados em parte para dar **interoperabilidade a aplicativos legados**, mas, entre **diferentes sistemas de fila**, aparecem obstáculos: quem escolhe o sistema do fabricante X pode ficar **restrito a soluções de X**; as soluções são, em grande parte, **proprietárias**. Em **2006** formou-se um grupo de trabalho que resultou na especificação do **AMQP**.
* **O que é** (gabarito, Q14): um protocolo que **padroniza as operações de um sistema de fila de mensagens**, garantindo **interoperabilidade** entre implementações diferentes. Segundo os slides, o AMQP é: **um serviço de mensagens**, **o protocolo de mensagens** e **a interface de mensagens** oferecida às aplicações.
* Gira em torno de **aplicativos, gerenciadores de filas e filas**. Um único gerenciador de filas roda como **servidor separado** e oferece o AMQP como serviço; o aplicativo fala com ele por **interface local** (o **stub AMQP**), e a comunicação aplicativo ↔ gerenciador segue o protocolo AMQP.

```
(figura 4.29 do slide 71 - uma instância AMQP de servidor único)

┌────────────────────┐   AMQP queuing (nível lógico)    ┌──────────────────────┐
│ Aplicação          │◄────────────────────────────────►│ Gerenciador de filas │
│  [mensagem]        │                                  │    [fila][fila]      │
│  Interface         │   AMQP communication (stubs)     │      Interface       │
│  Stub AMQP ────────┼◄────────────────────────────────►│      Stub AMQP       │
│  SO local          │          TCP/IP                  │      SO local        │
└────────┬───────────┘◄────────────────────────────────►└──────────┬───────────┘
         └────────────────────── rede ─────────────────────────────┘
```

##### Conexões, canais, sessões e links (gabarito, Q15)

* O AMQP permite estabelecer uma **conexão** com um gerenciador de filas; a conexão é um **contêiner para vários canais unidirecionais**. O AMQP **pressupõe TCP** para estabelecer conexões.
* A vida útil de um **canal** pode ser muito dinâmica; as **conexões** são **relativamente estáveis**.
* A **comunicação bidirecional** vem das **sessões**: **agrupamento lógico de dois canais**. Uma conexão pode ter **várias sessões**, mas **um canal não precisa fazer parte de uma sessão**.
* Para **transferir mensagens de fato** é necessário um **link**. Seus *endpoints* acompanham o **status das mensagens em transferência**.
* **Controle de fluxo por créditos:** o receptor informa ao remetente **quantas mensagens** ele pode enviar.

```
(figura do slide 70)
Container ─────────────────────────────────────────────── Container
 (saída)  ┌────────────── CONEXÃO (TCP) ────────────────┐   (entrada)
          │  canal CH0  ◄───────────────────────────►   │
          │  canal CH1  ◄───────────────────────────►   │
          │   ┌────── SESSÃO (2 canais = bidirecional) ──┐
          │   │ CH2 ◄──────────────────────────────►     │
          └───┴──────────────────────────────────────────┘
 Conexão = contêiner de canais unidirecionais | Sessão = 2 canais | Link = transferência + créditos
```

##### Os 3 passos da transferência de mensagem (gabarito, Q16)

Quando uma mensagem precisa ser transferida, o aplicativo a envia ao **stub local do AMQP**. Os estados relevantes são **não resolvido** e **resolvido**.

```
   REMETENTE (stub)                                   RECEPTOR (stub)           Gerenciador de filas (app receptora)
PASSO 1
 mensagem ganha ID único
 estado: NÃO RESOLVIDO ───────── transfere msg ───►  registra: NÃO RESOLVIDO ──► entrega a msg
PASSO 2                                                                         processa e avisa "concluí"
 estado: RESOLVIDO  ◄──── informa que concluiu ───── stub receptor ◄────────────┘
PASSO 3
 "transferência RESOLVIDA" ──────────────────────►  descarta informações da msg
 (remetente ESQUECE a msg)                           e registra: RESOLVIDA
```

* **Passo 1:** no stub do remetente, a mensagem recebe um **identificador único** e é registrada como **não resolvida**. O stub do remetente a transfere ao stub do receptor, que também a registra como **não resolvida**. O stub do receptor passa a mensagem ao gerenciador de filas (aplicação receptora).
* **Passo 2:** o aplicativo receptor (aqui, o gerenciador de filas) **assume o processamento** e normalmente informa ao seu stub que **concluiu**. O stub repassa a informação ao remetente original, e a mensagem no stub do remetente passa ao estado **resolvido**.
* **Passo 3:** o stub do remetente informa ao stub do receptor que a transferência foi **resolvida** (o remetente **esquecerá** a mensagem daí em diante). O stub do receptor pode **descartar** qualquer informação sobre a mensagem e registrar formalmente que ela também foi resolvida.
* **Conclusão dos slides:** como o aplicativo receptor pode indicar ao AMQP que **concluiu o processamento**, o AMQP possibilita **confiabilidade real de ponta a ponta**.

##### Troca de mensagens no AMQP

* Ocorre logicamente **em uma camada acima** da que lida com a comunicação. Formalmente, ocorre entre **dois nós**, de **três tipos**: **produtor**, **consumidor** ou **fila**. Produtores e consumidores costumam ser aplicações comuns; **filas armazenam e encaminham** mensagens. Um gerenciador de filas costuma ter **vários nós de fila**.
* O receptor pode indicar ao remetente se a mensagem foi **aceita** (processada com sucesso) ou **rejeitada**; isso significa que **uma notificação volta ao remetente original**.
* Suporta **fragmentação e montagem de mensagens grandes** (com notificações adicionais).
* **Mensagens persistentes (duráveis):** uma mensagem pode ser marcada como **durável**, indicando que a fonte espera que **qualquer nó intermediário, como uma fila, consiga se recuperar após falha**. **Um nó intermediário que não pode garantir a durabilidade rejeita a mensagem.**
* O AMQP é **verdadeiramente um protocolo de troca de mensagens**: **não oferece primitivas de publicação e assinatura** (publish/subscribe), que ficam para **gerenciadores de fila especializados**.
* É comum ligar gerenciadores de fila entre si, formando uma **rede sobreposta (overlay)** em que as mensagens são roteadas de produtores a consumidores. O AMQP **não especifica como construir e gerenciar** essa rede (cada fornecedor faz do seu jeito), mas é importante especificar como as mensagens são **roteadas**.

---

#### 9. RabbitMQ

* Uma das **implementações mais populares do AMQP**. **Baseado na versão 0.9** do AMQP, mas com **suporte total à versão 1.0**.
* **Diferença importante entre as duas versões: o uso de _exchanges_.** Em vez de manipular filas diretamente, **o produtor fala com uma exchange**, que **coloca a mensagem em uma ou várias filas**.
* Em essência, a exchange permite que o produtor use **uma RPC síncrona ou assíncrona** para um gerenciador de filas.
* **Uma exchange nunca armazena mensagens**: ela só garante que a mensagem seja colocada **na(s) fila(s) apropriada(s)**.

```
(figura do slide 80)

 PRODUCER ──► ┌──────────────────────── BROKER (RabbitMQ) ───────────────────────────┐
              │  EXCHANGE:  [Direct]        [Topic]              [Fanout]            │
              │                │               │  │                │  │  │           │
              │  BINDINGS:  Binding Key   Routing Pattern          (sem chave)        │
              │             "PDF process"  "eu.de.*"   "us.#"                         │
              │                ▼              ▼         ▼             ▼  ▼  ▼           │
              │  QUEUES:   [Queue 1]    [Queue 2]    [Q3]          [Q4] [Q5] [Q6]     │
              └────────────────────────────┬───────────────────────────────────────────┘
                                           ▼
                                      CONSUMER
```

##### Tipos de exchange

| Tipo | Como roteia | Regra de chave | Observação dos slides |
|---|---|---|---|
| **Fanout** (troca de emissão) | Para **todas as filas vinculadas** a ela | **Ignora completamente** a chave de roteamento | É o "broadcast" |
| **Direct** (troca direta) | Para filas com base em uma **chave de roteamento** | A chave da mensagem deve **corresponder exatamente** à da vinculação | Se **várias filas** se associam à **mesma chave**, funciona **como fanout** |
| **Topic** (troca de tópico) | Para filas com base em **padrões** de chave de roteamento | A fila é vinculada com chave que inclui **padrões (`*`, `#`, ...)** | Se a chave casa com o padrão de **várias filas**, funciona **como fanout** |

```
FANOUT                  DIRECT (chave exata)                 TOPIC (padrão)
msg(qualquer chave)     msg(chave="pdf")                     msg(chave="eu.de.berlin")
      │                       │                                    │
  ┌───▼───┐              ┌────▼────┐                          ┌────▼────┐
  │fanout │              │ direct  │                          │  topic  │
  └─┬─┬─┬─┘              └─┬─────┬─┘                          └─┬─────┬─┘
    ▼ ▼ ▼                  ▼     ✗                              ▼     ✗ (us.# não casa)
  Q4 Q5 Q6  (todas)      Q1("pdf") Q2("img")                 Q2("eu.de.*")  Q3("us.#")
```

* **(complemento) Significado dos curingas no topic:** `*` casa com **exatamente uma palavra**; `#` casa com **zero ou mais palavras** (as palavras são separadas por ponto). No exemplo da figura, `eu.de.*` e `us.#` são padrões de vinculação.
* **(complemento) Outros pontos que você poderá demonstrar no RabbitMQ** (não aparecem nos slides): existe também a **exchange padrão (default)** e a de tipo **headers**; a confirmação de processamento do consumidor é feita por **ACK** (*acknowledgement*), e sem ACK a mensagem pode ser reenviada ou perdida conforme o modo; mensagens duráveis exigem **fila durável + mensagem marcada como persistente**.

---

### 🔍 Tópico em Destaque

#### A) RPC x MOM (filas): duas formas de "falar" entre processos

| Aspecto | RPC | MOM (filas / RabbitMQ) |
|---|---|---|
| Ideia | Chamar um procedimento remoto como se fosse local | Depositar mensagens em filas e deixar o middleware entregar |
| Transparência | Esconde a troca de mensagens (stubs) | **Não** esconde: o programador usa `put/get/poll/notify` |
| Sincronismo típico | Síncrona (existe também a assíncrona com callback) | **Assíncrona** |
| Persistência | Em geral **transiente** (depende do receptor ativo) | **Persistente** (armazenamento de médio prazo) |
| Acoplamento no tempo | **Forte** | **Fraco** |
| Contrato | **IDL** → gera stubs | Formato da mensagem + nome/rota da fila |
| Gabarito, Q3 | Persistente assíncrona **por RPC** só faz sentido **salto a salto**: um gerenciador de fila passa a mensagem ao próximo por RPC (o serviço de um gerenciador ao outro é "guardar a mensagem") | |

#### B) ZeroMQ x RabbitMQ (gabarito, Q12)

| | ZeroMQ | RabbitMQ |
|---|---|---|
| Tipo | Biblioteca de **sockets** de alto nível | **Broker** (servidor) com filas e exchanges (AMQP) |
| Persistência | **Só transiente** | Pode ser **persistente** (mensagens duráveis) |
| Broker | **Não tem** | **Tem** (intermedia a comunicação) |
| Desacoplamento | Menor (ambos precisam estar ativos) | **Temporal e referencial** (o remetente não precisa conhecer o destino nem que ele esteja ativo) |
| Padrões | PAIR, REQ/REP, PUB/SUB, PUSH/PULL | Fanout, direct, topic (via exchanges) |

#### C) Como as peças da aula se encaixam no RabbitMQ

```
Aplicação produtora ─► stub AMQP ──(AMQP/TCP)──► [Exchange] ─(binding)─► [Fila durável] ─► stub AMQP ─► Aplicação consumidora
        │                                          ▲ nunca guarda msg        ▲ guarda (persistente)         │
        └─ marca msg como durável (AMQP)           └ regras fanout/direct/topic                             └ informa "concluí" → msg RESOLVIDA
```

* **MOM** = a ideia de filas e comunicação assíncrona persistente.
* **Message broker** = o servidor RabbitMQ (rotear, guardar temporariamente, entregar).
* **AMQP** = o protocolo padrão (conexões, canais, sessões, links, estados não resolvido/resolvido, mensagens duráveis).
* **Exchange** = a peça do RabbitMQ que decide para qual fila a mensagem vai.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Persistente/transiente x síncrona/assíncrona são eixos independentes.** Não confunda "quem guarda a mensagem" com "quem fica bloqueado".
> ---
> 💡 **Sockets e ZeroMQ e MPI são transientes; MOM (filas) é persistente.** Esse contraste é a base para comparar ZeroMQ x RabbitMQ.
> ---
> 💡 **Exchange nunca armazena mensagens.** Quem guarda é a **fila**. A exchange só roteia.
> ---
> 💡 **Direct e topic podem "virar fanout"** quando várias filas se vinculam à mesma chave (direct) ou a padrões que casam com a mesma chave (topic).
> ---
> 💡 **No AMQP, "resolvido" significa que o receptor concluiu o processamento**, e não apenas que recebeu. É isso que dá **confiabilidade de ponta a ponta**.
> ---
> 💡 **Garantia limitada do MOM:** o remetente só sabe que a mensagem vai entrar na fila do receptor; **não há garantia de quando ou se será lida**.
> ---
> 💡 **Mensagem durável exige nós intermediários capazes de se recuperar de falhas.** Se o nó não pode garantir isso, ele **rejeita** a mensagem.
> ---
> 💡 **AMQP não faz publish/subscribe por si só:** isso fica para gerenciadores de fila especializados (no RabbitMQ, os exchanges fanout/topic cumprem esse papel).
> ---
> 💡 **Erros de digitação nos slides:** aparece "AMPQ" em alguns títulos; o correto é **AMQP**. O slide de REQ/REP cita `zmq.PAIR` por engano.
> ---
> 💡 **(complemento) Para o vídeo do trabalho:** cada demo deve mostrar o conceito teórico em ação (stub/IDL no gRPC; exchange e binding no RabbitMQ; ACK e durabilidade). Cite o termo da aula na narração; isso rende pontos na parte teórica.

---

### 🧪 Exercícios e Gabarito Comentado

Resumo, em linguagem simples, das 17 questões do arquivo `Aula06-gab.md`.

**Q1. Por que os protocolos em camadas não usam um único cabeçalho com todo o controle (em vez de um por camada)?**
Resposta: porque cada camada precisa ser **independente**. A camada *k* recebe da *k+1* "cabeçalho + dados" e **não sabe separar** um do outro. Um cabeçalho único, lido e escrito por todas, **quebraria essa independência**, e mudar uma camada afetaria as outras.

**Q2. Por que serviços de comunicação do nível de transporte costumam ser inadequados para construir aplicações distribuídas?**
Resposta: eles quase **não oferecem transparência de distribuição**. O programador tem de cuidar da comunicação na mão, o que gera **soluções proprietárias**, difíceis de **portar** e de **interoperar** (ex.: aplicações feitas direto com sockets).

**Q3. Faz sentido implementar comunicação assíncrona persistente por meio de RPCs?**
Resposta: **sim, mas só salto a salto**: um gerenciador de fila passa a mensagem ao próximo gerenciador por uma RPC. O "serviço" que um gerenciador presta ao outro é **guardar a mensagem**, e ele pode receber um status de sucesso/falha. Assim, os gerenciadores só enxergam filas, nada além disso.

**Q4. Por que a comunicação síncrona transiente tem problemas inerentes de escalabilidade?**
Resposta: por causa da **escalabilidade geográfica limitada**. Como o remetente fica **bloqueado** até a mensagem ser recebida, se o receptor estiver **longe** o remetente pode esperar muito antes de continuar.

**Q5. Diferencie comunicação persistente e transiente.**
Resposta: na **persistente** o middleware **guarda** a mensagem pelo tempo necessário para entregá-la. Na **transiente** só guarda enquanto **remetente e receptor estão em execução**; se não consegue entregar, **descarta**.

**Q6. Diferencie síncrona e assíncrona no modelo requisição-resposta.**
Resposta: na **síncrona** o cliente usa chamada **bloqueante** para enviar e **bloqueante** para receber a resposta. Na **assíncrona** ele pode enviar de forma bloqueante ou não, mas **recebe a resposta de forma não bloqueante**.

**Q7. Diferencie comunicação discreta e em fluxo.**
Resposta: na **discreta** cada mensagem é uma **unidade completa** de informação. No **fluxo** as mensagens se relacionam pela **ordem** (ex.: transferência de arquivo) e, às vezes, pelo **tempo** (ex.: vídeo).

**Q8. Liste as etapas da RPC e diga em quais há diferença entre RPC síncrona e assíncrona.**
Resposta: as **10 etapas** estão listadas na seção 5 (cliente chama stub → stub monta msg → SO envia → SO remoto entrega ao stub do servidor → desempacota e chama serviço → servidor executa → stub empacota resultado → SO servidor envia → SO cliente entrega ao stub → stub desempacota e retorna). Na **síncrona** o cliente é bloqueado na **etapa 3** até a resposta chegar na **etapa 9**. Na **assíncrona** não há bloqueio e o stub do cliente retorna a uma **rotina de callback na etapa 10**.

**Q9. Qual é o problema da passagem de parâmetro por referência na RPC?**
Resposta: um **ponteiro só vale no espaço de endereços do processo** que o criou. Em memória distribuída, **cada nó tem o seu espaço**; o endereço não significa nada na outra máquina.

**Q10. O que é a IDL em RPC?**
Resposta: **Interface Definition Language**, uma linguagem para **descrever a interface**. É **compilada** para gerar o **stub do cliente e o stub do servidor**, que cuidam da **conversão de dados e da comunicação**, facilitando o desenvolvimento.

**Q11. Explique os padrões de comunicação do ZeroMQ.**
Resposta: **Par** (bidirecional, sem estado, um único par), **requisição/resposta** (REQ/REP, alternância obrigatória envio→resposta, REQ pode falar com vários servidores), **publica/subscreve** (PUB/SUB; só recebe quem assina; mensagens sem assinantes são perdidas; sem assinatura explícita o cliente não recebe nada) e **pipeline** (PUSH/PULL; distribuição round-robin entre trabalhadores; resultados seguem "para baixo" ao próximo PULL). Detalhes na seção 6.2.

**Q12. ZeroMQ e RabbitMQ oferecem tipos de comunicação equivalentes?**
Resposta: **não**. O ZeroMQ só faz troca de mensagens **transientes** e **não tem broker**. O RabbitMQ usa **sistema de filas**, com mensagens que podem ser **persistentes** e um **broker** intermediando, o que dá **desacoplamento temporal e referencial**.

**Q13. Explique a arquitetura geral de um sistema de enfileiramento de mensagens.**
Resposta: o sistema fornece **filas** a remetentes e receptores e garante que as mensagens sejam **transferidas da fila fonte para a fila destino**. Componentes: **fila de fonte** (local do remetente), **fila de destino** (para onde a mensagem deve ir), **gerenciadores de fila** (falam com a aplicação; processo separado ou biblioteca) e **repassadores** (roteadores que repassam mensagens a outros gerenciadores).

**Q14. O que é o AMQP?**
Resposta: um **protocolo que padroniza as operações de um sistema de fila de mensagens**, garantindo **interoperabilidade** entre implementações diferentes.

**Q15. Explique a arquitetura de comunicação do AMQP.**
Resposta: o aplicativo abre uma **conexão** (contêiner de vários **canais unidirecionais**; assume-se TCP; conexões estáveis, canais dinâmicos). A comunicação **bidirecional** vem das **sessões** (2 canais agrupados). Uma conexão pode ter várias sessões, e um canal pode existir sem sessão.

**Q16. Explique o passo a passo da transferência de mensagens no AMQP.**
Resposta: **3 passos.** (1) o stub do remetente dá **ID único** à mensagem e a marca **não resolvida**, envia ao stub do receptor, que também a marca **não resolvida** e entrega ao gerenciador de filas; (2) o receptor **conclui o processamento** e avisa; o remetente passa a **resolvida**; (3) o remetente avisa que está **resolvida** e **esquece** a mensagem; o receptor descarta as informações e registra **resolvida**. Isso dá **confiabilidade de ponta a ponta**.

**Q17. Qual a função do broker em um serviço de mensageria?**
Resposta: ser **intermediário entre produtores e consumidores**; **rotear, guardar temporariamente e entregar** as mensagens; e **converter formatos** usando regras e plugins, para que serviços diferentes troquem mensagens diretamente.

---

### 🧠 Perguntas de Revisão

1. **Por que cada camada de um protocolo tem seu próprio cabeçalho?** Para preservar a **independência/transparência** entre camadas; um cabeçalho único faria mudanças de uma camada vazarem para as outras.
2. **Qual a diferença entre persistente e transiente? Dê um exemplo de cada.** Persistente: o middleware guarda a mensagem até entregar (ex.: mailbox, fila). Transiente: só existe enquanto remetente e receptor executam (ex.: sockets, ZeroMQ, MPI).
3. **Síncrona e assíncrona: o que muda para o cliente?** Na síncrona ele fica **bloqueado** esperando; na assíncrona **continua trabalhando** e trata a resposta depois (callback), o que **oculta a latência**.
4. **Descreva o papel dos stubs na RPC.** Stub do cliente **empacota** parâmetros e envia; stub do servidor **desempacota**, chama o procedimento e devolve o resultado. Juntos dão **transparência de acesso**.
5. **Por que passar ponteiros em RPC é um problema e qual a saída?** Ponteiros só valem no espaço de endereço local. Saída: **copiar/restaurar** o conteúdo (difícil para estruturas complexas).
6. **O que é IDL e o que ela gera?** Linguagem para definir a interface; compilada, gera **stubs de cliente e servidor**, permitindo linguagens diferentes em cada lado.
7. **Cite os 4 padrões do ZeroMQ e o que o PUSH/PULL faz.** Par, REQ/REP, PUB/SUB e pipeline. PUSH distribui em **round-robin** aos PULL e o resultado segue para um coletor "adiante".
8. **O que é um MOM e que garantia ele dá ao remetente?** Middleware com filas (comunicação assíncrona persistente). Garante **entrada na fila do receptor**, mas **não garante quando/se será lida**.
9. **O que significa "resolvida" no AMQP?** A mensagem foi **processada pelo receptor**, que avisou o remetente; ambos os stubs podem **esquecê-la**. Dá **confiabilidade fim a fim**.
10. **Diferencie as exchanges fanout, direct e topic.** Fanout envia a **todas** as filas vinculadas (ignora chave); direct envia às filas cuja chave **casa exatamente**; topic envia às filas cujo **padrão** (`*`, `#`) casa com a chave. Exchange **não guarda** mensagens.

---

### 🔗 Conexão com o Trabalho Final

* **gRPC = RPC moderna:** liga-se a **RPC, stubs, IDL e geração de código** (o arquivo `.proto` faz o papel de IDL; os stubs de cliente/servidor são gerados; comunicação entre linguagens diferentes). Os slides citam gRPC como framework de RPC que disputa espaço com REST. **(complemento)** o gRPC usa **Protocol Buffers** e **HTTP/2**, e oferece chamadas unárias e com *streaming*.
* **REST = alternativa ao RPC na Web:** os slides dizem que, em aplicações Web, **RPC perdeu espaço para REST**. Compare: REST é **síncrono, transiente e requisição-resposta**. **(complemento)** baseia-se em HTTP, recursos e verbos (GET/POST...), sem stubs gerados obrigatórios.
* **RabbitMQ = MOM + AMQP + broker:** liga-se a **filas, message broker, AMQP e exchanges (fanout, direct, topic)**. É comunicação **assíncrona persistente** e fracamente acoplada.
* **Round-robin / ponderado:** a distribuição equilibrada aparece nos slides no **PUSH/PULL do ZeroMQ**. **(complemento)** no RabbitMQ, vários consumidores da mesma fila recebem mensagens em round-robin; o "ponderado" pode ser obtido controlando quantas mensagens cada consumidor pode ter pendentes (prefetch) ou o número de consumidores.
* **Persistente x transiente, com e sem ACK:** use **mensagens duráveis** (AMQP: nó que não garante durabilidade rejeita) e os estados **não resolvido/resolvido**, em que o ACK corresponde ao receptor concluir o processamento (aceita/rejeita). **(complemento)** no RabbitMQ: `durable`, `delivery_mode=2` (persistente) e `ack` manual x automático.
* **Prioridade em filas:** **(complemento)** não está nos slides; o RabbitMQ oferece filas com prioridade (`x-max-priority`).
* **Kafka x RabbitMQ:** **(complemento)** não está nos slides. Conceitualmente também é um MOM, mas é um **log distribuído** em que mensagens ficam retidas e os consumidores leem por posição (*offset*), enquanto no RabbitMQ o broker roteia por exchanges e a mensagem sai da fila ao ser confirmada.
* **Dica de roteiro dos vídeos (até 5 min cada):** 1) conceito da aula (ex.: stub/IDL, exchange, resolvido); 2) demo prática; 3) ligação com o conceito teórico.

---

### 📚 Links & Leituras Complementares

* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª Edição) — Capítulo 4, Seções 4.1.2, 4.2, 4.3 e 4.4.1
* 📖 *Distributed Systems: Principles and Paradigms* (Andrew S. Tanenbaum, 3ª Edição) — Capítulo 4, Seções 4.1.2, 4.2 e 4.3
* 📄 Slides da aula: `Aula06-sd-comunicacao.pdf` | Lista de exercícios com gabarito: `Aula06-gab.md`
* 📖 **(complemento)** Documentação oficial do RabbitMQ (tutoriais de *exchanges*, *routing* e *topics*), do ZeroMQ (guia) e do gRPC, úteis para o trabalho final.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 5: Arquiteturas de Sistemas Distribuídos](../Aula_5/README.md)
* ➡️ **Próxima Aula:** [Aula 7: Replicação e Consistência](../Aula_7/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
