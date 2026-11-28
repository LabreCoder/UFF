# Entrega 3: Análise e Redesenho TO-BE

Conteúdo de apoio para a apresentação TO-BE, que segue o modelo [3_Modelo_Mapeamento_TO-BE.pdf](../00_Enunciado/3_Modelo_Mapeamento_TO-BE.pdf).

**Base usada:** a apresentação AS-IS entregue ([PDF](../Entrega_2_AS-IS/Apresentacao_AS-IS_Contratacao_Novo_Colaborador.pdf)) e o BPMN final ([AS-IS](../Entrega_2_AS-IS/bpmn/AS-IS_Contratacao_Novo_Colaborador.bpmn)).
**Diagrama TO-BE:** [bpmn/TO-BE_P3_Provisionamento_TI.bpmn](bpmn/TO-BE_P3_Provisionamento_TI.bpmn)

Como não há dados quantitativos (dificuldade já registrada na entrega AS-IS), a análise é **qualitativa** e não apresenta números sem fonte.

---

## 0. O que o professor pede e quais aulas sustentam a entrega

| Slide | Conteúdo exigido | Aula |
| --- | --- | --- |
| Título | Título e integrantes | — |
| Resumo | Processo AS-IS escolhido, método de análise qualitativa e heurísticas de redesenho, **cada um com o porquê** | 07 e 09 |
| Análise qualitativa | Resultados e conclusões | 07 |
| Redesenho TO-BE | Novo diagrama BPMN; destacar e **justificar** as mudanças | 05, 06 e 09 |

---

## 1. Resumo

### 1.1 Processo selecionado
**Processo 03: Provisionamento de acessos e estação de trabalho (TI)**, classificado como *Principal* no macro processo *Contratação de novo colaborador*.

**Por quê:**
- É a motivação original do grupo: a parte de TI depende de conhecimento tácito e de um POP desatualizado.
- Concentra as esperas e os gargalos apontados nos comentários finais do AS-IS: resposta da Área solicitante, foto do RH, preparação da máquina e RH avisado só no final.
- É a última etapa antes do colaborador começar a trabalhar, então qualquer atraso nela chega direto ao cliente do processo.

### 1.2 Método de análise qualitativa (Aula 07)
1. **Análise de valor agregado (VA / BVA / NVA)** de cada elemento do BPD.
2. **Análise de desperdícios** (os 7 desperdícios).
3. **Causa-raiz** com **5 porquês**, seguida do **registro dos problemas** e da priorização pela **matriz PICK**.

**Por quê:** não existem medições de tempo nem de volume. Essas técnicas trabalham só com o modelo AS-IS e com o que foi levantado com o especialista. Mesmo assim, levam do sintoma (entrega lenta e dependente de pessoas) às causas que o TO-BE ataca.

### 1.3 Heurísticas de redesenho (Aula 09)
| Heurística | Meta | Aplicação |
| --- | --- | --- |
| **Resequenciamento** | Tempo | Perfil de acessos e foto passam a vir **no próprio chamado** |
| **Eliminação de atividades / Redução de contatos** | Custo e tempo | Saem a consulta à Área solicitante e as idas e vindas com o RH |
| ***Knock-out*** | Custo | Chamado incompleto é devolvido logo na triagem |
| **Paralelismo** | Tempo | A preparação da máquina começa logo após a triagem, sem esperar os acessos |
| **Integração / padronização (POP atualizado)** | Qualidade | A preparação segue um roteiro documentado, e não o conhecimento de uma pessoa |

**Por quê:** os problemas do AS-IS são, em sua maioria, **esperas e passagens entre áreas** (meta: tempo) e **dependência de conhecimento tácito** (meta: qualidade). Essas heurísticas atacam os dois pontos sem exigir sistemas novos.

---

## 2. Análise qualitativa: Resultados

### 2.1 Valor agregado (elementos do BPD AS-IS da TI)
| Elemento AS-IS | Classe | Comentário |
| --- | --- | --- |
| Chamado do RH recebido | NVA | Passagem RH → TI |
| Triar o chamado e separar as informações | BVA | Controle necessário |
| Informar recebimento do chamado | NVA | Passagem |
| Criar usuário no AD | VA | |
| Consultar a Área solicitante sobre o perfil de acessos | NVA | Passagem: a informação poderia vir no chamado |
| Aguardar a resposta da Área solicitante | NVA | Espera que **bloqueia acessos e máquina** |
| Os grupos existem? / Criar grupo com permissões | BVA | Controle |
| Associar o usuário aos grupos | VA | |
| Definir o e-mail corporativo (envia ao RH) | VA | Só depois disso o RH manda a foto |
| Incluir nas listas de distribuição | VA | |
| Aguardar a foto do RH | NVA | Espera |
| Gerar a assinatura de e-mail | VA | |
| Retornar com a assinatura criada | NVA | Passagem TI → RH |
| Formatar / instalar aplicativos / configurar impressoras | VA | Manual e dependente de conhecimento tácito |
| Gerar termo de Responsabilidade | BVA | |
| Entregar máquina e assinatura | VA | |
| Coletar assinatura do termo / Registrar no sistema documental | BVA | |
| Informar o RH de que o usuário foi criado | NVA | Passagem, **só no final** |

**Leitura:** 7 elementos NVA, todos esperas ou passagens entre áreas. O processo da TI troca **8 mensagens** com o RH e a Área solicitante.

### 2.2 Desperdícios
| Desperdício | Onde aparece no AS-IS |
| --- | --- |
| **Espera** | Resposta da Área solicitante (o gateway paralelo só abre depois dela, então a máquina também espera); foto do RH, que por sua vez espera o e-mail corporativo |
| **Transporte (passagens)** | 8 trocas de mensagem: chamado, confirmação, consulta, resposta, e-mail, foto, assinatura e aviso final |
| **Defeito / retrabalho** | Chamado incompleto gera reabertura (o RH já tem um laço de reabertura com temporizador de 24h) |
| **Inventário** | Chamado parado aguardando outra área |

### 2.3 Causa-raiz: 5 porquês
**Problema:** a máquina e os acessos demoram e dependem de pessoas específicas.
1. Por que demoram? → Porque o fluxo para várias vezes aguardando outras áreas.
2. Por que aguarda outras áreas? → Porque o chamado chega sem perfil de acessos e sem foto.
3. Por que chega incompleto? → Porque o chamado não define quais informações são obrigatórias.
4. Por que a máquina não adianta enquanto isso? → Porque, no fluxo, a preparação só começa depois da resposta da Área.
5. Por que a preparação depende de pessoas? → Porque o **POP está desatualizado** e o passo a passo está na cabeça do analista.

### 2.4 Registro e priorização (matriz PICK)
| # | Problema | Impacto | Esforço | PICK |
| --- | --- | --- | --- | --- |
| P1 | Perfil e foto pedidos depois da abertura do chamado | Alto | Baixo | **Implementar** |
| P2 | Preparação da máquina bloqueada pela resposta da Área | Alto | Baixo | **Implementar** |
| P3 | Chamado incompleto só é percebido no meio do fluxo | Médio | Baixo | **Implementar** |
| P4 | RH só é avisado no final | Médio | Baixo | **Implementar** |
| P5 | Preparação dependente de conhecimento tácito | Alto | Médio | **Desafio** |

### 2.5 Conclusões
- O tempo é consumido pelas **esperas entre áreas**, e não pelo trabalho técnico da TI.
- A **causa-raiz** é a falta de padrão: chamado sem conteúdo mínimo e POP desatualizado.
- P1 a P4 são mudanças de **sequência e de interface**, de baixo custo. P5 exige atualizar o POP.

---

## 3. Redesenho TO-BE

### 3.1 Fluxo do novo diagrama
Pool **TI**, com as raias *Analista de TI* e *Assistente de TI*. O **RH** aparece como caixa-preta. A Área solicitante deixa de trocar mensagens com a TI, porque passa a informar o perfil ao RH, que o envia no chamado.

1. **Início:** chamado de admissão recebido com dados, perfil de acessos e foto.
2. **Triar e conferir** → *Chamado completo?*
   - **Não:** fim "Chamado devolvido ao RH para complementação".
   - **Sim:** confirmar o recebimento ao RH.
3. **Gateway paralelo:**
   - **Analista:** criar usuário no AD → grupos existem? (se não, criar grupo) → associar aos grupos → definir e-mail → incluir nas listas → gerar assinatura (a foto já veio no chamado) → **informar o RH: usuário, e-mail e assinatura criados**.
   - **Assistente:** máquina formatada? (se não, formatar) → instalar aplicativos padrão → configurar impressoras e ajustes (conforme o POP atualizado) → gerar termo.
4. **Junção** → entregar máquina e assinatura → coletar assinatura do termo → registrar no sistema documental.
5. **Fim:** chamado encerrado e entrega informada ao RH.

### 3.2 Principais mudanças e justificativas (marcadas como M1 a M5 no diagrama)
| # | Mudança | Heurística | Problema | Justificativa |
| --- | --- | --- | --- | --- |
| M1 | Chamado já traz perfil de acessos e foto | Resequenciamento, Eliminação | P1 | Elimina a consulta à Área e a espera pela foto; as mensagens no caminho normal caem de 8 para 4 |
| M2 | Conferência de completude na triagem | *Knock-out* | P3 | O retrabalho é detectado no início, antes de qualquer trabalho técnico |
| M3 | Acessos e máquina em paralelo logo após a triagem | Paralelismo | P2 | O tempo passa a ser o do ramo mais lento, e não a soma das esperas (Aula 08: `CT = max`) |
| M4 | RH avisado assim que usuário, e-mail e assinatura existem | Redução de contatos | P4 | O RH segue a admissão sem esperar a entrega física; três mensagens viram uma |
| M5 | Preparação da máquina segue o POP atualizado | Padronização | P5 | Reduz a dependência de conhecimento tácito e a variação entre analistas |

### 3.3 *Trade-offs* (Aula 09)
- A Área solicitante e o RH precisam reunir mais informações **antes** de abrir o chamado: o esforço vai para o início do macro processo.
- Atualizar o POP tem custo inicial de tempo da equipe de TI, em troca de qualidade e menor risco.

### 3.4 Indicadores sugeridos (Aula 10)
| Indicador | Fórmula | Fonte |
| --- | --- | --- |
| Tempo de provisionamento | Data de encerramento − data de abertura do chamado | Sistema de chamados |
| Taxa de chamados devolvidos | Chamados devolvidos ÷ chamados abertos | Sistema de chamados |
| Entregas até o 1º dia do colaborador | Entregas no prazo ÷ total de entregas | Chamados + RH |
