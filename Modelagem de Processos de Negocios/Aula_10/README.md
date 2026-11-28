# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 06/11/2026 | 📚 Professor: Flávio Seixas | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 10: Monitoramento de Processos — Frameworks, Qualidade, Governança e Métricas

### 📝 Introdução

Esta aula fechou o ciclo de BPM com os **modelos de referência** que apoiam o desenho e a medição de processos (APQC PCF, SCOR, VRM e COBIT), os **modelos de maturidade** usados para diagnosticar a situação da organização e traçar sua evolução (com destaque para o BPMM) e, na atualização 2026.2, o **monitoramento de processos**, incluindo o uso de *process mining*. O fio condutor é que esses frameworks trazem práticas, métricas e vocabulário comuns, mas **modelo de referência não é um processo**: precisa ser adaptado ao contexto da organização.

---

### 💡 Conceitos Chave

* **Frameworks de Referência:** Modelos de processos reconhecidos que oferecem *insights* sobre desenho, medidas de desempenho e melhores práticas, e ajudam a escolher a sistemática mais adequada: APQC PCF, SCOR, VRM, eTOM, MIT Process Handbook, COBIT, ITIL e CMMI.
* **PCF (*Process Classification Framework*, APQC):** Biblioteca de processos comuns à maioria das organizações, desenvolvida no início dos anos 1990 pela APQC (organização sem fins lucrativos fundada em 1977). Serve como taxonomia de processos e base de *benchmarking*.
  * **Estrutura:** 12 categorias (5 de processos operacionais e 7 de processos gerenciais e serviços de apoio), organizadas em Categorias (4.0) → Grupos de processo (4.1) → Processos (4.1.1) → Atividades (4.1.1.1).
  * **Vantagens:** melhor *benchmarking*, padronização e medição (vocabulário comum e checklist para mapear processos e identificar KPIs) e controle de responsabilidades.
  * **Atualização 2026.2:** na consulta de 05/08/2026, a APQC indica o **PCF 8.0** como versão mais recente. Existem versões intersetoriais e específicas por indústria; a versão usada deve ser registrada no modelo.
* **SCOR (*Supply Chain Operations Reference*):** Modelo para analisar a configuração da cadeia de suprimentos, medir métricas, achar elos fracos e aplicar melhores práticas. Cobre interações com o cliente (da entrada do pedido à fatura paga), transações de produto (dos fornecedores do fornecedor aos clientes do cliente) e interações de mercado.
  * **Níveis:** Nível 1 define os tipos de processo (*plan, source, make, deliver, return*) e alvos de desempenho; Nível 2 traz 30 categorias de processo para configurar a cadeia; Nível 3 detalha elementos de processo, entradas e saídas, métricas, melhores práticas e funcionalidades de sistemas. O Nível 4 (implantação) é desenvolvido pela empresa e não faz parte do modelo.
  * **Atualização 2026.2:** o SCOR atual é o **SCOR Digital Standard**, mantido pela ASCM, que desloca a visão linear para uma **rede sincronizada** e inclui sustentabilidade e habilitadores digitais, com os processos *Orchestrate* (estratégia) e *Plan, Order, Source, Transform, Fulfill, Return* (execução).
* **VRM (*Value Reference Model*):** Criado pelo *Value Chain Group* para modelar a **cadeia de valor inteira** (e não só a de suprimentos), com metodologia, templates, métricas e boas práticas. Integra três domínios: desenvolvimento de produto, integração da rede de suprimentos e sucesso do cliente.
  * **Níveis:** Estratégico (planejar, governar, executar) → Tático → Operacional (191 processos) → Atividades → Ações (instruções de trabalho, indecomponíveis). Cada processo segue um formato padrão com definição, entradas e saídas, métricas e práticas.
* **COBIT (*Control Objectives for Information and related Technology*):** Conjunto de melhores práticas de **gestão e governança de TI**, criado pela ISACA em 1992. Para cada processo traz descrição, controles, entradas e saídas, metas e métricas, tabela de responsabilidades e escala de maturidade baseada no CMM.
  * **Atualização 2026.2:** o **COBIT 2019** substitui o COBIT 5 como referência corrente da ISACA.

#### 🔍 Tópico em Destaque

**Modelos de maturidade e o BPMM**

* **Modelos de maturidade para BPM:** A adoção do BPM é uma trajetória evolutiva. Os modelos de maturidade ajudam a diagnosticar a situação atual, identificar prioridades e estabelecer metas de melhoria. Os mais conhecidos: modelo do Gartner, da Universidade de Queensland, de Michael Rosemann, o PEMM (Michael Hammer) e o **BPMM** (padrão da OMG).
* **Por que o BPMM surgiu:** Muitas implantações de BPM fracassam e costuma-se culpar a tecnologia ou o fornecedor, mas a causa-raiz está, na maioria dos casos, na **maturidade da organização** em relação aos processos. O BPMM (desenvolvimento iniciado em 2002) busca preparar a organização para receber uma solução de BPM.
* **Objetivos do BPMM:** servir de padrão de avaliação da maturidade; avaliar a fidelidade entre como as tarefas são realizadas e como são modeladas; facilitar a padronização de tarefas similares; avaliar fornecedores de TI e de serviços; e guiar a implantação dos fundamentos de processos que trazem agilidade e redução de custos.
* **Origem:** Segue o *Process Maturity Framework* de Watts Humphrey e foi desenvolvido pelos coautores do CMM, CMMI e People CMM. Pode ser mapeado para o CMMI, mas foi escrito para melhorar **processos de negócio** (fluxos entre fronteiras organizacionais), e não projetos.

| Nível | Nome | Foco de gestão |
| --- | --- | --- |
| **1** | Inicial | Gestão inconsistente |
| **2** | Gerenciado | Gestão da unidade de trabalho |
| **3** | Padronizado | Gestão da linha de negócio |
| **4** | Previsível | Gestão da capacidade |
| **5** | Inovando | Gestão de mudança |

A evolução entre os níveis parte de **práticas repetitivas**, passa por **melhores práticas padronizadas** e por práticas **gerenciadas quantitativamente**, e chega a práticas **melhoradas continuamente**.

**Monitoramento de processos (atualização 2026.2)**

* **Monitorar** é observar a execução e os resultados para detectar desvios, compreender causas e orientar decisões.
* Um **painel** deve combinar resultado, tempo, custo, qualidade, capacidade, risco e experiência do cliente, conforme o processo.
* Todo indicador precisa de **fórmula, fonte, periodicidade, responsável, meta e regra de interpretação**.
* Métricas locais não devem induzir a otimização de uma etapa em prejuízo do desempenho ponta a ponta.

**Process mining no ciclo de monitoramento**

| Aplicação | O que faz |
| --- | --- |
| **Descoberta** | Reconstrói modelos de processo a partir de eventos registrados |
| **Conformidade** | Compara o comportamento observado com o modelo esperado |
| **Melhoria** | Identifica variantes, gargalos, retrabalho, desvios e oportunidades |

A qualidade da análise depende de **identificador de caso, atividade, *timestamp* e contexto** confiáveis. As evidências quantitativas complementam, mas não substituem, a interpretação do negócio e a validação com os *stakeholders*.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Modelo de referência não é um processo:** PCF, SCOR, VRM e COBIT organizam vocabulário, métricas e boas práticas, mas não prescrevem um processo executável. Eles apoiam arquitetura, *benchmarking* e padronização, e precisam ser adaptados à realidade da organização.
>
> 💡 **Maturidade não é uma nota isolada:** ela serve para priorizar capacidades, práticas e controles coerentes com os objetivos de negócio. O BPMM 1.0 continua sendo a versão formal publicada pela OMG, mas deve ser contextualizado como um modelo de 2008.

---

### 📚 Links & Leituras Complementares

* 📖 **DUMAS, M. et al. (2018).** *Fundamentals of Business Process Management*, 2ª edição, capítulos 11 e 12.
* 📖 **ABPMP BRASIL (2013).** *BPM CBOK V3.0*, capítulos 6, 8 e 9.
* 📖 **HARMON, P. (2019).** *Business Process Change*, 4ª edição, capítulos 5 a 7.
* 📖 **JESTON, J. (2018).** *Business Process Management*, 4ª edição, capítulo 29.
* 📖 **VOM BROCKE, J.; ROSEMANN, M. (ed.).** *Handbook on Business Process Management 2*, 2ª edição. Springer.
* 🔗 [APQC — Process Classification Framework](https://www.apqc.org/process-frameworks/pcf-faqs)
* 🔗 [ASCM — SCOR Digital Standard](https://www.ascm.org/corporate-solutions/standards-tools/scor-ds/)
* 🔗 [ISACA — COBIT 2019](https://www.isaca.org/resources/cobit)
* 🔗 [OMG — Business Process Maturity Model 1.0](https://www.omg.org/spec/BPMM/)

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 09: Redesenho e Melhoria de Processos de Negócio](../Aula_9/README.md)
* ➡️ **Próxima Aula:** *Em breve*

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
