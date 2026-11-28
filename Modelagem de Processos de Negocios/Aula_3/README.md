# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 28/08/2026 | 📚 Professor: Flávio Seixas | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 03: Ciclo de BPM, Conceitos e Fundamentos de Processos de Negócio

### 📝 Introdução

Esta aula aprofundou-se no **Ciclo de Gerenciamento de Processos de Negócio (BPM)** e em seus fundamentos conceituais. O professor apresentou como as estratégias de negócios se desdobram em processos operacionais utilizando frameworks consagrados como o **Balanced Scorecard (BSC)** e o **TOGAF**. Foi discutida a definição formal de processo por meio de múltiplos autores de referência, a transversalidade das atividades pelas áreas funcionais da empresa, as características que tornam os processos complexos e dinâmicos, e as divisões estruturais de arquitetura e níveis lógicos de desdobramento. Por fim, detalhamos os componentes fundamentais que constituem um processo (atividades, papéis, recursos, regras e metas de processo).

---

### 💡 Conceitos Chave

#### 1. O Ciclo de Gerenciamento de Processos (BPM Cycle)

O ciclo estruturado por Dumas et al. (2018) constitui o motor de transformação e gerenciamento contínuo, conectando os tópicos fundamentais da disciplina em seis grandes fases sequenciais:

1. **Identificar e priorizar processos:** Fase inicial focada no contexto e alinhamento com a estratégia organizacional.
2. **Descobrir e modelar o AS-IS:** Levantamento e representação do estado atual do processo, delimitando claramente seu escopo, os atores envolvidos, as regras vigentes e os resultados gerados.
3. **Analisar problemas e desempenho:** Avaliação crítica do processo atual utilizando tanto métodos qualitativos quanto quantitativos para identificar gargalos e ineficiências.
4. **Redesenhar o TO-BE:** Concepção do estado futuro ideal do processo e seleção de mudanças viáveis e realistas para implementação.
5. **Implementar:** Execução prática das mudanças desenhadas, combinando de forma harmoniosa pessoas, regras de negócio, dados e novas tecnologias.
6. **Monitorar e controlar:** Acompanhamento do desempenho operacional no dia a dia, realimentando o ciclo de melhoria contínua por meio de evidências mensuráveis.

#### 2. Frameworks de Alinhamento Estratégico

Para garantir que a operação execute o planejamento corporativo, utiliza-se o desdobramento da estratégia através de modelos estruturados:

* **Balanced Scorecard (Kaplan & Norton):** Propõe um mapa que conecta as metas de longo prazo dos acionistas (Perspectiva Financeira) a atributos de preço, qualidade e relacionamento com o cliente (Perspectiva do Cliente). Estes atributos, por sua vez, exigem a excelência e inovação nos processos internos (Perspectiva de Processos), que dependem diretamente de uma infraestrutura forte de cultura, liderança, alinhamento e trabalho em equipe (Perspectiva de Aprendizado e Crescimento).
* **TOGAF (The Open Group Architecture Framework):** Fornece uma arquitetura corporativa integrada dividida em diferentes perspectivas indispensáveis:
  - **Organizacional:** Mapeamento de atores, papéis e estrutura organizacional.
  - **Produto:** Definição de produtos, serviços e seus relacionamentos mútuos.
  - **Processos de Negócio:** Estruturação da arquitetura de processos corporativos.
  - **Dados:** Entidades informacionais e como elas se relacionam entre si.
  - **Aplicativo:** Diferentes softwares da empresa e suas respectivas dependências técnicas.
  - **Infraestrutura Técnica:** Recursos de hardware e redes de comunicação que dão suporte aos sistemas.

#### 3. Definições Formais de Processo de Negócio

A literatura traz diferentes nuances complementares para definir o que é um processo:

* **James F. Chang (2006):** Define processo como um fluxo coordenado e padronizado de atividades (executadas por pessoas ou máquinas) que cruza os limites departamentais para atingir uma meta de negócio que gere valor ao cliente interno ou externo.
* **Rummler & Brache (1995):** Trazem uma perspectiva simples e direta, caracterizando-o como uma série de passos que a empresa executa com a finalidade de produzir um produto ou serviço.
* **Martyn Ould (2005):** Define-o como um conjunto coerente de ações que é realizado por um grupo de papéis colaborativos de modo a alcançar um objetivo comum.
* **Smith & Fingar (2007):** Apresentam o processo como um conjunto completo e dinamicamente coordenado de atividades colaborativas e transacionais desenhadas para entregar valor direto aos clientes.
* **Business Motivation Model (2008):** Explica que os processos são responsáveis por materializar os "cursos de ação" definidos pela empresa para garantir que a organização progrida em direção às suas metas de negócio.

#### 4. Transversalidade e Características dos Processos de Negócio

* **A Empresa como Coleção de Processos:** Em vez de silos isolados, a organização é composta por fluxos horizontais. Os processos cruzam as áreas funcionais (ex.: o processo de "Desenvolvimento de Novos Produtos" inicia-se na Engenharia, passa pelo Marketing e Produção, e afeta o Financeiro).
* **A Coordenação como Fator Crítico:** A sincronização e coordenação de tarefas individuais são mais importantes do que as tarefas isoladas em si. A coordenação torna-se complexa por causa de múltiplos passos, branches (laços de decisão) e interações com parceiros externos, impactando diretamente o tempo total de ciclo do processo.
* **Principais Características:**
  - **Grandes e Complexos:** Envolvem fluxos ponta a ponta de materiais, compromissos e informações.
  - **Dinâmicos:** Mudam constantemente para responder às demandas de mercado e dos clientes.
  - **Distribuídos e Personalizados:** Espalham-se por diferentes limites de negócios e dependem de múltiplos aplicativos e plataformas tecnológicas integradas.
  - **Longa Duração:** Algumas instâncias (como o desenvolvimento de um produto complexo) podem durar meses ou anos.
  - **Automatizados (parcialmente):** Utilização de computadores para tarefas repetitivas, buscando agilidade e confiabilidade.
  - **Empresariais e Técnicos:** Processos de TI devem dar suporte e estar alinhados com os processos de negócios.
  - **Dependentes das Pessoas:** Demandam a inteligência, flexibilidade e suporte do capital humano.
  - **Dificilmente Visíveis:** Sem esforço de mapeamento e documentação, é difícil enxergar o processo de ponta a ponta.

#### 5. Classificação e Arquitetura de Processos

Os processos são classificados hierarquicamente para facilitar sua gestão:

* **Tipos de Processos segundo o Framework BPM CBOK:**
  - **Processos Primários ou Operacionais:** Constituem o "core business". Geram o fluxo de valor direto recebido pelo cliente (compras, fabricação, marketing, vendas, serviços pós-venda).
  - **Processos de Suporte:** Não geram valor perceptível direto para o cliente, mas garantem a execução adequada dos processos primários (contabilidade, RH, TI, manutenção preventiva).
  - **Processos Gerenciais:** Responsáveis por monitorar, governar e gerenciar o sistema da empresa (planejamento estratégico, orçamentos, governança de processos).
* **Níveis da Arquitetura de Processos:**
  - **Level 1 (Process Landscape):** Visão macro, mostrando cadeias de valor e grupos funcionais de alto nível.
  - **Level 2 (Business Processes):** Desdobramento das cadeias de valor em fluxos de processos de negócios integrados (geralmente modelados em BPMN).
  - **Level 3+ (Sub-processes and Tasks):** Detalhamento das atividades e tarefas específicas operacionais com suas respectivas regras.
* **Níveis Lógicos e Físicos (Exemplo British Telecom 2005):**
  - **Nível A ao C (Business Levels):** Definição conceitual de atividades, agrupamentos de processos e processos core ponta a ponta (Logical Levels).
  - **Nível D ao F (Operations Levels):** Modelagem detalhada de fluxos de processos operacionais com tratamento de exceções, especificidades geográficas e tarefas detalhadas (Physical Levels).

#### 6. Exemplos de Modelagem de Arquitetura (Process Landscape Model) nos Slides

Os slides ilustraram duas arquiteturas de referência para exemplificar os níveis de processos:

* **Caso 1: Transporte Público:** Mostra os processos gerenciais (gerenciar qualidade, riscos, comunicação, inovação), os processos operacionais core (contatar cliente, planejar/comprar/manter veículos, transportar cliente, avaliar transporte, planejar/construir/manter infraestrutura) e processos de suporte (manutenção de RH, TI, contabilidade, provisão de serviço de inverno, etc.).
* **Caso 2: Construção Civil:** Divide os processos core em duas grandes cadeias de valor de ponta a ponta: a de **Aquisição de Contratos** (do levantamento da demanda até a assinatura do contrato) e a de **Execução do Contrato** (do planejamento operacional à conclusão e expiração do contrato).

#### 7. Componentes e Estrutura de um Processo de Negócio

Qualquer processo operacional necessita de um conjunto de componentes integrados para funcionar corretamente:

* **Atividades e Tarefas:** Ações executadas de modo a agregar valor ao negócio e alcançar objetivos. Atividades são fluxos de maior nível que podem ser subdivididos em tarefas (unidades atômicas e indivisíveis de trabalho).
* **Papéis:** Conjunto padronizado de responsabilidades concedidas a um indivíduo ou grupo no processo. O papel não se confunde com o cargo organizacional, podendo corresponder a uma posição funcional ou a um grupo multifuncional colaborativo.
* **Recursos:** Insumos e ferramentas necessários para que os papéis realizem suas atividades. Podem ser **Físicos** (matérias-primas, maquinário, ferramentas) ou **Informacionais** (dados, relatórios, planos de projeto).
* **Regras de Negócio:** Mecanismos que controlam a ordem e as decisões das atividades no fluxo. Subdividem-se em:
  - **Políticas:** Diretrizes internas de alto nível que influenciam as tomadas de decisões (ex.: "compras acima de R\$1.000,00 exigem aprovação do gerente financeiro").
  - **Procedimentos:** Sequências e formas de execução de atividades padronizadas (ex.: "verificar estoque físico no sistema de representantes antes de efetivar o pedido").
  - **Padrões:** Diretrizes que estabelecem o layout, conteúdo ou aparência física dos entregáveis (ex.: "documentos de projeto devem seguir o template corporativo").
* **Metas dos Processos (Mecanismos de Sucesso):**
  - **Modo Ponto (Point Mode):** A meta é atingida no instante de término de uma ação (ex.: o cliente receber o novo cartão de crédito em casa, ou entregar um software no custo acordado).
  - **Estado Estável (Steady State):** A meta é alcançada quando um estado desejável é continuamente mantido (ex.: processo de gestão de fluxo de caixa, que tem sucesso contínuo se mantiver o saldo positivo para evitar juros bancários).

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Revisão dos Fundamentos de Processo:**
>
> * **Insumos:** todo o ínicio de processo receberá minimamente um insumo para seguir com o processo.
> * **Processos têm clientes:** Todo processo deve ter o foco em criar e entregar valor a um cliente (seja ele interno ou externo).
> * **Ativos corporativos:** Os processos bem desenhados refletem exatamente como uma empresa opera o seu negócio, devendo ser tratados como ativos de altíssimo valor que precisam ser geridos e melhorados de forma contínua.
> * **Gargalos horizontais:** Os maiores problemas de tempo de ciclo de uma empresa quase nunca estão na execução de uma tarefa individual, mas sim na coordenação e no tempo de transição das interações entre diferentes departamentos.

---

### 📚 Links & Leituras Complementares

* 📖 **DUMAS, M. et al. (2018).** *Fundamentals of Business Process Management*, 2ª edição, capítulos 1 a 3.
* 📖 **ABPMP BRASIL (2013).** *BPM CBOK V3.0*, capítulos 2 e 9.
* 📖 **HARMON, P. (2019).** *Business Process Change*, 4ª edição, capítulos 3 e 4.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 2: Gerenciamento de Processos de Negócio (BPM)](../Aula_2/README.md)
* ➡️ **Próxima Aula:** [Aula 04: Descoberta de Processos de Negócio (AS-IS)](../Aula_4/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
