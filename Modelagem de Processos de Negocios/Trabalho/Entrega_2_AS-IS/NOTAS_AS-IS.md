# Mapeamento AS-IS — Contratação de Novo Colaborador

Material de apoio para a apresentação de mapeamento de processos (Modelagem de Processos de Negócios).
Este documento organiza o **conteúdo**; não é a apresentação nem contém diagramas. Os BPMNs serão desenhados a partir dos roteiros das seções 4, 5 e 6.

**Convenções**
- `[A CONFIRMAR]` = informação que não foi dita pelo grupo e não deve ser apresentada como fato antes de validar.
- Dados internos da empresa são tratados de forma genérica (ex.: "aplicativos padrão", "demais ajustes"). Nenhum dado sensível é exposto.
- Os modelos analíticos são **qualitativos**: apontam esperas, dependências e gargalos a partir do desenho do processo, sem números sem fonte. Itens marcados como hipótese precisam ser validados antes de virar afirmação.

---

## 1. Estrutura geral

**Macro processo:** Contratação de novo colaborador.

**Fluxo macro (visão de ponta a ponta):**
1. A **Área solicitante** identifica a necessidade e solicita a contratação ao RH. *(início do macro processo)*
2. O **RH** conduz o processo seletivo *(subprocesso recolhido; detalhamento fora do escopo do grupo)* e confirma a contratação.
3. O **RH** abre um chamado para a **TI** com os dados básicos do colaborador.
4. A **TI** consulta a Área solicitante sobre o perfil de acessos, cria usuário e acessos, prepara a máquina, entrega e registra o termo.
5. A **TI** informa o RH de que o usuário foi criado. *(fim da participação da TI)*
6. O **RH** segue com a admissão. *(fora do escopo)*

**Processos mapeados (ordem em que aparecem no fluxo):**

| # | Processo | Departamento | Classificação |
|---|---|---|---|
| 1 | Solicitação de contratação, definição de perfil e acolhimento | Área solicitante | **Gerencial** |
| 2 | Admissão do colaborador (seleção e acionamento da TI) | RH | **Principal** |
| 3 | Provisionamento de acessos e estação de trabalho | TI | **Principal** |

Critério usado, considerando o novo colaborador como cliente do macro processo:
- **Principal:** entrega diretamente o que o cliente percebe (ser contratado; receber acessos e máquina).
- **Gerencial:** origina, decide e governa a demanda (a Área solicitante decide a necessidade e define o perfil).
- **Suporte:** apenas viabiliza ou registra. Nenhum dos três foi enquadrado assim.

---

## 2. Mapa de conteúdo para a apresentação (campos prontos)

**Slide 2 — Resumo**
- **Processo fim-a-fim:** Contratação de novo colaborador.
- **Propósito da escolha:** a parte de TI depende de conhecimento tácito e de um POP desatualizado; mapear o macro processo mostra onde estão as esperas e passagens entre áreas.
- **Dono / sponsor:**
  - Macro processo — **dono:** Gerente de RH, que conduz a contratação de ponta a ponta e aciona as demais áreas; **sponsor:** Diretoria da empresa, interessada em um onboarding padronizado e sem atrasos.
  - Processo da TI — Gerente de TI / Coordenador de Infraestrutura.
  - Processo da Área solicitante — Gestor da área.
- **Especialistas consultados:** Analista de Infraestrutura e/ou Gerente de TI.
- **Funções organizacionais:** Área solicitante, RH, TI.
- **Processos e classificação:** tabela da seção 1.
- **Papéis (mínimo 3):** Gestor da área solicitante, Analista de RH, Analista de Infraestrutura, Assistente de Suporte de TI, Novo colaborador.

**Slide 3 — Arquitetura:** macro processo no centro, com os três processos na ordem do fluxo e as passagens da seção 3 entre eles.

**Slides 4 a 6 — Processos 1, 2 e 3:** nome, modelo descritivo, modelo analítico e BPD (seções 4, 5 e 6).

**Slide 7 — Comentários finais:** pontos já visíveis para registrar:
- O gargalo de conhecimento tácito está na preparação da máquina.
- O RH só é informado no final do fluxo da TI.
- Há duas esperas por pessoas de outras áreas (resposta do gestor e foto).
- Próximo passo natural: TO-BE com paralelização e possível automação.

---

## 3. Macro processo — interfaces entre as áreas

| # | De → Para | O que passa | Canal |
|---|---|---|---|
| 1 | Área solicitante → RH | Solicitação de nova contratação | E-mail |
| 2 | RH → TI | Dados básicos do colaborador | Chamado |
| 3 | TI → Área solicitante | Consulta sobre o perfil de acessos | E-mail ou canal de atendimento de chamados |
| 4 | Área solicitante → TI | Perfil de acessos definido | Resposta à TI |
| 5 | RH → TI | Foto do colaborador | Retorno ao chamado |
| 6 | TI → Novo colaborador | Máquina, kit e termo de recebimento | Entrega presencial |
| 7 | TI → RH | Aviso de usuário criado | Chamado |

---

## 4. Processo 1 — Área solicitante

**Nome:** Solicitação de contratação, definição de perfil e acolhimento.
**Raia (pool único):** Gestor da área solicitante.
**Exemplo genérico para a apresentação:** "a área de Marketing precisa de mais um colaborador".

### Modelo descritivo
- **Gatilho:** necessidade de um novo colaborador na área.
- **Passos:**
  1. Identificar a necessidade de um novo colaborador.
  2. Solicitar a contratação ao RH por e-mail. *(dispara o processo do RH)*
  3. Aguardar o RH conduzir a contratação. *(a área pode participar do processo seletivo, por ser a solicitante)*
  4. Receber a consulta da TI sobre o perfil de acessos.
  5. Definir o perfil: grupos de permissão, listas de distribuição, aplicativos específicos e necessidade de monitor.
  6. Responder à TI.
  7. Acolher e integrar o colaborador na área.
- **Regras de negócio:**
  - A resposta ao passo 6 precisa chegar antes da associação de grupos na TI, porque trava a etapa seguinte.
  - A entrega da máquina é feita apenas pela TI; o gestor não participa dela.
- **Fim:** colaborador integrado à área.

### Modelo analítico
Análise qualitativa a partir do desenho do processo.

**Esperas e dependências**
- Aguardar o RH (passo 3): a área pode participar do processo seletivo, mas não controla o prazo da contratação.
- Resposta à consulta da TI (passos 4 a 6): está no caminho crítico do processo da TI, pois bloqueia a associação de grupos e tudo o que vem depois.

**Passagens entre áreas**
- Três interações externas: solicitação ao RH, recebimento da consulta da TI e resposta à TI.

**Pontos de atenção**
- Os canais são informais: a solicitação vai por e-mail e a consulta da TI pode chegar por e-mail ou pelo canal de chamados, sem um canal único definido. *(hipótese: sem rastreio padronizado, a consulta pode se perder ou atrasar)*
- O perfil de acessos só é definido quando a TI pergunta, e não junto com a solicitação de contratação.

**Oportunidades para o TO-BE (hipóteses a validar)**
- Informar o perfil de acessos já na solicitação ao RH, eliminando a espera da TI.
- Padronizar o canal de solicitação e de consulta.
- Definir perfis de acesso padrão por tipo de cargo.

**Indicadores que poderiam acompanhar o processo (sem valores levantados)**
- Tempo de resposta à consulta da TI.
- Tempo entre a solicitação da contratação e o colaborador integrado à área.

### Roteiro BPMN
- Pool Área solicitante, uma raia.
- Início (evento simples) → tarefa 1 → tarefa de envio (2, mensagem para o pool do RH) → evento intermediário de espera → evento intermediário de mensagem recebida (4, vindo da TI) → tarefa 5 → tarefa de envio (6, mensagem para a TI) → tarefa 7 → fim.
- Pools externos (caixa preta): RH e TI.

---

## 5. Processo 2 — RH

**Nome:** Admissão do colaborador (seleção e acionamento da TI).
**Raia (pool único):** Analista de RH.
**Escopo:** apenas o que toca o macro processo. O processo seletivo é um **subprocesso recolhido** (sem detalhamento por falta de conhecimento do grupo).

### Modelo descritivo
- **Gatilho:** solicitação de contratação vinda da Área solicitante.
- **Passos:**
  1. Receber a solicitação da Área solicitante.
  2. Conduzir o processo seletivo. *(subprocesso recolhido)*
  3. Confirmar a contratação.
  4. Reunir os dados básicos do novo colaborador.
  5. Abrir o chamado para a TI com essas informações.
  6. Obter a foto do colaborador.
  7. Enviar a foto à TI (retorno ao chamado).
  8. Receber o aviso da TI de que o usuário foi criado.
  9. Seguir com a admissão. *(fora do escopo; fim)*
- **Regras de negócio:** o chamado precisa conter as informações básicas; a foto é necessária para a assinatura de e-mail.
- **A confirmar:** se a TI devolve o chamado quando faltam dados.

### Modelo analítico
Análise qualitativa a partir do desenho do processo.

**Esperas e dependências**
- O início depende da solicitação enviada por e-mail pela Área solicitante.
- O processo seletivo (subprocesso recolhido) é a maior parte do ciclo do macro processo. *(hipótese: tende a ser a etapa mais longa, mas está fora do escopo do mapeamento)*
- O RH é fornecedor da foto, e a assinatura de e-mail da TI depende dela.
- O RH depende da TI para saber que o usuário foi criado.

**Visibilidade**
- O RH só é avisado no final do fluxo da TI, depois da entrega da máquina. O fluxo descrito não prevê aviso intermediário. *(hipótese: o RH não tem visibilidade do andamento entre a abertura do chamado e o aviso final)*

**Pontos de atenção**
- Chamado com dados básicos incompletos pode gerar retrabalho entre RH e TI. *(a confirmar)*

**Oportunidades para o TO-BE (hipóteses a validar)**
- Obter a foto mais cedo, junto com os dados básicos, para não atrasar a assinatura.
- Prever um aviso intermediário da TI (por exemplo, quando o usuário é criado) em vez de somente ao final.
- Formalizar a solicitação da Área solicitante em um canal rastreável.

**Indicadores que poderiam acompanhar o processo (sem valores levantados)**
- Tempo entre a abertura do chamado e o aviso da TI.
- Tempo entre a confirmação da contratação e a entrega da máquina.

### Roteiro BPMN
- Pool RH, uma raia.
- Início por mensagem (solicitação da Área solicitante) → subprocesso recolhido "Processo seletivo" → tarefas 3 e 4 → tarefa de envio (5, mensagem para a TI) → tarefa 6 → tarefa de envio (7, mensagem para a TI) → evento intermediário de mensagem recebida (8, da TI) → tarefa 9 → fim.
- Pools externos (caixa preta): Área solicitante e TI.

---

## 6. Processo 3 — TI (detalhado)

**Nome:** Provisionamento de acessos e estação de trabalho.
**Dono do processo:** Gerente de TI / Coordenador de Infraestrutura.
**Raias (pool único "TI"):** Analista de Infraestrutura e Assistente de Suporte de TI. A preparação da máquina é executada pelo Assistente.

### Modelo descritivo
- **Gatilho:** chamado do RH com os dados básicos do novo colaborador.
- **Subprocessos (agrupamento lógico das tarefas):**
  - A. Triagem e identidade: tarefas 2 a 3.
  - B. Perfil e acessos: tarefas 4 a 9.
  - C. Assinatura de e-mail: tarefas 11 e 12.
  - D. Preparação, entrega e registro: tarefas 13 a 20.
  - E. Retorno ao RH: tarefa 22.
- **Regras de negócio:**
  - Se o grupo necessário não existe, é criado antes da associação.
  - A assinatura de e-mail depende da foto enviada pelo RH.
  - A máquina deveria já estar preparada; quando não está, exige formatação, aplicativos padrão, impressoras e demais ajustes.
  - A entrega é feita apenas pela TI e inclui kit de teclado e mouse e, quando houver, monitor.
  - O termo de recebimento assinado é registrado no sistema documental pela TI e fica sujeito à auditoria da Garantia da Qualidade.
  - Acessos e preparação da máquina ocorrem **em sequência** (AS-IS).
  - A foto **não bloqueia** a máquina; bloqueia apenas a geração da assinatura.
- **Sistemas e artefatos:** canal de chamados, AD, listas de distribuição, sistema documental, termo de recebimento.

### Roteiro BPMN (numeração para usar no desenho)

**Pools:** TI (detalhado, 2 raias) e caixas pretas RH, Área solicitante e Novo colaborador.
**Objetos de dados:** chamado; termo de recebimento. **Repositório:** sistema documental.

| # | Raia | Elemento BPMN | Descrição |
|---|---|---|---|
| 1 | Analista | Início (mensagem) | Chamado do RH recebido |
| 2 | Analista | Tarefa | Triar o chamado e separar as informações |
| 3 | Analista | Tarefa | Criar usuário no AD |
| 4 | Analista | Tarefa de envio | Consultar a Área solicitante sobre o perfil de acessos |
| 5 | Analista | Evento intermediário (mensagem recebida) | Aguardar a resposta da Área solicitante |
| 6 | Analista | Gateway exclusivo | Os grupos necessários existem? **Não** → 6a (criar grupo) e volta; **Sim** → 7 |
| 7 | Analista | Tarefa | Associar o usuário aos grupos |
| 8 | Analista | Tarefa | Incluir nas listas de distribuição |
| 9 | Analista | Tarefa | Definir o e-mail corporativo |
| 10 | Analista | Gateway paralelo (divisão) | Abre dois ramos: assinatura e máquina |
| **Ramo A — assinatura** | | | |
| 11 | Analista | Evento intermediário (mensagem recebida) | Aguardar a foto do RH |
| 12 | Analista | Tarefa | Gerar a assinatura de e-mail |
| **Ramo B — máquina** | | | |
| 13 | Assistente | Gateway exclusivo | A máquina já está preparada? **Sim** → 17; **Não** → 14 |
| 14 | Assistente | Tarefa | Formatar |
| 15 | Assistente | Tarefa | Instalar os aplicativos padrão |
| 16 | Assistente | Tarefa | Configurar impressoras e demais ajustes |
| 17 | Assistente | Tarefa | Reunir kit (teclado, mouse, monitor quando houver) e termo |
| 18 | Assistente | Tarefa | Entregar ao colaborador (fluxo de mensagem para o pool do colaborador) |
| 19 | Assistente | Tarefa | Coletar a assinatura do termo |
| 20 | Assistente | Tarefa | Registrar o termo no sistema documental (repositório de dados) |
| 21 | — | Gateway paralelo (junção) | Aguarda os dois ramos |
| 22 | Analista | Fim (mensagem) | Informar o RH de que o usuário foi criado |

**Fluxos de mensagem a desenhar:** RH → 1; 4 → Área solicitante; Área solicitante → 5; RH → 11; 18 ↔ Novo colaborador; 22 → RH.

**Observações de modelagem**
- Os acessos (2–9) e a máquina (13–20) são sequenciais: a raia do Assistente só começa depois de 10. Isso aparece no desenho como ociosidade do assistente e é fiel ao AS-IS.
- O ramo A é paralelo ao ramo B, então a espera pela foto não atrasa a máquina.
- A junção (21) faz o RH ser informado só depois do ramo mais lento, quase sempre o da máquina e entrega.

### Modelo analítico (TI)
Análise qualitativa a partir do BPD, sem dados quantitativos levantados.

**Esperas e dependências**
- Resposta da Área solicitante (tarefa 5): bloqueia a associação de grupos e, por consequência, tudo o que vem depois.
- Foto do RH (tarefa 11): bloqueia apenas a assinatura de e-mail; não atrasa a máquina.
- Sequência entre acessos e preparação da máquina: a raia do Assistente só começa depois da tarefa 10.

**Gargalos**
- Preparação da máquina (tarefas 14 a 16): depende de conhecimento tácito e de um POP desatualizado. *(hipótese principal a validar na entrevista com o especialista)*
- Junção (tarefa 21): o RH só é informado depois do ramo mais lento, em geral o da máquina e entrega.

**Ociosidade**
- O Assistente fica sem tarefas durante a criação de usuário e acessos (tarefas 2 a 9) por causa da sequência.

**Passagens entre áreas**
- Seis fluxos de mensagem com outras áreas: chamado do RH, consulta e resposta da Área solicitante, foto do RH, entrega ao colaborador e aviso final ao RH.

**Oportunidades para o TO-BE (hipóteses a validar)**
- Antecipar o perfil de acessos junto ao chamado do RH, eliminando a espera da tarefa 5.
- Iniciar a preparação da máquina em paralelo aos acessos.
- Avisar o RH assim que o usuário for criado, em vez de somente ao final.
- Atualizar o POP e padronizar a preparação da máquina para reduzir a dependência de conhecimento tácito.

---

## 7. Decisões tomadas

- Macro processo: Contratação de novo colaborador, iniciado pela Área solicitante.
- Três departamentos/processos: Área solicitante, RH e TI. A Garantia da Qualidade ficou fora como processo.
- Classificação baseada na lógica "novo colaborador como cliente": Área solicitante Gerencial; RH e TI Principais.
- TI em um único BPD, uma pool, raias por cargo: Analista de Infraestrutura e Assistente de Suporte de TI.
- A preparação da máquina é executada pelo Assistente.
- Acessos e máquina em sequência no AS-IS.
- Consulta à Área solicitante após criar o usuário e antes de associar os grupos.
- A foto bloqueia apenas a assinatura, não a máquina.
- O RH só é avisado no final do fluxo da TI.
- Solicitação ao RH e consulta da TI por e-mail (a consulta também pode ocorrer pelo canal de chamados).
- A entrega da máquina é feita apenas pela TI.
- O termo é registrado pela TI.
- Modelos descritivo e analítico (qualitativo) para os três processos.

## 8. Pontos em aberto

1. Confirmar com o RH se a TI devolve o chamado quando faltam dados (seção 5).
2. Confirmar na empresa os cargos exatos do dono e do sponsor do macro processo (seção 2).
