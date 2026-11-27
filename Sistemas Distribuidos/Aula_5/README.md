# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: [DD/MM/AAAA] | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 05: Arquiteturas de Sistemas Distribuídos

### 📝 Introdução

Esta aula responde a uma pergunta central: **como organizar um sistema distribuído?** A resposta tem duas partes. A primeira é a **organização lógica** dos componentes de software (o *estilo arquitetônico*): quem fala com quem e de que forma. A segunda é a **organização física** (a *arquitetura de sistema*): em quais máquinas cada componente roda.

O percurso da aula é este:

1. O modelo **cliente-servidor** e as decisões de projeto de um servidor (iterativo ou concorrente, portas, interrupção, estado).
2. Os **estilos arquitetônicos**: em camadas, baseado em objetos e orientado a serviços (SOA), baseado em eventos, centrado em dados e baseado em recursos (REST).
3. As **arquiteturas de sistema**: centralizadas (cliente-servidor e multicamadas) e descentralizadas (**peer-to-peer**), incluindo tabelas hash distribuídas, o sistema **Chord**, *superpeers* e **BitTorrent**.

> 🎯 **Objetivo de estudo:** ao final, você deve saber diferenciar estilo de arquitetura, listar vantagens e desvantagens de cada estilo e explicar como funciona uma rede P2P estruturada e uma não estruturada.

---

### 💡 Conceitos Chave

#### 1. Estilo arquitetônico x Arquitetura de sistema

| | **Estilo arquitetônico** | **Arquitetura de sistema** |
|---|---|---|
| **O que trata** | Organização **lógica** dos componentes | Organização **física** dos componentes |
| **Pergunta que responde** | Como os componentes de software se organizam e interagem? | Em quais máquinas cada componente é colocado? |
| **Exemplos** | Camadas, SOA, eventos, REST | Cliente-servidor, multicamadas, peer-to-peer |

#### 2. Comunicação entre componentes: modelo cliente-servidor

* O **servidor** implementa um serviço específico.
* O **cliente** pede um serviço a um servidor.
* A interação é do tipo **request-reply**: o cliente envia uma requisição e **espera** a resposta.

```
 Cliente ---- requisição ---->  Servidor
 Cliente <---- resposta -------  Servidor
```

#### 3. O processo cliente oferece transparência de distribuição

O cliente esconde do usuário o fato de o sistema ser distribuído:

* **Esconde que fala com vários processos remotos.** Uma compra em e-commerce envolve servidores do vendedor, de instituições financeiras, do serviço de entrega etc. O usuário de um caixa eletrônico nem sabe que usa um sistema distribuído ligado à Internet.
* **Mascara falhas de comunicação:** repete a requisição N vezes e tenta trocar de servidor se houver falha. O processamento assíncrono mascara a latência.
* **Mascara a localização do servidor:** serviços de nomes, como o **DNS**, fazem isso.
* **Mascara o acesso aos dados:** a **replicação** permite buscar o dado de uma fonte mais próxima (ex.: cache do Facebook/Instagram com postagens acessadas recentemente).

#### 4. O processo servidor: quatro perguntas de projeto

**4.1 Como tratar as requisições dos clientes?**

| | **Servidor iterativo** | **Servidor concorrente** |
|---|---|---|
| Quem atende | O próprio servidor trata a requisição e responde | Repassa a requisição a uma *thread* ou outro processo (que pode estar em outra máquina) |
| Atendimento | Um cliente por vez (serializa) | Vários ao mesmo tempo; o servidor já espera a próxima requisição |
| Consequência | Latência altíssima e baixo desempenho | Melhor desempenho |

**4.2 Como o cliente se comunica com o servidor?**

* A comunicação é remota (pela rede) e os clientes enviam requisições para **portas**.
* Cada servidor "ouve" uma porta específica.
* Serviços conhecidos (FTP, HTTP) têm portas pré-definidas pela **IANA** (*Internet Assigned Numbers Authority*).
* Para serviços sem porta fixa, uma opção é um processo em segundo plano (**daemon**) que informa a porta dinamicamente.
* Outra opção é o **superservidor**: em vez de vários servidores passivos monitorando cada um a sua porta, um único superservidor escuta em todas as portas dos serviços. Quando chega uma requisição, ele **cria um processo** para atendê-la, e esse processo termina ao fim do atendimento.

**4.3 Como interromper a comunicação com o servidor?**

Exemplo da aula: você envia um arquivo enorme por FTP e percebe que é o arquivo errado. Como parar?

* **Finalização forçada:** o usuário fecha o cliente, o que derruba a conexão. Pode demorar até o servidor perceber e, em alguns casos, ele nunca percebe (ex.: fluxo de pacotes UDP).
* **Dados de interrupção fora da banda (*out-of-band*):** o cliente envia dados de controle ao servidor, na mesma conexão dos dados ou em uma conexão separada.

**4.4 O servidor guarda o estado dos clientes?**

| Tipo | O que faz | Exemplo da aula |
|---|---|---|
| **Sem estado (*stateless*)** | Não guarda informação sobre os clientes; pode mudar seu estado sem avisar ninguém | Servidor HTTP: processa a requisição e esquece o cliente |
| **Estado flexível (*soft state*)** | Guarda dados por **tempo limitado**; promete manter o cliente informado só durante esse tempo, depois o cliente precisa pedir de novo | Sites de e-commerce que esvaziam o carrinho após inatividade |
| **Com estado (*stateful*)** | Guarda informações **persistentes** do cliente | Servidor de arquivos que deixa o cliente manter cópia local e usa uma tabela (cliente, arquivo) para avisar quando o arquivo muda |

#### 5. Estilo arquitetônico: componentes e conectores

* **Componente:** unidade modular, **substituível**, com interfaces *requeridas* e *fornecidas* bem definidas.
* **Conector:** mecanismo que **medeia** a comunicação, coordenação ou cooperação entre componentes. Exemplos: RPC, troca de mensagens, *streaming*.
* O estilo define **como os componentes se conectam**, **como trocam dados** e **como componentes e conectores são configurados**.
* Combinando componentes e conectores surgem várias configurações, classificadas em **estilos arquitetônicos**.

O slide ilustra isso com um diagrama de componentes de uma loja online (`OnlineStore`), em que os componentes `Order`, `Customer` e `Product` se ligam por interfaces.

Estilos vistos na aula:

1. Arquitetura em camadas
2. Arquitetura baseada em objetos e orientada a serviços
3. Arquitetura baseada em eventos
4. Arquitetura centrada em dados
5. Arquitetura baseada em recursos

---

#### 6. Estilo em camadas

* Componentes organizados em camadas. Um componente da camada **Li** pode chamar a camada **Li-1**, mas **não o contrário**.
* Modelo muito usado em redes.
* O controle flui de camada em camada: **requisições descem**, **resultados sobem**. Só em casos excepcionais há chamada "para cima" (ex.: o SO sinaliza um processo quando um evento ocorre).

```
   Camada N      <-- recebe o resultado
      |  ^
      v  |
   Camada N-1
      |  ^
      v  |
   Camada N-2
```

**Protocolos de comunicação em camadas.** Cada camada:

* implementa um ou mais serviços de comunicação para o dado ir da origem ao destino;
* oferece uma **interface** (funções que podem ser chamadas) e **esconde a implementação**;
* segue um **protocolo**, que são as regras que as partes devem seguir para trocar informações.

Exemplo: o **TCP** oferece comunicação confiável orientada a conexão entre nós remotos, define as regras de troca de mensagens para criar e encerrar a conexão e tem uma interface com chamadas para criar conexão e enviar/receber mensagens. Por seguir um protocolo, dois nós com implementações diferentes (ex.: Linux e Windows) conseguem conversar.

O diagrama do slide mostra duas partes (A e B), cada uma com Camada N e Camada N-1. Na vertical, uma camada usa a **interface** e o **serviço** da camada de baixo. Na horizontal, as camadas de mesmo nível das duas partes conversam pelo **protocolo**.

**Aplicação web em 3 camadas:**

| Camada | O que contém |
|---|---|
| **Aplicação** (interface com o usuário) | Interfaces para usuários e sistemas externos |
| **Processamento** | Funções de uma aplicação específica |
| **Dados** | Os dados que o cliente quer manipular por meio da aplicação |

Exemplo do slide, um **buscador web**:

```
 [Camada de interface]    Interface do usuário
                              | expressão de palavras-chave      ^ página HTML com a lista
 [Camada de processamento]    v                                   |
                          Gerador de consultas -> Algoritmo de ranking -> Gerador de HTML
                              | consultas ao BD         ^ títulos de páginas com meta-informação
 [Camada de dados]            v                         |
                          Banco de dados com páginas web
```

| **Vantagens** | **Desvantagens** |
|---|---|
| Simplicidade | Não é escalável |
| Acesso centralizado aos dados | Extensibilidade limitada (a modularidade está na divisão em pacotes, não em camadas) |
| Segurança | Uma camada pode ficar grande e complexa com o tempo, com alto acoplamento |
| Separação de responsabilidades | Implantação lenta |

---

#### 7. Estilo baseado em objetos e orientado a serviços

**Baseado em objetos**

* Objetos se conectam por **chamadas de método**, e podem estar em máquinas diferentes (objetos remotos).
* Cada objeto **encapsula dados** (seu estado) e oferece **métodos** (a interface) sem revelar a implementação. Por isso retém estado (*stateful*).
* Objetos correspondem à definição de componente: interface bem definida e serviço independente da implementação.
* **CORBA** foi um middleware muito popular para orquestrar objetos distribuídos, mas **caiu em desuso**.
* Esse estilo **pavimentou o caminho** para a arquitetura orientada a serviços.

**SOA (*Service Oriented Architecture*)**

* O **serviço** é uma entidade **autocontida**: pode ser uma função ou um conjunto de classes que oferecem uma funcionalidade, e aparece como **uma unidade** para o mundo externo.
* Possui e requer **interfaces bem definidas**, expressas por **contratos**.
* Serviços **compõem** outros serviços e **são compostos** por eles, o que favorece **reuso** e **baixo acoplamento**.
* Podem pertencer a organizações administrativas diferentes.
* **Inventário de serviços:** conjunto de serviços complementares, administrado e gerenciado de forma independente por uma organização.

Outras características do SOA:

| Característica | Significado |
|---|---|
| Abstração de implementação | Quem usa não vê como o serviço é feito |
| Implantação independente | Cada unidade pode ser implantada sozinha |
| Autonomia | Controle total dos recursos de que precisa, sem interferência externa |
| Baixo acoplamento | Pouca dependência de outros serviços |
| ***Statelessness*** | Não guarda estado entre chamadas; os dados vêm na requisição ou são buscados em outro serviço (ex.: BD) |
| Descoberta de serviços | Serviços se registram no sistema para serem encontrados |

**O serviço ideal** é: pequeno (pode fazer uma única ação, como *Functions as a Service*, ex.: AWS Lambda); dono dos seus recursos (por exemplo, não divide BD com outros serviços para evitar interferência de *locks*); fácil de implantar (tipicamente em contêineres); independente da tecnologia dos demais. **Ou seja, o serviço ideal é um microsserviço.**

O slide compara um sistema **monolítico** (UI, lógica de negócio e acesso a dados juntos, sobre um único banco) com **microsserviços** (a UI chama vários microsserviços, cada um com seu próprio banco).

| **Vantagens** | **Desvantagens** |
|---|---|
| Escalabilidade | Configuração e manutenção complexas |
| Reuso | Complexidade cresce com o número de serviços |
| Implantação ágil | Maior latência de comunicação |
| Extensibilidade (modularização por serviços) | |
| Flexibilidade (vários *stacks* tecnológicos coexistem) | |

---

#### 8. Estilo baseado em eventos (publish-subscribe)

* **Motivação:** processos precisam se comunicar de forma **menos acoplada**. Separa-se **processamento** de **coordenação** (comunicação e cooperação entre processos).
* As formas de coordenação diferem em dois eixos: **temporalmente** acopladas ou desacopladas, e **referencialmente** acopladas ou desacopladas.
* Funcionamento: processos **publicam** notificações em **tópicos** e **se inscrevem** em tópicos para receber as notificações. As notificações costumam ser eventos, mas podem carregar dados.
* É **desacoplado no tempo e na referência**:
  * quem publica **não conhece** os inscritos, e vice-versa;
  * os processos **não precisam estar rodando ao mesmo tempo**.
* O **broker** (intermediário) gerencia tópicos e inscritos, repassa as mensagens (pode guardar a notificação até todos os inscritos receberem) e pode restringir quem pode publicar.

```
 Publicador A --publica--> [ Tópico "pedidos" ] --entrega--> Assinante 1
 Publicador B --publica--> [     BROKER       ] --entrega--> Assinante 2
```

No slide, o estilo aparece como um **barramento de eventos** onde os componentes publicam e recebem a entrega do evento.

#### 9. Estilo centrado em dados

* Parte da ideia de que **os dados são o recurso mais importante** e o resto do sistema opera em função deles.
* Os processos se comunicam por um **repositório comum** (no slide, um espaço de dados persistente e compartilhado).
  * Vantagem: reduz o volume de dados trafegado entre componentes.
  * Desvantagem: o repositório é um **gargalo** e limita a escalabilidade.
* Combina com o estilo baseado em eventos para avisar os processos de que os dados estão prontos e onde estão.
* Uso citado: **recuperação de erros e resolução de inconsistências**. As falhas são registradas (*log*) em um repositório, e um processo reparador varre os logs periodicamente para encontrar erros e corrigir inconsistências.

#### 10. Estilo baseado em recursos (REST)

* O sistema é visto como uma **coleção de recursos**, cada um gerenciado individualmente por componentes de software.
* Recursos podem ser **adicionados, removidos, modificados e recuperados** remotamente, e cada componente suporta essas **4 operações**. Esse é o **REST (*Representational State Transfer*)**.
* A interface é definida pelo **formato dos dados** enviados e recebidos.
* Os componentes **não retêm estado**: depois de executar a operação, esquecem a chamada.
* É muito conveniente para a **web com HTTP**: a Web é centrada em dados, cada um com um identificador único (**URI**), e o HTTP tem verbos para as 4 operações.

| Operação | Verbo HTTP (segundo os slides) |
|---|---|
| Recuperar | `GET` |
| Adicionar | `POST` |
| Remover | `DELETE` |
| Modificar | `UPDATE` |

```
 GET    /clientes/42   -> recupera o recurso "cliente 42"
 POST   /clientes      -> cria um novo cliente
 DELETE /clientes/42   -> remove o cliente 42
```

> ℹ️ *(complemento)* Os slides citam o verbo `UPDATE`. No HTTP real, a modificação costuma ser feita com `PUT` (ou `PATCH`). Os caminhos acima são exemplos didáticos meus, não estão nos slides.

---

#### 11. Arquiteturas de sistema: distribuição vertical e horizontal

A arquitetura de sistema decide **em quais máquinas reais** colocar cada componente de software.

| | **Distribuição vertical** | **Distribuição horizontal** |
|---|---|---|
| **Ideia** | Divide componentes **logicamente diferentes** em máquinas diferentes | Divide componentes **logicamente equivalentes** em máquinas diferentes, cada uma com sua parte dos dados, equilibrando a carga |
| **Detalhe** | Cada máquina é projetada para um grupo de funções; ajuda no gerenciamento | Grande parte da interação é simétrica: cada processo age como cliente e servidor ao mesmo tempo |
| **Exemplo 1** | Cada **camada** da arquitetura em camadas em uma máquina | Distribuir uma camada em várias máquinas (limitado) |
| **Exemplo 2** | Cada **serviço** da SOA em uma máquina | Várias **instâncias** de um mesmo serviço da SOA em máquinas diferentes |

As arquiteturas de sistema se dividem em:

* **Centralizadas:** cliente-servidor e multicamadas.
* **Descentralizadas:** peer-to-peer.

#### 12. Arquitetura centralizada

* **Ponto único de controle:** processamento e gestão de dados ficam no servidor central. É mais fácil de administrar.

| **Vantagens** | **Desvantagens** |
|---|---|
| **Simplicidade:** fácil de implantar e gerenciar | **Escalabilidade:** o ponto único vira **gargalo** quando a carga cresce muito |
| **Eficiência:** o servidor central pode ser otimizado para desempenho | **Ponto único de falha:** se o servidor cair, o sistema pode parar; alta disponibilidade e redundância são essenciais |

#### 13. Modelo cliente-servidor simples

* A máquina servidora implementa a maioria dos componentes de software.
* Os clientes a acessam por comunicação simples (*sockets* TCP ou UDP). Protocolos de nível mais alto oferecem mais abstração.

**Funcionalidades executadas pelo cliente**

| | **Cliente gordo (*fat client*)** | **Cliente magro (*thin client*)** |
|---|---|---|
| Quando é popular | Cliente com boa capacidade de processamento e armazenamento, e rede limitada | Cliente com pouca capacidade de processamento e armazenamento, e rede de alta velocidade |
| Gerenciamento | Muitos clientes: mais difícil gerenciar as funcionalidades | Mais fácil de gerenciar |
| Custo | Maior | Reduz o custo da máquina cliente |
| Exemplos | Aplicações multimídia web (processam no cliente) | Aplicativos móveis (limite computacional e de energia); jogos em nuvem, para quem tem máquina fraca |

**"Tons de cinza" entre gordo e magro.** O slide mostra cinco formas (a) a (e) de dividir a aplicação, em três níveis (interface do usuário, aplicação, banco de dados). A linha tracejada marca o que fica na **máquina cliente** (em cima) e na **máquina servidora** (embaixo):

```
 (a)           (b)           (c)           (d)           (e)
 UI  | cliente UI | cliente  UI  | cliente UI  | cliente UI  | cliente
 ----          ----         App  | cliente App | cliente App | cliente
 UI  | servidor ----         ----          ----         BD   | cliente
 App | servidor App          App | servidor ----         ----
 BD  | servidor BD           BD  | servidor BD            BD  | servidor
```

* **Divisão da interface do usuário** (a): só a parte da interface que depende do dispositivo fica no cliente, e a aplicação controla remotamente a apresentação. Em (b), toda a interface fica no cliente, que não processa nada além do necessário para mostrá-la.
* **Divisão da aplicação** (c): parte da aplicação roda no cliente. Ex.: um formulário que só pode ser processado depois de totalmente preenchido, e o cliente confere a correção e a consistência antes de enviar. Em (d), grande parte da aplicação roda no cliente, mas todas as operações com arquivos e BD vão ao servidor. Ex.: *player* multimídia.
* **Divisão do banco de dados** (e): o disco local do cliente guarda parte dos dados. Ex.: cache em disco local de páginas web recentes; no e-commerce, o carrinho de compras guardado em cache local.

#### 14. Modelo multicamadas

* Componentes **logicamente diferentes** do servidor rodam em **máquinas separadas**, ou seja, é a **distribuição vertical** aplicada ao servidor.
* Cada camada atua como **cliente** da camada de baixo e **servidor** da camada de cima.
* Exemplo (aplicação web em 3 camadas): a camada de processamento age como **cliente** ao repassar requisições ao **SGBD**.

```
 [ Cliente / Interface ] --> [ Servidor de aplicação ] --> [ Servidor de banco de dados ]
                              (é servidor do cliente         (é servidor da aplicação)
                               e cliente do BD)
```

---

#### 15. Arquiteturas descentralizadas

* **Controle distribuído:** não há ponto único de controle ou de falha. Cada nó opera de forma independente e contribui para o todo.

| **Vantagens** | **Desvantagens** |
|---|---|
| **Tolerância a falhas:** se um nó cai, os demais continuam; maior resiliência a falhas e ataques | **Complexidade:** algoritmos e protocolos complexos para manter a consistência |
| **Escalabilidade:** basta adicionar nós, sem sobrecarregar um ponto central; a carga se distribui | **Maior latência:** algoritmos mais complexos consomem mais recursos computacionais |

#### 16. Redes peer-to-peer (P2P) e redes de sobreposição

* As arquiteturas P2P se dividem pela forma de organizar os processos em uma **rede de sobreposição (*overlay network*)**.
* Em uma rede de sobreposição:
  * os **nós são processos** e os **enlaces são canais de comunicação**;
  * nós vizinhos na sobreposição **não estão necessariamente em máquinas diretamente conectadas**;
  * as mensagens trafegam por qualquer canal de comunicação disponível.
* Há dois tipos: **estruturadas** e **não estruturadas**.
* O slide mostra duas topologias possíveis (anel e grafo), com a rede de sobreposição desenhada sobre a rede física (*underlay*).

#### 17. P2P estruturada e tabela hash distribuída (DHT)

* A rede de sobreposição é construída por um **procedimento determinístico**.
* Os processos se organizam por uma **tabela hash distribuída**:
  * cada dado recebe uma chave: `chave = hash(dado)`;
  * cada nó é responsável por um **subconjunto de chaves**;
  * a função **`lookup`** mapeia uma chave para o endereço do nó responsável.

**Módulo hash (`chave mod num_nós`).** O slide usa as chaves 0 a 8 e 3 nós:

```
 Nó 0: 0, 3, 6     Nó 1: 1, 4, 7     Nó 2: 2, 5, 8
```

O problema aparece quando o número de nós muda. No slide, o nó do meio (com as chaves 1, 4 e 7) é removido (sai da rede ou falha) e restam 2 nós, então a conta passa a ser `chave mod 2` e o conteúdo é **redistribuído**, **até chaves em nós não afetados**:

```
 Antes (3 nós):  Nó 0: 0, 3, 6    Nó 1: 1, 4, 7    Nó 2: 2, 5, 8
 Depois (2 nós): Nó A: 0, 2, 4, 6, 8              Nó B: 1, 3, 5, 7
```

Note que as chaves 2, 3, 5, 6 e 8, que estavam em nós que continuam vivos, também mudaram de lugar.

**Hash consistente.** Técnica que distribui dados ou requisições de forma equilibrada em um conjunto **dinâmico** de nós, **sem refazer o hash de tudo** quando um nó entra ou sai, com **mínimo movimento de dados**. No slide, com o mesmo cenário (nó do meio removido), **só as chaves do nó removido se movem**: as chaves 1 e 4 vão para o primeiro nó e a chave 7 vai para o último. Os demais dados ficam onde estavam:

```
 Antes:  Nó 0: 0, 3, 6      Nó 1: 1, 4, 7      Nó 2: 2, 5, 8
 Depois: Nó 0: 0, 3, 6, 1, 4                   Nó 2: 2, 5, 8, 7
```

* É usado no **Apache Cassandra** (banco NoSQL de colunas distribuído) e no **Amazon DynamoDB** (banco NoSQL chave-valor distribuído).
* Outras abordagens citadas: *Hypercube network*, **Pastry** e ***Content-Addressable Network (CAN)***.

#### 18. Sistema Chord

* Os nós formam logicamente um **anel**.
* A chave **k** é mapeada para o nó de **menor id maior ou igual a k**. Esse nó é o **sucessor** da chave, escrito **succ(k)**.
* Cada nó conhece o endereço do seu **sucessor** e de **atalhos** para outros nós (a **tabela de derivação**, ou *finger table*).
* A tabela de derivação de cada nó tem **log K entradas**, onde K é o total de chaves possíveis (de 0 a K-1). Para o nó `p`: `FTp[i] = succ((p + 2^(i-1)) % K)`.
* O caminho mais curto entre qualquer par de nós é da ordem de **O(log N)**, com N sendo o número de nós físicos.

**Busca (*lookup*):**

* Um nó qualquer consulta o dado de chave k chamando `LOOKUP(k)`, que retorna o endereço de rede de `succ(k)`.
* Se o nó atual não conhece `succ(k)`, repassa a consulta ao **nó mais próximo de succ(k) sem ultrapassá-lo**. Assim cada salto "pula" uma grande parte do anel.

**Gerenciamento de nós:**

| | **Nó entra** | **Nó sai** |
|---|---|---|
| 1 | Gera um **id aleatório** (com bom gerador, a chance de repetir um id é quase zero) | Informa a saída ao **predecessor** e ao **sucessor** |
| 2 | Pesquisa o id e recebe `succ(id)` | **Transfere seus dados** para `succ(id)` |
| 3 | Contata sucessor e predecessor e se insere no anel | O predecessor atualiza seu novo sucessor |
| 4 | Recebe de `succ(id)` os dados que passam a ser seus | |
| 5 | Os outros nós são informados e atualizam suas tabelas (FT) | |
| **Efeito** | Só **algumas chaves do sucessor** são redistribuídas | Só **as chaves do nó que saiu** são redistribuídas |

**Balanceamento de carga e nós virtuais.** Se os nós físicos não estiverem bem espalhados no anel, a distribuição de dados fica desequilibrada. No exemplo do slide, se os nós 18, 20 e 21 saírem, o nó 28 fica com **quase metade das chaves**. A solução são os **nós virtuais**:

* Aplica-se o hash a cada servidor **várias vezes**, com funções de hash diferentes (`S_ij = hash_j(S_i)`).
* A faixa de hash de um servidor é a **união** das faixas de todos os seus nós virtuais.
* **Remover** um servidor remove todos os seus nós virtuais, e os dados vão para **vários outros** servidores. **Adicionar** um servidor faz com que ele receba dados de **vários outros**.
* A qualidade do balanceamento depende da qualidade das funções de hash.

Exemplo do slide (3 servidores, cada um com 3 nós virtuais, cores azul S0, vermelho S1 e verde S2). Se **S0 (azul)** sair:

* chaves de `S0,0` e `S0,2` vão para S1 (`S0,0` para `S1,1` e `S0,2` para `S1,0`);
* chaves de `S0,1` vão para S2 (`S0,1` para `S2,0`).

#### 19. P2P não estruturada

* A rede de sobreposição forma um **grafo aleatório**.
* Nós adjacentes na sobreposição podem estar **fisicamente distantes**, e nós distantes na sobreposição podem estar no **mesmo nó físico**. A construção da topologia tem **grande impacto no desempenho**.
* Cada nó guarda uma **lista de vizinhos** montada de forma aleatória, e os dados são colocados **aleatoriamente** nos nós.

**Consulta por inundação (*flooding*):**

```
   u --pede dado--> v1 --pede--> v3
    \--pede dado--> v2 --pede--> v3 (já viu: ignora)
```

1. O nó emissor **u** passa a solicitação a **todos os seus vizinhos**.
2. Um nó receptor **v**, se já viu a solicitação, **a ignora**.
3. Senão, v procura o dado localmente. Se tem, responde direto a u ou devolve pelo caminho de volta (ao encaminhador anterior, e assim por diante).
4. Se não tem, v **encaminha a solicitação a todos os seus vizinhos**.
5. O **TTL (*time-to-live*)** define o **número máximo de saltos** da solicitação, para reduzir o número de mensagens na rede.

**Entrada e saída:**

* **Entrar:** o nó contata um nó arbitrário de uma lista de **pontos de acesso bem conhecidos**. Eles são membros comuns, mas supõe-se que tenham alta disponibilidade.
* **Sair:** como os nós trocam visões parciais com frequência, basta **sair sem avisar**. Quem contatar um nó que não responde remove a entrada da sua visão parcial e contata outro.

#### 20. Superpeers (superpares)

* **Problema:** inundar a rede para achar um dado fica caro à medida que a rede cresce.
* **Solução:** nós especiais, os **superpares**, mantêm um **índice** dos dados e facilitam a localização. Os superpares formam entre si uma rede P2P, resultando em uma **organização hierárquica**.
* Quando um nó comum entra, **liga-se a um superpar**, e toda a comunicação de e para ele passa pelo superpar. No slide, os nós comuns são "pares fracos" (*weak peers*) ligados a superpares, e os superpares formam a rede de sobreposição.
* **Requisitos de um bom superpar:**
  * alta disponibilidade;
  * suportar grande número de conexões;
  * rede de alta velocidade;
  * ser confiável.
* Em muitos casos a relação cliente-superpar é **fixa**, o que nem sempre é bom. Uma alternativa é deixá-la **mudar** conforme os clientes descobrem superpares melhores.

#### 21. BitTorrent

Sistema de compartilhamento de arquivos que baixa **porções (*chunks*)** do arquivo de vários usuários e as monta até formar o arquivo completo.

```
 Cliente --Lookup(F)--> Página web / buscador --> Arquivo .torrent de F --> Rastreador (tracker)
    ^                                                                         | lista de nós com F
    +----------- recebe porções de K entre N nós <--------------------------- Nó 1 ... Nó N
```

1. O usuário acessa um **diretório global** (página web ou buscador) que contém o arquivo **`.torrent`**.
2. O `.torrent` traz as informações para obter o arquivo, inclusive a do **rastreador (*tracker*)**: o servidor que mantém a contabilidade exata dos nós ativos que têm o arquivo, ou porções dele.
3. Identificados os nós e as porções, o nó que baixa passa a ser **ativo**: é **forçado a ajudar os outros**, o que garante a **colaboração**.

---

### 🔍 Tópico em Destaque: Como escolher e combinar estilos (resumo comparativo)

| Estilo | Ideia central | Estado | Ponto forte | Ponto fraco |
|---|---|---|---|---|
| **Camadas** | Cada camada chama a de baixo | Depende da aplicação | Simples, seguro, dados centralizados | Pouco escalável, implantação lenta |
| **Objetos** | Objetos remotos com chamadas de método | *Stateful* | Encapsulamento | CORBA caiu em desuso |
| **Orientado a serviços (SOA)** | Serviços autocontidos com contratos | *Stateless* | Reuso, escalabilidade, flexibilidade | Complexidade e latência |
| **Baseado em eventos** | Publicar/assinar via broker | Desacoplado no tempo e na referência | Baixo acoplamento | Depende de um intermediário (*broker*) |
| **Centrado em dados** | Repositório comum | Estado no repositório | Menos dados trafegados | Repositório é gargalo |
| **Baseado em recursos (REST)** | Recursos + 4 operações via HTTP | *Stateless* | Casa com a web | Interface limitada às 4 operações |

| Arquitetura de sistema | Controle | Tolerância a falhas | Escalabilidade |
|---|---|---|---|
| **Centralizada** (cliente-servidor, multicamadas) | Ponto único | Ponto único de falha | Gargalo no servidor |
| **Descentralizada** (P2P) | Distribuído | Alta (outros nós seguem) | Alta (adiciona-se nós) |

| P2P estruturada (ex.: Chord) | P2P não estruturada |
|---|---|
| Sobreposição por **procedimento determinístico** | Sobreposição em **grafo aleatório** |
| DHT: `chave = hash(dado)` | Dados colocados aleatoriamente |
| Busca direta com `LOOKUP`, em O(log N) | Busca por **inundação** com TTL |
| Entrada e saída organizadas (transfere chaves) | Entrada contatando um ponto de acesso; saída sem avisar |

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Não confunda os dois conceitos que começam a aula:** *estilo arquitetônico* é lógico (como os componentes se organizam e interagem) e *arquitetura de sistema* é físico (em quais máquinas ficam). Esta é a questão 6 do gabarito.
> ---
> 💡 **Camadas x multicamadas:** "camadas" é um **estilo** (organização lógica). "Multicamadas" é uma **arquitetura de sistema** em que as camadas rodam em **máquinas diferentes** (distribuição vertical).
> ---
> 💡 **Vertical x horizontal:** vertical separa o que é **diferente** (camada de dados em uma máquina, camada de aplicação em outra); horizontal replica o que é **igual** (várias instâncias do mesmo serviço).
> ---
> 💡 **Estado do servidor:** *stateless* esquece o cliente (HTTP); estado flexível guarda por tempo limitado (carrinho que esvazia); *stateful* guarda de forma persistente.
> ---
> 💡 **Módulo hash x hash consistente:** com `chave mod nº de nós`, mudar o número de nós redistribui **quase tudo**. Com hash consistente (Chord), só se movem as chaves do nó que saiu (ou do vizinho de quem entrou).
> ---
> 💡 **Rede de sobreposição é lógica:** dois nós vizinhos no overlay podem estar fisicamente longe, e um caminho logicamente curto pode virar um caminho físico longo. É a desvantagem da questão 4 do gabarito.
> ---
> 💡 **Fórmula do Chord:** `succ(k)` é o nó de menor id **maior ou igual** a k. A finger table tem **log K** entradas, e a busca custa **O(log N)** saltos.

---

### 🧪 Exercícios e Gabarito Comentado

As questões 1 a 5 vêm em inglês (adaptadas do livro do Tanenbaum) e as 6 a 16 estão em português. Abaixo, cada uma está resumida e explicada.

**1. Cliente e servidor muito distantes: a latência de rede domina o desempenho. Como atacar o problema?**
O resultado depende de como o cliente é organizado. Duas ideias: (a) dividir o código do cliente em partes menores que rodem separadas, de modo que, enquanto uma parte espera a resposta do servidor, outra seja executada; (b) reorganizar o cliente para que ele faça outro trabalho depois de enviar a requisição, trocando a comunicação **síncrona** por uma comunicação **assíncrona** de mão única.
*Em linguagem simples:* em vez de ficar parado esperando a resposta, o cliente aproveita o tempo fazendo outra coisa.

**2. O que é uma arquitetura cliente-servidor de três camadas (*three-tiered*)?**
Três camadas lógicas, cada uma, em princípio, em uma máquina separada. A de cima é a **interface do cliente**, a do meio é a **aplicação** de fato e a de baixo implementa os **dados** usados.

**3. Cadeia de processos P1, P2, ..., Pn (multicamadas), em que cada Pi é cliente de Pi+1 e só responde a Pi-1 depois de receber a resposta de Pi+1. Quais os problemas para o desempenho visto por P1?**
O desempenho tende a ser **ruim para n grande**. Cada comunicação entre camadas vizinhas é, em princípio, entre máquinas diferentes. Assim, o tempo entre P1 e P2 também depende de **n-2 interações request-reply** entre as outras camadas. Além disso, se uma máquina da cadeia for lenta ou ficar temporariamente inacessível, isso **degrada imediatamente** o desempenho no topo.
*Em linguagem simples:* é como uma fila de pessoas passando um recado: a demora de qualquer uma atrasa quem fez a pergunta.

**4. Em uma rede de sobreposição estruturada, as mensagens são roteadas pela topologia do overlay. Qual a desvantagem importante?**
Trata-se apenas de **caminhos lógicos**. Dois nós A e B vizinhos no overlay podem estar **fisicamente muito distantes**. Assim, o caminho logicamente curto entre eles pode exigir uma rota longa na rede física subjacente.

**5. Nem todo nó P2P deve virar superpeer. Quais requisitos razoáveis?**
Primeiro, ser **altamente disponível**, pois muitos nós dependem dele. Segundo, ter **capacidade** suficiente para processar as requisições. E, talvez o mais importante, ser **confiável** para fazer bem o seu trabalho.

**6. Diferencie estilo arquitetônico de arquitetura de sistema.**
Estilo arquitetônico é a organização **lógica** do conjunto de componentes (como devem ser organizados e interagir). Arquitetura de sistema é a organização **física** dos componentes.

**7. Vantagens e desvantagens do estilo em camadas.**
* Vantagens: simplicidade, acesso centralizado a dados, segurança, separação de responsabilidades.
* Desvantagens: não é escalável; extensibilidade limitada (a modularidade está na divisão em pacotes, não em camadas); a camada pode ficar grande e complexa, com alto acoplamento; implantação lenta.

**8. Vantagens e desvantagens do estilo orientado a serviços.**
* Vantagens: escalabilidade, reuso, implantação ágil, extensibilidade (modularização por serviços), flexibilidade (coexistência de vários *stacks* tecnológicos).
* Desvantagens: configuração e manutenção complexas; complexidade crescente com o número de serviços; maior latência de comunicação.

**9. Explique o estilo baseado em recursos.**
O sistema é uma **coleção de recursos** gerenciados individualmente por componentes. Os recursos podem ser adicionados, removidos, modificados e recuperados remotamente, e cada componente suporta essas 4 operações (**REST**). A interface é definida pelo formato dos dados enviados e recebidos, e os componentes **não retêm estado**. Combina bem com a web e o HTTP porque a Web é centrada em dados, cada um com um identificador único (URI), e o HTTP tem verbos (GET, POST, DELETE, UPDATE) para as 4 operações.

**10. O que é um serviço nos estilos arquitetônicos?**
Uma entidade **autocontida** (uma função ou um conjunto de classes que oferecem uma funcionalidade). Aparece como **uma unidade** para o mundo externo, tem e exige interfaces bem definidas por **contratos**, sem revelar a implementação. Pode compor e ser composto por outros serviços, o que dá **reuso** e **baixo acoplamento**.

**11. Diferença entre distribuição vertical e horizontal.**
A **vertical** divide componentes **logicamente diferentes** em máquinas diferentes (ex.: cada camada da arquitetura em camadas). A **horizontal** divide componentes **logicamente equivalentes** em máquinas diferentes (ex.: várias instâncias de um mesmo serviço na SOA).

**12. O que é um cliente magro?**
Um cliente que executa **poucas funcionalidades** e consome poucos recursos. É ideal quando a máquina cliente tem baixa capacidade de processamento e armazenamento e a rede é de alta velocidade. É o caso dos **aplicativos móveis**.

**13. Diferencie servidores quanto à manutenção de estado.**
* **Sem estado:** não guarda informações sobre o estado dos clientes.
* **Estado flexível:** guarda dados por tempo limitado.
* **Com estado:** guarda informações persistentes sobre o cliente.

**14. O que é uma rede de sobreposição?**
Uma rede cujos **nós são os processos** e cujos **enlaces são os canais de comunicação possíveis**.

**15. Diferencie P2P estruturada de não estruturada.**
Na **estruturada**, a sobreposição é construída por um procedimento **determinístico** que permite a cada nó saber qual outro nó tem o dado desejado. Na **não estruturada**, a sobreposição forma um **grafo aleatório**, e a consulta é feita **inundando** a rede com uma mensagem de busca.

**16. Explique como funciona a inundação de rede.**
O nó emissor **u** envia a solicitação a todos os seus vizinhos. Um nó receptor **v** ignora a solicitação se já a viu. Senão, procura o dado localmente: se tem, responde direto a u ou devolve pelo caminho de volta (ao encaminhador original, que devolve ao anterior, e assim por diante). Se não tem, encaminha a solicitação a todos os seus vizinhos. O **TTL (*time-to-live*)** define o número máximo de saltos, para reduzir as mensagens na rede.

---

### 🧠 Perguntas de Revisão

1. **Qual a diferença entre estilo arquitetônico e arquitetura de sistema?**
   O estilo é a organização *lógica* dos componentes de software. A arquitetura de sistema é a organização *física*, ou seja, onde cada componente roda.

2. **Por que um servidor concorrente tem melhor desempenho que um iterativo?**
   O iterativo atende um cliente por vez e serializa os atendimentos (latência alta). O concorrente passa a requisição a uma *thread* ou outro processo e já fica livre para a próxima.

3. **O que diferencia servidores sem estado, com estado flexível e com estado?**
   O primeiro esquece o cliente (HTTP). O segundo guarda dados por tempo limitado (carrinho que esvazia). O terceiro guarda informações persistentes (servidor de arquivos com tabela cliente-arquivo).

4. **Cite duas vantagens e duas desvantagens do estilo orientado a serviços.**
   Vantagens: reuso, escalabilidade, flexibilidade. Desvantagens: configuração e manutenção complexas, maior latência de comunicação.

5. **Como funciona o publish-subscribe e por que ele é "desacoplado"?**
   Publicadores enviam notificações a tópicos e assinantes recebem as dos tópicos que assinaram, com um *broker* no meio. Quem publica não conhece quem assina e não precisam estar ativos ao mesmo tempo (desacoplamento de referência e de tempo).

6. **Diferencie distribuição vertical de horizontal, com um exemplo de cada.**
   Vertical: componentes diferentes em máquinas diferentes (cada camada em uma máquina). Horizontal: componentes equivalentes em máquinas diferentes (várias instâncias do mesmo serviço).

7. **Por que o hash consistente é melhor que `chave mod num_nós` em uma rede P2P?**
   Quando um nó entra ou sai, só se movem as chaves do nó que saiu (ou do sucessor de quem entrou). No módulo hash, a mudança do número de nós redistribui chaves até em nós não afetados.

8. **Como o Chord encontra o nó responsável por uma chave e quantos saltos leva?**
   `LOOKUP(k)` devolve `succ(k)`, o nó de menor id maior ou igual a k. Se o nó atual não o conhece, repassa ao nó mais próximo sem ultrapassá-lo, usando a tabela de derivação. O custo é O(log N).

---

### 🔗 Conexão com o Trabalho Final

Os protocolos do trabalho se encaixam nos estilos desta aula. **REST** é o estilo baseado em recursos (recursos com URI e verbos HTTP, sem estado). **gRPC** segue o modelo cliente-servidor com *request-reply*, próximo das chamadas de objetos/serviços remotos. **RabbitMQ** e **Apache Kafka** correspondem ao estilo baseado em eventos (publish-subscribe com *broker*, desacoplamento no tempo e na referência). *(complemento: a associação com os protocolos é interpretação minha, não consta nos slides.)*

---

### 📚 Links & Leituras Complementares

* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª Edição) — Capítulo 2, Seções 2.1 e 2.2; Capítulo 3, Seções 3.3 e 3.4; Capítulo 5, Seção 5.2.3 (Tabelas de hash distribuídas)
* 📖 *Distributed Systems: Principles and Paradigms* (Andrew S. Tanenbaum, 3ª Edição) — Capítulo 2, Seções 2.1 e 2.3; Capítulo 3, Seções 3.3 e 3.4; Capítulo 5, Seção 5.2 (Distributed hash tables)

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 4: Internet das Coisas (IoT)](../Aula_4/README.md)
* ➡️ **Próxima Aula:** [Aula 6: Comunicação entre Processos — RPC, Mensagens, Filas (MOM), AMQP e RabbitMQ](../Aula_6/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
