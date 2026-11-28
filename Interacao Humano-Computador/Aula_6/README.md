# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 10/09/2026 | 📚 Professora: Daniela Gorski Trevisan | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 06: Personas, Cenários & Análise de Tarefas

### 📝 Introdução

Esta aula tratou da **organização do espaço do problema**, isto é, das representações que ajudam a registrar o conhecimento obtido dos usuários na análise da situação atual. Na primeira parte, foram vistos o **perfil de usuário**, as **personas** e os **cenários de problema**. Na segunda, a **análise de tarefas**, com três métodos: **HTA**, **GOMS** (com a técnica **KLM**) e **CTT**. O conteúdo se baseia em Barbosa e Silva (2010), capítulo 6.

---

### 💡 Conceitos Chave

#### Parte 1: Perfil de Usuário, Personas e Cenários

* **Modelo simples de design em IHC:** ciclo que parte de *identificar necessidades e definir requisitos*, passa por *(re)design* e *construir uma versão interativa*, e volta por *avaliar*, até chegar ao produto final. Os dados para a primeira etapa vêm da análise da situação atual (dados a coletar, de quem coletar, aspectos éticos e técnicas de coleta, vistos na Aula 4).
* **Perfil de usuário:** descrição detalhada das características dos usuários. Os principais métodos de coleta são entrevista e questionário. Exemplos de características: cargo, função, experiência, nível de instrução, atividade principal, faixa etária. Os usuários devem ser categorizados em grupos.
* **Personas:** descrição detalhada de usuários típicos. Não são pessoas reais, e sim uma **síntese de características de usuários reais**. Não devem ser idealizadas e devem ter "vida", isto é, rigor de detalhe na descrição. São arquétipos que representam necessidades de grupos de usuários (objetivos, características pessoais, motivações e expectativas) e motivam seu comportamento na aplicação.
  * **Exemplo do slide:** Paulo Correa, 43 anos, técnico de suporte de uma universidade, que prefere aprender fazendo, usa linguagem de comando em vez de assistentes gráficos e precisa acessar o sistema remotamente para atender os professores com eficiência.
* **Elementos característicos de uma persona:**

| Elemento | O que descreve |
| --- | --- |
| **Identidade** | Nome, sobrenome, idade, foto ou caricatura |
| **Status** | Primária, secundária, *stakeholder* ou antiusuário |
| **Objetivos** | Não se limitam aos objetivos relacionados ao produto |
| **Habilidades** | Educação, treinamento, competências |
| **Tarefas** | Básicas ou críticas, em linhas gerais |
| **Relacionamentos** | Como se conecta a outras personas |
| **Requisitos** | O de que a persona precisa |
| **Expectativas** | Como acredita que o produto funciona |

* **Por que usar personas:** permitem que os designers se coloquem no lugar dos usuários; focam o esforço de design e evitam que cada integrante da equipe tenha uma visão diferente de quem é o usuário (um usuário real como representante de um grupo pode introduzir desvio nas necessidades); sem definição precisa, o usuário vira um alvo móvel, hora novato, hora especialista.
* **Influência das personas no design:** priorizam esforços de design (projetar para uma única persona aumenta as chances de agradar todo um grupo de usuários), ajudam a resolver discordâncias e permitem avaliar alternativas continuamente, reduzindo a frequência de testes de usabilidade mais caros.
* **Cenário de problema:** história sobre pessoas realizando uma atividade. Deve ser concreto, rico em detalhes contextuais e descrever situações de uso. Pode ou não ser usado com personas.
  * **Exemplo do slide:** cadastro de projetos finais com coorientador externo não cadastrado, com os atores Joana Marinho (secretária) e Fernando Couto (aluno).
* **Elementos característicos de um cenário:** ambiente ou contexto, atores, objetivos, planejamento (mental), ações (comportamento observável), eventos (ações externas ou reações do computador) e avaliação (mental).
* **Por que usar cenários:** destacam objetivos sugeridos pela aparência e pelo comportamento do sistema; quando algo não está bem descrito, surgem perguntas "e se" cujas respostas completam o cenário e geram novas proposições; permitem obter *feedback* do usuário sem o custo de um protótipo funcional.
* **Pontos problemáticos do cenário de exemplo:** necessidade de transição dos dados preenchidos em formulário impresso para o sistema; falta de integração do sistema com as informações dos alunos; incapacidade de enviar mensagem pelo sistema às pessoas envolvidas.
* **Questões para refinar cenários:**

| Tipo | Questão | Conteúdo da resposta |
| --- | --- | --- |
| **Exploratória** | **Por que...?** | Condição para realizar a atividade, consequência da atividade, estados e eventos anteriores ou posteriores |
| **Exploratória** | **Como...?** | Detalhes da sequência de ações que compõem a atividade; pode revelar objetivos que não constavam do cenário original |
| **Exploratória** | **O que é...?** | Objetos e seus atributos, organizados em hierarquia ou outro modelo de dados |
| **Verificação** | **<X> pode ser feito da maneira <Y>?** | Resposta sim ou não; avalia se uma ação ou atributo está bem definido e no nível certo da hierarquia |
| **Verificação** | **<X> faz parte de <Y>?** | O mesmo da questão anterior |

#### Parte 2: Análise de Tarefas

* **Análise de tarefas:** usada para entender qual é o trabalho dos usuários, como e por que o realizam. Três situações habituais de uso: análise da situação atual, (re)design de um sistema computacional e avaliação do resultado de uma intervenção que inclua a introdução de um sistema.
* **Métodos:** **HTA** (*Hierarchical Task Analysis*), **GOMS** (*Goals, Operators, Methods and Selection Rules*) e **CTT** (*ConcurTaskTrees*).

| Método | Ideia central | Foco |
| --- | --- | --- |
| **HTA** | Quebrar uma tarefa em subtarefas, e estas em sub-subtarefas, agrupando as partes em **planos** que dizem como as tarefas são executadas | Ações físicas e observáveis, incluindo ações não relacionadas ao software; parte de um objetivo do usuário |
| **GOMS** | Descrever **objetivos**, **operadores**, **métodos** e **regras de seleção** | Processos cognitivos e ações do usuário; a técnica KLM permite prever tempo |
| **CTT** | Modelo de tarefas hierárquico com quatro tipos de tarefa e operadores temporais entre elas | Relações temporais e de interação entre tarefas |

* **HTA, exemplo:** objetivo "pegar emprestado um livro da biblioteca", com as tarefas 1 (ir até a biblioteca), 2 (encontrar o livro, com subtarefas 2.1 a 2.5), 3 (ir até a estante certa e pegar o livro) e 4 (levar o livro ao balcão de empréstimos). **Plano 0:** fazer 1-3-4; se o livro não estiver na prateleira, esperar e fazer 2-3-4. **Plano 2:** fazer 2.1-2.4-2.5; se o livro não for identificado, fazer 2.2-2.3-2.4.
* **Modelo hierárquico de tarefas (notação adaptada):** os slides mostram relações **sequencial**, **independente de ordem**, **alternativa**, além de tarefa **opcional**, **iterativa** e **ubíqua**.
* **GOMS:**
  * **Goals (objetivos):** o que o usuário quer fazer, como no HTA.
  * **Operators (operadores):** processos cognitivos ou ações do usuário para atingir o objetivo.
  * **Methods (métodos):** procedimentos para realizar as tarefas (sequência de operadores).
  * **Selection Rules (regras de seleção):** decidem qual método usar, se houver mais de um.
  * **Exemplo:** objetivo de deletar uma palavra em uma frase. Método 1, pelo menu (marcar a palavra, lembrar que o comando é Recortar e que está no menu Editar). Método 2, pela tecla Delete (posicionar o cursor e apagar letra por letra). Regra 1: usar mouse e menu para grande quantidade de texto. Regra 2: usar a tecla Delete para poucas letras.
* **CTT:** considera quatro tipos de tarefa e oito operadores.

| Tipo de tarefa | Descrição |
| --- | --- |
| **Do usuário** | Realizada fora do sistema |
| **Do sistema** | O sistema realiza um procedimento sem interagir com o usuário |
| **Interativa** | Ocorre diálogo entre usuário e sistema |
| **Abstrata** | Não é uma tarefa em si, e sim a preparação de uma composição de tarefas que auxilia a decomposição |

* **Leitura de uma árvore CTT:** para considerar T1 como realizada, as tarefas T2 e T3 (suas subtarefas) devem ter sido realizadas.

| Operador do CTT | Significado |
| --- | --- |
| **Ativação** | T2 só pode iniciar após T1 terminar |
| **Ativação com passagem de informação** | T2 só pode iniciar após T1 terminar, e a informação produzida por T1 é passada para T2 |
| **Concorrência e comunicação** | T1 e T2 podem ser realizadas em qualquer ordem ou ao mesmo tempo, e podem trocar informações |
| **Concorrência** | T1 e T2 podem ser realizadas em qualquer ordem ou ao mesmo tempo |
| **Escolha** | T1 e T2 estão habilitadas ao mesmo tempo, mas, quando uma é iniciada, a outra é desabilitada |
| **Independência** | T1 e T2 podem ser realizadas em qualquer ordem, mas, quando uma é iniciada, precisa terminar para que a outra possa ser iniciada |
| **Desativação** | T1 é completamente interrompida por T2 |
| **Suspensão/retomada** | T1 pode ser interrompida por T2 e é retomada do ponto em que parou assim que T2 terminar |

* **Exemplo de CTT:** modelo da tarefa "marcar compromisso em agenda", com operadores de ativação, ativação com passagem de informação e concorrência.

#### 🔍 Tópico em Destaque

**KLM-GOMS: prevendo o tempo de uma tarefa**

A **KLM** é a técnica mais simples de GOMS e serve para **prever o tempo gasto por um especialista** para realizar uma tarefa, descrevendo-a por operadores.

| Operador | Significado | Tempo |
| --- | --- | --- |
| **K** | Apertar uma tecla | 0,08 s a 1,20 s |
| **B** | Clicar um botão do mouse | 0,10 s (ver Pontos de Atenção) |
| **P** | Mover o mouse até uma posição alvo | 1,10 s |
| **H** | Trocar de dispositivo de entrada | 0,40 s |
| **M** | Preparar-se mentalmente para uma ação | 1,20 s |
| **T(n)** | Digitar uma cadeia de *n* caracteres | n × K |
| **W(t)** | Esperar a resposta do sistema | Depende do sistema |

**Exemplo do slide: salvar arquivo**

| Método | Operadores | Total |
| --- | --- | --- |
| **Menu Arquivo > Salvar** | M + H + P + B + B + P + B + B = 1,20 + 0,40 + 1,10 + 0,20 + 0,20 + 1,10 + 0,20 + 0,20 | **4,60 s** |
| **Botão Salvar na barra de ferramentas** | M + H + P + B + B = 1,20 + 0,40 + 1,10 + 0,20 + 0,20 | **3,10 s** |
| **Tecla de atalho Ctrl+S** (digitador mediano) | M + K + K = 1,20 + 0,20 + 0,20 | **1,60 s** |

Conclusão do slide: o atalho é quase duas vezes mais eficiente que o botão da barra de ferramentas (3,10 ÷ 1,60 ≈ 1,9) e quase três vezes mais eficiente que o item de menu (4,60 ÷ 1,60 ≈ 2,9).

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Inconsistência no valor de B (KLM):** o slide define B (clicar um botão do mouse) como 0,10 s, mas as tabelas do exemplo usam 0,20 s para cada B (pressionar e soltar o botão). Os totais de 4,60 s, 3,10 s e 1,60 s fecham com 0,20 s por B, e foram mantidos como estão nos slides. Com 0,10 s por B, os totais do menu e do botão seriam 4,20 s e 2,90 s. Vale confirmar com a professora qual valor adotar em exercícios.
>
> 💡 **Perguntas do cenário sem marcação:** o slide traz 14 perguntas exploradas no cenário de projetos finais e marca o texto com os números, mas as perguntas 4 (quais dados cadastrar), 10 (de que informações os responsáveis precisam) e 11 (como um envolvido confirma o cadastro) não aparecem marcadas no texto.
>
> 💡 **Persona não é o usuário real:** persona é síntese de características de usuários reais, não um usuário específico, e não deve ser idealizada. Usar um usuário real como representante de um grupo pode introduzir desvio nas necessidades.
>
> 💡 **Erros de grafia nos slides:** "Selecion Rules" (o correto é *Selection Rules*), "fraase" (frase) e "cadeira de n caracteres" (cadeia de n caracteres).
>
> 💡 **Numeração interna dos slides:** os slides trazem referências a outros números de aula ("Aula 7", "Aula 8", "Aula 5"), herdadas de outra numeração do curso, e os títulos "Aula 9" e "Aula 10" não correspondem à numeração desta pasta.
>
> 💡 **Atividades propostas nos slides:** a Atividade 5 pede um questionário de levantamento de perfil de usuário e uma persona para o sistema especificado pela professora. A Atividade 6 pede a análise de tarefas do cenário e das personas, com pelo menos 3 tarefas de nível 1, cada uma gerando ao menos 2 de nível 2, e cada uma destas ao menos 1 de nível 3, comparando um usuário experiente e um inexperiente.

---

### 📚 Links & Leituras Complementares

* 📖 **BARBOSA, S. D. J.; SILVA, B. S. (2010).** *Interação Humano-Computador*. Editora Campus-Elsevier. Capítulo 6. Os exemplos de persona, cenário, árvore HTA e figuras do CTT são adaptados desse livro.
* 📖 Slides elaborados a partir do material do Prof. Leandro Fernandes (UFF).

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 05: Teorias de IHC: Engenharia Semiótica & Engenharia Cognitiva](../Aula_5/README.md)
* ➡️ **Próxima Aula:** [Aula 07: Princípios de Design & Introdução à Avaliação de IHC](../Aula_7/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
