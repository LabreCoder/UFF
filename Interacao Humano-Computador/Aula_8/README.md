# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 24/09/2026 | 📚 Professora: Daniela Gorski Trevisan | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 08: Avaliação Heurística & Percurso Cognitivo

### 📝 Introdução

Esta aula apresentou os **métodos de avaliação de IHC** e aprofundou os dois métodos de **avaliação por inspeção**, que não envolvem usuários e são conduzidos por especialistas: a **avaliação heurística**, o método mais utilizado, baseada nas 10 heurísticas de Nielsen, e o **percurso cognitivo**, baseado na Engenharia Cognitiva e voltado à facilidade de aprendizado. O conteúdo se baseia em Barbosa e Silva (2010), capítulo 10.

---

### 💡 Conceitos Chave

#### Parte 1: Introdução aos Métodos de Avaliação de IHC

* **Avaliação em IHC:** julga a qualidade de interação de um sistema ou artefato computacional. Seus objetivos são os já vistos na Aula 7 (verificar o entendimento dos projetistas, investigar como a interface afeta a forma de trabalho, comparar alternativas, identificar problemas, verificar conformidade com padrão ou heurísticas e elaborar material de apoio e treinamento).
* **Duas abordagens:**

| Abordagem | Usuários | Como funciona | Métodos que serão abordados |
| --- | --- | --- | --- |
| **Avaliação por inspeção** (inspeção de interface) | Não envolve | Um especialista "advoga" pelos usuários, com base em conhecimento prático e/ou teórico, e tenta antever as consequências de decisões de design. Em produtos, inspeciona as características do artefato; em processos, as condições de uso | **Avaliação heurística** (método mais utilizado) e **percurso cognitivo** (baseado em Engenharia Cognitiva) |
| **Avaliação por observação** (teste de interface) | Envolve (observá-los, entrevistá-los), com ou sem apoio de tecnologia | Coleta dados de situações em que os participantes realizam suas atividades, em laboratório ou em campo. Identifica problemas reais, e não só os potencialmente previstos | **Teste de usabilidade** (experiência de uso dos usuários-alvo), **avaliação de comunicabilidade (MAC)** (qualidade da comunicação da metamensagem do designer) e **prototipação em papel** (simulação de uso de um design em papel) |

#### Parte 2: Avaliação Heurística

* **O que é:** método de inspeção, sem usuários, realizado por um especialista, baseado em conhecimento prático (princípios gerais de bom design de interfaces) e que ajuda a encontrar problemas de usabilidade. Foi proposto por **Jakob Nielsen e Rolf Molich em 1990**. O avaliador identifica situações em que uma ou mais das 10 heurísticas são violadas (as heurísticas e seus exemplos estão na Aula 7).
* **Vantagens:** é **rápida** (um dia ou menos, enquanto testes de usabilidade padrão podem levar semanas), **barata** (sem laboratório ou equipamento) e **fácil de usar** (pode ser ensinada em duas horas ou menos).

#### 🔍 Tópico em Destaque

**Quantos avaliadores e com que experiência**

Recomenda-se envolver de **3 a 5 avaliadores**. Um só avaliador pode fazer a avaliação, mas identificará apenas **35%** dos problemas, e cada avaliador identifica problemas diferentes. O número exato depende de uma análise de custo-benefício: na situação normal, 3 a 5 avaliadores (cerca de 75%); em situações críticas, muitos avaliadores.

| Perfil do avaliador | Problemas identificados |
| --- | --- |
| **Noviços** (apenas conhecimentos de computadores, sem perícia em usabilidade) | 22% |
| **Peritos em usabilidade** (não no tipo de interface) | 41% |
| **Peritos em usabilidade e no tipo de interface** | 60% |

* **Atividades da avaliação heurística:**

| Atividade | O que se faz |
| --- | --- |
| **1. Preparação** | Todos os avaliadores aprendem sobre a situação atual e selecionam as partes da interface a avaliar |
| **2. Coleta de dados** | Cada avaliador inspeciona a interface para identificar violações das heurísticas, indicando local, gravidade, justificativa e recomendações de solução. Duração de 1 a 2 horas |
| **3. Interpretação** | Análise do local e da severidade de cada problema |
| **4. Consolidação dos resultados** | Todos os avaliadores revisam os problemas encontrados, julgam suas interpretações e geram um relatório consolidado |
| **5. Relato dos resultados** | Não detalhado nos slides |

* **Local do problema:** em um único local, em dois ou mais locais, na estrutura geral da interface, ou "não está lá" (precisa ser incluído).
* **Severidade ou gravidade do problema:**

| Critério | Escala |
| --- | --- |
| **Frequência** | 1) comum, 2) raro |
| **Impacto** | 1) fácil superação, 2) difícil superação |
| **Persistência** | 1) uma vez e é superado, 2) atrapalhará muitas vezes |
| **Severidade** | 1) cosmético, 2) pequeno, 3) grande, 4) catastrófico |

#### Parte 3: Percurso Cognitivo

* **O que é:** método de inspeção, sem usuários, realizado por um especialista. É motivado pela preferência em **"aprender fazendo"**: muitos usuários não leem manuais nem assistem a tutoriais antes, e em um sistema novo costumam usá-lo de forma exploratória.
* **Base teórica:**
  * Dos aspectos de usabilidade (facilidade de aprendizado, facilidade de recordação, eficiência, segurança no uso e satisfação do usuário), o percurso cognitivo foca **apenas na facilidade de aprendizado**.
  * Da **Engenharia Cognitiva**: conhecendo as estratégias de aprendizado por ensaio e erro, é possível projetar para maximizar os bons ensaios e minimizar os erros no caminho entre o ponto de partida (o usuário não conhece o sistema) e o ponto de chegada (o usuário aprendeu a usá-lo).
  * Considera a correspondência entre o **modelo conceitual dos usuários** e a **imagem do sistema** (conceitualização das tarefas, resposta do sistema a cada ação e vocabulário utilizado).
* **Na prática:** a inspeção é guiada pelas **tarefas do usuário**. O avaliador se coloca no papel do usuário e detalha como seria a interação. Para cada estado interativo, do início ao fim de cada tarefa, constrói uma narrativa e justifica por que o próximo caminho produtivo seria a escolha preferencial do usuário. Em um bom projeto, a própria interface guia os usuários pela sequência de ações esperadas. Os avaliadores precisam conhecer o perfil completo dos usuários, uma representação completa das interações oferecidas pelo sistema (executável ou não) e as tarefas da avaliação. Havendo problemas, o método levanta hipóteses sobre as causas e os avaliadores sugerem reprojeto.
* **Atividades do percurso cognitivo** (um ou mais avaliadores, em conjunto):

| Atividade | O que se faz |
| --- | --- |
| **1. Preparação** | Identificar perfis de usuários, definir as tarefas a avaliar e descrever as ações necessárias para cada tarefa |
| **2. Coleta de dados** | Para cada tarefa, percorrer a interface na sequência de ações |
| **3. Interpretação** | Para cada ação, analisar como o usuário a executaria, respondendo e justificando as **4 perguntas-chave**, e relatar uma história aceitável de sucesso ou insucesso |
| **4. Consolidação dos resultados** | Apontar o que os usuários precisam saber a priori e o que devem aprender durante a tarefa, e sugerir correções |
| **5. Relato dos resultados** | Consolidar um relato formal, completo e bem explicado |

* **As 4 perguntas-chave e as correções sugeridas em caso de insucesso:**

| # | Pergunta a cada ação | O usuário tem mais chance de acertar se... | Correções sugeridas |
| --- | --- | --- | --- |
| **1** | O usuário **tentaria atingir o efeito correto** (a formulação da interação seria a esperada pelo designer)? | Tem experiência com o sistema ou semelhantes; o sistema fornece uma instrução ou pede a ação | Eliminar a ação (combinando-a com outras ou deixando o sistema executá-la); fornecer instrução ou indicação; modificar parte da tarefa para que se entenda a necessidade da ação |
| **2** | O usuário **perceberia que a ação correta está disponível**? | Tem experiência; percebe na interface uma representação da ação desejada | Tornar a ação mais evidente (item de menu, botão, teclas de atalho explícitas) |
| **3** | O usuário **conseguiria associar a ação correta ao efeito** que quer atingir? | Tem experiência; a interface comunica a associação; nenhuma outra ação parece adequada (por eliminação) | Renomear ações e reescrever instruções com vocabulário mais familiar |
| **4** | Realizada a ação correta, o usuário **perceberia que está progredindo** para concluir a tarefa? | Tem experiência; as respostas do sistema estão de acordo com o efeito esperado | Destacar ou expressar mais claramente o *feedback*; deixar claro o que ocorreu e o que fazer em seguida |

* **Exemplo do slide:** tarefa "comprar o livro de IHC na Amazon.com", para estudantes que usam a web regularmente. No passo 1 (selecionar a categoria de produtos na página inicial), os usuários sabem que devem encontrar livros, sabem como fazê-lo por já terem usado menus e entendem pelo *feedback* que acertaram, pois são levados a um formulário de busca. No passo 2 (completar o formulário), sabem o que fazer porque o formulário se parece com um de papel, e o espaço de digitação e o botão de busca são claros, mas podem não perceber que o formulário tem valores padrão para prevenir respostas impróprias. O *feedback* é uma página com foto, descrição e detalhes da compra.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Exemplo do percurso cognitivo usa 3 perguntas, não 4:** o método é definido com 4 perguntas-chave, mas o exemplo da Amazon responde a três ("saberão o que fazer?", "saberão como fazê-lo?" e "entenderão pelo *feedback* se a ação estava correta?"), sem a pergunta sobre perceber que a ação está disponível. Ao resolver exercícios, siga as 4 perguntas definidas nos slides.
>
> 💡 **Resposta contraditória no exemplo (passo 2):** para "os usuários saberão o que fazer?", o slide traz duas respostas, "Sim" (o formulário on-line se parece com o de papel) e "Não" (podem não perceber os valores padrão). Elas se referem a aspectos diferentes do formulário, e o slide não consolida um resultado.
>
> 💡 **Inspeção × observação:** a avaliação por inspeção prevê problemas **potenciais** com especialistas. Já a observação, com usuários, identifica problemas **reais**. Os métodos de observação (teste de usabilidade, MAC e prototipação em papel) são tratados nas próximas aulas.
>
> 💡 **Os percentuais da avaliação heurística:** 35% (um avaliador), 75% (3 a 5 avaliadores) e 22%, 41% e 60% (por perfil) são os números exatos dos slides. A fonte dos dados não é citada nos slides.
>
> 💡 **Erros de grafia nos slides:** o exemplo do percurso cognitivo traz "formulario", "faze-lo", "completa-lo", "açao", "previnir", "imprórpias", "apresnetados". Também "devem realizam as atividades em conjunto" no lugar de "realizem". Vale ignorar esses erros ao estudar.
>
> 💡 **Numeração e nomes antigos:** o deck de percurso cognitivo se intitula "Aula 20" e mantém o rodapé "TCC-00.184 Interface Homem/Máquina (2011.2)". A Aula 8 aqui reúne a avaliação heurística (primeira parte) e o percurso cognitivo.

---

### 📚 Links & Leituras Complementares

* 📖 **BARBOSA, S. D. J.; SILVA, B. S. (2010).** *Interação Humano-Computador*. Editora Campus-Elsevier. Capítulo 10.
* 🔗 [Jakob Nielsen e Rolf Molich: material sobre avaliação heurística](http://www.useit.com/papers/heuristic/), endereço citado nos slides (não verificado).
* 📖 Slides elaborados a partir do material do Prof. Leandro Augusto Frata Fernandes (UFF).

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 07: Princípios de Design & Introdução à Avaliação de IHC](../Aula_7/README.md)
* ➡️ **Próxima Aula:** [Aula 09: Teste de Usabilidade & First Click](../Aula_9/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
