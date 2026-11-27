# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 04/08/2026 | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 01: Introdução aos Sistemas Distribuídos

### 📝 Introdução

A aula inicial apresenta as diretrizes e o planejamento para a disciplina **TCC00362 — Sistemas Distribuídos para Sistemas de Informação**, ministrada pelo **Prof. Raphael Guerra**. O objetivo principal do curso é capacitar os alunos nos conceitos de **computação em nuvem, arquiteturas distribuídas, internet das coisas (IoT)** e no **gerenciamento de réplicas, consistência e tolerância a falhas**. Para isso, foram apresentados o cronograma de conteúdo programático, as ferramentas de comunicação oficial, os critérios de avaliação da matéria e as bibliografias sugeridas.

Além da organização do curso, a aula entrega o **vocabulário-base** de toda a disciplina: o que é um sistema distribuído, para que ele serve (os 4 objetivos), quais problemas ele traz (falhas, latência, escala) e quais são os 3 grandes tipos de sistemas distribuídos. Tudo que vem depois (clusters, nuvem, IoT, réplicas, tolerância a falhas) é um aprofundamento destes conceitos.

> 📄 **Sobre o arquivo `RelatorioDeDisciplinasCompleto.pdf`:** é o *Relatório de Disciplinas* emitido pelo sistema acadêmico IdUFF (gerado em 29/07/2025). Ele é a **ficha oficial da disciplina** e não faz parte dos slides. Os dados relevantes estão resumidos na seção [📋 Ficha Oficial da Disciplina](#-ficha-oficial-da-disciplina-e-ementa) abaixo.

---

### 📋 Ficha Oficial da Disciplina e Ementa

| Item | Informação (conforme o Relatório de Disciplinas) |
|---|---|
| **Código** | TCC00362 |
| **Nome** | Sistemas Distribuídos para Sistemas de Informação |
| **Departamento** | TCC — Departamento de Ciência da Computação |
| **Grau** | Graduação |
| **Carga horária total** | 68 h (todas teóricas; 0 h de prática, estágio e extensão) |
| **Vigência** | 2023, 1º semestre |
| **Status** | Ativa (disciplina "Comum") |

**Ementa oficial (8 tópicos):**

1. Introdução a sistemas distribuídos  *(esta aula)*
2. Computação em cluster e grid  *(Aula 2)*
3. Virtualização e computação em nuvem
4. Internet das Coisas (IoT)
5. Arquiteturas
6. Modelos de comunicação
7. Réplica e consistência
8. Tolerância a falhas

---

### 💡 Conceitos Chave

#### 1. Histórico: por que os sistemas distribuídos surgiram?

* A tecnologia de computadores evoluiu de forma enorme e sem precedentes em outros setores nos últimos 50 anos.
* Dois avanços da **década de 80** foram decisivos:
  * **Microprocessadores poderosos**;
  * **Redes de interconexão de alta velocidade**.
* Consequência: tornou-se possível montar sistemas com **grandes quantidades de componentes conectados por uma rede de alta velocidade**. Em vez de um computador gigante, vários computadores comuns trabalhando juntos.

#### 2. Definição de Sistema Distribuído (SD)

> **Um sistema distribuído é um conjunto de componentes autônomos que colaboram entre si e é visto pelo usuário como um sistema único.**

Cada parte da frase importa:

| Trecho | O que significa |
|---|---|
| **Componentes autônomos** | São os **nós**. Cada computador funciona de forma independente, faça ele parte do SD ou não. |
| **Colaboram entre si** | Os nós precisam trabalhar juntos (comunicando-se pela rede) para o sistema funcionar. |
| **Visto como sistema único** | O usuário **não sabe** que existem vários computadores nem **onde** eles estão. |

* **Autonomia dos nós:** cada nó tem seu próprio processador e memória; a comunicação se dá por canais de rede e troca de mensagens.
* **Computação distribuída:** é o projeto, a implementação e a avaliação de **algoritmos que executam em processadores distintos, interconectados por canais de comunicação**. Aplica-se a telecomunicações, serviços Web, computação científica, controle de processos de tempo real, "cidades inteligentes" etc.

#### 3. Principais características

* As **diferenças entre os componentes**, o **modo como se conectam** e **onde** o armazenamento e o processamento acontecem ficam em grande parte **ocultos** do usuário.
* Usuários e programas interagem com o SD de forma **uniforme e consistente**, não importa onde a interação ocorra.
* **Desde computadores poderosos até nós de sensores** podem compor um SD (heterogeneidade).
* O SD deve ser **fácil de expandir e escalar**.
* **Cada nó tem sua própria noção de tempo** (não existe um relógio único e global).
* **Os nós membros mudam dinamicamente.** Por isso é preciso:
  * descobrir quais nós fazem parte do SD;
  * garantir que a comunicação ocorra **apenas com membros autorizados**.
* **Manutenção invisível:** o usuário não deve notar quando partes do sistema são trocadas, adicionadas ou reparadas. A meta é **disponibilidade contínua**, mesmo com algumas partes desligadas.
* Para suportar componentes e conexões heterogêneos e dar a visão de sistema único, usa-se uma camada de software chamada **middleware**.

#### 4. Middleware

* **O que é:** um **gerenciador de recursos distribuídos em rede** que oferece aos usuários a visão de um sistema único.
* **Serviços típicos:** descoberta de recursos, comunicação entre processos, transações atômicas, composição de serviços, confiabilidade, etc.
* **Como se organiza (diagrama do slide):** o middleware fica **entre as aplicações e o sistema operacional local** de cada máquina, oferecendo a **mesma interface em todos os computadores**.

```
 Computador 1      Computador 2       Computador 3      Computador 4
┌───────────┐   ┌───────────────────────────┐   ┌───────────┐
│  Appl. A  │   │       Aplicação B         │   │  Appl. C  │
├───────────┴───┴───────────────────────────┴───┴───────────┤
│     Camada do sistema distribuído  (MIDDLEWARE)           │  <- mesma interface em todos
├───────────┬───────────┬───────────┬───────────────────────┤
│ SO local 1│ SO local 2│ SO local 3│ SO local 4            │
└─────┬─────┴─────┬─────┴─────┬─────┴──────┬────────────────┘
      └───────────┴───── Rede ─┴────────────┘
```

Em outras palavras: a aplicação "conversa" com o middleware e não precisa saber qual SO ou qual hardware existe por baixo.

#### 5. Exemplos de SDs

* **Servidor Web:** usuários espalhados pelo país fazem pedidos de notebooks ou celulares; os pedidos chegam, são processados e respondidos automaticamente por algum servidor. O usuário não sabe por onde o pedido navegou: parece falar com **um único computador**.
* **Armazenamento em nuvem:** Dropbox, Google Drive.
* **Internet como sistema de documentos:** oferece um modelo uniforme e consistente de documentos distribuídos. Para ver um documento, basta ativar a referência (link); não é preciso saber de qual servidor ele vem; para publicar, basta que ele tenha um **nome único**. Para o usuário, a Internet é um **enorme sistema descentralizado de documentos**.

#### 6. Os 4 objetivos de um SD

```
        ┌─ Compartilhamento de recursos
 Metas ─┼─ Transparência de distribuição
        ├─ Abertura
        └─ Escalabilidade
```

##### 6.1 Compartilhamento de recursos

* Facilitar o compartilhamento de **arquivos, serviços, dados, armazenamento** entre usuários.
* Facilitar a **colaboração**: grupos geograficamente dispersos trabalhando juntos (edição colaborativa, teleconferências).
* Exemplos clássicos: compartilhamento de arquivos em redes **peer-to-peer**; distribuição de conteúdo multimídia em larga escala (partida de futebol ao vivo; áudio e vídeo sob demanda, como Spotify e Netflix).

##### 6.2 Transparência de distribuição

Transparência é **ocultar** do usuário algum aspecto da distribuição. São 7 tipos:

| Tipo | O que oculta | Exemplo dado nos slides |
|---|---|---|
| **Acesso** | Diferenças na representação de dados e no modo de acesso ao recurso | Sistemas operacionais e arquiteturas diferentes, cada um com sua convenção de nomes de arquivo; essas diferenças ficam ocultas |
| **Localização** | O lugar onde o recurso está | A URL `www.prenhall.com/index.html` não dá pista de onde fica o servidor; no Dropbox ou na Netflix não sabemos onde está o servidor. Usam-se **nomes lógicos** |
| **Migração** | Que o recurso pode ser movido para outra localização | Não dá para saber se `index.html` sempre esteve no mesmo lugar; trocar de provedor web não afeta os usuários do site |
| **Relocação** | Que o recurso pode ser movido **enquanto está sendo usado** | Usuário de laptop que se desloca de um lugar para outro sem sequer se desconectar |
| **Replicação** | Que o recurso é replicado | A Netflix guarda réplicas dos vídeos mais acessados em vários servidores dispersos e carrega do mais próximo |
| **Concorrência** | Que o recurso é compartilhado por vários usuários | Dois usuários tentam comprar a última unidade de um produto: só um deve ter a compra confirmada |
| **Falhas** | A falha e a recuperação de um recurso | Difícil de implementar (veja abaixo) |

Detalhes importantes de cada tipo:

* **Acesso:** exige um **acordo sobre como representar os dados** em máquinas e SOs diferentes.
* **Localização x Migração x Relocação:** são "irmãs". Localização = *onde está*; migração = *foi movido* (sem afetar o acesso); relocação = *foi movido durante o uso*, sem o usuário perceber.
* **Replicação:** serve para **aumentar a disponibilidade** ou o **desempenho**. Para ocultá-la, **todas as réplicas precisam ter o mesmo nome**. Por isso, um SD com transparência de replicação normalmente também oferece transparência de localização (senão seria impossível referir-se a réplicas em lugares diferentes).
* **Concorrência:** o acesso simultâneo deve deixar o recurso em **estado consistente**, usando mecanismos que dão a cada usuário, **um por vez, acesso exclusivo** ao recurso.
* **Falhas:** o usuário não deve perceber que um recurso parou de funcionar bem ou que o sistema está se recuperando. É difícil porque **o sistema não consegue distinguir um recurso "morto" de um "insuportavelmente lento"**.

##### 6.3 Abertura (openness)

* **Sistema aberto** = tem suas **interfaces especificadas e publicadas** para interagir com outros sistemas, oferecendo serviços conforme regras padronizadas que descrevem **sintaxe e semântica**.
* As especificações devem ser:
  * **Completas:** tudo o que é necessário para implementar foi especificado;
  * **Neutras:** não ditam como deve ser a aparência/estrutura da implementação.
* Benefícios:

| Propriedade | Significado | Exemplo do slide |
|---|---|---|
| **Interoperabilidade** | Sistemas de fabricantes diferentes coexistem e cooperam | Smartphones de fabricantes diferentes trocando dados |
| **Portabilidade** | A aplicação executa sobre plataformas diferentes | App móvel que roda em Android e iOS |
| **Extensibilidade** | Dá para adicionar novas funcionalidades | (sem exemplo nos slides) |

##### 6.4 Escalabilidade

* **Definição:** capacidade de **crescer mantendo desempenho satisfatório**.
* Medida em **3 dimensões**:

| Dimensão | Pergunta | Problema típico |
|---|---|---|
| **Tamanho** | Aguenta mais usuários/recursos? | O servidor vira **gargalo**: sistema centralizado é limitado em processamento, armazenamento e largura de banda |
| **Geografia** | Aguenta usuários/recursos muito distantes? | Baixa confiabilidade (links intermediários falham, congestionamento), **alta latência** (LAN em microssegundos; WAN em milissegundos) e WAN sem multiponto/broadcast eficiente (LAN tem) |
| **Administração** | É fácil gerenciar com várias organizações? | Domínios administrativos distintos (políticas diferentes) |

* **Para escalar em tamanho, use algoritmos descentralizados**, que seguem estas regras:
  * nenhuma máquina tem informação completa sobre o estado do sistema;
  * decisões baseadas apenas em **informação local**;
  * a falha de uma máquina **não arruína** o algoritmo;
  * **não há premissa de relógio global**.

#### 7. Técnicas de escalabilidade

| Técnica | Ideia | Exemplos dos slides |
|---|---|---|
| **Ocultar latência de comunicação** | **Não bloquear** o processo que fez a requisição (comunicação **assíncrona**): ele faz trabalho útil enquanto espera e conclui a operação quando a resposta chega | Programação **multithread**; linguagens modernas têm recursos de alto nível para assincronia |
| **Particionamento e distribuição** | Dividir um componente em partes menores e espalhá-las pelo sistema | Tabela de produtos de um e-commerce dividida por letra do alfabeto em nós diferentes (alterar "bicicleta" e "televisão" ocorre em nós distintos); **DNS** |
| **Replicação** | Copiar componentes para aumentar **disponibilidade** e equilibrar **carga** (uma cópia por perto reduz a latência) | *Mirrored sites*, cache web, replicação de arquivos em servidores e bancos de dados |

**Como o DNS particiona (hierarquia):** a resolução de nomes é distribuída hierarquicamente entre vários servidores. Cada servidor resolve a sua parte e devolve o endereço do servidor responsável pelo resto do nome; o último devolve o **IP** do hospedeiro. O slide mostra a árvore: raiz, domínios genéricos (`com`, `edu`, `org`, `gov`, `net`...) e de países (`jp`, `nl`...), cada um com subdomínios e zonas (Z1, Z2, Z3) sob responsabilidade de servidores diferentes.

```
                 raiz
   ┌────┬────┬───┴───┬────┐
  com  edu  org     jp    nl ...
   │    │    │       │     │
  sun  yale  acm    ac    vu      <- cada nível é resolvido por servidores diferentes
```

⚠️ **O preço da replicação e do cache: consistência.** Alterar uma cópia a torna diferente das outras. Manter todas sincronizadas globalmente **reduz o desempenho**. Dependendo da aplicação, **diferentes graus de inconsistência podem ser tolerados**.

#### 8. Premissas falsas mais comuns sobre a rede

Quem projeta SDs **não pode assumir** que:

| # | Premissa falsa | Realidade |
|---|---|---|
| 1 | A rede é confiável | Mensagens se perdem, links caem |
| 2 | A rede é segura | Precisa de autenticação e proteção |
| 3 | A rede é homogênea | Há hardware, SOs e protocolos diferentes |
| 4 | A topologia não muda | Nós entram e saem |
| 5 | A latência é zero | Comunicar leva tempo |
| 6 | A largura de banda é infinita | A rede tem limite |
| 7 | O custo de transporte é zero | Transportar dados custa tempo/recursos |
| 8 | Há apenas um administrador | Costuma haver vários domínios administrativos |

#### 9. Tipos de sistemas distribuídos

##### 9.1 Sistemas distribuídos de alto desempenho (HPC)

* Executam algoritmos que exigem **altíssimo poder computacional**: simulação de fenômenos físicos complexos (previsão do tempo; análises espaciais e testes de modelos de reservatório e dutos na indústria de óleo e gás), redes neurais (IA), análise de risco em operações financeiras, genômica etc.
* Usam **processamento paralelo** para fazer muitos cálculos complexos rapidamente, e podem trabalhar com **grandes volumes de dados**.
* **Abordagens de paralelismo:**

| Abordagem | Como funciona | Observação |
|---|---|---|
| **Compilação paralela** | O compilador descobre quais partes do programa podem rodar em paralelo e as distribui entre os computadores do cluster | Transparente para o programador |
| **Aplicações paralelas** | O programador escreve a aplicação com **vários processos distribuídos** e usa **passagem de mensagens** para mover dados entre nós | Coloca grande responsabilidade no programador, mas explora melhor as chances de otimização |
| **Computação paramétrica** | A aplicação roda **muitas vezes**, cada uma com um conjunto diferente de condições iniciais/parâmetros (ex.: simulações) | Precisa de ferramentas para organizar, executar e gerenciar os trabalhos |

##### 9.2 Sistemas de informação distribuídos

* São **essencialmente transacionais**: o cliente envia uma solicitação para executar uma operação específica (normalmente envolvendo **banco de dados**) e recebe uma resposta.
* A operação deve ser feita **por completo ou nada** (atomicidade). Uma **transação distribuída** envolve vários subsistemas independentes e vários nós.
* Cada transação é simples, mas o sistema precisa lidar com **alto volume de transações simultâneas** (e-commerce, operações financeiras).
* Também resolvem a **interoperabilidade** entre os sistemas de uma organização (gestão de processos, de pessoas, financeiro...).
* Com o crescimento da TI, passaram a exigir mais capacidade de processamento (**escalabilidade**).

##### 9.3 Sistemas distribuídos pervasivos

* Vêm da **computação móvel e embutida**. Características: comportamento **inerentemente instável**, **pequeno tamanho**, **alimentados por bateria**, **comunicação sem fio**, **poucos recursos** (memória, processamento, banda), objetivo de **mobilidade** e alta **cooperação**.
* **Aplicações:**
  * Monitoramento ambiental: deslizamento de encostas, qualidade da água, migração de animais, terremotos;
  * Monitoramento de tráfego: Waze;
  * Aplicações médicas: cuidado com o idoso, esportes de alto rendimento;
  * Indústria: Indústria 4.0 e agropecuária 4.0.
* Todas convergem para o conceito de **Internet das Coisas (IoT)**.

##### Comparativo dos 3 tipos

| | Alto desempenho | Sistemas de informação distribuídos | Pervasivos |
|---|---|---|---|
| **Foco** | Poder de cálculo | Transações | Mobilidade e sensores |
| **Ideia central** | Paralelismo | "Tudo ou nada" (atomicidade) + muitas operações simultâneas | Poucos recursos e rede instável |
| **Exemplos** | Previsão do tempo, IA, genômica | E-commerce, bancos | Waze, monitoramento médico, IoT |

---

### 🔍 Tópico em Destaque: Transparência de Falhas e o Problema do "Morto ou Lento?"

A transparência de falhas é a mais difícil das sete. O motivo é prático: quando um servidor não responde, o sistema **não tem como saber** se ele realmente caiu ou se está apenas muito lento. Consequência: o sistema pode ter que informar que "o serviço não está disponível" **mesmo que o servidor esteja só lento** (é exatamente a resposta do gabarito, questão 6). Esse dilema reaparece em toda a disciplina (replicação, consistência, tolerância a falhas).

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Premissas Falsas de Rede:** No projeto de sistemas distribuídos, nunca assuma premissas incorretas: a rede não é necessariamente confiável, segura ou homogênea; a latência não é zero; a largura de banda não é infinita; a topologia muda; o custo de transporte não é zero; e raramente há apenas um administrador.

--

> 💡 **Tipos de Transparência:** Atente-se às diferenças entre os vários níveis de transparência (acesso, localização, migração, relocação, replicação, concorrência e falhas). A transparência de falhas é particularmente complexa de implementar, pois o sistema frequentemente não consegue distinguir entre um recurso que falhou ("morto") e um que está apenas muito lento.

--

> 💡 **Técnicas de Escalabilidade:** Para combater gargalos de escalabilidade em sistemas centralizados e latências geográficas de conexões WAN, utilizam-se técnicas como a **ocultação de latência** (através de comunicação assíncrona/não-bloqueante e programação multithread), o **particionamento e distribuição** (como subdivisão de tabelas de banco de dados e resolução hierárquica do DNS), e a **replicação** (que, contudo, gera desafios de consistência e sincronização dos dados).

--

> 💡 **Classificação dos Sistemas Distribuídos:** Os SDs são tradicionalmente classificados em três grandes categorias:
>
> 1. **Alto Desempenho (High-Performance):** Voltados para processamento paralelo e computação paramétrica ou científica de alta demanda computacional (como previsões de tempo ou processamento de redes neurais).
> 2. **Sistemas de Informação Distribuídos:** Essencialmente transacionais (ACID), lidando com alto volume de transações simultâneas (como e-commerce e operações financeiras).
> 3. **Sistemas Distribuídos Pervasivos:** Sistemas móveis, embutidos e altamente cooperativos baseados em Internet das Coisas (IoT), caracterizados por restrições severas de bateria, memória e banda (como Waze e monitoramento médico).

--

> 💡 **Dica de estudo (complemento):** para memorizar as transparências, use a frase "**A**ssim **L**ogo **M**e **R**eparam **R**apidamente **C**om **F**é": **A**cesso, **L**ocalização, **M**igração, **R**elocação, **R**eplicação, **C**oncorrência, **F**alhas. Já para a escalabilidade, lembre das 3 dimensões **T**amanho, **G**eografia, **A**dministração.

---

### 🧪 Exercícios e Gabarito Comentado

Resumo das 11 questões do gabarito (`Aula01-gab.pdf`), em linguagem simples.

**1. O que é um sistema distribuído?**
Um conjunto de componentes autônomos (nós) que colaboram entre si e que o usuário enxerga como **um único sistema**.

**2. Quais as principais características?**
Resumo (o gabarito lista todas as do slide): diferenças entre componentes, conexões e local de processamento/armazenamento ficam ocultos; interação uniforme e consistente; de computadores potentes a sensores podem participar; fácil de expandir; cada nó tem sua noção de tempo; os membros mudam dinamicamente (é preciso descobrir quem participa e garantir comunicação só com autorizados); usuários não percebem trocas/reparos; o sistema deve estar sempre disponível mesmo com partes desligadas.

**3. O que é um middleware?**
Um gerenciador de recursos distribuídos em rede que suporta componentes e interconexões heterogêneos e dá a visão de sistema único. Serviços: descoberta de recursos, comunicação entre processos, transações atômicas, composição de serviços e confiabilidade.

**4. Dê 4 exemplos de aplicações distribuídas modernas.**
Resposta do gabarito: **Waze, Dropbox, WhatsApp e Google Meet**. (Qualquer exemplo em que vários computadores colaboram e o usuário vê "um só serviço" serve.)

**5. Quais os 4 objetivos de SDs? Explique cada um.**
**Compartilhamento de recursos**, **transparência de distribuição** (7 tipos: acesso, localização, migração, relocação, replicação, concorrência, falhas), **abertura** (interoperabilidade, portabilidade, extensibilidade, com especificações completas e neutras) e **escalabilidade** (tamanho, geografia, administração). Para a prova, cite os subitens de cada um, como na seção de Conceitos Chave.

**6. Por que é tão difícil esconder a ocorrência e a recuperação de falhas?**
Porque em geral é **impossível detectar se um servidor está realmente inativo ou apenas respondendo devagar**. O sistema pode acabar informando que o serviço está indisponível quando, na verdade, o servidor está só lento.

**7. Explique 3 técnicas para obter escalabilidade.**
(1) **Ocultar latência:** comunicação assíncrona, não bloquear o processo, fazer trabalho útil enquanto espera (multithread). (2) **Particionamento e distribuição:** dividir um componente em partes menores e espalhá-las. (3) **Replicação:** copiar componentes para aumentar disponibilidade e equilibrar carga; uma cópia próxima reduz a latência.

**8. Premissas falsas mais comuns sobre a rede?**
Rede confiável; rede segura; rede homogênea; topologia que não muda; latência zero; largura de banda infinita; custo de transporte zero; um único administrador.

**9. O que é um SD de alto desempenho?**
Executa algoritmos de altíssimo poder computacional (previsão do tempo, análises na indústria de óleo e gás, redes neurais, risco financeiro, genômica) com **processamento paralelo**, podendo trabalhar sobre grandes quantidades de dados.

**10. O que é um sistema de informação distribuído?**
Sistema essencialmente **transacional**: o cliente pede uma operação (geralmente envolvendo banco de dados) que deve ser feita **por completo ou nada**; uma transação distribuída envolve vários subsistemas e nós. Cada transação é simples, mas o volume simultâneo é alto (e-commerce, finanças).

**11. Características dos SDs pervasivos?**
Comportamento instável, pequeno tamanho, alimentados por bateria, comunicação sem fio, poucos recursos (memória, processamento, banda), foco em mobilidade e alta cooperação.

---

### 🧠 Perguntas de Revisão

1. **Qual a definição de sistema distribuído e por que o "sistema único" é importante?**
   Conjunto de componentes autônomos que colaboram e são vistos como um só sistema; o usuário não precisa saber quantos computadores existem nem onde estão.
2. **Qual o papel do middleware?**
   Camada de software entre aplicações e SO local que esconde a heterogeneidade e oferece serviços comuns (descoberta, comunicação entre processos, transações, confiabilidade).
3. **Diferencie transparência de migração e de relocação.**
   Migração: o recurso pode ser movido sem afetar o acesso. Relocação: ele é movido *enquanto está em uso*, sem o usuário perceber.
4. **Por que a transparência de falhas é difícil?**
   Porque não dá para distinguir um servidor morto de um muito lento.
5. **Quais as 3 dimensões da escalabilidade e um problema de cada uma?**
   Tamanho (gargalo no servidor), geografia (latência e baixa confiabilidade da WAN), administração (várias organizações com políticas diferentes).
6. **Como a replicação ajuda e qual problema ela cria?**
   Aumenta disponibilidade e desempenho (cópia por perto, balanceamento de carga), mas cria o problema de **consistência** entre as cópias.
7. **Cite 4 premissas falsas sobre redes.**
   Ex.: rede confiável, latência zero, banda infinita, topologia fixa (também: segura, homogênea, custo zero, um administrador).
8. **Diferencie os 3 tipos de SD.**
   Alto desempenho (paralelismo e cálculo pesado), sistemas de informação (transações "tudo ou nada" em alto volume) e pervasivos (dispositivos móveis/embutidos com poucos recursos, base da IoT).

---

### 🔗 Conexão com o Trabalho Final

* O trabalho final demonstra **gRPC, REST, RabbitMQ e Apache Kafka**: todos são formas de os nós de um SD **se comunicarem pela rede** e podem ser vistos como peças de **middleware** (complemento).
* A técnica de **ocultar latência por comunicação assíncrona** é a base da lógica de filas e *streams* de mensagens (RabbitMQ e Kafka), e as **premissas falsas da rede** (rede não confiável, latência não zero) justificam recursos como reenvio, confirmação e persistência de mensagens (complemento).

---

### 📚 Links & Leituras Complementares

* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª e 3ª Edições) — Capítulo 1
* 📖 *Sistemas Distribuídos: Conceitos e Projeto* (G. Coulouris et al., 5ª Edição) — Capítulo 1

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** *Primeira aula do curso*
* ➡️ **Próxima Aula:** [Aula 2: Grids e Clusters — Em busca de maior capacidade de processamento](../Aula_2/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
