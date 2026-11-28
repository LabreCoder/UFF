# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 11/09/2026 | 📚 Professor: Flávio Seixas | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 05: Modelagem de Processos de Negócio com BPMN — Conceitos

### 📝 Introdução

Esta aula apresentou a **BPMN** (*Business Process Model and Notation*), notação padrão para representar processos de negócio por meio de diagramas (*Business Process Diagram* — BPD). Foram abordados a motivação e o escopo da notação, sua evolução até a versão 2.0, os três níveis de modelagem e, principalmente, as quatro categorias de elementos: objetos de fluxo (atividades, eventos e *gateways*), objetos de conexão, partições (piscinas e raias) e artefatos.

---

### 💡 Conceitos Chave

* **BPMN:** Notação baseada em fluxogramas, orientada ao uso humano, cuja meta é ser entendida tanto pelo pessoal de **negócio** quanto pelo de **TI**, eliminando a lacuna entre o desenho e a implementação do processo. Também busca que linguagens de execução, como a BPEL-WS, possam ser visualizadas em uma notação orientada ao negócio.
* **Escopo:** A BPMN foi criada para representar **processos de negócio**. Não serve para representar estruturas e recursos organizacionais, repartições funcionais, modelos de dados e informação, estratégia ou regras de negócio.
* **Evolução:** O BPMI.org (hoje parte da OMG) desenvolveu a BPML e sentiu a necessidade de uma representação gráfica; a BPMN 1.0 foi liberada em maio de 2004 e adotada como padrão OMG em fevereiro de 2006. A **BPMN 2.0** acrescentou novos símbolos e regras, um metamodelo para intercâmbio de modelos, regras de conversão para BPEL e critérios de conformidade de ferramentas. O nome mudou de *Modeling Notation* para ***Model and Notation***, indicando que ela é mais do que uma notação.
* **Independência de ferramentas:** A BPMN não depende de sistema ou plataforma. Mais de 60 ferramentas a suportam, muitas gratuitas.
* **Níveis de Modelagem com BPMN:**
  * **Nível 1 — Descritiva:** mapeamento orientado ao negócio, com elementos básicos e omissão de alguns caminhos de exceção.
  * **Nível 2 — Analítica:** usa a notação completa para descrever com precisão o fluxo, incluindo exceções e eventos, sem detalhes técnicos como estrutura de dados e expressões; serve tanto para análise quanto para automação em BPMS.
  * **Nível 3 — Executável:** detalhes de execução capturados nos atributos padrão da BPMN, de modo que o sistema seja governado pelo modelo gráfico e não pelo código.
* **Níveis de complexidade da especificação:** Conjunto **principal** (o essencial para modelar diagramas simples, suficiente para a maioria dos usuários) e conjunto **estendido** (lista completa de elementos, muitos raramente usados).

#### 🔍 Tópico em Destaque

**As quatro categorias de elementos da BPMN**

| Categoria | Elementos | Função |
| --- | --- | --- |
| **Objetos de Fluxo** | Atividades, Eventos e *Gateways* | Definem o comportamento do processo |
| **Objetos de Conexão** | Fluxo de sequência, fluxo de mensagem e associação | Ligam os elementos entre si |
| **Partições (*Swimlanes*)** | Piscinas (*pools*) e raias (*lanes*) | Organizam participantes e responsáveis |
| **Artefatos** | Objeto de dados, grupo e anotação | Acrescentam informação sem alterar o fluxo |

**Objetos de fluxo**

* **Atividades:** Passos lógicos que consomem recursos (tempo e custo), representados por retângulos de cantos arredondados. Podem ser **tarefa** (atômica, o menor nível do processo) ou **subprocesso** (atividade composta, que pode aparecer retraído, com sinal de "+", ou expandido).
* **Eventos:** Algo que acontece ou pode acontecer e afeta o fluxo, com uma causa (gatilho) ou um impacto (resultado). Há eventos de **início**, **intermediários** (durante o processo: atrasos, envio/recebimento de mensagens, interrupções do fluxo normal) e de **fim**.
* ***Gateways*:** Losangos que controlam a divergência e a convergência do fluxo, usados em decisões, caminhos paralelos e pontos de sincronização. São quatro tipos, cada um com comportamento próprio:
  * **Exclusivo:** primeiro faz A, depois B *ou* C, conforme a condição.
  * **Inclusivo:** executa B e/ou C conforme as condições; se mais de uma for verdadeira, os ramos rodam em paralelo.
  * **Paralelo:** divide o fluxo em ramos simultâneos; o gateway que junta deve corresponder ao que dividiu.
  * **Complexo:** trata situações que os demais não cobrem (detalhado na Aula 06, junto com a variante do exclusivo baseada em eventos).

**Objetos de conexão**

* **Fluxo de sequência:** Mostra a ordem das atividades (B só ocorre após A) e conecta objetos de fluxo. **Nunca atravessa piscinas**; só liga elementos dentro da mesma piscina.
* **Fluxo de mensagem:** Representa troca de informação entre participantes (piscinas distintas). **Nunca ocorre dentro da mesma piscina** e nunca substitui um fluxo de sequência.
* **Associação:** Liga objetos de dados, anotações e outros artefatos aos objetos de fluxo; a seta indica se a atividade usa ou produz o dado.

**Piscinas e raias**

* **Piscina (*pool*):** Container dos objetos de fluxo de um participante. Cada piscina contém **um único processo**, e todo BPD tem ao menos uma (mesmo que implícita). Representa um participante (papel genérico como cliente ou fornecedor, ou uma entidade como a FedEx) em diagramas colaborativos (B2B). Pode aparecer vazia (caixa-preta) para um participante cujo processo interno não é conhecido; o fluxo de mensagem se conecta à borda.
* **Raia (*lane*):** Subdivisão dentro da piscina que indica quais papéis internos, sistemas ou departamentos executam cada atividade.

**Artefatos**

* **Objeto de dados:** Indica qual informação uma atividade precisa ou produz, sem afetar o fluxo; pode ser entrada, saída ou enviado de uma atividade para outra.
* **Grupo:** Retângulo de cantos arredondados com linha tracejada que agrupa atividades da mesma categoria, para documentação ou análise; não altera a sequência.
* **Anotação:** Retângulo aberto, de linha sólida, ligado por associação, que traz informação adicional ao leitor.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Boas práticas e referência normativa:**
>
> * Apresente as atividades na sequência em que ocorrem, evitando fluxos que voltam e se cruzam sem necessidade.
> * Use o **mesmo tipo de gateway** para dividir e juntar um fluxo paralelo.
> * Nunca use fluxo de sequência entre piscinas, nem fluxo de mensagem dentro da mesma piscina.
> * **Atualização 2026.2:** a versão normativa consultada é a **BPMN 2.0.2** (OMG, 2014), que substitui referências genéricas ao antigo portal bpmn.org. Diagramas de processo, colaboração e coreografia têm escopos semânticos distintos.

---

### 📚 Links & Leituras Complementares

* 📖 **OBJECT MANAGEMENT GROUP.** *Business Process Model and Notation, version 2.0.2* (2014). [omg.org/spec/BPMN](https://www.omg.org/spec/BPMN/)
* 📖 **DUMAS, M. et al. (2018).** *Fundamentals of Business Process Management*, 2ª edição, capítulo 3.
* 📖 **ACHARYA, V. (2014).** *Oracle BPM Suite 12c Modeling Patterns*, capítulo 1.
* 🔗 [BPMN Quick Guide](https://www.bpmnquickguide.com/view-bpmn-quick-guide/) — resumo visual dos elementos.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 04: Descoberta de Processos de Negócio (AS-IS)](../Aula_4/README.md)
* ➡️ **Próxima Aula:** [Aula 06: Modelagem de Processos de Negócio com BPMN — Habilidades](../Aula_6/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
