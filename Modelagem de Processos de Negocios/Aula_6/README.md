# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 18/09/2026 | 📚 Professor: Flávio Seixas | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 06: Modelagem de Processos de Negócio com BPMN — Habilidades

### 📝 Introdução

Continuação da aula anterior, com foco em **aplicar** a BPMN. A aula percorreu os três tipos de processo que um diagrama pode representar (privado, abstrato e colaborativo), aprofundou atividades e subprocessos, o conceito de **instâncias e tokens**, as regras para eventos de início, intermediários e de fim, e o comportamento de cada tipo de *gateway* na divergência e na convergência do fluxo. Encerrou com um checklist de consistência e o exercício "jogo dos 7 erros".

---

### 💡 Conceitos Chave

* **Tipos de modelo de processo na BPMN:**
  * **Privado (interno):** ocorre dentro da organização, em uma única piscina, com todas as atividades executadas internamente.
  * **Abstrato (público):** mostra a interação entre um processo privado e outro participante. Inclui apenas as atividades de comunicação com o exterior (mais o controle de fluxo apropriado); o participante é uma piscina vazia.
  * **Colaborativo (global ou B2B):** retrata a interação entre duas ou mais entidades de negócio, com processos abstratos se comunicando; só os **pontos de contato** são mostrados.
* **Instâncias e Tokens:** Cada vez que um processo inicia, nasce uma nova **instância**. Para ler um BPD, imagina-se um **token** que percorre os fluxos de sequência: o evento de início o gera e o evento de fim o consome. O processo segue em execução até que todos os tokens sejam consumidos.
* **Atividades:**
  * **Tarefa:** atividade atômica, o nível mais detalhado do processo.
  * **Subprocesso:** atividade composta, que pode ser expandida ou contraída e permite modelagem **hierárquica**, mantendo a visão global limpa e detalhando só quando necessário. Também serve para criar caixas paralelas e subprocessos *ad hoc*.
  * **Incorporado (*embedded*):** depende do processo-pai e não pode conter piscinas e raias.
  * **Reutilizável (*reusable*):** chama outro processo existente no BPD, é usado em vários contextos e pode conter múltiplas piscinas.

#### 🔍 Tópico em Destaque

**Eventos: regras e tipos**

**Eventos de início**

* São opcionais em qualquer nível, mas, se existir início, deve existir fim (e vice-versa).
* Com evento de início, nenhum outro objeto de fluxo pode ficar sem fluxo de sequência de entrada. Sem ele, todo objeto sem entrada é instanciado junto com o processo.
* Os gatilhos (*triggers*) mais comuns são **mensagem** (boa prática: mostrar o participante externo que a envia com uma piscina vazia) e **tempo** (boa prática: descrever a data ou o ciclo abaixo do evento).
* Um processo pode ter **mais de um evento de início**, quando segue caminhos diferentes conforme a forma como é iniciado (ex.: correção de provas iniciada por e-mail ou pela web).

**Eventos de fim**

* Indicam onde um caminho do processo ou subprocesso termina; **não aceitam fluxo de saída**.
* Diferente do início, pode haver **vários eventos de fim**, um para cada estado final distinto. O evento de fim por mensagem indica o participante que recebe o resultado (confirmação, rejeição etc.).
* No subprocesso, o fim vazio devolve o fluxo ao processo-pai.
* O **evento de fim Término** interrompe imediatamente todas as atividades em execução.

**Eventos intermediários**

* Acontecem entre o início e o fim, afetam o fluxo, mas não iniciam nem terminam o processo. Podem **lançar** (*throw*) ou **capturar** (*catch*) um evento.
* **Mensagem:** ícone **não preenchido** indica que o processo espera uma mensagem; ícone **preenchido** indica que ela é enviada imediatamente e o fluxo segue sem atraso. Usa-se evento quando só se quer representar o envio/recebimento; usa-se tarefa quando há trabalho associado ao passo.
* **Tempo:** no fluxo de sequência, representa um **atraso** (uma duração, ou uma hora/data específica). Anexado à borda de uma atividade, trata **time-out**: se o tempo estourar, a atividade é interrompida e o fluxo segue pelo caminho de exceção. Exemplo da aula: atraso de 1 hora entre A e B e *time-out* de 3 horas em B — se estourar, executa C; se não, executa D.

**Gateways: comportamento na divergência e na convergência**

| Gateway | Divergência | Convergência |
| --- | --- | --- |
| **Exclusivo baseado em dados (XOR)** | Escolhe **um único** caminho, o da condição verdadeira | Não precisa de gateway para juntar, pois só um ramo é percorrido |
| **Exclusivo baseado em eventos** | Escolhe o caminho conforme o **evento que ocorrer primeiro** | Igual ao exclusivo por dados |
| **Inclusivo (OR)** | Avalia todas as condições; **uma ou mais** podem ser verdadeiras (ao menos um caminho deve ser possível) | **Sincroniza** todos os tokens produzidos |
| **Paralelo (AND)** | Cria fluxos paralelos, todos executados | **Sincroniza** os ramos paralelos |
| **Complexo** | A regra de quais caminhos seguir fica **dentro do gateway**, não nas condições dos fluxos | Pode atuar como fusão (ex.: deixa passar só um token dos caminhos paralelos) |

* O gateway inclusivo pode ser substituído por **fluxos de sequência condicionais** (mini-losango), e um **fluxo padrão** evita que nenhuma alternativa seja verdadeira.
* O gateway paralelo não é obrigatório para criar paralelismo, mas deixa o paralelo explícito, por isso é boa prática usá-lo.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Checklist de consistência BPMN (atualização 2026.2):**
>
> * O fluxo de sequência permanece dentro de um processo/piscina; a comunicação entre participantes usa **fluxo de mensagem**.
> * Os gateways devem refletir a **semântica real** da decisão ou sincronização, e não apenas melhorar a aparência.
> * Eventos precisam ter posição, tipo e marcador compatíveis com início, intermediário ou fim.
> * Subprocessos, exceções e repetição devem preservar o comportamento dos tokens.
> * Todo diagrama deve ter início, resultados e responsabilidades compreensíveis para o público-alvo.
>
> 🎯 A aula terminou com o **"Jogo dos 7 erros"**: encontrar e corrigir erros de modelagem em um diagrama, aplicando as regras acima.

---

### 📚 Links & Leituras Complementares

* 📖 **OBJECT MANAGEMENT GROUP.** *Business Process Model and Notation, version 2.0.2* (2014). [omg.org/spec/BPMN](https://www.omg.org/spec/BPMN/)
* 📖 **DUMAS, M. et al. (2018).** *Fundamentals of Business Process Management*, 2ª edição, capítulo 4.
* 📖 **ACHARYA, V. (2014).** *Oracle BPM Suite 12c Modeling Patterns*. Packt.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 05: Modelagem de Processos de Negócio com BPMN — Conceitos](../Aula_5/README.md)
* ➡️ **Próxima Aula:** [Aula 07: Análise Qualitativa de Processos](../Aula_7/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
