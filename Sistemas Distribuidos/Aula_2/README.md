# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 11/08/2026 | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 02: Grids e Clusters — Em busca de maior capacidade de processamento

### 📝 Introdução

A segunda aula apresenta os conceitos fundamentais de **computação em grade (grid computing)** e **computação em cluster**, abordando seus principais componentes, arquiteturas de armazenamento (SAN e NAS) e gerenciamento de falhas. O objetivo principal deste tópico é capacitar os alunos na compreensão das alternativas arquiteturais para a busca de **alta capacidade de processamento**, **escalabilidade absoluta e incremental**, **alta disponibilidade** e estratégias de **balanceamento de carga** em larga escala. Para isso, foram analisados a taxonomia de Flynn, o funcionamento de comutadores e distribuidores de requisição, os serviços essenciais de um middleware de cluster e exemplos práticos de supercomputadores.

---

### 💡 Conceitos Chave

* **Taxonomia de Flynn:** Classificação de arquiteturas de computadores com base no número de fluxos simultâneos de instruções e dados. Divide-se em:
* **SISD (Single Instruction, Single Data):** Processador único executa uma sequência única de instruções sobre um único fluxo de dados (uniprocessadores).
* **SIMD (Single Instruction, Multiple Data):** Uma instrução controla a execução simultânea de múltiplos elementos de processamento sobre conjuntos de dados diferentes.
* **MISD (Multiple Instruction, Single Data):** Múltiplas instruções operando simultaneamente sobre um único conjunto de dados (sem aplicação comercial).
* **MIMD (Multiple Instruction, Multiple Data):** Vários processadores executando diferentes instruções sobre diferentes conjuntos de dados ao mesmo tempo (SMPs, clusters e NUMA).


* **Computação em Grade (Grid Computing):** Sistemas fracamente acoplados, altamente heterogêneos (diferentes redes, sistemas operacionais e políticas de segurança). Reúnem recursos (processamento, armazenamento) de organizações distintas para formar uma **organização virtual**. É muito comum em *volunteer computing* (doação de poder computacional ocioso de computadores pessoais para fins acadêmicos/científicos).
* **Computação em Cluster:** Sistemas fortemente acoplados e homogêneos, compostos por nós idênticos interconectados por uma rede local de alta velocidade (LAN) sob uma topologia estável e rodando o mesmo sistema operacional. É projetado para atuar como uma única máquina de alto desempenho a partir de computadores de menor custo.
* **Blade e Rack:** Um *blade* é um módulo computacional individual contendo CPU, memória e armazenamento. Os blades são organizados em um chassi vertical chamado *rack*, que provê energia e interconexão de rede rápida.
* **Storage-Area Network (SAN):** Rede de armazenamento dedicada de alta velocidade que permite que vários servidores acessem dispositivos de armazenamento externos compartilhados como recursos de mesmo nível. É uma alternativa ao **Network-Attached Storage (NAS)**, onde um único servidor gerencia o acesso e transferência de arquivos.
* **Fibre Channel (FC):** SAN baseada em cabos de fibra dedicada, de alto desempenho (até 16Gbps), mas de alta complexidade e custo elevado.
* **iSCSI:** Protocolo que encapsula comandos SCSI em pacotes IP trafegados sobre a infraestrutura de rede Ethernet existente (até 10Gbps), dispensando redes dedicadas caras.


* **Balanceamento de Carga:** Prática de distribuir requisições e tráfego de forma equilibrada entre os nós ativos de um cluster para evitar gargalos, melhorar a tolerância a falhas e manter alta disponibilidade. Divide-se em:
* **Balanceamento Estático:** Segue regras fixas e não considera a carga em tempo real (ex.: *Round-robin*, *Round-robin ponderado* e *Hash IP*).
* **Balanceamento Dinâmico:** Avalia o estado real do servidor antes de encaminhar a requisição (ex.: *Conexão mínima*, *Conexão mínima ponderada*, *Menor tempo de resposta* e *Baseado em recursos* via agentes de monitoramento local).


* **Middleware de Cluster:** Camada de software que provê a ilusão de um **sistema único (Single System Image - SSI)** ao usuário. Oferece serviços unificados como ponto de entrada único, sistema único de arquivos, espaço único de memória compartilhada distribuída (DSM), balanceamento via migração de processos e pontos de salvamento para tolerância a falhas (*checkpoints*).

#### 🔍 Tópico em Destaque: Computação em Grade vs. Computação em Cluster

* **Acoplamento & Homogeneidade:** Clusters são sistemas fortemente acoplados e homogêneos (mesmo SO, nós idênticos e mesma rede local dedicada), enquanto Grids são fracamente acoplados e altamente heterogêneos (diferentes sistemas operacionais, redes WAN e domínios administrativos distintos).
* **Objetivo & Administração:** O Cluster busca atuar como uma única máquina unificada sob uma única entidade administrativa (Single System Image). O Grid une recursos dispersos geograficamente pertencentes a múltiplas organizações para formar uma Organização Virtual cooperativa.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Limites de Processamento Sequencial:** O aumento contínuo de desempenho de processadores sequenciais encontrou um limite físico intransponível. Por isso, o ganho de desempenho em sistemas modernos depende essencialmente do paralelismo, usando técnicas como múltiplos processadores simétricos (SMP), GPUs e clusters computacionais.

> 💡 **Tolerância a Falhas em Clusters (Failover e Failback):** Em sistemas de alta disponibilidade, o comutador detecta automaticamente a queda de um nó. A recuperação é feita através do **failover** (migração de processos e dados para outro nó operacional). Assim que o nó original é reparado, realiza-se o **failback** (retorno das atividades ao hardware de origem).

> 💡 **Gargalo do Ponto de Entrada Único:** Embora um ponto de entrada centralizado (comutador) ofereça transparência de acesso, ele representa um ponto único de falha (*Single Point of Failure*). Soluções para contornar isso incluem a definição de múltiplos pontos de acesso utilizando distribuição de requisições baseada em servidores DNS (ex.: DNS *round-robin*) ou mecanismos de mobilidade para IPv6.

> 💡 **Supercomputadores de Referência:** A aula destaca alguns exemplos reais de grande relevância:
> * **OSCAR (IC-UFF):** O cluster local do IC-UFF, composto de 42 máquinas (40 de cálculo, 1 de compilação/login e 1 de manutenção), totalizando 240 núcleos de processamento Intel Xeon e 14,5 TB de capacidade.
> * **Santos Dumont (LNCC):** Instalado no Laboratório Nacional de Computação Científica, é conhecido como o computador mais rápido da América Latina, possuindo 756 nós computacionais e 18.144 núcleos.
> * **Frontier (OLCF/EUA):** Desenvolvido pela HP, opera na escala de *Exaflops* (1.102 exaFLOPS), sendo composto por 9.472 CPUs AMD Epyc e 37.888 GPUs Radeon Instinct distribuídos em 74 racks.
> 
> 

---

### 📚 Links & Leituras Complementares

* 📖 *Arquitetura e Organização de Computadores* (William Stallings, 10ª Edição) — Capítulo 17, Seções 17.1 e 17.5
* 📖 *Redes de Computadores e a Internet* (James Kurose, 8ª Edição) — Seção 6.6
* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª Edição) — Seção 1.3.1

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 1: Introdução aos Sistemas Distribuídos](../Aula_1/README.md)
* ➡️ **Próxima Aula:** [Aula 3: ](../Aula_3/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)