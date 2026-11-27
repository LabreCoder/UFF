# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 25/08/2026 | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 04: Internet das Coisas (IoT)

### 📝 Introdução

A quarta aula da disciplina **TCC00362 — Sistemas Distribuídos para Sistemas de Informação** apresenta a **Internet das Coisas (IoT)**: o que ela é, quais tecnologias a tornaram possível, onde ela é aplicada, quais componentes eletrônicos formam uma "coisa" e como o sistema inteiro é organizado em camadas (da borda até a nuvem).

O roteiro da aula segue cinco blocos, na mesma ordem dos slides:

1. **Definição**: conceito, história, características, tecnologias viabilizadoras e desafios.
2. **Aplicações**: impacto nos negócios, Indústria 4.0, frotas, energia, logística, saúde, cidades inteligentes.
3. **Componentes eletrônicos das coisas**: sistemas embarcados, tempo real, sensores, atuadores, microcontroladores, comunicação e RFID.
4. **Arquitetura**: modelos de referência (IIC, IEEE P2413, ITU-T e outros).
5. **IoT e a nuvem**: borda (*Edge*), névoa (*Fog*), rede central e nuvem (*Cloud*).

> 🎯 **Ideia central para estudar:** IoT é um sistema distribuído em **ultra larga escala**. Milhares de "coisas" pequenas e muito diferentes entre si geram dados, e esses dados passam por várias camadas (borda → névoa → nuvem) até virarem informação útil para o negócio.

---

### 💡 Conceitos Chave

#### 1. O que é IoT?

* **Ideia geral:** o futuro da Internet envolverá um grande número de objetos que usarão arquiteturas de comunicação padrão para fornecer serviços aos usuários. Isso cria novas interações entre o mundo físico e a computação, o conteúdo digital, a análise de dados, aplicativos e serviços. Esse paradigma de rede é chamado de **Internet das Coisas (*Internet of Things*)**.
* **Números (slides):** 30 bilhões de dispositivos conectados em **2026**, segundo relatório de GSMA Intelligence e IoT Analytics, com previsão de **40 bilhões até 2030** e **50 bilhões até 2035**.
* **Origem do termo:** cunhado em **1999 por Kevin Ashton**, cofundador do **Auto-ID Center no MIT (EUA)**, grupo responsável por criar padrões para **RFID** e outros sensores. A ideia de Ashton: se os computadores soubessem tudo sobre as coisas, coletando dados **sem ajuda humana**, poderíamos rastrear e contar tudo, reduzindo desperdício, perda e custo, e saberíamos quando algo precisa ser trocado, consertado ou recolhido.
* **Origem semântica da expressão (slide):** é a junção de duas palavras: **Internet** (rede mundial de redes baseada em protocolo padrão, o TCP/IP) + **Thing** (objeto não precisamente identificável). Logo, IoT significa *uma rede mundial de objetos interconectados, endereçáveis de forma única, baseada em protocolos de comunicação padrão*.

**Outras definições apresentadas na aula** (todas dizem a mesma coisa com ênfases diferentes):

| Ênfase | Definição resumida |
|---|---|
| Identidade | "Coisas têm identidades e personalidades virtuais, operando em espaços inteligentes, usando interfaces inteligentes para se conectar e se comunicar em contextos sociais, ambientais e de usuário." |
| "Qualquer coisa" | IoT permite que pessoas e coisas estejam conectadas *a qualquer hora, em qualquer lugar, com qualquer coisa e qualquer pessoa*, idealmente por qualquer rede e qualquer serviço. |
| Infraestrutura global | "Infraestrutura global para a sociedade da informação, habilitando serviços avançados ao interconectar coisas (físicas e virtuais)." |
| Nova dimensão | Soma a dimensão **"qualquer COISA"** à comunicação que já era **"qualquer HORA"** e **"qualquer LUGAR"**. |
| ⭐ **Favorita do professor (ISO/IEC JTC 1)** | *"IoT é uma infraestrutura de objetos, pessoas, sistemas e recursos de informação interconectados, junto com serviços inteligentes que permitem **processar informação do mundo físico e virtual e reagir**."* |

> Esta última definição é a mesma usada como resposta da **Questão 1** do gabarito. Vale decorar.

**Popularização do termo (linha do tempo):**

```
1999  Kevin Ashton cita o termo pela primeira vez (Auto-ID Center, MIT)
2003-2004  Aparece na grande mídia (The Guardian, Scientific American...)
2005  ITU (International Telecommunications Union) define IoT em relatório técnico
2008  Primeira conferência europeia sobre o tema
```

#### 2. Características de IoT

| Característica | O que significa (com exemplo) |
|---|---|
| **Distribuição em ultra larga escala** | Quantidade massiva de dispositivos e dados interconectados, acessíveis de forma transparente. |
| **Interação implícita** | O usuário nem percebe que está fornecendo entrada ao sistema. Computação presente em todos os ambientes e atividades. |
| **Consciência de contexto** | O sistema sabe **onde** (localização), **quem** (identidade), **quando** (tempo) e **o quê** (atividade) do usuário, para otimizar a interação. |
| **Composição altamente heterogênea** | De pequenos sensores a supercomputadores; de redes sem fio de baixa vazão/confiabilidade/alcance a redes cabeadas rápidas e confiáveis. Várias unidades administrativas independentes colaborando. |
| **Inteligência** | O sistema define ações e interações entre dispositivos **de forma autônoma**. |

#### 3. Tecnologias viabilizadoras

O que mudou para IoT se tornar viável? Quatro avanços ao mesmo tempo (também é a resposta da **Questão 2**):

* **Dispositivos embarcados:** ficaram menores, mais baratos, com mais autonomia (bateria), precisão, capacidade de processamento e armazenamento.
* **Conectividade:** internet de alta velocidade (fibra ótica), comunicação móvel mais rápida (**5G**), comunicação sem fio econômica (**BLE**, *Bluetooth Low Energy*), comunicação descentralizada (**redes mesh**) e de longo alcance (**LoRa**).
* **Computação em nuvem:** serviços escaláveis e mais baratos, com alta capacidade de armazenamento (*Big Data*) e de processamento (*HPC*). A **virtualização** permite oferecer Infraestrutura como Serviço (IaaS), tema da Aula 3.
* **Inteligência artificial:** visão computacional, reconhecimento de fala, aprendizado de máquina, análise de dados, realidade aumentada etc.

#### 4. Evolução de IoT: quatro "famílias" de dispositivos

O slide mostra que IoT reúne mundos que antes eram separados:

| Família | Quem usa/compra | Exemplos | Conectividade |
|---|---|---|---|
| **Tecnologia da Informação (TI)** | Profissionais de TI das empresas | PCs, servidores, roteadores, firewalls | Principalmente cabeada |
| **Tecnologia Operacional (TO)** | Profissionais de TO (empresas que não são de TI) | Equipamentos médicos, SCADA (controle e aquisição de dados de supervisão), controle de processos, quiosques | Principalmente cabeada |
| **Tecnologia Pessoal** | Consumidores | Smartphones, tablets, leitores de eBook | Exclusivamente sem fio, às vezes várias formas |
| **Sensores/Atuadores** | Consumidores, profissionais de TI e TO | Dispositivos de uso único, parte de sistemas maiores | Exclusivamente sem fio, em geral de uma única forma |

O slide ainda mostra graficamente a evolução de **M2M** (*machine-to-machine*: soluções pontuais, dispositivos isolados, dentro de uma empresa) para **IoT** (aberta, interempresas, "tudo pode se conectar a tudo"), com aumento de escopo, agilidade, riqueza semântica e diversidade de ativos.

#### 5. Principais desafios (Questão 3)

| Desafio | Em uma frase |
|---|---|
| **Escalabilidade** | Dezenas de bilhões de dispositivos e muitos dados. |
| **Heterogeneidade** | De pequenos sensores a supercomputadores. |
| **Interoperabilidade** | Alta dinamicidade dos componentes e de suas relações (tudo muda e precisa continuar conversando). |
| **Segurança** | Em vários níveis: operacional, institucional, pessoal, social, governamental... |

#### 6. Impacto nos negócios: disrupção x evolução (Questão 4)

IoT abre oportunidades sem precedentes para usuários, fabricantes e prestadores de serviços em vários setores.

| | **Disrupção** | **Evolução** |
|---|---|---|
| **O que faz** | Cria **novos nichos de mercado**, como a economia compartilhada, em que ativos físicos viram serviços (**servitização**). | **Agrega valor a nichos já existentes**. |
| **Exemplos (slides)** | Pagar por uso de veículos, seguros, infraestrutura de TI (nuvem), frota de logística. | Reduzir custo com manutenção preditiva, avisar automaticamente emergência em caso de acidente de carro, monitoramento remoto de saúde de pacientes (e-Health). |

**Servitização (*servitization*):** a empresa muda o foco de **vender produtos físicos** para **oferecer serviços** em torno deles. O slide compara:

| Fabricante tradicional | → | Servitização |
|---|---|---|
| Produtos | → | Soluções |
| CAPEX (investimento em compra) | → | OPEX (pagamento por uso) |
| Transação (venda única) | → | Relacionamento (contínuo) |
| "Do fabricante para a frente" | → | "Do cliente para trás" |
| *(novo, habilitado por IoT)* | | Gestão do ciclo de vida do ativo conectado + serviços digitais |

Exemplos do gabarito: manutenção e suporte contínuos, monitoramento remoto para prever e prevenir falhas, **SaaS** (assinatura em vez de licença permanente) e **EaaS** (equipamento como serviço: aluguel/arrendamento cobrando pelo uso).

#### 7. Áreas de aplicação

Os slides listam: saúde e bem-estar, assistência médica, monitoramento e automação residencial, economia de energia e redes inteligentes, agricultura, transporte, monitoramento ambiental, gerenciamento de inventário e produtos, segurança, vigilância, educação e outras. A aula aprofunda os casos abaixo.

##### 7.1 Indústria (de 1.0 a 4.0)

* **1.0:** revolução industrial na Inglaterra; o homem é substituído por máquinas.
* **2.0:** linhas de produção em série (fordismo).
* **3.0:** automação industrial.
* **4.0:** termo cunhado na Alemanha; **alta integração de serviços de TI no processo de manufatura e venda** dos produtos.

A Indústria 4.0 é dividida nos seguintes temas (todos nos slides):

* **Vendas/Marketing e novos modelos de negócio:**
  * Servitização (ver acima).
  * Equipes de marketing usam dados detalhados de uso do produto para campanhas e segmentos de mercado precisos; a ligação direta com o cliente facilita venda cruzada e venda adicional.
  * **Personalização do produto** (do tênis personalizado ao carro sob medida). Duas implicações: (1) o produto é **vendido antes de ser produzido**; (2) a produção precisa ser de **"batch size 1"**: cada lote é exatamente uma peça.
* **Engenharia digital ponta a ponta:** IoT liga o mundo virtual ao físico.
  * **CAD** (projeto assistido por computador): design e simulação de **produtos**.
  * **CAE** (engenharia assistida por computador): design e simulação de **sistemas de fabricação**.
  * **MES** (sistemas de execução de fabricação): integra os dados do produto ao longo do ciclo de vida, agenda recursos, despacha pedidos, rastreia materiais, analisa a produção.
  * **Gêmeo digital (*digital twin*):** sensores, lasers e tecnologias de localização criam conexão entre o modelo 3D virtual e o mundo físico. Sensores nas partes móveis da linha de montagem enviam dados de movimento para o sistema de TI, que **atualiza a posição no modelo 3D em tempo real**.
  * **Realidade aumentada:** convergência entre modelos 3D e mundo físico, útil em treinamento e controle de qualidade.
* **Manufatura:** conceitos como **MOM** (Gerenciamento das Operações de Manufatura) integram dados de vários níveis (máquina, linha, planta, empresa). Produtos, semiacabados e componentes terão um chip **RFID** que funciona como **memória do produto** (configuração, instruções de trabalho, histórico). Em vez de um MES central mandar em tudo, **produtos inteligentes informam aos módulos de produção o que precisa ser feito**.
* **Implementação e operação de serviços de IoT:** combinar manufatura (OT) com serviços de TI ainda não é comum. Passar de **fabricante para operador de serviços** é essencial, tanto na operação técnica quanto em manter bom relacionamento com clientes.
* **Serviços pós-venda:**
  * **Monitoramento remoto de condições (RCM):** acesso ao estado do produto em tempo real facilita análise de causa raiz e soluções.
  * **Manutenção preditiva:** sensores de imagem térmica, vibração, som e ultrassom, análise de óleo/líquidos e de emissões detectam problemas **antes de ocorrerem**.
* **Ambiente de trabalho:** há quem tema mais automação e robôs, mas há evidência de que a automação reduz trabalho tedioso e repetitivo, tornando o trabalho mais especializado e variado; a fábrica do futuro exigirá mais resolução de problemas e auto-organização.
* **Logística adaptativa e redes de valor agregado:** cadeias de suprimento tradicionais evoluem para **redes de valor**, com estruturas capazes de se adaptar rapidamente a pedidos personalizados (batch size 1).

##### 7.2 Gerenciamento de frota

O slide mostra um quadro com quatro grupos de funcionalidades (produtividade da frota, comportamento do motorista, estado do veículo e gestão da frota). Em texto:

* **Manutenção proativa:** com a quilometragem, o sistema mostra a próxima data de serviço e orienta o motorista até uma oficina adequada.
* **Relatório de quilometragem:** compara a quilometragem projetada com o contrato de *leasing*.
* **Notificação de acidente/quebra:** avisa o gestor da frota e apoia o motorista.
* **Diagnóstico do veículo:** guarda códigos de erro e os mostra em texto simples.
* **Alerta de roubo.**
* **Comportamento do motorista:** registra velocidade, frenagem e aceleração.
* **Registro de acidentes:** guarda valores de aceleração e status dos sensores antes/depois do acidente, o que ajuda a reconstruir a causa raiz.
* **Análise de trajetos** (otimizar rotas) e **geocerca** (*geofencing*; controlar uso do veículo e prevenir roubo).
* Resultado: otimização de custos e da disponibilidade da frota.

O slide seguinte mostra os **degraus da condução automatizada** (de "só controle longitudinal ou lateral" até o "piloto automático porta a porta"), com mais sensores e fusão de dados a cada nível.

##### 7.3 Smart energy

O slide exibe a cadeia de valor da energia em seis etapas, com exemplos de uso de IoT: **Geração e comercialização** (usinas virtuais, monitoramento remoto de geração descentralizada), **Transmissão** (monitoramento de condição), **Distribuição e medição** (medidores inteligentes, redes inteligentes/*smart grids*, tarifas variáveis), **Armazenamento** (integração de armazenamento descentralizado, *vehicle-to-grid*), **Marketing, vendas e serviços** e **Cliente** (casa inteligente, resposta à demanda, e-mobilidade).

##### 7.4 Logística

* **Rastreamento de lote:** saber localização e destino dos lotes em armazéns e o estado de processamento de cada um.
* **Solução LotTrack (empresa suíça Intellion):** um receptor RFID (*DisTag*) em cada lote, antenas de alta frequência para **triangulação de sinal** e processamento dos sinais para calcular a localização.

##### 7.5 Car sharing

O cliente usa o smartphone para localizar carros disponíveis e reservar; ao chegar, destrava com chip **RFID** e usa o computador de bordo (geralmente touchscreen) para identificação e outras interações; no destino (dentro de um perímetro definido) apenas tranca e deixa o carro; o sistema devolve o carro ao grupo de disponíveis automaticamente.

##### 7.6 Saúde 4.0, pecuária de precisão e cidades inteligentes

* **Saúde 4.0:** a população está envelhecendo e muitos idosos vivem sozinhos. IoT permite monitorar sinais vitais, reforçar e verificar a adesão a medicamentos, enviar socorro em emergência e antecipar intervenção médica. (O slide mostra um diagrama de integração entre a Unidade Básica de Saúde, UPA 24h, programas como "Melhor em Casa", "Academia da Saúde", CRAS etc.)
* **Pecuária de precisão (agronegócio):** monitoramento constante e preciso de animais e plantações, automação de intervenções como alimentação e irrigação e controle ponta a ponta da fabricação ao consumo. A figura mostra uma vaca com sensores medindo respiração, temperatura, escore corporal, ruminação, frequência cardíaca, mobilidade, saúde dos cascos, produção/composição do leite, mastite e comportamento em pé/deitado.
* **Smart cities:** uso de dados e tecnologia para criar eficiências, melhorar a sustentabilidade, promover o desenvolvimento econômico e a qualidade de vida de quem vive e trabalha na cidade. É a **convergência de várias aplicações IoT**; normalmente associada a logística urbana, saúde digital, rede elétrica, produção/distribuição de alimentos e sustentabilidade.

#### 8. Sistemas embarcados (Questão 7)

* **Definição:** uso de eletrônica e software **dentro de um produto** que tem uma função específica ou um conjunto de funções, **ao contrário de um computador de propósito geral** (laptop, desktop).
* **Escala:** centenas de milhões de computadores (laptops, PCs, servidores, mainframes, supercomputadores) são vendidos por ano, mas **dezenas de bilhões de microcontroladores** são produzidos por ano e embutidos em dispositivos maiores. Hoje, muitos (talvez a maioria) dos dispositivos que usam energia elétrica têm um sistema embarcado.
* **Exemplos (slides):** celular, câmera digital, calculadora, micro-ondas, segurança residencial, máquina de lavar, iluminação, termostato, impressora, sistemas automotivos (transmissão, cruzeiro, injeção, freios ABS, suspensão), raquetes de tênis, escovas de dente...
* **Dispositivos *smart*:** dispositivos que se conectam à Internet e cooperam com outros sistemas embarcados e maiores: smartphone, *smart meter*, smartwatch, smart TV. Comunicação tipicamente sem fio com acesso à Internet.

**Características:**

* A interface humana pode ser só uma luz piscante ou algo complexo como visão robótica em tempo real; muitas vezes **não há interface humana**.
* Pode usar hardware específico (**FPGA**, **ASIC** ou até hardware não digital) para ganhar desempenho e confiabilidade.
* O software tem **função fixa**, específica da aplicação.
* **Eficiência é crucial:** otimizados para energia, tamanho de código, tempo de execução, peso/dimensões e custo.
* Interagem com o mundo externo (detectam, manipulam, comunicam), sendo tipicamente **sistemas reativos** (em interação contínua com o ambiente, em ritmo ditado por ele). Também chamados de sistemas de tempo real: o ambiente **não espera** o processamento; os dados coletados devem representar **o instante atual**.

**Exemplo do freio ABS** (slide): o **sensor** monitora se a roda está girando, a **lógica de programação** calcula o quanto apertar ou soltar as pastilhas, e o **atuador** controla as pastilhas, evitando que a roda deslize na frenagem.

#### 9. Sistemas de tempo real (Questão 9)

* Sistemas de computação que devem **reagir dentro de restrições de tempo precisas** a eventos do ambiente.
* Estar correto depende **do valor do resultado e do momento em que ele é produzido**.
  * Exemplo do slide: um carro a 60 km/h bate e o airbag é ativado: a lógica está certa. Mas se o airbag demorar **1 minuto**, o comportamento do sistema está **incorreto**.
* **Não é necessariamente um sistema reativo.**
* **Determinismo é de vital importância:** o sistema deve atender às restrições de tempo **sempre**, projetado para funcionar **até no pior caso**.

| | Sistema embarcado | Sistema de tempo real |
|---|---|---|
| Foco | Função fixa dentro de um produto; custo, energia, tamanho | Cumprir **prazos** (*deadlines*) |
| "Correto" significa | Faz a função dedicada | Resultado certo **no momento certo** |
| Um pode existir sem o outro? | Sim: o controle remoto de TV é embarcado e sem prazo rígido *(complemento)* | Sim: controle de tráfego aéreo em servidores comuns é tempo real, mas não embarcado *(complemento)* |
| Junção típica | Freio ABS, airbag, equipamento médico: embarcados **e** de tempo real | |

#### 10. Componentes de um sistema embarcado em IoT (Questão 10)

Os slides listam quatro componentes (sensores, atuadores, microcontroladores e comunicação); o gabarito acrescenta o quinto, **meio de identificação (RFID)**.

```
 Mundo físico --(mede)--> [SENSOR] --sinal--> [MICROCONTROLADOR] --sinal--> [ATUADOR] --(age)--> Mundo físico
                                                    |
                                              [COMUNICAÇÃO] <---> gateway / rede / nuvem
```
*(diagrama de apoio, complemento)*

* **Sensores:** medem um parâmetro de uma entidade física, química ou biológica e fornecem um **sinal eletrônico proporcional** (tensão analógica ou sinal digital). A saída vai tipicamente para um microcontrolador. Tipos citados: posição, velocidade, aceleração, força/torque, GPS, pressão, temperatura, fluxo, umidade, visão.
* **Atuadores:** o caminho inverso. Recebem um sinal eletrônico de um controlador e **respondem interagindo com o ambiente**. Exemplos: abrir/fechar porta ou válvula, soar alarme, adicionar um elemento químico a uma solução, aumentar/reduzir a temperatura de um ambiente.
* **Microcontroladores (µC):** veja a seção a seguir.
* **Comunicação:** veja mais abaixo.

##### Microcontroladores

* É **um único chip** com: núcleo do processador, memória **não volátil** para o programa (**ROM**), memória **volátil** (**RAM**) para entrada/saída, **relógio** (*clock*) e **unidade de controle de entrada/saída**.
* O processador tem **área de silício muito menor** que outros microprocessadores e maior **eficiência energética**.
* Lembretes dos slides: **microprocessador** é um processador construído em um único chip; **chip** é uma peça única de material semicondutor (normalmente silício) onde são fabricados os circuitos e portas lógicas; construir circuitos, memórias e barramentos em um único chip dá o nome de **circuito integrado**.
* Variam em tamanho e poder: arquiteturas de **4 a 64 bits**, muito mais lentos que microprocessadores (faixa de **MHz**, não GHz), pouca memória e **muito mais baratos**.
* São **processadores dedicados** a tarefas específicas, muito usados na automação industrial (ligar/desligar ventiladores, abrir/fechar válvulas) sem interação humana. Ao contrário dos computadores de propósito geral, cujo software é fácil de trocar e define a aplicação.

**Von Neumann x Harvard (Questão 8):**

```
 Von Neumann                         Harvard
 +-----+  <-->  RAM (dados+instr.)   +-----+  <-->  RAM (só dados)
 | CPU |                             | CPU |  <-->  ROM (só instruções)
 | ULA |  <-->  I/O                  | ULA |  <-->  I/O
 | CU  |                             | CU  |
 +-----+                             +-----+
```

| | Von Neumann | Harvard |
|---|---|---|
| Memória | **Única** para instruções e dados | **Separadas**: RAM (dados) e ROM (instruções) |
| Barramento | **Único** para instruções e dados | **Separados** |
| Características (gabarito) | Mais flexível, em geral mais fácil de programar | Maior desempenho e eficiência |
| Exemplo (gabarito) | Computadores pessoais | Microcontroladores e DSPs |

Os slides mostram o diagrama interno de um **micro-ondas** (microcontrolador com processador, ROM e RAM, ligado a teclas, sensor de porta aberta, magnetron, ventilador, display, luz e alto-falante) e de uma **câmera digital** (sensores ópticos, conversão A/D, processador, motor, flash, LCD, armazenamento de imagem e interface com o PC).

##### Comunicação

| Tipo de sistema | Requisito | Tecnologias citadas |
|---|---|---|
| **Críticos** | Alta confiabilidade, baixa latência e vazão adequada | **CAN Bus** e **FlexRay** (redes automotivas); **PROFINET, EtherNet/IP, EtherCAT, Modbus TCP/IP** (plantas industriais); **WirelessHART** (plantas industriais); **TTEthernet** (naves espaciais da NASA) |
| **Não críticos** | Aceitam menor confiabilidade e maior latência | **Bluetooth, Zigbee, LoRa, Wi-Fi** |
| **Meio de identificação** | Identificar objetos | **RFID/NFC** |

> ⚠️ Os slides escrevem "baixa confiabilidade, alta latência e vazão" para os não críticos. Leia como: toleram menor confiabilidade e maior latência. É a leitura coerente com a lógica da comparação.

##### RFID: identificação por radiofrequência (Questões 11 e 12)

* **O que é:** tecnologia que usa **ondas de rádio** para identificar itens. Cada vez mais uma tecnologia habilitadora de IoT.
* **Elementos:** **etiquetas (tags)**, pequenos dispositivos programáveis para rastrear objetos, animais e pessoas (formas, tamanhos, funcionalidades e custos variados), e **leitores**, que adquirem e, às vezes, reescrevem informações das tags dentro do alcance (de poucas polegadas a vários pés). Os leitores normalmente estão ligados a um computador que registra e formata os dados.

| Tipo de tag | Fonte de energia | Características |
|---|---|---|
| **Ativa** | Bateria própria gera o sinal | Bem mais cara e fisicamente maior; sinal mais forte, **maior alcance de leitura**, leitura em **alta velocidade** |
| **Passiva** | Energia vinda do sinal de RF que incide sobre a tag | Barata, pode ser fina o suficiente para virar etiqueta; **mais comum** em identificação automática e chaves eletrônicas |
| **Semi-passiva** | Tem bateria, mas se comporta como passiva | |

**Aplicações de RFID:**

* **Rastreamento e identificação:** bilhões de produtos e componentes nas cadeias de abastecimento.
* **Pagamento e armazenamento de valor:** pedágio eletrônico, cartões de pagamento em lojas e locais de entretenimento.
* **Controle de acesso:** cartões de proximidade em empresas e universidades.
* **Combate à falsificação:** cassinos usam tags em fichas; a indústria de medicamentos usa tags para garantir procedência e detectar roubo.

#### 11. Arquitetura de IoT (Questão 13)

Não existe um padrão único: **diversos grupos propõem arquiteturas**: Industrial Internet Consortium (IIC), IEEE P2413 (o slide escreve "P4213"; o nome do grupo na página seguinte é P2413), IEC, ISO/IEC 30141:2018, ITU-T, Open Connectivity Foundation (OCF) e IETF.

##### a) Industrial Internet Consortium (IIC)

Reúne fabricantes, vendedores, usuários e pesquisadores necessários para projetar e desenvolver a IoT (o slide mostra logos de ABB, Bosch, Dell EMC, Fujitsu, GE, Huawei, Microsoft, MITRE, Purdue, RTI). A arquitetura tem **três níveis**:

```
  EDGE TIER                      PLATFORM TIER                  ENTERPRISE TIER
 +---------------------+  Access  +------------------+ Service +----------------------+
 | Dispositivos        | Network  | Plataforma de    | Network | Aplicações do        |
 | (sensores/atuadores)|--------->| serviços:        |-------->| domínio específico   |
 | Proximity Network   | <--------| transformação de | <-------| Regras e controles   |
 | Edge Gateway        | (fluxo   | dados, analytics,|  (fluxo | (pode ser VPN        |
 | (gerência de        |  de dados| operações,       |  de     |  na Internet)        |
 |  dispositivos,      |  e de    | armazenamento    | dados e |                      |
 |  agregação de dados)|  controle)|                  | controle)|                     |
 +---------------------+          +------------------+         +----------------------+
```
*(diagrama redesenhado a partir da figura do slide)*

| Nível | O que contém / faz |
|---|---|
| **Edge Tier** | **Dispositivos de borda** (sensores e atuadores). **Proximity Network**: rede entre dispositivos (mesh, Zigbee, Wi-Fi, Bluetooth). **Edge Gateway**: dá conectividade à Access Network (ex.: roteador Wi-Fi), faz a ligação entre dispositivos e WAN e oferece alguns serviços da Platform Tier, como gerenciamento de recursos e fusão de dados. **Access Network**: rede de longa distância (WAN), infraestruturada, que leva à Platform Tier. |
| **Platform Tier** | Recebe, processa e encaminha **comandos de controle** da Enterprise Tier para a Edge Tier. Gerencia dispositivos; armazena, processa, analisa e disponibiliza dados. Implementa funcionalidades das camadas operacionais e de informação. |
| **Enterprise Tier** | **Aplicações do domínio específico**. A **Service Network** conecta com a Platform Tier (pode ser VPN na Internet) e oferece níveis de segurança entre usuários e serviços. Implementa funcionalidades das camadas de aplicação e de negócio. |

##### b) IEEE P2413: modelo tradicional de 3 camadas

| Camada | Conteúdo |
|---|---|
| **Application Layer** | Aplicações específicas (ex.: saúde, residência). |
| **Abstraction Layer** | Gerenciamento de recursos; transmissão de dados (*things* para gateways via Bluetooth, Wi-Fi...; gateways para o resto da rede via **MQTT, HTTP**...); armazenamento, processamento e análise de dados. **Equivale a um middleware.** |
| **Things Layer** | µC, SoC, ASIC, FPGA, sensores, atuadores; comunicação com periféricos via I2C, serial, CAN. |

##### c) ITU-T

Parte do modelo anterior e **refina a camada de middleware** em duas:

* **Processing Layer:** armazenamento, processamento e análise.
* **Transport Layer:** transmissão de dados entre *things*, gateways e o resto da rede.

E deixa explícito que **segurança e gestão de recursos permeiam todas as camadas**.

##### d) Outros modelos (figura de um slide)

O professor mostra, sem aprofundar, um modelo de cinco camadas (Percepção, Rede, Middleware, Aplicação e Negócio) e o *IoT World Forum Reference Model* de sete níveis (do nível 1, dispositivos físicos e controladores, ao nível 7, colaboração e processos).

> Dica: compare os três modelos principais. O IIC separa por **onde cada coisa roda** (borda, plataforma, empresa); o IEEE P2413 e o ITU-T separam por **função** (coisas, middleware, aplicação).

#### 12. IoT e a nuvem: Edge, Fog, Core e Cloud (Questão 14)

O slide "Embarcados | Nuvem" resume o fluxo: o lado **embarcado** faz **capturar** e **transferir** dados (água, eletricidade, gás, ar, temperatura, vibração); o lado **nuvem** faz **armazenar**, **reportar** e **mudar** (e-mail, SMS/voz, plugins de API, dashboards).

```
 Smart things network  --->  Fog network  --->  Core network  --->  Datacenter / Cloud
 (milhões de devices;        (dezenas de milhares;  (milhares;           (centenas;
  Bluetooth, Wi-Fi,           3G/4G/LTE/Wi-Fi;       IP/MPLS;             Ethernet;
  cabeado; resposta em        inteligência           segurança;           resposta
  milissegundos)              distribuída; tempo     QoS/QoE)             transacional)
                              real)
```
*(esquema baseado na figura do slide)*

* **Edge (borda):** na borda de uma rede empresarial típica há uma rede de dispositivos habilitados para IoT (sensores e talvez atuadores) que podem se comunicar entre si. Pode haver **gateways**, que interconectam esses dispositivos com redes de nível superior, **traduzem protocolos** entre as redes e os dispositivos e podem fazer **agregação básica** de dados.
* **Fog (névoa):**
  * **Problema:** IoT gera dados em quantidade massiva (campos de petróleo offshore e refinarias podem gerar **1 TB por dia**; um avião, **vários TB por hora**).
  * **Solução:** em vez de guardar tudo, por muito tempo, em um armazenamento central, **processar o máximo possível perto dos sensores**. O objetivo da névoa é **converter fluxos de dados da rede em informação** adequada ao armazenamento e processamento de nível superior; os elementos de processamento fazem **transformação de dados**, resultando em volumes **muito menores** armazenados.
  * Traz funcionalidades da nuvem para **perto de onde estão os sensores e atuadores**, com sistemas de capacidade de processamento e armazenamento **altos em comparação aos dispositivos de borda**, tipicamente **nas premissas da organização**.
  * **Origem do nome:** a névoa (*fog*) paira perto do solo, enquanto as nuvens estão no alto do céu.
* **Core network (rede central ou *backbone*):** conecta as redes de névoa geograficamente dispersas e dá acesso a outras redes fora da empresa. Usa roteadores de alto desempenho, linhas de alta capacidade e vários roteadores interconectados para redundância e capacidade; pode conectar a servidores de alto desempenho (grandes bancos de dados, nuvens privadas).
* **Cloud (nuvem):** topo da hierarquia, para armazenamento e processamento de nível superior *(complemento; no slide a nuvem aparece só como título e o professor encerrou com "já vimos o suficiente!", pois o tema foi visto na Aula 3)*.

| Camada | Perto de quê? | Função resumida | Nº de dispositivos (figura) |
|---|---|---|---|
| Smart things / Edge | Do sensor | Capturar, atuar, agregar | Milhões |
| Fog | Da organização | Filtrar, transformar, reduzir dados; baixa latência | Dezenas de milhares |
| Core | Da WAN | Interligar redes, redundância | Milhares |
| Cloud | Do datacenter | Armazenar, analisar em grande escala | Centenas |

---

### 🔍 Tópico em Destaque: Sistemas Embarcados x Sistemas de Tempo Real

* **Propósito e restrições:** sistemas embarcados têm funções fixas e dedicadas dentro de um dispositivo maior, e priorizam custo, tamanho e consumo de energia. Já nos sistemas de tempo real a correção está presa ao cumprimento de **prazos temporais**: o determinismo é obrigatório.
* **Interseção:** muitos sistemas de IoT são **as duas coisas** ao mesmo tempo (controle automotivo, equipamento médico), mas uma não implica a outra *(complemento: um controle remoto de TV é embarcado sem prazo rígido; o controle de tráfego aéreo é tempo real mesmo rodando em servidores comuns)*.
* **Regra prática:** pergunte-se "se a resposta chegar atrasada, o sistema está **errado**?". Se sim, é tempo real.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Arquitetura Harvard x Von Neumann:** na Von Neumann, memória e barramento são únicos para dados e instruções. Na Harvard são separados (RAM só dados, ROM só instruções). Microcontroladores costumam ser Harvard.

> 💡 **Redes críticas x não críticas:** ambientes industriais, automotivos e espaciais pedem confiabilidade e baixa latência (CAN, FlexRay, PROFINET, EtherCAT, TTEthernet). Ambientes não críticos aceitam mais latência (Wi-Fi, Bluetooth, Zigbee, LoRa).

> 💡 **Gêmeo digital (*Digital Twin*):** conexão em tempo real entre o mundo físico (sensores na linha de montagem) e o modelo virtual 3D (CAD/CAE/MES). Permite simular, prever manutenção e viabilizar a manufatura personalizada (*batch size 1*).

> 💡 **Passiva x ativa (RFID):** a pergunta clássica é "qual tag tem bateria?". Ativa e semi-passiva têm; a passiva não (usa a energia do leitor) e por isso é a mais barata e comum.

> 💡 **Disrupção x evolução:** disrupção **cria** um novo mercado (pagar por uso); evolução **melhora** um mercado que já existe (manutenção preditiva).

> 💡 **Modelos arquiteturais:** IIC = 3 níveis físicos (Edge, Platform, Enterprise). IEEE P2413 = 3 camadas funcionais (Things, Abstraction, Application). ITU-T = divide o middleware em Processing e Transport e destaca que segurança e gestão de recursos cruzam todas as camadas.

> 💡 **Erro de digitação nos slides:** o slide de lista de propostas escreve "IEEE P4213"; o grupo de trabalho correto, conforme o slide seguinte, é **IEEE P2413**.

---

### 🧪 Exercícios e Gabarito Comentado

O gabarito (`Aula04-gab.pdf`) tem 14 questões. Resumo com explicação simples:

| # | Pergunta | Resposta (em linguagem simples) |
|---|---|---|
| 1 | O que é IoT? | Infraestrutura de objetos, pessoas, sistemas e fontes de informação interligados, com serviços inteligentes, que **processam informação do mundo físico e virtual e reagem** (definição da ISO/IEC JTC 1). |
| 2 | Tecnologias viabilizadoras? | Dispositivos embarcados (menores, baratos, mais autônomos), conectividade (fibra, 5G, BLE, mesh, LoRa), computação em nuvem (escalável, Big Data, HPC, IaaS por virtualização) e inteligência artificial (visão, fala, ML, AR). |
| 3 | Principais desafios? | **Escalabilidade, heterogeneidade, interoperabilidade e segurança.** |
| 4 | Disruptivo x evolutivo? | Disrupção **cria novos nichos** (economia compartilhada, servitização; pagar por uso de veículos, seguros, nuvem). Evolução **agrega valor a nichos existentes** (manutenção preditiva, chamada automática de emergência em acidente, e-Health). |
| 5 | Servitização com IoT e nuvem? | Empresas que vendem produtos físicos passam a oferecer **serviços em torno deles** (manutenção, suporte, monitoramento, consultoria, leasing/aluguel). Gera relações duradouras e receita recorrente. Exemplos: manutenção e suporte, monitoramento remoto, **SaaS**, **EaaS**. IoT fornece os dados de uso; a nuvem sustenta o serviço contínuo. |
| 6 | Áreas de aplicação? | **Indústria** (vendas/marketing e personalização com *batch size 1*, engenharia digital CAD/CAE/MES e gêmeo digital, manufatura com RFID como memória do produto, servitização, pós-venda com RCM e manutenção preditiva), **gerenciamento de frota/logística**, **saúde** e **agronegócio**. |
| 7 | O que é sistema embarcado? | Eletrônica + software dentro de um produto com função específica (ao contrário de um computador de propósito geral). Ex.: celular, micro-ondas, ABS, escova de dentes. |
| 8 | Von Neumann x Harvard? | Von Neumann: memória e barramento únicos (mais flexível, PCs). Harvard: separados para instruções e dados (mais desempenho e eficiência, microcontroladores e DSPs). |
| 9 | Sistema de tempo real? | Reage em prazos precisos; correto = valor certo **e** no tempo certo (airbag atrasado 1 min está errado); não necessariamente reativo; determinismo vital, projetado para o pior caso. |
| 10 | Componentes de um embarcado em IoT? | Sensores, atuadores, microcontroladores, comunicação e meio de identificação (RFID). |
| 11 | O que é RFID? | Identificação por ondas de rádio com **tags** (bateria própria ou energia do sinal de RF) e **leitores** (leem e às vezes reescrevem; ligados a um computador). |
| 12 | Aplicações de RFID? | Rastreamento na cadeia de suprimentos, pagamento (pedágio, cartões), controle de acesso, combate à falsificação (fichas de cassino, medicamentos). |
| 13 | Arquitetura tradicional de 3 camadas? | A resposta do gabarito descreve os **três níveis do IIC**: Edge Tier (dispositivos, Proximity Network, Edge Gateway, Access Network), Platform Tier (processamento e comando) e Enterprise Tier (aplicações e Service Network). Há uma figura ilustrando o fluxo de dados e de controle entre eles. |
| 14 | O que é Fog Computing? | IoT gera volumes enormes de dados (1 TB/dia em refinaria offshore; vários TB/hora em um avião). Em vez de enviar tudo para o armazenamento central, processa-se o máximo **perto dos sensores**, convertendo fluxos em informação e guardando **volumes bem menores**. |

> Observação: na Questão 13 o gabarito chama de "arquitetura tradicional de 3 camadas" o modelo **IIC** (Edge/Platform/Enterprise). Os slides chamam de "modelo tradicional de 3 camadas" o **IEEE P2413** (Things/Abstraction/Application). Convém saber as duas e deixar claro de qual você está falando.

---

### 🧠 Perguntas de Revisão

1. **Quem cunhou o termo IoT, quando e onde?** Kevin Ashton, em 1999, no Auto-ID Center do MIT.
2. **Cite as quatro tecnologias que viabilizaram a IoT.** Dispositivos embarcados, conectividade, computação em nuvem e inteligência artificial.
3. **Quais são os quatro grandes desafios da IoT?** Escalabilidade, heterogeneidade, interoperabilidade e segurança.
4. **O que é servitização e qual a diferença para um negócio tradicional?** Transformar produto em serviço: passa-se de CAPEX para OPEX, de transação para relacionamento, de soluções pontuais para gestão do ciclo de vida do ativo conectado.
5. **Por que o airbag atrasado 1 minuto é um exemplo de sistema de tempo real incorreto?** Porque a lógica está certa, mas o resultado chegou fora do prazo; em tempo real o momento do resultado faz parte da correção.
6. **Qual a diferença entre RFID ativo e passivo?** Ativo tem bateria própria (mais alcance e velocidade, mais caro). Passivo usa energia do sinal do leitor (mais barato, fino e comum).
7. **Quais são os três níveis da arquitetura do IIC e o papel do Edge Gateway?** Edge, Platform e Enterprise. O gateway conecta os dispositivos à WAN e oferece serviços como gerência de recursos e fusão de dados.
8. **Por que existe a computação em névoa (*fog*)?** Porque IoT gera dados demais para enviar tudo à nuvem; a névoa processa perto dos sensores, reduz o volume e a latência.

---

### 🔗 Conexão com o Trabalho Final

O trabalho da disciplina demonstra **gRPC, REST, RabbitMQ e Apache Kafka**. No modelo IEEE P2413, os gateways falam com o resto da rede por protocolos como **MQTT e HTTP** (este último é a base de REST). O grande fluxo de dados de sensores descrito na aula é o tipo de cenário em que sistemas de mensageria como RabbitMQ e Kafka são úteis *(complemento)*.

---

### 📚 Links & Leituras Complementares

* 📖 *Operating Systems* (William Stallings, 9ª Edição) — Capítulo 13 (Seção 13.1) e Capítulo 16 (Seção 16.3)
* 📖 *Enterprise IoT* (O'Reilly) — Capítulos 1, 2, 3, 4 (páginas 67-77) e Capítulo 5 (páginas 129-132, 140-142)

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 3: Virtualização e Computação em Nuvem](../Aula_3/README.md)
* ➡️ **Próxima Aula:** [Aula 5: Arquiteturas de Sistemas Distribuídos](../Aula_5/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
