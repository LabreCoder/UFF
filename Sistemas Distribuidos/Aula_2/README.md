# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 11/08/2026 | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 02: Grids e Clusters — Em busca de maior capacidade de processamento

### 📝 Introdução

A segunda aula apresenta os conceitos fundamentais de **computação em grade (grid computing)** e **computação em cluster**, abordando seus principais componentes, arquiteturas de armazenamento (SAN e NAS) e gerenciamento de falhas. O objetivo principal deste tópico é capacitar os alunos na compreensão das alternativas arquiteturais para a busca de **alta capacidade de processamento**, **escalabilidade absoluta e incremental**, **alta disponibilidade** e estratégias de **balanceamento de carga** em larga escala. Para isso, foram analisados a taxonomia de Flynn, o funcionamento de comutadores e distribuidores de requisição, os serviços essenciais de um middleware de cluster e exemplos práticos de supercomputadores.

Em uma frase: **se um único computador não dá conta, juntamos vários**. A aula mostra as duas formas clássicas de fazer isso (grid e cluster) e como organizar, proteger e distribuir o trabalho entre os computadores.

---

### 💡 Conceitos Chave

#### 1. A busca por maior desempenho

* Tradicionalmente, o computador é uma **máquina sequencial**: executa instruções de máquina **uma por vez, em sequência**. Cada instrução passa por etapas (obter instrução, obter operandos, executar a operação, armazenar o resultado).
* Existe um **limite físico** que impede continuar ganhando desempenho só fazendo processadores mais rápidos.
* Uma das soluções é **usar mais processadores**:
  * **Multiprocessadores simétricos (SMP)**;
  * **GPUs**;
  * **Computadores interconectados em rede** (foco desta aula).

#### 2. Taxonomia de Flynn

Classifica as arquiteturas conforme o **número de fluxos de instruções** e de **dados** processados ao mesmo tempo.

| | **Um fluxo de dados** | **Vários fluxos de dados** |
|---|---|---|
| **Uma instrução** | **SISD** | **SIMD** |
| **Várias instruções** | **MISD** | **MIMD** |

| Sigla | Significado | Como funciona | Exemplos |
|---|---|---|---|
| **SISD** | Single Instruction, Single Data | Um processador único executa **uma** sequência de instruções sobre dados de **uma** memória | Uniprocessadores |
| **SIMD** | Single Instruction, Multiple Data | **Uma** instrução controla vários elementos de processamento ao mesmo tempo; cada um tem sua memória de dados, então a **mesma instrução** roda em **dados diferentes** | Processador vetorial, processador de matrizes (figura do slide) |
| **MISD** | Multiple Instruction, Single Data | Um fluxo de dados é enviado a vários processadores, cada um com uma sequência de instruções diferente | **Não é implementado comercialmente** |
| **MIMD** | Multiple Instruction, Multiple Data | Vários processadores executam **instruções diferentes** ao mesmo tempo sobre **dados diferentes** | SMPs, clusters e sistemas NUMA |

**Árvore "Organizações dos processadores" (figura do slide)**, com o ramo MIMD destacado em vermelho:

```
                       Organizações dos processadores
        ┌───────────┬──────────────┬─────────────┬─────────────────────┐
      SISD         SIMD           MISD          MIMD
        │        ┌───┴────┐                 ┌─────┴─────────────┐
 Uniprocessador Vetorial  Matrizes    Memória compartilhada   Memória distribuída
                                      (fortemente acoplada)   (fracamente acoplada)
                                        ┌──────┴──────┐               │
                                       SMP          NUMA          Clusters
```

**MIMD de memória compartilhada x distribuída (gabarito, questão 2):**

| | Memória compartilhada | Memória distribuída |
|---|---|---|
| **Estrutura** | CPUs ligadas a uma memória principal com **espaço único de endereçamento**, por barramento de alta velocidade | **Cada CPU (ou grupo)** tem o seu próprio espaço de endereçamento e se conecta às outras **por rede** |
| **Acoplamento** | Fortemente acoplada | Fracamente acoplada |
| **Tempo de acesso** | Igual para todas as CPUs (**UMA**, Uniform Memory Access) ou diferente conforme a CPU e o endereço (**NUMA**, Non-Uniform Memory Access) | (comunicação por rede) |
| **Exemplos** | SMP, NUMA | Clusters |

#### 3. Computação em Grade (Grid Computing)

* Sistemas **altamente heterogêneos** em tudo: rede, sistemas operacionais, domínios administrativos, políticas de segurança, capacidade de processamento e de memória dos nós.
* Nós **fracamente acoplados** (*loosely coupled*).
* Reúne **recursos e pessoas de organizações diferentes**, formando uma **organização virtual**. Recursos = capacidade de processamento, armazenamento e bancos de dados.
* **Processos da mesma organização virtual têm os mesmos direitos**, independentemente da organização do nó em que estejam rodando.

**Volunteer computing (computação voluntária):**

* Predomina em grids: usuários **doam recursos subutilizados** dos seus computadores para processar dados de aplicações acadêmicas e científicas.
* A ideia: o usuário comum quase nunca usa todo o poder da máquina; projetos aproveitam esse tempo ocioso.
* As aplicações costumam ser otimizadas para **processamento paralelo**.
* Desafios: **baixa confiabilidade dos nós** (podem cair de repente), **alta latência** e falhas de rede.

**Arquitetura de grid em camadas (figura e texto dos slides):**

```
┌──────────────────────────────┐
│  Application layer           │  Aplicações da organização virtual
├──────────────────────────────┤ ┐
│  Collective layer            │ │
├───────────────┬──────────────┤ │ núcleo do middleware de grade
│ Connectivity  │ Resource     │ │ (resource + collective + connectivity)
│ layer         │ layer        │ ┘
├───────────────┴──────────────┤
│  Fabric layer                │  Recursos locais
└──────────────────────────────┘
```

| Camada | Papel |
|---|---|
| **Fabric layer** (base) | Fornece **interfaces para consultar o estado e as capacidades dos recursos locais**, mais funções para gerenciá-los (ex.: bloqueio de recursos) |
| **Connectivity layer** | **Protocolos de comunicação** para transações que abrangem vários recursos e **protocolos de segurança** para autenticar usuários e recursos |
| **Resource layer** | Gerencia **um único recurso** de forma distribuída; usa a connectivity layer para acessar e controlar as interfaces da fabric layer |
| **Collective layer** | Gerencia o acesso a **vários recursos**: descoberta de recursos, alocação e agendamento de tarefas, replicação de dados etc. |
| **Application layer** (topo) | As aplicações que rodam dentro da organização virtual e usam o ambiente de grid |

Dica de leitura: *de baixo para cima*, vai do recurso físico (fabric), passa pela comunicação/segurança (connectivity), pelo gerenciamento de um recurso (resource), pelo gerenciamento de vários (collective) e chega à aplicação.

#### 4. Computação em Cluster

* Sistema **homogêneo e fortemente acoplado**:
  * nós semelhantes, tipicamente **idênticos**;
  * interligados por **rede local de alta velocidade (LAN)**;
  * **topologia estável**;
  * **mesmo sistema operacional** em todos os nós (ou um SO distribuído que roda em todos em paralelo para gerir os recursos).
* Usos: computação paralela, **servidor de serviços web** (e-commerce, streaming de vídeo) e, mais recentemente, **hospedagem de serviços de computação em nuvem**.
* **Ideia central:** construir um **supercomputador** com uma coleção de **computadores baratos** e de menor poder, ligados por uma rede rápida. Antigamente eram PCs comuns e workstations potentes; hoje, **datacenters**.

**Hardware de um cluster/datacenter:**

| Termo | O que é |
|---|---|
| **Blade** | Módulo computacional com **CPU, memória e disco** |
| **Rack** | **Chassi** onde os blades são organizados; fornece **energia e rede local de alta velocidade** |
| **Switch ToR (Top of Rack)** | Switch no topo de cada rack que liga seus blades (10 e 40 Gbps na figura) |
| **Switches de agregação** | Interligam os switches de todos os racks (N × 100 Gbps na figura) |
| **Data center** | Salas, prédios ou grupos de prédios que abrigam sistemas computacionais e componentes associados (telecomunicações, armazenamento) |

```
         [Switches de agregação]        <- N x 100 Gbps
            /       |       \
       [ToR]      [ToR]     [ToR]       <- Top of Rack switch
        |          |          |
    [rack com   [rack com  [rack com
     blades]     blades]    blades]     <- 10/40 Gbps até os blades
```

**Sistema de arrefecimento (gabarito, questão 8):** os racks são organizados em **corredores quentes** (por onde o ar sai dos nós) e **corredores frios** (por onde o ar entra), o que melhora a eficiência do resfriamento. A figura mostra a unidade de ar-condicionado de precisão (CRAC), corredores frios/quentes e placas perfuradas no piso. Um cluster pode ter **um ou mais datacenters** geograficamente dispersos.

**Arquitetura de um cluster computacional (figura do slide):** vários PCs/estações de trabalho, cada um com *software de comunicação* e *hardware de interface de rede*, ligados a uma **rede de alta velocidade/comutador**. Sobre eles fica o **middleware do cluster**, que dá a **imagem única do sistema** e a disponibilidade da infraestrutura. No topo, aplicações sequenciais e aplicações paralelas (com ambiente de programação paralela).

#### 5. Modos de clusterização de nós (tabela do slide e do gabarito)

Como os servidores de um cluster se organizam para suportar falhas:

| Método | Descrição | Benefícios | Limitações |
|---|---|---|---|
| **Secundário passivo** (*passive standby*) | Um servidor secundário assume se o primário falhar | Fácil de implementar | Custo alto: o secundário fica indisponível para outras tarefas |
| **Secundário ativo** | O secundário também executa tarefas de processamento | Custo menor (secundários são aproveitados) | Maior complexidade |
| **Servidores separados** | Cada um tem seus próprios discos; os dados são **copiados continuamente** do primário para o secundário | Alta disponibilidade | Grande sobrecarga de rede e de servidores por causa das cópias |
| **Servidores conectados aos discos** | Ligados aos mesmos discos, mas cada um tem os seus; se um falha, seus discos são assumidos por outro | Carga de rede e de servidores menor (sem cópias) | Costuma exigir espelhamento de discos ou **RAID** para compensar o risco de falha do disco |
| **Servidores que compartilham discos** | Vários servidores acessam os mesmos discos **simultaneamente** | Baixa carga; menos risco de inatividade por falha de disco | Exige software de gerenciamento de **bloqueio**; normalmente usado com espelhamento ou RAID |

Os slides também trazem a figura (a) "servidor secundário **sem** disco compartilhado" (dois servidores, cada um com seu disco, ligados por um link de alta velocidade para troca de mensagens) e (b) "**disco compartilhado**" (dois servidores ligados a um RAID comum, além do link de mensagens).

#### 6. Storage-Area Network (SAN)

* **O que é:** uma **rede especializada** que dá acesso rápido e confiável entre servidores e **recursos de armazenamento externos ou independentes**. O dispositivo de armazenamento **não pertence a nenhum servidor**: é compartilhado por todos como **recurso de mesmo nível** (*peer*).
* Assim como uma LAN liga clientes a servidores, a SAN liga **servidores a armazenamento, servidores entre si e armazenamento a armazenamento**.
* É uma alternativa ao **NAS (Network-Attached Storage)**, em que **um servidor controla** os dispositivos de armazenamento e administra as transferências.
* Usa **armazenamento baseado em blocos**, o que exige **protocolos especiais** de transferência.

```
 Usuários ── switches ── LAN ──┐
                        Servidores
                           │  (malha)
                    ┌──── SAN ────┐
                    Storages (armazenamento)
```

**Fibre Channel (FC) x iSCSI:**

| | **SAN Fibre Channel (FC)** | **SAN iSCSI** |
|---|---|---|
| **Rede** | Rede de armazenamento **separada** da LAN | Usa a **LAN Ethernet** existente (comandos SCSI **encapsulados em pacotes IP**); não exige rede dedicada |
| **Velocidade** | Mais rápida, até **16 Gbps** | Até **10 Gbps** |
| **Custo/complexidade** | Justa fama de **cara, complexa e difícil de gerenciar** | Mais simples e barata (complemento: por reaproveitar a infraestrutura Ethernet) |
| **Público ideal** | **Grandes** organizações | Organizações de **pequeno e médio porte** |

(iSCSI = *Internet Small Computer System Interface*. A figura do slide mostra servidores com *initiators* ligados por um switch gigabit a *iSCSI appliances* (*targets*), com roteador e firewall em direção à nuvem.)

#### 7. Vantagens de clusters

| Vantagem | Explicação |
|---|---|
| **Escalabilidade absoluta** | Podem ter dezenas, centenas e até milhares de nós |
| **Escalabilidade incremental** | O poder cresce aos poucos, **adicionando nós** |
| **Alta disponibilidade** | Cada nó é um computador independente; a falha de um **não compromete o cluster todo** |
| **Custo-benefício** | Mais barato (e viável!) que uma única máquina gigante; ajustar o nível de atividade e o número de nós ativos à demanda **economiza energia** e aumenta a vida útil dos equipamentos |

#### 8. Gerenciamento de falhas: failover e failback

* **Failover (recuperação de falhas):** trocar as aplicações e os recursos de dados de um nó que **falhou** para um nó **alternativo**.
* **Failback (retorno da falha):** **devolver** as aplicações e os dados ao nó **original** quando ele for consertado.

```
 Normal:      [Nó A] ativo      [Nó B] reserva
 Nó A cai:    [Nó A] X          [Nó B] assume   <- FAILOVER
 A consertado:[Nó A] volta      [Nó B] reserva  <- FAILBACK
```

#### 9. Comutador e distribuição de requisições

* O **comutador** distingue os serviços e **repassa as requisições às máquinas corretas**. É o **ponto de entrada** do cluster, com **um único endereço de rede** (visão de sistema único).
* Oferece **transparência de acesso**: clientes remotos não precisam conhecer a organização interna do cluster.
* **Organização em três camadas (figura 3.11 do slide):** (1ª) **comutador lógico** (possivelmente múltiplo) recebe a requisição do cliente e a despacha; (2ª) **servidores de aplicação/computação**; (3ª) **sistema distribuído de arquivos/banco de dados**.

```
 Requisição ─> [Comutador lógico] ─> [Servidores de aplicação] <─> [Arquivos / Banco de dados]
  do cliente      1ª camada              2ª camada                    3ª camada
```

**Problema do ponto único de acesso:** se o comutador falha, o **cluster inteiro fica indisponível**. Solução: oferecer **vários pontos de acesso**, mas isso ainda exige que os clientes **tentem de novo** em caso de falha e requer pontos de acesso **estáticos**.

**Distribuição por DNS** (muito popular em aplicações web):

1. O cliente informa um **nome de domínio** a um servidor DNS local, que devolve o **IP** do serviço (possivelmente após consultar outros servidores DNS).
2. O cliente envia seu **próprio IP** junto com a consulta; assim, o servidor DNS pode escolher o **melhor servidor para esse cliente** (um IP próximo).
3. O DNS também pode devolver **vários endereços** do mesmo nome usando **round-robin**.

**Servidores distribuídos:** um conjunto de máquinas, possivelmente variável dinamicamente, atua como ponto de acesso e se apresenta ao mundo como **uma única máquina poderosa**. Usa o **suporte de mobilidade do IPv6** para ter um ponto de acesso que muda dinamicamente. Vantagens: **alto desempenho** e **flexibilidade**.

#### 10. Balanceamento de carga

* **O que é:** distribuir a carga entre os nós disponíveis. É **requisito para a escalabilidade incremental**: o balanceador deve **incluir o novo nó** na distribuição.
* **Benefícios:**
  * **Tolerância a falhas:** detecta problemas de um nó e redireciona o tráfego para os disponíveis;
  * **Evita gargalos:** permite prever o tráfego para adicionar/remover nós com antecedência;
  * Envia a carga ao **nó mais apto** a atender a requisição.
* **Algoritmo de balanceamento** = conjunto de regras que o balanceador segue para escolher o melhor servidor para cada requisição.

| | **Estático** | **Dinâmico** |
|---|---|---|
| **Critério** | Regras **fixas**, independentes do estado atual do servidor | **Examina o estado atual** dos servidores antes de distribuir |
| **Políticas** | Round-robin, Round-robin ponderado, Hash IP | Conexão mínima, Conexão mínima ponderada, Menor tempo de resposta, Baseado em recursos |

**Políticas estáticas:**

| Política | Como funciona |
|---|---|
| **Round-robin** | **Rodízio** de nós: a cada requisição, o próximo da fila é escolhido |
| **Round-robin ponderado** | Cada nó tem um **peso**; quem tem maior peso recebe **mais tráfego** |
| **Hash IP** | O balanceador aplica uma função **hash** ao IP do cliente, que vira um número mapeado a um servidor específico |

**Políticas dinâmicas:**

| Política | Como funciona | Observação |
|---|---|---|
| **Conexão mínima** | Envia para o servidor com **menos conexões ativas** (conexão = canal aberto entre cliente e servidor) | Pressupõe que todas as conexões exigem o mesmo poder de processamento |
| **Conexão mínima ponderada** | Cada servidor tem um **peso/capacidade**; a nova requisição vai para o que tem **menos conexões por capacidade** | Considera que alguns servidores aguentam mais conexões que outros |
| **Menor tempo de resposta** | Combina o **tempo de resposta** (tempo total para processar e responder) com as **conexões ativas** para achar o melhor servidor | Garante serviço mais rápido a todos |
| **Baseado em recursos** | Um **agente** (software) em cada servidor calcula o uso de recursos (computação, memória); o balanceador só envia tráfego se houver recursos livres suficientes | Também pode equalizar a taxa de utilização entre os servidores |

Exemplo numérico simples (complemento) para fixar a diferença: com 3 servidores A, B, C e 6 requisições, o **round-robin** manda A, B, C, A, B, C. Se A tiver peso 2 no **ponderado**, ficaria A, A, B, C, A, A... (A recebe o dobro). Já na **conexão mínima**, se A tem 10 conexões abertas e B tem 2, a próxima vai para B.

#### 11. Serviços do middleware de um cluster (Single System Image)

O middleware cria a ilusão de **sistema único (SSI, Single System Image)**. Os serviços listados:

| Serviço | O que oferece |
|---|---|
| **Ponto de entrada único** | O usuário faz *logon* no **cluster**, não em uma máquina individual |
| **Hierarquia única de arquivos** | Uma só árvore de diretórios sob o mesmo diretório raiz |
| **Ponto de controle único** | Uma estação de trabalho padrão para **gerenciar e controlar** o cluster |
| **Rede virtual única** | Qualquer nó acessa qualquer ponto do cluster, mesmo que haja várias redes interconectadas |
| **Espaço único de memória** | **Memória compartilhada distribuída (DSM)**: programas compartilham variáveis |
| **Sistema único de gerenciamento de trabalhos** | Com um **agendador de jobs**, o usuário submete o trabalho sem dizer qual computador o executará |
| **Interface de usuário única** | Uma interface gráfica comum, de qualquer estação de acesso |
| **Espaço de E/S único** | Qualquer nó acessa remotamente qualquer periférico/disco sem saber onde ele está |
| **Espaço único de processos** | Identificação uniforme de processos; um processo em qualquer nó cria ou se comunica com processos em nós remotos |
| **Pontos de verificação (checkpoints)** | Salvam **periodicamente** o estado dos processos e resultados intermediários, permitindo recuperação após falhas |
| **Migração de processos** | Mover processos entre nós; **habilita o balanceamento de carga** |

#### 12. Exemplos reais (conforme os slides)

| Sistema | Local | Números dos slides |
|---|---|---|
| **OSCAR** (cluster do IC-UFF) | Instituto de Computação da UFF | 42 máquinas (1 para login e compilação, 1 para manutenção e monitoramento, 40 para cálculo); 14,5 TB de armazenamento; cada máquina com 2 Intel Xeon quadcore (8 cores); "totalizando 240 núcleos" |
| **Santos Dumont** | LNCC (Laboratório Nacional de Computação Científica) | "O computador mais rápido da América Latina"; 756 nós, 18.144 núcleos; 1,7 PB de armazenamento |
| **Frontier** | Oak Ridge Leadership Computing Facility (OLCF), Tennessee, EUA; produzido pela HP | 9.472 CPUs AMD Epyc 7453s "Trento" (64 núcleos a 2 GHz; 606.208 núcleos); 37.888 GPUs Radeon Instinct MI250X de 128 GB (8.335.360 núcleos); 74 racks com 64 blades de 2 nós cada; nó = 1 Epyc + 4 GPUs + 4 TB de memória flash + 512 GB de RAM; desempenho máximo de 1.102 exaFLOPS e 700 PB de armazenamento (75 TB/s de leitura e 35 TB/s de gravação) |

> ⚠️ **Observação de estudo:** no slide do OSCAR, 40 máquinas de cálculo x 8 núcleos dariam 320; o slide informa 240 núcleos. Os números acima seguem **exatamente o slide**; para a prova, repita o que o slide diz e, se perguntarem, mencione que o total se refere ao informado no material.

---

### 🔍 Tópico em Destaque: Computação em Grade vs. Computação em Cluster

| Característica | **Cluster** | **Grid** |
|---|---|---|
| **Acoplamento** | Fortemente acoplado | Fracamente acoplado |
| **Homogeneidade** | Homogêneo (nós idênticos, mesmo SO) | Altamente heterogêneo (SOs, redes, capacidades diferentes) |
| **Rede** | LAN de alta velocidade, topologia estável | Redes diversas, alta latência e falhas |
| **Administração** | Uma única entidade administrativa | Múltiplos domínios administrativos e políticas de segurança |
| **Objetivo** | Atuar como **uma única máquina** poderosa (*Single System Image*) | Unir recursos de várias organizações em uma **organização virtual** |
| **Confiabilidade dos nós** | Alta | Baixa (nós podem cair de repente; comum no *volunteer computing*) |
| **Exemplos** | OSCAR, Santos Dumont, Frontier | Projetos de computação voluntária |

* **Acoplamento & Homogeneidade:** Clusters são sistemas fortemente acoplados e homogêneos (mesmo SO, nós idênticos e mesma rede local dedicada), enquanto Grids são fracamente acoplados e altamente heterogêneos (diferentes sistemas operacionais, redes WAN e domínios administrativos distintos).
* **Objetivo & Administração:** O Cluster busca atuar como uma única máquina unificada sob uma única entidade administrativa (Single System Image). O Grid une recursos dispersos geograficamente pertencentes a múltiplas organizações para formar uma Organização Virtual cooperativa.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Limites de Processamento Sequencial:** O aumento contínuo de desempenho de processadores sequenciais encontrou um limite físico intransponível. Por isso, o ganho de desempenho em sistemas modernos depende essencialmente do paralelismo, usando técnicas como múltiplos processadores simétricos (SMP), GPUs e clusters computacionais.
> ---
> 💡 **Tolerância a Falhas em Clusters (Failover e Failback):** Em sistemas de alta disponibilidade, o comutador detecta automaticamente a queda de um nó. A recuperação é feita através do **failover** (migração de processos e dados para outro nó operacional). Assim que o nó original é reparado, realiza-se o **failback** (retorno das atividades ao hardware de origem).
> ---
> 💡 **Gargalo do Ponto de Entrada Único:** Embora um ponto de entrada centralizado (comutador) ofereça transparência de acesso, ele representa um ponto único de falha (*Single Point of Failure*). Soluções para contornar isso incluem a definição de múltiplos pontos de acesso utilizando distribuição de requisições baseada em servidores DNS (ex.: DNS *round-robin*) ou mecanismos de mobilidade para IPv6.
> ---
> 💡 **Não confunda:** SAN x NAS (SAN = rede dedicada, armazenamento em blocos, compartilhado entre servidores; NAS = um servidor controla o armazenamento e administra as transferências); estático x dinâmico (estático ignora o estado do servidor, dinâmico o consulta); failover x failback (failover = *sair* do nó que falhou; failback = *voltar* ao nó original).
> ---
> 💡 **Supercomputadores de Referência:** A aula destaca alguns exemplos reais de grande relevância:
> * **OSCAR (IC-UFF):** O cluster local do IC-UFF, composto de 42 máquinas (40 de cálculo, 1 de compilação/login e 1 de manutenção), totalizando 240 núcleos de processamento Intel Xeon e 14,5 TB de capacidade.
> * **Santos Dumont (LNCC):** Instalado no Laboratório Nacional de Computação Científica, é conhecido como o computador mais rápido da América Latina, possuindo 756 nós computacionais e 18.144 núcleos.
> * **Frontier (OLCF/EUA):** Desenvolvido pela HP, opera na escala de *Exaflops* (1.102 exaFLOPS), sendo composto por 9.472 CPUs AMD Epyc e 37.888 GPUs Radeon Instinct distribuídos em 74 racks.

---

### 🧪 Exercícios e Gabarito Comentado

Resumo das 17 questões do gabarito (`Aula02-gab.pdf`), em linguagem simples.

**1. Explique a taxonomia de Flynn.**
Classifica arquiteturas em 4 categorias pelo fluxo de instruções e de dados: **SISD** (uma instrução, um dado; uniprocessador), **SIMD** (uma instrução, vários dados; mesma instrução em dados diferentes), **MISD** (várias instruções, um dado; sem uso comercial) e **MIMD** (várias instruções, vários dados; SMPs, clusters e NUMA).

**2. Explique arquiteturas MIMD de memória compartilhada e distribuída.**
*Compartilhada:* CPUs ligadas a uma memória principal com espaço de endereçamento único por barramento rápido; o tempo de acesso pode ser igual (UMA) ou variar (NUMA). *Distribuída:* cada CPU (ou grupo) tem seu próprio espaço de memória e se liga às outras por rede.

**3. Características de um grid computacional?**
Altamente heterogêneo (rede, SOs, domínios administrativos, políticas de segurança, capacidade dos nós) e com nós fracamente acoplados.

**4. Explique a arquitetura de grid vista em aula.**
Cinco camadas: **fabric** (interface com recursos locais), **connectivity** (comunicação e segurança), **resource** (gerencia um recurso), **collective** (gerencia vários recursos: descoberta, agendamento, replicação) e **application**. Resource + collective + connectivity formam o middleware de grade.

**5. O que é volunteer computing?**
Usuários doam recursos subutilizados dos seus computadores para processar dados de aplicações acadêmicas e científicas, geralmente otimizadas para processamento paralelo.

**6. O que é um cluster computacional?**
Um supercomputador feito de vários computadores baratos e de menor poder, ligados por rede rápida (antes PCs e workstations; hoje datacenters).

**7. Características de um cluster?**
Homogêneo e fortemente acoplado: nós semelhantes/idênticos, LAN de alta velocidade, topologia estável e mesmo SO (ou SO distribuído em todos os nós).

**8. Explique a arquitetura de um data center.**
Blades (CPU + memória + disco) ficam em racks (energia + rede local rápida); o switch de cada rack se conecta a **switches de agregação** que interligam todos os racks. O datacenter abriga computadores, telecomunicações e armazenamento. Os racks formam corredores quentes e frios para eficiência do resfriamento. Um cluster pode ter um ou mais datacenters dispersos.

**9. Explique os modos de clusterização de nós.**
A questão traz a tabela de 5 métodos (secundário passivo, secundário ativo, servidores separados, conectados aos discos e que compartilham discos) com descrição, benefícios e limitações: veja a tabela na seção [Modos de clusterização](#5-modos-de-clusterização-de-nós-tabela-do-slide-e-do-gabarito). Resumo: passivo é simples mas desperdiça o secundário; ativo aproveita-o mas é mais complexo; separados copiam dados (sobrecarga); conectados aos discos evitam cópias (pedem RAID); compartilhando discos têm baixa carga (pedem gerenciamento de bloqueio).

**10. O que é uma SAN?**
Rede especializada que dá acesso rápido e confiável entre servidores e armazenamento externo; o armazenamento é compartilhado entre os servidores como recursos de mesmo nível; pode conectar servidores a armazenamento, servidores entre si e armazenamento entre si; usa armazenamento em blocos, com protocolos especiais.

**11. Fibre Channel x iSCSI.**
FC: mais rápida (até 16 Gbps), rede separada da LAN, cara e complexa, ideal para grandes organizações. iSCSI: comandos SCSI em pacotes IP sobre a LAN Ethernet, sem rede dedicada, até 10 Gbps, ideal para pequeno/médio porte.

**12. Defina failover e failback.**
Failover: passar aplicações e dados de um nó que falhou para um alternativo. Failback: devolvê-los ao nó original quando consertado.

**13. Importância do balanceamento de carga?**
É requisito para escalabilidade incremental (o novo nó entra na distribuição), e melhora disponibilidade, escalabilidade e desempenho: detecta nós com problema e redireciona tráfego, evita gargalos e envia a carga ao nó mais apto.

**14. Balanceamento estático x dinâmico.**
Estático segue regras fixas, independentes do estado atual do servidor; dinâmico examina o estado atual dos servidores antes de distribuir.

**15. Três políticas estáticas.**
Round-robin (rodízio), round-robin ponderado (pesos: mais peso, mais tráfego) e Hash IP (hash do IP do cliente mapeia para um servidor).

**16. Quatro políticas dinâmicas.**
Conexão mínima (menos conexões ativas), conexão mínima ponderada (menos conexões por capacidade), menor tempo de resposta (combina tempo de resposta e conexões ativas) e baseada em recursos (agentes medem CPU/memória em cada servidor).

**17. Serviços de um middleware de cluster.**
Ponto de entrada único, hierarquia única de arquivos, ponto de controle único, rede virtual única, espaço único de memória, sistema único de gerenciamento de trabalhos, interface de usuário única, espaço de E/S único, espaço único de processos, pontos de verificação e migração de processos (11 serviços; detalhes na tabela da seção 11).

---

### 🧠 Perguntas de Revisão

1. **Por que não basta fazer processadores cada vez mais rápidos?**
   Há um limite físico; por isso se usa paralelismo (SMP, GPUs, computadores em rede).
2. **Em qual categoria de Flynn se encaixam os clusters e por quê?**
   MIMD: vários processadores executam instruções diferentes sobre dados diferentes ao mesmo tempo (memória distribuída, fracamente acoplada).
3. **Qual a diferença essencial entre grid e cluster?**
   Cluster é homogêneo e fortemente acoplado, numa LAN e sob uma administração; grid é heterogêneo, fracamente acoplado e reúne recursos de várias organizações (organização virtual).
4. **O que são failover e failback e quando ocorrem?**
   Failover: ao falhar um nó, o trabalho vai para outro. Failback: quando o nó original é reparado, o trabalho volta a ele.
5. **Qual o risco de um único ponto de entrada (comutador) e como mitigá-lo?**
   É ponto único de falha: se cai, o cluster inteiro fica indisponível. Mitiga-se com vários pontos de acesso, DNS (inclusive round-robin) ou mobilidade IPv6.
6. **Diferencie SAN Fibre Channel e iSCSI.**
   FC: rede dedicada, até 16 Gbps, cara, para grandes organizações. iSCSI: SCSI sobre IP na LAN, até 10 Gbps, para pequeno/médio porte.
7. **Dê um exemplo de balanceamento estático e um de dinâmico e explique a diferença.**
   Estático: round-robin (rodízio, ignora a carga real). Dinâmico: conexão mínima (consulta quantas conexões cada servidor tem agora).
8. **O que é Single System Image e quais serviços de middleware a sustentam?**
   Ilusão de uma única máquina; sustentada por ponto de entrada único, hierarquia única de arquivos, espaço único de memória/processos/E/S, gerenciamento único de trabalhos, checkpoints e migração de processos.

---

### 🔗 Conexão com o Trabalho Final

* Serviços de um cluster ficam atrás de um **ponto de entrada com balanceamento de carga**; ao demonstrar APIs REST e serviços gRPC, é nesse tipo de ambiente (várias instâncias do mesmo serviço) que eles costumam rodar em produção (complemento).
* Em **RabbitMQ** e **Kafka**, vários consumidores podem dividir o trabalho de uma fila/tópico, o que lembra a distribuição de carga entre nós; e os conceitos de **alta disponibilidade, failover e escalabilidade incremental** desta aula se aplicam diretamente a brokers em cluster (complemento).

---

### 📚 Links & Leituras Complementares

* 📖 *Arquitetura e Organização de Computadores* (William Stallings, 10ª Edição) — Capítulo 17, Seções 17.1 e 17.5
* 📖 *Redes de Computadores e a Internet* (James Kurose, 8ª Edição) — Seção 6.6
* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª Edição) — Seção 1.3.1

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 1: Introdução aos Sistemas Distribuídos](../Aula_1/README.md)
* ➡️ **Próxima Aula:** [Aula 3: Virtualização e Computação em Nuvem](../Aula_3/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
