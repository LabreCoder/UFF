# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 04/09/2026 | 📚 Professor: Flávio Seixas | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 04: Descoberta de Processos de Negócio (AS-IS)

### 📝 Introdução

Esta aula tratou da **descoberta de processos** (*process discovery*), etapa do ciclo de BPM responsável por transformar o conhecimento tácito sobre como o trabalho é realizado em um modelo explícito, compreensível por todos os envolvidos. Foram discutidos os motivos que levam uma organização a mapear seus processos, o planejamento necessário antes de começar, a relação entre os modelos **AS-IS** e **TO-BE**, os níveis de modelagem, as principais notações, quem participa da descoberta (patrocinador, especialistas e analista), as técnicas de levantamento (workshops/JAD, abordagens *top-down* × *bottom-up*, entrevistas livres × estruturadas) e os produtos gerados ao final.

---

### 💡 Conceitos Chave

* **Descoberta de Processos (*Process Discovery*):** Também chamada de mapeamento de processos. Consiste em tornar explícito aquilo que na organização costuma ser tácito: cada departamento enxerga apenas uma parte local do processo e raramente alguém tem a visão ponta a ponta. Um processo explícito comunica estrutura e detalhes de forma que todos possam entendê-lo e decidir com base nele.
* **Modelo de Processo:** Desenho, gráfico ou diagrama que torna o processo visível às partes envolvidas. É uma versão simplificada da realidade complexa, representando apenas o que for necessário para o propósito da modelagem.
* **Por que descobrir processos?** Entender como o processo realmente funciona; encontrar gargalos, passos manuais e redundâncias; documentar para treinamento de novos funcionários; ter uma linha de base de comparação entre AS-IS e TO-BE (inclusive análise de ROI); identificar e controlar riscos; padronizar processos entre filiais; adotar boas práticas (SCOR, ITIL, COBIT, PMBOK); atender a *compliance*; gerar requisitos funcionais para sistemas; e desenhar a lógica de negócio de processos apoiados por um BPMS.
* **Antes de começar:** Definir o **propósito** (a modelagem é um meio, não um fim, e o propósito determina o nível de detalhe), **quais processos** serão descobertos e com qual critério de priorização, **qual notação** será o padrão, **quem** compõe a equipe (com plano de trabalho, responsáveis, prazos e recursos), **qual ferramenta** será usada e **qual metodologia** será seguida.
* **Do AS-IS para o TO-BE:** O consenso obtido sobre o processo atual (AS-IS) serve de entrada para a etapa de análise, a partir da qual se desenha o processo futuro (TO-BE).
  * **Vale levantar o AS-IS quando:** ele traz restrições às melhorias, as mudanças pretendidas são pequenas, o processo atual não é plenamente entendido, a organização tem aversão a riscos, o processo é estratégico ou a diferença AS-IS × TO-BE gerará um documento de gestão de mudança.
  * **Pode-se pular o AS-IS quando:** o processo é uma *commodity* ou será desenhado um processo novo, que ainda não existe na organização.
* **Níveis de Modelagem (valem para AS-IS e TO-BE):**
  * **Descritiva:** abstrata e de alto nível, fácil de comunicar; exige entender piscinas (*pools*), raias (*lanes*), tarefas, subprocessos e fluxo de sequência, sem a complexidade dos padrões de evento da BPMN.
  * **Analítica:** mais detalhada, mostra todos os passos, inclusive caminhos de exceção; é necessária para simulação de desempenho ou para levantar requisitos detalhados de TI.
  * **Executável:** a BPMN passa a fazer parte da implementação do processo, com muitas restrições de validação.
* **Notações:** **Fluxograma** (simples e limitado, origem no TQM nos anos 1950 e padrão ANSI nos anos 1970); **EPC** (*Event Process Chain*, parte do framework ARIS nos anos 1990, com conectores para fluxos alternativos e paralelos); **UML** (voltada a analistas de sistemas); **IDEF** (ampla, da modelagem funcional à simulação); e **BPMN** (padrão aberto, suportado pela maioria das ferramentas e criado para ser usado tanto por TI quanto pelo negócio).

#### 🔍 Tópico em Destaque

**O que se identifica na descoberta do AS-IS**

* **Espaço do processo:** Processos *core* (como "fabricar o produto") formam uma rede de processos inter-relacionados, na qual um alimenta o outro (ex.: gerenciamento de pedidos invoca o faturamento). Eles se decompõem em camadas até as **tarefas atômicas**, que não podem mais ser divididas.
* **Topologia do processo:** O fluxo lógico, com pontos de entrada e saída, sequência de atividades, decisões, bifurcações (*fork*) e junções (*join*).
* **Atributos do processo:** Dono do processo (*process owner*), propósito, cliente e especialistas no assunto (SME).
* **Atributos de cada atividade:** Papéis (quem executa), recursos (sistemas usados), dados (consumidos ou produzidos), duração (tempo para iniciar e total), descrição, regras de negócio e a fonte de informação.

**Quem participa da descoberta**

| Papel | Responsabilidade |
| --- | --- |
| **Patrocinador (*sponsor*)** | Autoriza o projeto, define escopo, meta e prazo, expõe os problemas atuais e garante os recursos para os analistas |
| **Especialistas no assunto (SMEs)** | Fontes de informação sobre o processo: gerentes, funcionários da linha de frente ou profissionais de TI |
| **Analista de processos** | Compila, organiza, analisa e representa as informações coletadas; pode precisar de várias sessões com os SMEs |

**Abordagens de descoberta**

| Abordagem | Como funciona | Vantagem | Desvantagem |
| --- | --- | --- | --- |
| **Sessões centralizadas** | Analista reúne vários SMEs em workshops/JAD e constrói o processo pedaço por pedaço | Interação entre participantes revela lacunas | Difícil reunir as pessoas; depende da experiência do analista |
| **Sessões distribuídas** | Informações coletadas em sessões separadas e depois unidas | Mais democrática; ouve quem seria calado em grupo | Informações divergentes precisam ser conciliadas |
| ***Top-down*** | Parte dos processos maiores e os divide em menores | Garante o escopo correto | Pode perder detalhes e deixar passos incompletos |
| ***Bottom-up*** | Parte dos SMEs e compila o contexto do processo | Grande riqueza de detalhes | Difícil saber se todos foram ouvidos e montar o contexto geral |
| **Forma livre** | SMEs descrevem livremente o processo, problemas e exemplos | Sem censura; surgem *insights* valiosos | Muito tempo para estruturar; difícil garantir consistência |
| **Estruturada** | SMEs respondem a perguntas pré-definidas | Consistência e completude | Pode perder *insights* que fogem do formulário |

**Workshops e sessões JAD**

* **JAD (*Joint Application Design*):** Técnica criada pela IBM para coletar requisitos, em que a equipe e os *stakeholders* trabalham juntos em workshops. Costuma envolver um facilitador (o analista), o patrocinador (normalmente na primeira e na última sessão), especialistas de negócio, especialistas de TI e um documentador. A ferramenta mais utilizada é o **Post-it**.
* **Por que as sessões falham:** gerentes que não acreditam no resultado, dificuldade de reunir as pessoas-chave, descrições imprecisas, medo de apontar falhas do próprio departamento, excesso de detalhes e documentos que dependem da aprovação de várias pessoas.

**Ferramentas e saídas da descoberta**

* **Ferramentas:** Recursos simples do MS-Office nem sempre bastam. Duas funcionalidades são críticas: **validação** (identificar inconsistências e informações incompletas) e **integração** (conectar fragmentos de processo, essencial na abordagem *bottom-up*).
* **Produtos de visualização:** diagramas de fluxo de atividade, de informação e de recursos; e visões hierárquica, ponta a ponta, de piscinas/raias e análise de caminho.
* **Produtos de análise:** descrições de trabalho, especificações funcionais, análises de custo, de ciclo de tempo, de pontos de toque, de repasse entre papéis e de *gaps*.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **AS-IS baseado em evidências (atualização 2026.2):**
>
> * Combine entrevistas, observação, documentos, sistemas e workshops para reduzir o viés de uma única fonte.
> * Registre separadamente o **fato observado**, a **interpretação** e a **hipótese**.
> * Valide o modelo com quem executa o processo e com quem recebe o resultado.
> * Mantenha **rastreabilidade** entre evidências, decisões de modelagem, problemas e oportunidades do TO-BE.

---

### 📚 Links & Leituras Complementares

* 📖 **DUMAS, M. et al. (2018).** *Fundamentals of Business Process Management*, 2ª edição, capítulo 5.
* 📖 **ABPMP BRASIL (2013).** *BPM CBOK V3.0*, capítulos 3 e 4.
* 📖 **HARMON, P. (2019).** *Business Process Change*, 4ª edição, capítulos 8 a 10.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 03: Ciclo de BPM, Conceitos e Fundamentos de Processos de Negócio](../Aula_3/README.md)
* ➡️ **Próxima Aula:** [Aula 05: Modelagem de Processos de Negócio com BPMN — Conceitos](../Aula_5/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
