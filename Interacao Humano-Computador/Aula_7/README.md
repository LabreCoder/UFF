# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 17/09/2026 | 📚 Professora: Daniela Gorski Trevisan | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 07: Princípios de Design & Introdução à Avaliação de IHC

### 📝 Introdução

Esta aula fez a passagem do design para a avaliação. Primeiro, foram apresentados os **princípios e diretrizes de design** que ajudam um projeto de IHC por apontarem soluções boas e conhecidas para problemas comuns: os 6 princípios de Don Norman, as 8 regras de ouro de Ben Shneiderman e as 10 heurísticas de Nielsen, cada heurística com exemplos de violação e de conformidade. Depois, a **introdução à avaliação de IHC** (Barbosa e Silva, 2010, capítulo 9): o que é, o que e quando avaliar, os paradigmas e técnicas de avaliação e o guia DECIDE para planejar uma avaliação.

---

### 💡 Conceitos Chave

#### Parte 1: Princípios de Design

* **Princípios × diretrizes (*guidelines*):**

| | Princípios | Diretrizes |
| --- | --- | --- |
| **Natureza** | Genéricos | Específicas |
| **Vantagem** | Aplicáveis a uma ampla gama de problemas | Mais concretas, aplicáveis a um problema específico |
| **Limitação** | Não oferecem soluções diretas e podem ser conflitantes entre si (por exemplo, as heurísticas de Nielsen, 1994) | É preciso saber se o problema "se encaixa" na diretriz |

* **6 princípios de design de Don Norman:**

| Princípio | Definição |
| --- | --- |
| **Visibilidade** | Quanto mais visíveis as funções do artefato, mais fácil para os usuários saberem o que fazer |
| **Feedback** | Toda ação do usuário deve ser sinalizada por algum retorno, na forma, na medida e na hora certa |
| **Restrições** | O espaço de ações do usuário deve ser limitado por restrições claras e efetivas. **Físicas** (inibição física, como botão desabilitado), **lógicas** (expectativas consistentes sobre as consequências de uma ação) e **culturais** (elementos de interface que desincentivem ou valorem negativamente a ação restringida) |
| **Mapeamento** | Correspondência entre os controles do artefato e seus efeitos no mundo |
| **Consistência** | Usar controles e ações semelhantes para sinalizar a possibilidade de efeitos semelhantes |
| **Affordance** | Fazer os elementos de interface "anteciparem" a forma de interação (botões têm a *affordance* de apertar, menus de abrir, janelas de minimizar, maximizar ou fechar) |

* **8 regras de ouro de Ben Shneiderman:**
  1. Batalhe pela consistência.
  2. Ofereça atalhos para usuários frequentes.
  3. Dê *feedback* informativo.
  4. Dê um fechamento claro aos diálogos com o sistema.
  5. Ofereça técnicas simples de tratamento de erro.
  6. Facilite a reversão de ações erradas.
  7. Dê (sensação de) controle ao usuário.
  8. Reduza a quantidade de coisas que as pessoas têm de guardar na memória durante a interação.

#### 🔍 Tópico em Destaque

**As 10 heurísticas de Nielsen**

| # | Heurística | O que pede | Exemplo nos slides |
| --- | --- | --- | --- |
| **1** | **Visibilidade do estado do sistema** | Manter os usuários informados sobre o que está acontecendo, em tempo real | Exemplos de conformidade |
| **2** | **Correspondência entre o sistema e o mundo real** | Usar palavras, expressões e conceitos familiares ao usuário | Violação: o CSE HTML Validator v3.05 verifica erros de sintaxe em HTML sem deixar claro o que cada *flag* significa |
| **3** | **Controle e liberdade do usuário** | Fornecer alternativas para o usuário sair de uma situação indesejada | Conformidade: busca fácil de abrir, preencher, executar ou cancelar; indica onde a pessoa está e para onde pode ir |
| **4** | **Consistência e padronização** | Seguir as convenções da plataforma ou do ambiente computacional | Violação: a cor dos textos estáticos, botões ou painel foge do padrão do ambiente |
| **5** | **Reconhecimento em vez de memorização** | Apresentar claramente objetos, ações e opções, sem exigir que o usuário "decore" formas de acionamento | Violação: a ordenação da lista está escondida no menu "Table" |
| **6** | **Flexibilidade e eficiência de uso** | Permitir que as ações sejam acionadas de diferentes formas | Violação: uso excessivo de abas e categorias acessadas apenas com o mouse |
| **7** | **Projeto estético e minimalista** | Não incluir informação irrelevante ou raramente necessária; manter a interface "clean" | O slide destaca que mais de uma heurística pode ser violada na mesma situação |
| **8** | **Prevenção de erros** | Evitar, sempre que possível, que enganos e erros ocorram | Violação: aparece "Desfazer Excluir" quando a última ação foi criar uma pasta |
| **9** | **Ajude os usuários a reconhecerem, diagnosticarem e se recuperarem de erros** | Mensagens de erro claras e informativas, que ajudem a entender o que houve e a reparar | Exemplos de violação e de conformidade |
| **10** | **Ajuda e documentação** | Acesso rápido e claro a conteúdo informativo, focado na tarefa do usuário | Conformidade: *showcase features* podem servir como tutoriais |

#### Parte 2: Introdução à Avaliação de IHC

* **Etapas fundamentais do design:** análise da situação atual (estudar e interpretar a situação atual), síntese de uma intervenção (planejar e executar uma intervenção) e avaliação da nova situação (verificar o efeito da intervenção, comparando a situação anterior com a nova).
* **O que é avaliação de IHC:** atividade profissional especializada, **não é uma emissão de opinião** nem se baseia em preferências ou conjecturas. Seu objetivo é **julgar a qualidade de interação** de um sistema ou artefato. Usuários sempre têm opiniões e julgamentos, mas isso não é uma avaliação de IHC.
* **Conhecimentos requeridos:** conceitos de IHC, métodos de avaliação, modos e meios de aplicar conceitos e métodos, disciplina e rigor na coleta de dados e cuidados éticos.
* **Importância:** o sistema sempre será avaliado, ao menos informalmente, a cada uso. Avaliar permite consertar problemas antes do lançamento, colocar a questão humana em meio à exatidão da computação e comercializar produtos mais sólidos.
* **O que avaliar:**

| Aspecto | Perguntas dos slides |
| --- | --- |
| **Cognitivos e funcionais** | É rápido? É fácil aprender? É confiável? Permite reverter erros facilmente? Permite ser lembrado depois de algum tempo sem uso? |
| **Sociais e culturais** | A solução se integra ao ambiente físico? Causa problemas com outra tecnologia, com quem usa outra tecnologia ou com quem não usa nenhuma? Pode-se prever mudanças das práticas do ambiente? Há redistribuição de poder? |
| **Afetivos** | As pessoas vão gostar? É bonito e agradável? Usar a tecnologia trará *status* ou inibirá o usuário? |

* **Quando avaliar:**

| Tipo | Quando | Artefatos |
| --- | --- | --- |
| **Formativa (construtiva)** | Ao longo de todo o processo de design | Cenários, *storyboards*, modelagem da interação, protótipos do sistema |
| **Somativa (conclusiva)** | Nas etapas finais de cada ciclo de desenvolvimento | Produto ou protótipo funcionando |

* **Objetivos da avaliação:** verificar o entendimento dos projetistas sobre as necessidades e preferências do usuário; investigar como a interface afeta a forma de trabalho; comparar alternativas; identificar problemas potenciais ou reais; verificar conformidade com um padrão ou conjunto de heurísticas; elaborar material de apoio e treinamento.
* **Paradigmas de avaliação:**

| Paradigma | Características |
| --- | --- |
| **Rápido e rasteiro** | Informal, comum no design de IHC. Designers pedem apreciações informais, que podem se repetir em vários pontos do ciclo. Dão *feedback* imediato, mas são menos cuidadosas e informativas |
| **Testes de usabilidade** | Envolvem usuários reais ou potenciais, em laboratório ou em campo. Os participantes realizam tarefas controladas, o que permite avaliar o desempenho. Registro por vídeo, *log* da interação, áudio de comentários, sinais sensório-motores, entrevistas e questionários |
| **Estudos de campo** | Realizados exclusivamente no ambiente natural dos usuários, com observação sem interferência e uso livre (sem tarefas específicas). Ajudam a determinar requisitos, decidir estratégias de adoção da tecnologia e descobrir como ela é de fato usada |
| **Avaliação preditiva** | Não envolve usuários: especialistas usam seu conhecimento sobre usuários e situações típicas de uso para prever os efeitos da tecnologia. Alternativa atraente em termos de custo |

* **Técnicas de avaliação:** observar os usuários (rápida e rasteira, teste de usabilidade, estudos de campo); perguntar aos usuários, por questionário ou entrevista (os mesmos três paradigmas); consultar especialistas (rápida e rasteira, avaliação preditiva); testes com usuários (teste de usabilidade); e modelos de desempenho dos usuários, como GOMS e lei de Fitts (avaliação preditiva).
* **DECIDE, guia para planejar uma avaliação:**

| Letra | Etapa | Perguntas e cuidados |
| --- | --- | --- |
| **D** | *Determine* | Determinar os objetivos gerais. Quais são? Quem solicitou a avaliação e por quê? Influenciam a escolha do paradigma e da técnica? |
| **E** | *Explore* | Explorar perguntas específicas: quem são os usuários-alvo, quais suas atividades, em quais tarefas ocorrem mais erros, quais têm problemas mais graves de desempenho, se a proposta A é melhor que a B em algum aspecto |
| **C** | *Choose* | Escolher paradigma e técnicas que respondam às perguntas, considerando prazo, custo e equipamentos. Alguns paradigmas são incompatíveis com certas técnicas |
| **I** | *Identify* | Identificar questões práticas: seleção de usuários, orçamento, cronograma, avaliadores, equipamentos, tarefas avaliadas, material a preparar |
| **D** | *Decide* | Decidir como lidar com questões éticas e preparar o termo de consentimento |
| **E** | *Evaluate* | Avaliar, interpretar e apresentar os dados: a técnica produz os mesmos resultados nas mesmas circunstâncias, mede o que deveria, existe viés oculto, o escopo pode ser ampliado, o quanto o ambiente distorce os resultados |

* **Direitos dos participantes (etapa *Decide*):** saber o objetivo do estudo e o que será feito com os dados; ter garantia de privacidade; não ser exposto sem consentimento prévio; abandonar o estudo quando e por que quiser; exigir e ser tratado com toda educação.
* **Estudos-piloto:** avaliam se a avaliação ou experimento é viável, se o procedimento inteiro pode ser conduzido bem e se roteiros, entrevistas e questionários estão claros e sem "bugs". Devem ser feitos quantos forem necessários para ajustar o experimento, e pelo menos um é indispensável. Sem usuários "sobrando", procurar pessoas com perfil semelhante.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Opinião não é avaliação:** os slides insistem que avaliar IHC é atividade profissional, com método, rigor e cuidados éticos. A opinião do usuário é valiosa, mas não substitui a avaliação.
>
> 💡 **Princípios podem conflitar:** por serem genéricos, os princípios não dão solução direta e podem entrar em conflito entre si. Já uma mesma situação pode violar mais de uma heurística de Nielsen ao mesmo tempo.
>
> 💡 **Listas de Norman diferentes entre aulas:** os 6 princípios deste material (visibilidade, *feedback*, restrições, mapeamento, consistência e *affordance*) não coincidem com a lista de 6 pilares de Norman registrada na Aula 1 (que inclui significantes e modelo conceitual). Os decks citam fontes diferentes, então confira qual lista a professora cobra.
>
> 💡 **Erros de grafia nos slides:** "Sheneiderman" (o correto é Shneiderman), "Fitt's Law" (lei de Fitts) e "estudos de campo não são compatíveis como testes" (com testes).
>
> 💡 **Numeração interna dos slides:** o deck de princípios se intitula "Aula 11" e o de avaliação traz "(Aula 7)" no slide de etapas do design, numerações herdadas de outra versão do curso.

---

### 📚 Links & Leituras Complementares

* 📖 **BARBOSA, S. D. J.; SILVA, B. S. (2010).** *Interação Humano-Computador*. Editora Campus-Elsevier. Capítulo 8 (princípios de design) e capítulo 9 (introdução à avaliação).
* 📖 **SHARP, H.; ROGERS, Y.; PREECE, J. (2007).** *Interaction Design: Beyond Human-Computer Interaction*, 2ª edição. New York, NY. Fonte do guia DECIDE.
* 📖 Slides elaborados a partir do material do Prof. Leandro Augusto Frata Fernandes (UFF).
* 🔗 Imagens de exemplo das heurísticas extraídas de homepage.mac.com/bradster/iarchitect (endereço citado nos slides como fonte das imagens; não verificado).

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 06: Personas, Cenários & Análise de Tarefas](../Aula_6/README.md)
* ➡️ **Próxima Aula:** [Aula 08: Avaliação Heurística & Percurso Cognitivo](../Aula_8/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
