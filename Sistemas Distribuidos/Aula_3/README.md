# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 18/08/2026 | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 03: Virtualização e Computação em Nuvem

### 📝 Introdução

A terceira aula da disciplina **TCC00362 — Sistemas Distribuídos para Sistemas de Informação** (Prof. Raphael Guerra) tem três grandes blocos, que se encaixam como uma "escada":

1. **Máquinas Virtuais (MVs):** o que são, quais requisitos precisam cumprir, os tipos de hipervisor (0, 1 e 2), paravirtualização, emuladores, contêineres e as técnicas que fazem tudo isso funcionar (trap-and-emulate, NPT, overcommitment, balloon e compartilhamento de páginas).
2. **Virtualização de servidores em datacenters:** por que as empresas viraram "fãs" de MVs (consolidação, legado, recuperação de desastres, alta disponibilidade, escalabilidade, computação sob demanda, ciclo de desenvolvimento e ensino).
3. **Computação em Nuvem:** a definição, as 5 características essenciais, os modelos de precificação, os 3 modelos de serviço (IaaS, PaaS, SaaS), os 4 modelos de implantação e a arquitetura de referência com seus 5 atores.

> 🪜 **Ideia central:** a virtualização é a **tecnologia** que permite dividir uma máquina física em várias máquinas "de mentira". A nuvem é o **modelo de negócio** que usa essa tecnologia para alugar recursos de computação sob demanda.

**Sumário rápido:** [Máquinas Virtuais](#-parte-1--máquinas-virtuais) · [Virtualização em Datacenters](#-parte-2--virtualização-de-servidores-em-datacenters) · [Computação em Nuvem](#-parte-3--computação-em-nuvem) · [Exercícios](#-exercícios-e-gabarito-comentado) · [Revisão](#-perguntas-de-revisão)

---

### 💡 Conceitos Chave

## 🖥️ Parte 1 — Máquinas Virtuais

#### 1.1 Visão geral

* **Máquina virtual (MV):** camada de software que abstrai o hardware de uma máquina física (CPU, memória, discos, placas de rede...) em vários ambientes de execução, criando a **ilusão** de que cada ambiente roda em seu próprio computador privado.
* É parecida com a **abordagem em camadas**: cada camada é uma MV sobre a qual rodam sistemas operacionais e aplicações.
* É um conceito **antigo** (década de 70) que foi **popularizado a partir da década de 90**.

#### 1.2 Componentes

| Componente | O que é |
|---|---|
| **VMM (Virtual Machine Monitor) ou Hipervisor** | Cria e executa as MVs. Abstrai o hardware físico do hardware virtualizado, assim como o SO abstrai o hardware do software. Oferece uma interface **idêntica** ao hardware real (exceto na paravirtualização). |
| **Guest (convidado)** | Processo que executa sobre o hardware virtual, normalmente um sistema operacional. A plataforma de hardware é idêntica à do host; na **emulação** ela pode ser diferente. |
| **Host (hospedeiro)** | A máquina física (MF) onde as MVs rodam. |

#### 1.3 Modelo arquitetural (figura do slide)

```
 SEM MÁQUINA VIRTUAL            COM MÁQUINA VIRTUAL
 ┌───────────────────┐          ┌────────┬────────┬────────┐
 │    processos      │          │ proces.│ proces.│ proces.│
 ├───────────────────┤          ├────────┼────────┼────────┤
 │      kernel       │          │ kernel │ kernel │ kernel │
 ├───────────────────┤          ├────────┼────────┼────────┤
 │     hardware      │          │  MV 1  │  MV 2  │  MV 3  │
 └───────────────────┘          ├────────┴────────┴────────┤
                                │ virtual machine manager  │
                                ├──────────────────────────┤
                                │         hardware         │
                                └──────────────────────────┘
```

Sem MV, há **um** kernel sobre o hardware. Com MV, o hipervisor fica entre o hardware e **vários** kernels, cada um achando que é o único dono da máquina.

#### 1.4 Os 3 requisitos da virtualização

| Requisito | Significado |
|---|---|
| **Fidelidade** | O hipervisor oferece um ambiente de execução **idêntico** ao ambiente físico original. |
| **Desempenho** | Programas no ambiente virtualizado **não perdem desempenho** em comparação a um ambiente físico real. |
| **Proteção (isolamento)** | O hipervisor tem **total controle** sobre os recursos físicos; as MVs **não podem afetar** outras MVs nem o hipervisor. |

#### 1.5 Uma MV é definida em arquivos

* Os **atributos do hardware virtualizado** ficam registrados em arquivos: quantidade de CPUs e especificações, RAM, dispositivos de E/S, placas de rede (NICs) e armazenamento (discos virtuais).
* Por isso, **copiar os arquivos é mais do que um backup de dados**: copia-se a **configuração do "hardware"** e o **estado de execução** da máquina.

#### 1.6 Vantagens das MVs

| Vantagem | Explicação |
|---|---|
| **Consolidação** | Um hardware físico atende várias aplicações (taxa de consolidação **N:1**: N MVs em 1 host). Compartilhar recursos reduz custo e maximiza os tipos de aplicação por máquina física. |
| **Hardware legado** | Aplicações feitas para hardware antigo vão para hardware moderno **sem alterar a aplicação** (transparente). |
| **Versatilidade** | MVs iniciam e desligam rapidamente; dá para ter vários ambientes na mesma MF (testes, desenvolvimento etc.). |
| **Clonagem** | Cópia da MV com seu estado atual (configuração de hardware e software instalado). **Templating:** usar uma MV pré-configurada como molde para várias instâncias. |
| **Suspensão rápida e flexível** | Parar a MV e reiniciá-la **com o mesmo estado**. **Relocação:** mudar de host *entre* operações (MV parada). **Migração:** mudar de host *durante* a operação. |

#### 1.7 Funções do hipervisor

1. **Gestão da execução das MVs:** cada MV enxerga só os recursos físicos para os quais foi configurada; uma MV não afeta outra nem o host (isolamento).
2. **Emulação de dispositivos e controle de acesso:** permite compartilhar recursos físicos, p. ex. uma placa de rede.
3. **Execução de operações privilegiadas:** só o hipervisor tem acesso ao modo privilegiado.
4. **Gerenciamento das MVs:** iniciar, pausar, clonar etc.
5. **Gerenciamento do hardware físico:** como qualquer kernel faz.

#### 1.8 Tipos de hipervisor

**Tipo 0 — particionamento físico ou de hardware**

* Implementado em **firmware**. Exemplos: **IBM LPARs** e **Oracle LDOMs**.
* Cria **partições lógicas** dos recursos físicos; cada guest enxerga um **subconjunto** dos recursos do host.
* Os guests rodam **diretamente no hardware** (nativamente), sem traduções. Exige cuidado especial com E/S (p. ex. placa de rede).
* ✅ Maior isolamento e menor overhead. ❌ Subutilização de recursos, baixa portabilidade e suporte limitado a sistemas operacionais.
* Tipicamente **não é visto como virtualização** de fato.

**Tipo 1 — *bare metal***

* Executa **direto no hardware, em modo kernel** (compatível com partições do Tipo 0). É dedicado a criar, executar e gerir MVs.
* Exemplos: **VMware ESX, Joyent SmartOS, Citrix XenServer**. Também existem os **integrados ao kernel do SO host**: **Hyper-V** (Windows Server) e **KVM** (Linux).
* Assim como um SO, cuida de **drivers de dispositivos, CPU e memória, proteção e segurança**.
* Permite **migrar, clonar e reconfigurar** MVs e explora vários níveis de acesso da CPU para **reduzir as intervenções** do hipervisor nas operações dos SOs convidados.
* **Muito popular em datacenters.**

**Tipo 2 — *hosted***

* O hipervisor roda **sobre um SO nativo, como um processo comum de usuário**. O SO nativo **não tem ciência** do hipervisor.
* O usuário precisa de **direitos de administrador** no SO nativo para acessar certos recursos.
* ✅ **Portabilidade** entre hosts (Windows, Linux, Mac...). Popular para **ambientes de teste**: VMware Workstation e Oracle VM VirtualBox.
* ❌ **Pior desempenho** que Tipo 0 e 1: o guest não controla o hardware diretamente e o hipervisor precisa fazer mais intervenções (overhead).

```
 TIPO 1 (bare metal)                TIPO 2 (hosted)
 ┌─────────┬─────────┐              ┌─────────┬─────────┐
 │ Apps    │ Apps    │              │ Apps    │ Apps    │
 │ Libs    │ Libs    │              │ Libs    │ Libs    │
 │ Guest OS│ Guest OS│              │ Guest OS│ Guest OS│
 ├─────────┴─────────┤              ├─────────┴─────────┤
 │ Hipervisor Tipo 1 │              │ Hipervisor Tipo 2 │
 ├───────────────────┤              ├───────────────────┤
 │ Hardware          │              │ SO hospedeiro     │
 └───────────────────┘              ├───────────────────┤
                                    │ Hardware          │
                                    └───────────────────┘
```

| | Tipo 0 | Tipo 1 | Tipo 2 |
|---|---|---|---|
| Onde roda | Firmware | Direto no hardware (modo kernel) | Como processo sobre um SO |
| Exemplos | IBM LPARs, Oracle LDOMs | VMware ESX, XenServer, SmartOS, Hyper-V, KVM | VMware Workstation, VirtualBox |
| Desempenho | Menor overhead | Bom (reduz intervenções do hipervisor) | Pior (mais intervenções) |
| Portabilidade | Baixa | — (não destacada nos slides) | Alta |
| Uso típico | Partições fixas | Datacenters | Testes / desktop |

#### 1.9 Paravirtualização

* O **SO guest é modificado** para chamar diretamente o hipervisor (as chamadas são conhecidas como *hypercalls* — complemento).
* A MV **não é idêntica** a um sistema físico real; o guest **sabe** que existe um hipervisor. Isso **reduz o overhead**.
* Exemplo do slide: **VirtIO** (paravirtualização de E/S).
* O **suporte de hardware** para virtualização reduz a necessidade de paravirtualização: **AMD-Vi (antigo AMD-V)**, **Intel VT-d e VT-x**.

```
 (a) Hipervisor Tipo 1 "puro"          (b) Hipervisor Tipo 1 paravirtualizado
 ┌──────────┐ ┌──────────┐             ┌──────────┐ ┌──────────┐
 │ Guest OS │ │ Guest OS │             │ Guest OS │ │ Guest OS │
 │ drivers  │ │ drivers  │             │ drivers  │ │ drivers  │
 │ REAIS    │ │ REAIS    │             │ MODIFICA-│ │ MODIFICA-│
 └────┬─────┘ └────┬─────┘             │ DOS      │ │ DOS      │
      ▼            ▼                   └────┬─────┘ └────┬─────┘
 ┌──────────────────────────┐               ▼            ▼
 │ Hipervisor: modelos de   │          ┌──────────────────────────┐
 │ dispositivo (hw emulado) │          │ Hipervisor: interface de │
 │ + drivers reais          │          │ drivers + drivers reais  │
 └──────────────────────────┘          └──────────────────────────┘
```

Em (a) o hipervisor precisa **emular** um dispositivo para o guest. Em (b) o guest já "fala a língua" do hipervisor, o que corta o trabalho de emulação.

#### 1.10 Máquina virtual de processo

* Também **foge do nosso conceito** de virtualização: a MV **não representa um hardware real**.
* É um ambiente personalizado que oferece **APIs para executar um único processo**.
* Exemplos: linguagens interpretadas em geral (**JVM**, Python) e **Wine** (executa programa Windows no Linux).

#### 1.11 Emuladores

* As MVs vistas até aqui oferecem a **mesma arquitetura do host**. Às vezes queremos rodar programas compilados para **outra arquitetura**: é preciso **traduzir instruções de máquina**, ou seja, "escrever uma CPU em software".
* **Maior desafio: desempenho.** Uma instrução do guest vira **várias** instruções nativas, então o host precisa ser **bem mais potente** que a arquitetura emulada.
* Popular entre gamers: emular consoles antigos em máquinas modernas.

#### 1.12 Contêineres

* Executam **sobre o SO nativo** e **não virtualizam hardware**, logo **não precisam de SO interno**. Isso economiza recursos e reduz overhead.
* Baseados em **kernel control groups (cgroups)**: estrutura hierárquica de processos em que cada grupo é uma partição com **alocação própria de recursos** (CPU, memória, E/S), **contabilidade e controle individuais** e **ambiente de execução** (pilha de rede, IPC, processos etc.).
* **Container Engine:** ambiente de execução leve e isolado (toolchains, bibliotecas, dependências). Cria um processo para o contêiner, gerencia o sistema de arquivos, controla acessos e **requisita recursos ao kernel do SO nativo**.

```
 (a) Hipervisor Tipo 1   (b) Hipervisor Tipo 2     (c) CONTÊINER
 ┌─────┬─────┐           ┌─────┬─────┐             ┌──────┬──────┐
 │Apps │Apps │           │Apps │Apps │             │ Apps │ Apps │
 │Libs │Libs │           │Libs │Libs │             │ Libs │ Libs │
 │Guest│Guest│           │Guest│Guest│             ├──────┴──────┤
 │ OS  │ OS  │           │ OS  │ OS  │             │Container    │
 ├─────┴─────┤           ├─────┴─────┤             │Engine       │
 │Hipervisor │           │Hipervisor │             ├─────────────┤
 ├───────────┤           ├───────────┤             │ SO host     │
 │ Hardware  │           │ SO host   │             ├─────────────┤
 └───────────┘           ├───────────┤             │ Hardware    │
                         │ Hardware  │             └─────────────┘
                         └───────────┘
```

**Overhead de E/S (figura do slide):**

```
 Hipervisor                          Contêiner
 Aplicação                           Aplicação
   ▼                                   ▼
 Driver do SO guest                  Indireção via kernel control groups
   ▼                                   ▼
 Dispositivo de E/S virtual          Driver do dispositivo físico
   ▼                                   ▼
 Interceptação do hipervisor         Dispositivo de E/S físico
   ▼
 Driver do dispositivo físico
   ▼
 Dispositivo de E/S físico
```

O caminho do contêiner é bem mais curto, por isso o overhead é menor.

| Vantagens dos contêineres | Desvantagens dos contêineres |
|---|---|
| Compartilham o mesmo SO e as mesmas bibliotecas | Todos os ambientes virtualizados precisam ser **compatíveis com o SO nativo** |
| São isolados entre si | **Não são portáveis entre SOs** |
| **Menor overhead** | **Não servem** para aplicações que exigem **alto nível de isolamento** |

#### 1.13 Técnicas de virtualização

O slide lista cinco técnicas: **trap-and-emulate, Nested Page Tables (NPT), overcommitment, balloon memory manager e compartilhamento de páginas.**

**a) Trap-and-emulate**

* **Problema:** CPUs "dual-mode" têm só modo **kernel** e **usuário**, e apenas o hipervisor pode usar o modo kernel (para garantir proteção e isolamento). Mas o SO guest *acha* que roda em modo kernel.
* **Solução:** criam-se um **modo kernel virtual** e um **modo usuário virtual**; **ambos executam fisicamente em modo usuário**.
* **Funcionamento:**
  1. Instruções **não privilegiadas** do guest executam **direto** na CPU.
  2. Quando o guest tenta uma instrução **privilegiada**, ocorre uma **trap** (desvio para o hipervisor).
  3. O hipervisor **executa a ação em nome do guest** (emula), atualiza a **VCPU** (CPU virtual) e **retorna** o resultado ao guest.
  4. Operações indevidas **não são realizadas** (isolamento).

```
 guest (modo usuário)  │  instrução privilegiada ──trap──┐
                       │                                  ▼
 VMM (modo kernel)     │            emula a ação ──atualiza──► VCPU
                       │                                  │
 guest                 │  ◄───────────── retorno ─────────┘
```

* **Custo:** a cada instrução privilegiada há **chaveamento de processo e de modo** (overhead).
* **Solução do slide:** CPUs novas têm **suporte em hardware** à virtualização (ex.: **Intel VT-d e VT-x**), com vários modos de operação que evitam a intervenção do hipervisor mantendo o isolamento. Há também gerenciamento de CPUs virtuais.

**b) Nested Page Tables (NPT) — tabelas de páginas aninhadas**

* O **guest** gerencia sua tabela de páginas normalmente (página → quadro), mas **não sabe** que esses quadros não são memória física real: são "quadros virtuais", da MV.
* O **hipervisor** mantém **outra tabela** que traduz quadro virtual (da MV) → quadro físico real (do host).

```
 endereço virtual do guest = [página | deslocamento]
          │ tabela de páginas do GUEST (página → quadro virtual da MV)
          ▼
 endereço físico da MV      = [quadro virtual | deslocamento]
          │ tabela de páginas do VMM (quadro virtual → quadro físico)
          ▼
 endereço físico do host    = [quadro físico | deslocamento]
```

* O **suporte de hardware reduz o overhead**: a **MMU** (controlador de memória, em hardware) usa as duas tabelas **aninhadas**. Uma falta de página no guest **só exige o hipervisor** se o quadro virtual ainda **não estiver alocado** a um quadro físico.
* Implementações: **EPT (Extended Page Table)** da **Intel** e **RVI (Rapid Virtualization Indexing)** da **AMD**. (O slide escreve "NTP" por engano em vez de NPT.)

**c) Overcommitment (supercomprometimento)**

* O **somatório dos recursos alocados às MVs é maior que o disponível fisicamente**.
* Explora o fato de as MVs serem **subutilizadas**: o hipervisor **remaneja** recursos entre elas.
* ⚠️ **Mau desempenho** se **todas** as MVs pedirem o total ao mesmo tempo. E não faz sentido o excesso ficar em apenas uma MV.
* Exemplo (complemento): 4 MVs com 8 GB cada em um host com 16 GB; funciona enquanto não usarem tudo ao mesmo tempo.

**d) Balloon Memory Manager**

* **Problema:** os SOs **não suportam** alterar dinamicamente a quantidade de memória disponível.
* **Técnica:** o hipervisor **força o guest a fixar páginas na memória principal**, reduzindo o espaço livre dele. Requer um **driver especial no kernel do guest**. O hipervisor ajusta a memória de cada MV **sob demanda**.
* No gabarito, a mesma ideia é descrita como o hipervisor forçar o guest a enviar páginas da RAM para a memória virtual (**disco**); o guest libera memória, e o hipervisor a **realoca para outra MV**.
* Analogia (complemento): o "balão" **infla** dentro do guest (ocupa memória, o guest sente falta e libera o resto) e **esvazia** quando a MV precisar de volta.

**e) Compartilhamento de páginas**

* Algumas páginas virtuais têm **exatamente a mesma assinatura**: partes do kernel (se as MVs usam o mesmo SO) e um subconjunto igual de aplicações.
* O hipervisor usa **apenas um quadro** para páginas de MVs diferentes. Se uma MV **alterar** a página, ela ganha um **quadro próprio** (cópia na escrita — complemento).

```
 Memória virtual MV1   Memória virtual MV2   Memória virtual MV3
        [▓]                  [▓]                  [▓]
          └──────────────┬─────┴──────────────┘
                         ▼
                  Memória física: [▓]  (um único quadro)
```

**f) Entre outras técnicas** (citadas, sem detalhar)

* **Comunicação em rede:** várias MVs compartilham uma placa de rede, via **NAT** (Network Address Translation) ou **modo bridge**.
* **Dispositivos de armazenamento:** HD virtual e compartilhamento de arquivos entre MVs.
* **Gerenciamento de interrupções.**

#### 🔍 Tópico em Destaque: Máquinas Virtuais vs. Contêineres

| | **Máquina Virtual** | **Contêiner** |
|---|---|---|
| O que virtualiza | O **hardware** (via hipervisor) | O **SO** (isolamento por cgroups/namespaces) |
| SO próprio? | Sim, cada MV tem um **guest OS** completo | Não, compartilha o **kernel do host** |
| Overhead | Maior (RAM, disco, inicialização) | Menor; caminho de E/S mais curto |
| Isolamento | Forte | Mais fraco |
| Portabilidade | Roda guests diferentes do host | Só ambientes compatíveis com o SO nativo |
| Bom para | Isolamento alto, SOs variados, legado | Muitas instâncias leves, microsserviços (complemento) |

> *Namespaces* aparecem no README original da aula; os slides citam especificamente **cgroups** e "ambiente de execução (rede, IPC, processos)". Tratar *namespaces* como complemento.

---

## 🏢 Parte 2 — Virtualização de Servidores em Datacenters

Benefícios listados: **consolidação, hardware legado, recuperação de desastres, alta disponibilidade, escalabilidade incremental, computação sob demanda, ciclo de vida do desenvolvimento de software e ensino/aprendizagem de software.**

#### 2.1 Consolidação

* Empresas têm vários servidores dedicados (arquivos, impressão, e-mail, web...). Algumas aplicações exigem ou recomendam fortemente servidor dedicado, pois não "convivem bem" com outras no mesmo ambiente.
* Com o tempo, o datacenter acumula **muitos servidores pequenos e subutilizados**, o que aumenta custos.
* Na MV, a aplicação continua com um "servidor dedicado" (hardware e SO totalmente isolados), e **várias MVs ficam em um único servidor físico**.

#### 2.2 Hardware legado

* **Legado:** sistemas desatualizados, possivelmente sem suporte, ou feitos de componentes de versões anteriores; dor de cabeça de muitas áreas de TI.
* Por que existem: **alto custo de substituição**, partes de **missões críticas**, feitos por **terceirizada que não existe mais**, **falta de conhecimento** da equipe para migrar.
* Não escalam bem por limitações do hardware e do ambiente em que rodam.
* **Migrando para MV**, o hardware físico é abstraído: a MV roda em **qualquer MF moderna** que suporte a plataforma de virtualização (portabilidade). Como máquinas novas são mais potentes, o legado passa a **escalar** para demandas maiores.

#### 2.3 Recuperação de desastres

* Estratégia e processos para recuperar infraestrutura e dados **em tempo razoável** após um desastre, garantindo **continuidade do negócio**.
* Estratégia comum: **backup de dados**. Protege contra exclusão acidental, invasão etc., **mas exige reinstalar SO e software** (restaurar SO é trabalhoso por causa dos **drivers**).
* Restaurar um sistema completo é demorado: é preciso hardware adequado; tradicionalmente guarda-se **hardware antigo externamente** para os sistemas mais críticos, e os secundários esperam por mais hardware.
* **Com virtualização:** as MVs são facilmente **restauradas em qualquer hardware compatível**, aproveitando recursos ociosos de MFs já ativas (consolidação). Mesmo servidores **não virtualizados** em produção (por desempenho) podem ter **MVs pré-configuradas** para assumir a demanda temporariamente.

#### 2.4 Alta disponibilidade

* Forma comum: **servidores redundantes** que assumem se o primário falhar. Mas **secundário ocioso custa caro**.
* Com virtualização, o **secundário** consome poucos recursos e fica **hospedado em outra MF junto com outras MVs**, então essa MF não fica ociosa.

#### 2.5 Escalabilidade incremental

* Aplicações muito usadas rodam em vários servidores iguais. Como a demanda **oscila**, **alterar dinamicamente** o número de servidores reduz a subutilização.
* Criar, replicar, reiniciar (**sem perder estado**) e reconfigurar MVs facilita **balanceamento de carga, maximização do uso de recursos e tolerância a falhas** → infraestrutura **altamente dinâmica**.

#### 2.6 Computação sob demanda

* A virtualização permite alocar **rápido** um ou mais servidores para um grupo de usuários por **curto período**, e depois **recuperar e reutilizar** esses recursos quando o tempo expirar ou forem liberados.
* Cada servidor pode ter a **configuração específica** de cada usuário. Sem virtualização, isso é **muito difícil e caro**.

#### 2.7 Ciclo de vida do desenvolvimento de software

* **Problema:** fabricar software é cada vez mais difícil: muitas opções de SO (com hot fixes, patches, service packs), várias versões de navegador e de banco de dados, forte interoperabilidade. Desenvolvedores acabavam mantendo **vários computadores** na mesa.
* **Exemplo do slide:** testar uma aplicação web multicamadas que exige banco (SQL Server **ou** Oracle), SO (Windows 2000, Windows 2003 ou Red Hat), servidor web (IIS, Apache ou NGINX) e navegador (Edge, Chrome, Firefox ou Safari). As combinações crescem **exponencialmente** quando se contam service packs e hot fixes.
* **Solução:** "fatiar" um computador físico em vários computadores individuais, aumentando a produtividade e reduzindo custos com várias imagens virtuais no mesmo computador.
* **Economia (números dos slides):**
  * gastos com hardware reduzidos **imediatamente em 50% a 80%**;
  * atrasa ou elimina a necessidade de mais espaço de laboratório;
  * menos energia, refrigeração, cabeamento e manutenção/gerenciamento.
* **Utilização:** em produção, um servidor costuma ficar entre **5% e 20%** de uso; em desenvolvimento/teste isso é capacidade ociosa e desperdiçada. A virtualização leva o host a **60% a 80%** de utilização.
* **Templates:** imagens-modelo com diferentes SOs, navegadores e idiomas; o QA monta **um banco de testes inteiro instantaneamente**. Mais tempo testando, menos tempo montando ambiente → produto de maior qualidade.
* **Instalação limpa:** sem virtualização, é preciso desinstalador ou reinstalar imagens zeradas. Com MV, o testador **desliga, descarta as alterações e retoma de um estado anterior**; com novo build/patch, atualiza a MV, desliga para confirmar e liga de novo.
* **"Rede em uma caixa":** ambientes de rede isolados e virtuais, sem cabos, sem esperar o TI, com IPs rápidos. Exemplo: uma MV Windows XP com Internet Explorer conversando com uma MV Linux com Apache, tudo **dentro do host**, sem sair para a rede física.
* **Hardware sob demanda:** sem virtualização, pedir hardware envolve justificar, contatar o TI e adquirir. Com virtualização bem feita, é muito mais rápido.
* **Dev + QA trabalham melhor juntos:** achou um bug? Desliga a MV e **copia os arquivos do disco virtual** para a máquina do desenvolvedor, que reproduz o bug e valida a correção sem recriar o cenário.
* ⚠️ **Exceção — testes de desempenho:** a MV divide hardware com outras MVs, com o SO host e com o próprio software de virtualização; isso distorce a medição. Recomenda-se **servidor físico dedicado** (ou grupo deles). A única exceção é se a aplicação for rodar em **produção dentro de uma MV**.

#### 2.8 Ensino e aprendizagem de software

* Alguns softwares dependem do SO (uma máquina para cada SO; **dual boot** mal feito pode corromper o sistema), alguns ambientes têm **configuração complexa** e demorada, e o uso incorreto pode obrigar a **reinstalar tudo**, o que leva os alunos a só seguir passo a passo.
* Com MVs, os alunos têm **prática e liberdade para explorar** sem medo de travar o SO ou corromper a aplicação.

---

## ☁️ Parte 3 — Computação em Nuvem

#### 3.1 Definição

> Modelo para possibilitar o acesso **onipresente, conveniente e sob demanda** a um **agrupamento compartilhado de recursos de computação configuráveis** (redes, servidores, armazenamento, aplicativos e serviços) que podem ser **rapidamente provisionados e liberados** com **esforço mínimo** de gerenciamento ou interação com o provedor.

A nuvem é composta por: **5 características essenciais**, **3 modelos de serviço** e **4 modelos de implantação**.

```
 NUVEM
 ├── 5 características: agrupamento de recursos · autoatendimento sob demanda ·
 │                      amplo acesso à rede · elasticidade · serviços mensuráveis
 ├── 3 modelos de serviço:    IaaS · PaaS · SaaS
 └── 4 modelos de implantação: pública · privada · comunitária · híbrida
```

#### 3.2 As 5 características essenciais

| Característica | Ideia | Detalhes dos slides |
|---|---|---|
| **Agrupamento de recursos** (*resource pooling*) | Recursos do provedor são agrupados para atender vários consumidores (CSCs) em modelo **multilocatário** (*multitenancy*), atribuídos e reatribuídos **dinamicamente** conforme a demanda. | "Economia compartilhada" e **economias de escala** (muitos clientes reduzem o custo por cliente). Há **independência de localização**: o cliente não sabe a localização exata, mas pode escolher em alto nível (país, estado, datacenter). Pequenos negócios acessam poder antes restrito a grandes empresas. Exemplos de recursos: armazenamento, processamento, memória, banda e MVs. Mesmo nuvens privadas agrupam recursos entre áreas da mesma organização. |
| **Autoatendimento sob demanda** | O CSC **provisiona sozinho e automaticamente** capacidade (tempo de servidor, armazenamento) **sem interação humana** com o provedor. | Reduz o tempo de acesso a recursos, aumentando produtividade e competitividade. |
| **Amplo acesso à rede** | Recursos acessíveis por rede de alta velocidade e disponibilidade, via **mecanismos padrão**, por clientes heterogêneos (celulares, laptops, tablets) e outros serviços. | Acessível de qualquer lugar; se precisar de mais banda, não é preciso contatar o provedor de Internet e esperar upgrade. |
| **Elasticidade** | **Expandir e reduzir** recursos rapidamente conforme os requisitos do serviço. | Ex.: muitos servidores durante uma tarefa e liberá-los depois. **Sem superdimensionar** o sistema para o pico. |
| **Serviços mensuráveis** | O sistema **monitora, controla e otimiza** o uso por medição (armazenamento, processamento, banda, contas ativas), com transparência para provedor e consumidor. | Base do **"pague conforme usar"**; permite mover gastos de **CAPEX** (capital) para **OPEX** (operacional). O cliente não paga por infraestrutura ociosa (a aplicação deve saber **liberar** recursos); o provedor realoca o que foi devolvido e maximiza a utilização. |

> **CAPEX** = comprar a infraestrutura (grande investimento inicial). **OPEX** = pagar pelo uso, de forma contínua e proporcional.

#### 3.3 Modelos de precificação mais comuns

| Modelo | Como funciona | Quando serve |
|---|---|---|
| **Pay-As-You-Go** | Paga só pelo que usa, conforme usa. Mais popular. | Flexibilidade para aumentar/diminuir o uso. |
| **Assinatura pré-paga/fixa** | Taxa mensal fixa por quantidade definida de serviços. | Carga **previsível** ou necessidade de preço fixo. |
| **Instâncias reservadas** | Pré-compra de capacidade **com desconto**. | Uso **constante** por longo período. |
| **Spot instances** | Lances em capacidade **excedente** a preço com desconto. | Uso **de curto prazo ou imprevisível**; é a mais barata. |

#### 3.4 Modelos de serviço: IaaS, PaaS, SaaS

**IaaS — Infrastructure as a Service**

* O cliente tem acesso (mas **não gerencia a infraestrutura de base**) a processamento, armazenamento, rede e outros recursos fundamentais, para **implantar e executar software arbitrário**, incluindo SO e aplicativos. Os recursos existem graças a **softwares de virtualização**.
* O usuário tem **controle total** de SOs e aplicativos implantados e, possivelmente, controle limitado de alguns componentes de rede (ex.: firewall). Precisa ter **licenças** de SO e aplicativos.
* Autoprovisionamento por **console web** ou por **APIs** (**Infrastructure as Code, IaC**). Muitos provedores permitem escolher **várias localizações geográficas** (vários datacenters).
* Exemplos: **Amazon EC2** e **Google Compute Engine (GCE)**.
* ⚠️ Contrapartida: o cliente **instala e gerencia** SO, middleware e ambientes de execução (JVM, servidor de aplicação, servidor web, bancos). Pequenas e médias empresas podem não ter mão de obra/habilidade para isso.

**PaaS — Platform as a Service**

* Oferece uma **plataforma** na qual as aplicações do cliente (criadas ou adquiridas) são implantadas. Entrega **blocos de construção** e ferramentas de desenvolvimento: linguagens, ambientes de execução, SGBDs, servidores de aplicação, **middleware orientado a mensagens** etc. Na prática, é **"um sistema operacional na nuvem"**.
* O provedor mantém SO e middleware **gerenciados**, mas espera que a aplicação seja desenvolvida em **estilo específico** para lidar com **escalabilidade elástica** e **resiliência a falhas**.
* Útil para quem quer **desenvolver aplicações personalizadas** pagando só pelo necessário e pelo tempo necessário.
* Exemplos do slide: **Amazon SQS** (middleware orientado a mensagens na nuvem), **Google App Engine** e **Stratos Live (WSO2)** (apps web Java), **CloudBees** e **Heroku** (construir, executar e operar apps na nuvem), **plataforma Force (Salesforce)** (extensões do CRM).

**SaaS — Software as a Service**

* Serviços web na forma de **aplicação pronta**, executada e acessada na infraestrutura do provedor, via dispositivos de cliente com interface simples (navegador).
* O cliente **não compra licenças** de desktop e servidor e evita a complexidade de instalar, manter, atualizar e corrigir software.
* Exemplos: **Gmail, Google Drive, Microsoft 365, Salesforce, Citrix GoToMeeting, Cisco WebEx**.
* Assinantes típicos: pequenas e médias organizações (e-mail, documentos) e indivíduos, pelos recursos como **backup automático**, **compartilhamento de dados** e acesso ubíquo por várias plataformas.

**Quem gerencia o quê (figura do slide):** em verde, o que o **cliente** gerencia; o restante é do **provedor**.

| Camada | TI tradicional (on-premises) | IaaS | PaaS | SaaS |
|---|:-:|:-:|:-:|:-:|
| Aplicações | Cliente | Cliente | Cliente | **Provedor** |
| Dados | Cliente | Cliente | Cliente | **Provedor** |
| Runtime | Cliente | Cliente | **Provedor** | **Provedor** |
| Middleware | Cliente | Cliente | **Provedor** | **Provedor** |
| SO | Cliente | Cliente | **Provedor** | **Provedor** |
| Virtualização | Cliente | **Provedor** | **Provedor** | **Provedor** |
| Servidores | Cliente | **Provedor** | **Provedor** | **Provedor** |
| Armazenamento | Cliente | **Provedor** | **Provedor** | **Provedor** |
| Rede | Cliente | **Provedor** | **Provedor** | **Provedor** |

**Clientes típicos (figura do slide, funil):** **IaaS** → arquitetos de rede (*networks architects*); **PaaS** → desenvolvedores de aplicações (*application developers*); **SaaS** → usuários finais (*end users*). O eixo lateral indica a **visibilidade do valor para o usuário final**, que cresce de IaaS para SaaS.

#### 3.5 Modelos de implantação

| Modelo | Quem usa / onde fica | Características dos slides |
|---|---|---|
| **Pública** | Público em geral ou grande grupo da indústria; de propriedade de uma organização que **vende** serviços (empresa, instituição acadêmica ou governo). Fica **nas instalações do provedor**. | Infraestrutura **multilocatária**, acessada pela Internet, **fora do firewall** da empresa. **Econômica e escalável**; voltada a consumidores finais e pequenas e médias empresas (preço por uso, às vezes centavos por GB). Exemplos: Yahoo! Mail, Facebook, LinkedIn. ❌ Em geral **sem SLAs**, sem garantia contra perda/corrupção de dados e sem garantia de conformidade com leis de privacidade (que continua sendo responsabilidade do assinante). |
| **Privada** | **Uma única organização**. Dentro do ambiente de TI interno, ou fora das instalações, conforme o nível de segurança exigido. | **Motivação principal: segurança.** Gestão interna ou terceirizada. Acesso via **intranet** ou Internet por **VPN**. |
| **Comunitária** | Várias organizações **independentes** com **requisitos similares** e necessidade de trocar dados. | Mistura de privada (acesso restrito) e pública (recursos compartilhados). Exemplo: **saúde**, cumprindo regulamentações de privacidade com troca controlada de dados. Gerida pelas organizações ou por terceiros, dentro ou fora das instalações. Custos divididos entre **menos** usuários que a pública (mas **mais** que a privada), logo aproveita só **parte** da economia. |
| **Híbrida** | Composição de **duas ou mais** nuvens (privadas, comunitárias ou públicas) que **continuam entidades distintas**, unidas por tecnologia padronizada ou proprietária que permite **portabilidade de dados e aplicativos**. | Dados sensíveis na área privada; dados menos sensíveis aproveitam a pública. Atraente para pequenas empresas. |

**Comparação (tabela do slide):**

| | Privada | Comunitária | Pública | Híbrida |
|---|---|---|---|---|
| Escalabilidade | Limitada | Limitada | Muito alta | Muito alta |
| Segurança | A mais segura | Muito segura | Moderadamente segura | Muito segura |
| Desempenho | Muito bom | Muito bom | Baixo a médio | Bom |
| Confiabilidade | Muito alta | Muito alta | Média | Média a alta |
| Custo | Alto | Médio | Baixo | Médio |

#### 3.6 Por que migrar para a nuvem? (e os contras)

* **Flexibilidade:** escala sob demanda; nível de controle configurável; ferramentas avançadas prontas (ex.: IA para reconhecimento de voz, linguagem natural e objetos em vídeo/imagens).
* **Eficiência:** entrega rápida ao mercado; acesso de qualquer lugar e dispositivo; paga só pelo que usa; backup na rede.
* **Valor estratégico:** acesso às tecnologias mais recentes; foco no **negócio**, não na infraestrutura de TI.
* **"Mas nem tudo são flores":** segurança e privacidade; governança; questões legais, regulatórias e de conformidade; falta de padronização; escolher o melhor modelo de serviço, implantação e precificação; escolher o provedor certo; continuidade do negócio e recuperação de desastres.

#### 3.7 Arquitetura de referência e os 5 atores

| Ator | Papel |
|---|---|
| **Cloud Service Provider (CSP)** | Pessoa, organização ou entidade que **disponibiliza** serviços de nuvem. |
| **Cloud Service Consumer (CSC)** | Pessoa ou organização que mantém relação comercial com CSPs e **usa** seus serviços. |
| **Cloud Auditor** | Faz **avaliação independente** da conformidade com SLAs, das operações dos sistemas de informação, do desempenho e da segurança da implementação. |
| **Cloud Broker** | **Gerencia** uso, desempenho e entrega dos serviços e **negocia** a relação entre CSPs e CSCs. |
| **Cloud Carrier** | Intermediário que fornece **conectividade e transporte** dos serviços entre CSPs e CSCs, respeitando SLAs. |

**Figura "Arquitetura de referência" (descrição):** no centro está o **Cloud Provider**, com (i) **Service Orchestration**, formada por três camadas: *Service Layer* (SaaS, PaaS, IaaS), *Resource Abstraction and Control Layer* e *Physical Resource Layer* (hardware e instalações), (ii) **Cloud Service Management** (suporte ao negócio, provisionamento/configuração, portabilidade/interoperabilidade) e (iii) **Security** e **Privacy**, que atravessam tudo. À esquerda ficam o **Cloud Consumer** e o **Cloud Auditor** (auditorias de segurança, de impacto à privacidade e de desempenho). À direita fica o **Cloud Broker** (intermediação, agregação e arbitragem de serviços). Na base, o **Cloud Carrier** liga tudo.

**Figura "Interação entre os atores" (descrição):**

```
 Rede da empresa              Cloud Carrier            Rede do datacenter
 [Cloud Consumer] ─────────── (nuvem) ─────────── [Cloud Provider]
        │ \                                         / │
        │  └────────────► [Cloud Broker] ◄─────────┘  │
        │                        │                     │
        └────────────► [Cloud Auditor] ◄───────────────┘
```

O consumidor e o provedor se comunicam pelo carrier; o broker intermedeia os dois; o auditor observa ambos de forma independente. (Na figura original o provedor aparece como "Cloud Producer".)

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Confusão clássica: Tipo 1 x Tipo 2.** Tipo 1 roda **direto no hardware**; Tipo 2 roda **como um processo de um SO**. Para lembrar: Tipo 2 tem uma camada a mais (o SO host), por isso perde desempenho.

> 💡 **Paravirtualização x trap-and-emulate.** Em trap-and-emulate o guest **não sabe** que é virtualizado e o hipervisor "pega" cada instrução privilegiada. Na paravirtualização o guest **sabe** e chama o hipervisor de propósito.

> 💡 **Balloon x Overcommitment.** Overcommitment é a **política** (prometer mais memória do que existe). Balloon é um **mecanismo** para recuperar memória de uma MV quando outra precisa.

> 💡 **MV de processo e emulador não são "virtualização" no sentido da aula.** A MV de processo (JVM) não representa hardware real; o emulador traduz instruções de outra arquitetura (complemento: por isso é lento).

> 💡 **Contêiner não é MV leve "igual".** Ele não virtualiza hardware, compartilha o kernel e só roda ambientes compatíveis com o SO nativo.

> 💡 **IaaS ⟶ PaaS ⟶ SaaS:** quanto mais à direita, **menos** o cliente gerencia. Decore pela tabela "quem gerencia o quê".

> 💡 **Nuvem pública** não oferece SLAs nem garantias de privacidade por padrão; **privada** foca segurança; **comunitária** compartilha entre organizações com regras semelhantes; **híbrida** mistura nuvens para unir segurança e custo.

> 💡 **Teste de desempenho** é a exceção em que a virtualização **não** é aconselhada (a menos que a produção também seja em MV).

> 📝 **Pequenas inconsistências nos slides:** o slide de NPT escreve "NTP" onde deveria ser NPT, e o balloon é descrito nos slides como "fixar páginas na memória principal" e no gabarito como "enviar páginas para a memória virtual (disco)". Ambos descrevem o mesmo efeito: o guest fica com menos memória livre.

---

### 🧪 Exercícios e Gabarito Comentado

Resumo das 16 questões do gabarito (`Aula03-gab.pdf`), em linguagem simples.

1. **O que é máquina virtual?** Uma camada de software que "fatia" o hardware de uma máquina física (CPU, memória, disco, rede) em vários ambientes, cada um com a ilusão de ser um computador próprio. Precisa de uma máquina física para rodar e permite executar várias instâncias independentes de SO ao mesmo tempo.
2. **Funções do hipervisor:** (1) gerir a execução das MVs garantindo isolamento; (2) emular dispositivos e controlar acesso para compartilhar recursos (ex.: placa de rede); (3) executar operações privilegiadas (só ele tem modo privilegiado); (4) gerenciar as MVs (iniciar, pausar, clonar); (5) gerenciar o hardware físico como um kernel.
3. **3 requisitos:** **fidelidade** (ambiente idêntico ao físico), **desempenho** (sem perda em relação ao físico) e **proteção/isolamento** (hipervisor controla tudo; MVs não afetam umas às outras nem o hipervisor).
4. **2 vantagens (qualquer duas):** *consolidação* (várias aplicações no mesmo hardware, reduzindo custo); *hardware legado* (roda aplicações antigas em hardware moderno sem alterá-las); *versatilidade* (criar, replicar, ligar e desligar rápido); *clonagem/templating* (copiar arquivos gera cópia da MV com seu estado, ou usar uma MV-modelo para várias instâncias).
5. **Tipos de virtualização:** **Tipo 0** (partições de hardware em firmware; guests rodam nativamente em um subconjunto dos recursos); **Tipo 1** (modo kernel, controla o hardware, tem drivers, escalonador de CPU, gerência de memória e E/S, proteção); **Tipo 2** (outro processo do host; o host não sabe da virtualização; roda em vários SOs sem alterá-los; serve para testar SOs sem trocar o nativo; o usuário precisa de privilégios administrativos); **paravirtualização** (guest modificado, ciente do hipervisor, MV não idêntica ao físico); **emulação** (hardware do guest emulado em software, útil para portar legado; guests compilados para outra CPU); **conteinerização** (roda sobre o kernel do host, sem SO por aplicação, reduz custos).
6. **Overcommitment e ballooning:** guests raramente usam todos os recursos. *Overcommitment* permite que a soma alocada às MVs passe do que existe fisicamente (ex.: RAM). *Ballooning* faz o hipervisor forçar o guest a mandar páginas da RAM para a memória virtual (disco), liberando memória que o hipervisor realoca a outra MV.
7. **Compartilhamento de páginas:** páginas virtuais de MVs diferentes que têm exatamente a mesma assinatura (partes do kernel, se o SO for o mesmo; aplicações iguais) podem usar **um só quadro** físico, economizando memória.
8. **Benefícios na etapa de testes:** (a) combinações enormes de SO, navegador e banco são resolvidas com várias imagens virtuais e templates no mesmo computador; (b) **instalação limpa** fácil: desliga, descarta alterações e volta a um estado anterior; atualizar build/patch é simples; (c) **portabilidade**: o QA copia o disco virtual com o bug para o desenvolvedor, que o reproduz e valida a correção.
9. **Quando não usar para testar:** em **testes de desempenho**, porque a MV divide recursos com outras MVs, com o SO host e com o software de virtualização, distorcendo a medição. Use servidor físico dedicado, exceto se a produção também for MV.
10. **O que é computação em nuvem?** Modelo de acesso onipresente, conveniente e sob demanda a um conjunto compartilhado de recursos configuráveis, provisionados e liberados rapidamente com mínimo esforço de gerenciamento ou interação com o provedor.
11. **5 características essenciais:** agrupamento de recursos, autoatendimento sob demanda, amplo acesso à rede, elasticidade, serviços mensuráveis.
12. **O que é elasticidade?** Capacidade de **expandir e reduzir recursos rapidamente** de acordo com a necessidade do serviço.
13. **4 modelos de precificação:** *Pay-As-You-Go* (paga pelo uso), *assinatura pré-paga/fixa* (taxa mensal por quantidade definida, para carga previsível), *instâncias reservadas* (capacidade pré-comprada com desconto, para uso constante e longo), *spot instances* (lances em capacidade excedente, a mais barata, para uso curto ou imprevisível).
14. **3 modelos de serviço:** **IaaS** (servidores e infraestrutura flexíveis graças à virtualização; o cliente instala e gerencia SO, middleware e runtimes); **PaaS** (provedor gerencia SO e middleware; a aplicação deve lidar com elasticidade e falhas; bom para desenvolver apps personalizadas pagando só pelo necessário); **SaaS** (aplicação pronta acessada pelo navegador, sem licenças nem instalação).
15. **Diferença entre os modelos de implantação:** **pública** (aberta ao público, de um provedor que vende serviço, mais econômica); **privada** (uma só organização, nas instalações do cliente ou do provedor, foco em segurança); **comunitária** (acesso restrito como a privada, recursos compartilhados como a pública, entre organizações com requisitos parecidos que trocam dados); **híbrida** (duas ou mais nuvens distintas unidas por tecnologia que dá portabilidade; dados sensíveis na privada, o resto na pública).
16. **Atores da arquitetura de referência:** **CSP** (disponibiliza serviços), **CSC** (consome), **Cloud Auditor** (avalia SLAs, operações, desempenho e segurança de forma independente), **Cloud Broker** (gerencia uso, desempenho e entrega, e negocia entre CSPs e CSCs) e **Cloud Carrier** (conectividade e transporte entre CSPs e CSCs, respeitando SLAs).

---

### 🧠 Perguntas de Revisão

1. **Qual a diferença entre hipervisor Tipo 1 e Tipo 2?** O Tipo 1 roda direto no hardware em modo kernel (VMware ESX, Hyper-V, KVM) e é o mais usado em datacenters; o Tipo 2 roda como processo sobre um SO hospedeiro (VirtualBox), é mais portável, porém mais lento.
2. **Por que o trap-and-emulate gera overhead e como o hardware ajuda?** Cada instrução privilegiada causa uma trap, com chaveamento de processo e de modo. CPUs com suporte (Intel VT-x/VT-d, AMD-V) têm modos extras que evitam parte dessas intervenções. Para memória, usam-se as NPT (EPT/RVI).
3. **Como funcionam as Nested Page Tables?** O guest traduz página → quadro virtual da MV; o hipervisor traduz quadro virtual → quadro físico real; a MMU usa as duas tabelas aninhadas e o hipervisor só é chamado se o quadro virtual não estiver alocado.
4. **O que é overcommitment e qual o risco?** Alocar às MVs mais recursos do que o host tem, apostando na subutilização. Se todas as MVs pedirem tudo ao mesmo tempo, o desempenho cai.
5. **Por que contêineres têm menos overhead que MVs, e qual o preço disso?** Não têm SO convidado nem emulação de dispositivos (compartilham o kernel via cgroups). Em troca, só rodam ambientes compatíveis com o SO nativo, não são portáveis entre SOs e isolam menos.
6. **Cite 3 benefícios da virtualização de servidores em datacenters.** Ex.: consolidação (N:1), recuperação de desastres mais simples (restaurar a MV em qualquer hardware compatível) e alta disponibilidade sem secundário ocioso.
7. **Quais as 5 características essenciais da nuvem e o que muda de CAPEX para OPEX?** Agrupamento de recursos, autoatendimento sob demanda, amplo acesso à rede, elasticidade e serviços mensuráveis. A medição permite "pagar pelo uso" (OPEX) em vez de comprar infraestrutura (CAPEX).
8. **Em IaaS, PaaS e SaaS, o que o cliente gerencia?** IaaS: SO, middleware, runtime, dados e aplicações. PaaS: dados e aplicações. SaaS: praticamente nada (usa o software pronto).

---

### 🔗 Conexão com o Trabalho Final

Os protocolos do trabalho (gRPC, REST, RabbitMQ e Kafka) normalmente são demonstrados com vários serviços e brokers rodando ao mesmo tempo; **MVs e contêineres** são a forma natural de isolar cada serviço e de reproduzir o ambiente (complemento). O slide de PaaS cita o **Amazon SQS** como middleware orientado a mensagens na nuvem, a mesma família de tecnologia do RabbitMQ e do Kafka. Além disso, a ideia de **elasticidade e consumidores em paralelo** lembra o balanceamento de carga em filas que o trabalho pede (complemento).

---

### 📚 Links & Leituras Complementares

* 📖 *Operating Systems* (William Stallings, 9ª Edição) — Capítulo 14 (Seções 14.1 a 14.5) e Seção 16.1
* 📖 *Fundamentos de Sistemas Operacionais* (Abraham Silberschatz, 9ª Edição) — Capítulo 16
* 📖 *Advanced Server Virtualization: VMware and Microsoft Platforms in the Virtual Data Center* (David Marshall, Wade A. Reynolds, Dave McCrory; Auerbach Publications, 2006) — Capítulos 1 e 2 (virtualização) e 4 e 5 (datacenters)
* 📖 *Arquitetura e Organização de Computadores* (William Stallings, 10ª Edição) — Seção 17.7

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 2: Grids e Clusters — Em busca de maior capacidade de processamento](../Aula_2/README.md)
* ➡️ **Próxima Aula:** [Aula 4: Internet das Coisas (IoT)](../Aula_4/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
