# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 01/10/2026 | 📚 Professora: Daniela Gorski Trevisan | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 09: Teste de Usabilidade & First Click

### 📝 Introdução

Esta aula tratou de métodos de **avaliação por observação**, que envolvem usuários. Primeiro, o **teste de usabilidade**, com seu ambiente de aplicação, a coleta de dados e as cinco atividades do método (preparação, coleta de dados, interpretação, consolidação e relato dos resultados), com base em Barbosa e Silva (2010), capítulo 10. Depois, o **teste de First Click** (primeiro clique), uma técnica para verificar se as pessoas conseguem encontrar o que procuram em uma interface, com orientações sobre o que testar e como escrever tarefas efetivas.

---

### 💡 Conceitos Chave

#### Parte 1: Teste de Usabilidade

* **O que é:** método de avaliação por observação que envolve usuários reais ou potenciais e permite identificar imprevistos. Os participantes convidados realizam **tarefas controladas**, e os avaliadores coletam e analisam dados para avaliar o desempenho dos participantes, apontar problemas na interação com o sistema e sugerir melhorias.
* **Ambiente de avaliação:**

| Ambiente | Características | Ferramentas citadas nos slides |
| --- | --- | --- |
| **Controlado** | Laboratório de usabilidade, com computador do participante, monitor clone e avaliadores observando (o slide mostra o Laboratório de Usabilidade da IBM) | Não se aplica |
| **Remoto, pago** | Para páginas e aplicativos | UserZoom |
| **Remoto, gratuito** | Apenas para páginas | Usabilla (*free trial* para 2 páginas), GhostRec (100 créditos grátis), Silverback (*free trial* por 30 dias), Userfly (10 capturas por mês) |

* **Coleta de dados:** observa a experiência de uso, registrando o desempenho dos participantes e suas opiniões e sentimentos. Formas de registro: vídeo do usuário usando o sistema, *log* da interação na interface, áudio de comentários ou interjeições, sinais sensório-motores, entrevistas e questionários.
* **Exemplos de resultados obtidos:**

| Tipo de dado | Perguntas dos slides |
| --- | --- |
| **Mensuráveis** | Quantos erros os usuários cometem nas primeiras sessões? Quantos conseguiram completar determinada tarefa? Quantas vezes consultaram a ajuda on-line ou o manual? Qual o tempo mediano para realizar determinada tarefa? |
| **Não mensuráveis** | Impressões, opiniões e reações emocionais |

#### 🔍 Tópico em Destaque

**As cinco atividades do teste de usabilidade**

O teste é realizado por um ou mais avaliadores, que podem trabalhar em conjunto, revezar ou dividir as tarefas.

| Atividade | O que se faz |
| --- | --- |
| **1. Preparação** | Definir as tarefas dos participantes; definir o perfil e recrutar participantes; preparar o material para observar e registrar o uso; executar um **teste piloto**. Tipicamente selecionam-se de **5 a 10 usuários** (gráfico de custo × benefício segundo Jakob Nielsen). As tarefas geralmente não demoram mais de **30 minutos**, com as mesmas condições de teste para todos. Lembrar do termo de consentimento e das questões éticas |
| **2. Coleta de dados** | Observar e registrar a performance e a opinião dos participantes durante sessões de uso controladas. Combina questionário pré-teste, observação da interação e entrevista pós-teste |
| **3. Interpretação** | Reunir, contabilizar e sumarizar os dados coletados; organizá-los de modo a evidenciar as relações entre eles |
| **4. Consolidação dos resultados** | Categorizar os problemas encontrados na interação de todos os participantes |
| **5. Relato dos resultados** | Relatar a performance e a opinião dos participantes |

* **O que medir (coleta de dados):** grau de sucesso da execução; total de erros cometidos; quantos erros de cada tipo; tempo necessário para concluir as tarefas; número de vezes que a ajuda on-line foi consultada; grau de satisfação do usuário. Como coletar: vídeo, *log* da interação, áudio, sinais sensório-motores e anotações do avaliador.
* **Ferramentas citadas para coleta:** SurveyMonkey e Google Docs (questionário); CamStudio e Free Screen Capture (interação).
* **Interpretação: análise quantitativa × qualitativa:**

| Análise | O que faz |
| --- | --- |
| **Quantitativa** | Levantamento de estatísticas de ocorrência dos fenômenos observados (média, mediana, moda etc.) para testar hipóteses, descobrir tendências e comparar o desempenho de soluções alternativas. Apresentação em gráficos e tabelas |
| **Qualitativa** | Identifica a **origem do problema**. A informação relevante emerge da análise conjunta, sincronizando as fontes de dado, por exemplo relacionando o áudio com as interações e com os comentários do observador. Cobre o que é difícil de medir razoavelmente com números |

* **Consolidação:** categorizar os problemas encontrados com todos os participantes, descrevendo cada categoria, apontando em que parte da interface ocorre, relatando os impactos imediatos na usabilidade, explicando hipóteses sobre as causas e sugerindo melhorias.
* **Conteúdo do relato dos resultados:**
  * Objetivos e escopo da avaliação e breve descrição do método.
  * Número e perfil dos avaliadores e dos voluntários, e tarefas executadas.
  * Tabelas e gráficos que sumarizam as medições.
  * Lista de problemas encontrados, indicando para cada um: local onde ocorreu, descrição e justificativa, fatores de usabilidade prejudicados e sugestões de solução.

#### Parte 2: First Click

* **Para que serve:** quando as pessoas acertam o primeiro clique em um site, têm de **duas a três vezes mais chances** de encontrar o que procuram do que se errassem esse clique. O teste mostra se usuários encontram o que procuram de forma rápida e fácil e, se não encontram, onde estão clicando. Apoia decisões sobre o conteúdo e os elementos visuais a priorizar, a linguagem de rótulos, links e conteúdo e o posicionamento de itens como botões, ícones de carrinho de compras e menus.
* **Como testar:** selecionar imagens que reflitam a interface existente ou planejada: *screenshots* do site completo (*homepage*, páginas de produtos, preços, informações, carrinho) ou de partes dele (menus, *mega-menus*, opções de conta), *wireframes* de baixa, média ou alta fidelidade, designs de app e internet das coisas (controles remotos, consoles de jogos).
* **O que testar:** cada tarefa responde a variações destas perguntas.
  * Quantas pessoas acertaram o primeiro clique? Quantas falharam?
  * Onde clicaram incorretamente e por quê?
  * Onde a maioria clica quando há mais de uma resposta correta?
  * Quanto tempo levaram, em média, para clicar? É muito longo?
* **Como escrever tarefas efetivas:** imitar o pensamento de uma pessoa que visita o site, app ou interface, em estilo simples e natural e com um cenário real. Menos "clique na coisa" e mais "encontre as informações de que precisa para fazer algo".

| Em vez de... | Escreva... |
| --- | --- |
| "Encontre o local do nosso escritório" | "Você marcou uma reunião com um de nossos funcionários e deseja saber aonde ir" |
| Usar a palavra "eventos" no cenário | "Você ouviu falar que está chegando um festival de rua na sua cidade. Você não sabe muito sobre isso e gostaria de ver se o Yelp tem alguma informação sobre isso" |

No exemplo do Yelp, a equipe queria saber se as pessoas encontrariam o link Eventos e qual dos dois links relacionados escolheriam. Usar "eventos" na descrição entregaria a resposta, e os dados seriam conclusivos, mas bastante inúteis.

* **Ferramentas citadas para praticar:** Optimal Workshop (demos), Useberry e Maze.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Comece pelo piloto:** o teste piloto está na preparação do teste de usabilidade, e o termo de consentimento e as questões éticas, vistos nas Aulas 3 e 7, valem aqui. Todos os participantes devem enfrentar as mesmas condições de teste.
>
> 💡 **Quantos usuários:** os slides indicam de 5 a 10 usuários, com o gráfico de custo × benefício de Nielsen, que mostra ganho decrescente a cada usuário adicional (eixo de 0 a 15 usuários).
>
> 💡 **Quantitativo × qualitativo:** os números mostram **o que** e **quanto** acontece. A análise qualitativa explica **por que**, e por isso exige sincronizar áudio, interações e comentários do observador.
>
> 💡 **Ferramentas com condições antigas:** os endereços e as condições gratuitas das ferramentas remotas (UserZoom, Usabilla, GhostRec, Silverback, Userfly) vêm de slides com rodapé 2011.2. Confirme se ainda estão disponíveis antes de usar. Os slides do First Click citam outras ferramentas (Optimal Workshop, Useberry, Maze).
>
> 💡 **Título confuso no slide 11:** o slide da etapa de coleta de dados do teste de usabilidade está intitulado apenas "Usabilidade". O conteúdo trata da atividade 2, coleta de dados.
>
> 💡 **First Click sem fonte:** o slide afirma que acertar o primeiro clique dá de duas a três vezes mais chances de encontrar o que se procura, mas não cita a origem dessa estatística. O deck também mistura português e inglês e traz um marcador vazio e erros como "voce" e "media".
>
> 💡 **Numeração interna dos slides:** o deck de teste de usabilidade se intitula "Aula 22" e mantém o rodapé "TCC-00.184 Interface Homem/Máquina (2011.2)".

---

### 📚 Links & Leituras Complementares

* 📖 **BARBOSA, S. D. J.; SILVA, B. S. (2010).** *Interação Humano-Computador*. Editora Campus-Elsevier. Capítulo 10.
* 📖 Slides de teste de usabilidade elaborados pelo Prof. Leandro Augusto Frata Fernandes (UFF).
* 🔗 [UserZoom](http://www.userzoom.com/), [Usabilla](http://usabilla.com/), [GhostRec](http://www.ghostrec.com/), [Silverback](http://silverbackapp.com/) e [Userfly](http://userfly.com/), ferramentas de teste remoto citadas nos slides.
* 🔗 [SurveyMonkey](http://www.surveymonkey.com), [CamStudio](http://camstudio.org/) e [Free Screen Capture](http://www.free-screen-capture.com/), ferramentas de coleta citadas nos slides.
* 🔗 [Optimal Workshop (demos)](https://www.optimalworkshop.com/demos/), [Useberry](https://www.useberry.com/) e [Maze](https://maze.co/), ferramentas de First Click citadas nos slides.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 08: Avaliação Heurística & Percurso Cognitivo](../Aula_8/README.md)
* ➡️ **Próxima Aula:** [Aula 10: Avaliação de Comunicabilidade & Prototipação em Papel](../Aula_10/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
