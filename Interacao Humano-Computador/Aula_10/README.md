# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 08/10/2026 | 📚 Professora: Daniela Gorski Trevisan | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 10: Avaliação de Comunicabilidade & Prototipação em Papel

### 📝 Introdução

Esta aula completou os métodos de **avaliação por observação** com dois métodos: a **avaliação de comunicabilidade (MAC)**, fundamentada na Engenharia Semiótica e centrada nas rupturas de comunicação entre o designer e o usuário, e a **prototipação em papel**, que avalia a usabilidade de um design por simulação, antes de existir uma solução executável. Ao final, os métodos de avaliação vistos nas aulas anteriores foram comparados quanto aos aspectos avaliados, aos casos de utilização e aos tipos de dados produzidos. O conteúdo se baseia em Barbosa e Silva (2010), capítulo 10.

---

### 💡 Conceitos Chave

#### Parte 1: Avaliação de Comunicabilidade (MAC)

* **O que é:** método de avaliação por observação, com usuários reais, que avalia a qualidade da comunicação da **metamensagem do designer** para os usuários. Sua fundamentação teórica é a Engenharia Semiótica (Aula 5).
* **MAC × inspeção semiótica:**

| | Inspeção semiótica | Avaliação de comunicabilidade |
| --- | --- | --- |
| **Tipo** | Avaliação por inspeção | Avaliação por observação |
| **Avalia** | A qualidade da **emissão** da metacomunicação | A qualidade da **recepção** da metacomunicação |
| **Foco do avaliador** | No emissor, o designer | No receptor, o usuário |

* **Método:** ambiente controlado; os usuários são convidados a realizar um conjunto de tarefas com o sistema; os registros são feitos por vídeos de interação e anotações do avaliador. A análise abrange os **caminhos de interpretação** dos usuários, as **intenções de comunicação** e as **rupturas de comunicação** durante a interação.
* **Atividades** (realizado por dois ou mais avaliadores, com 5 a 10 participantes):

| Atividade | O que se faz |
| --- | --- |
| **1. Preparação** | Inspecionar os signos estáticos, dinâmicos e metalinguísticos; definir tarefas para os participantes; preparar material para observar e registrar o uso; definir o perfil dos participantes e recrutá-los; executar teste piloto |
| **2. Coleta de dados** | Questionário pré-teste; observar e registrar sessões de uso em laboratório; gravar vídeo e áudio da interação de cada participante; entrevista pós-teste |
| **3. Interpretação** | **Etiquetar** cada vídeo de interação individualmente, identificando rupturas (13 classes); tabular os resultados |
| **4. Consolidação dos resultados** | Interpretar as etiquetas de todos os vídeos de interação; elaborar o **perfil semiótico** |
| **5. Relato dos resultados** | Relatar a avaliação da comunicabilidade da solução de IHC, do ponto de vista do receptor da metamensagem |

* **Dados coletados:** captura de tela; expressão do usuário (vídeo e áudio); interações com mouse, teclado e outros dispositivos; anotações do que ocorreu, atento a possíveis rupturas de comunicabilidade e ambiguidades. As rupturas são questionadas na entrevista pós-teste.

#### 🔍 Tópico em Destaque

**As 13 etiquetas de ruptura de comunicabilidade**

A etiquetagem classifica cada ruptura em uma de 13 expressões. O slide as agrupa por gravidade da falha: **parcial**, **temporária** e **completa**, e associa cada uma a uma categoria de problema de IHC.

| Etiqueta | Falha | O que acontece | Sintomas típicos | Categoria de problema |
| --- | --- | --- | --- | --- |
| **Vai de outro jeito** | Parcial | O usuário não consegue realizar a tarefa como o designer idealizou e segue outro caminho, geralmente mais longo ou complicado | Atinge o objetivo de modo não ótimo; não sabe que há forma mais eficiente, rápida ou direta | Affordances e pressuposições |
| **Não, obrigado!** | Parcial | O usuário conhece a solução preferencial do designer, mas opta explicitamente por outra forma de interação | A ação preferencial ocorre e é seguida de alternativas, ou nem ocorre, se o usuário já conhece o sistema (confirmar no pós-teste) | Affordances e pressuposições |
| **Epa!** | Temporária | O usuário executa uma ação indesejada e, ao perceber de imediato, a desfaz | Acionar o desfazer; cancelar um diálogo aberto indevidamente | Atribuição de significado |
| **O que é isso?** | Temporária | O usuário espera uma dica explicativa ou outra indicação sobre o significado de um signo da interface | Deixar o cursor sobre o elemento esperando dica; explorar menus, listas e diálogos para ver o que dizem | Atribuição de significado |
| **E agora?** | Temporária | O usuário não sabe o que fazer e procura descobrir o próximo passo | Vagar com o cursor e inspecionar menus de forma aleatória ou sequencial | Atribuição de significado |
| **Onde estou?** | Temporária | O usuário faz operações apropriadas para outros contextos, mas não para o atual | Digitar em campo desabilitado; comum em aplicações com modos (edição, visualização, impressão); desfazer e mudar para o contexto desejado | Atribuição de significado |
| **Assim não dá** | Temporária | O usuário abandona um caminho de vários passos consistentemente encadeados, por achar que não leva ao objetivo | Interromper de repente uma atividade e seguir direção totalmente diferente | Raciocínio tem de ser abandonado |
| **Cadê?** | Temporária | O usuário sabe a operação que quer executar, mas não a encontra de imediato | Abrir e fechar menus e submenus, passar o cursor sobre botões, inspecionar elementos sem ativá-los | Estrutura e organização |
| **Por que não funciona?** | Temporária | O usuário não entende ou não se conforma com o fato de a operação não produzir o resultado esperado | Repetir a ação, às vezes tentando pequena mudança de parâmetros ou contexto | Raciocínio tem de ser abandonado |
| **Socorro!** | Temporária | O usuário não consegue realizar a tarefa explorando a interface e busca outros meios de ajuda | Ativar o *help*; procurar documentação on-line ou off-line; pedir explicações a alguém | Estrutura e organização, atribuição de significado, raciocínio abandonado e *affordances* |
| **Ué, o que houve?** | Temporária | O usuário não percebe ou não entende a resposta do sistema à sua ação, ou o sistema não responde | Repetir a ativação de uma função cujo *feedback* não existe ou não foi percebido; buscar forma alternativa | Atribuição de significado |
| **Desisto** | Completa | O usuário admite explicitamente sua incapacidade de alcançar o objetivo | Desistir de atividades intermediárias; interromper a tarefa prematuramente | Metas não são atingidas |
| **Para mim está bom** | Completa | O usuário acha, equivocadamente, que concluiu uma tarefa ou ação com sucesso | Encerrar a tarefa e indicar, no pós-teste, que foi realizada com sucesso | Metas não são atingidas |

* **Lembretes sobre a etiquetagem:**
  * Etiquetar **não é adivinhação**: fundamenta-se na observação cuidadosa, no registro da interação e nos esclarecimentos do usuário na entrevista pós-teste.
  * Se a ambiguidade só for notada depois do teste, sem acesso ao usuário, não se deve inventar ou forçar um sentido. Registra-se a ambiguidade e, se mais de uma etiqueta for possível, **todas as etiquetas possíveis**, uma por hipótese de interpretação.
* **Tabulação dos resultados (interpretação):** levantar os tipos de etiqueta, a frequência e os trechos ou atividades em que ocorreram; levantar tipo e frequência por usuário (por atividade); associar os padrões de etiquetagem a classes de problemas de IHC (podem-se usar diretrizes, heurísticas, modelos ou tipos gerais de problemas). **Os números não dizem tudo:** uma única ocorrência de falha completa basta para comprometer toda a interação.
* **Perfil semiótico:** responde a quatro perguntas. Quem o designer pensa ser o usuário (perfis, características e valores)? Na visão do designer, de que maneiras os usuários preferem fazer o que desejam e precisam, onde, quando e por quê (existem outras formas de comunicação)? Qual foi o sistema projetado e como deve ser usado? Quão bem a lógica de design é compreendida e aceita pelos usuários?
* **Relato dos resultados:** objetivos e escopo; breve descrição do método; número e perfil dos avaliadores e participantes; tarefas executadas; resultado da etiquetagem, contabilizando etiquetas por usuário e tarefa; problemas de comunicabilidade encontrados; perfil semiótico do sistema.

#### Parte 2: Prototipação em Papel

* **O que é:** método de avaliação por observação, com usuários reais ou potenciais, que avalia a usabilidade de um design de IHC **por meio de simulação**. Vantagens: é rápido, barato e identifica problemas antes mesmo de construir uma solução executável.
* **Equipe:** pelo menos dois avaliadores, um que **simula o sistema** e outro que **observa a experiência de uso**.
* **Protótipos em papel:** representação das telas do sistema em papel (desenhos à mão livre, telas estáticas, menus, dicas sobre elementos da interface, resultados de busca e diálogos). Representam e destacam os principais elementos, sem preocupação com detalhes. O que não for possível prever é desenhado durante a simulação.
* **Ambiente de avaliação:** tipicamente uma sala de reunião, com câmera de vídeo e gravador de voz.
* **Atividades:**

| Atividade | O que se faz |
| --- | --- |
| **1. Preparação** | Definir as tarefas dos participantes; definir o perfil e recrutá-los; criar os protótipos em papel da interface para executar as tarefas; preparar o ambiente; executar teste piloto |
| **2. Coleta de dados** | Cada usuário executa as tarefas interagindo com os protótipos, mediado pelo avaliador. O avaliador explica como os *widgets* estão representados e como interagir com eles, simula o sistema (compreendendo as ações do usuário e modificando a interface conforme o comportamento planejado), sem fornecer explicações ou orientações: o usuário deve se guiar pelo que está na interface. Também executa pequenos ajustes para sanar problemas simples, observa o que funciona bem e mal, anota as tarefas concluídas, registra erros e grava comentários |
| **3. Interpretação** | Realizada após cada experiência de uso: analisar os dados e listar os problemas de usabilidade. Os problemas podem ser corrigidos antes da próxima experiência |
| **4. Consolidação dos resultados** | Priorizar as correções não resolvidas dos protótipos e sugerir correções |
| **5. Relato dos resultados** | Relatar os problemas encontrados e as sugestões de correção |

* **Relato dos resultados:** objetivos e escopo; breve descrição do método; número e perfil dos avaliadores e participantes; tarefas executadas; **lista de problemas corrigidos durante a avaliação** (local, descrição e justificativa, fatores de usabilidade prejudicados, correção feita no protótipo e se o problema voltou a ocorrer); **lista de problemas ainda não corrigidos** (local, descrição e justificativa, fatores prejudicados, prioridade e sugestões de correção); e indicações de partes do sistema que podem ser mais bem elaboradas.

#### Parte 3: Comparativo dos Métodos de Avaliação

Os quadros dos slides usam estrelas, de uma a três (célula vazia indica que o método não se aplica). O slide não traz legenda, e a leitura natural é que mais estrelas indicam maior adequação.

**Aspectos avaliados**

| Método | Apropriação de tecnologia | Alternativas de design | Conformidade com padrão | Problemas de IHC |
| --- | --- | --- | --- | --- |
| **Entrevistas** | ★★★ | ★ | | ★★ |
| **Questionários** | ★★ | ★ | | ★★ |
| **Avaliação heurística** (inspeção) | | ★★★ | ★★★ | ★★★ |
| **Percurso cognitivo** (inspeção) | ★ | ★★ | | ★★★ |
| **Inspeção semiótica** (inspeção) | | ★★ | ★ | ★★★ |
| **Teste de usabilidade** (observação) | ★★★ | ★★ | | ★★★ |
| **Avaliação de comunicabilidade** (observação) | ★★★ | ★★ | | ★★★ |
| **Prototipação em papel** (observação) | ★ | ★★★ | | ★★★ |

**Casos de utilização** (formativa: ao longo de todo o processo de design; somativa: nas etapas finais)

| Método | Avaliação formativa | Avaliação somativa |
| --- | --- | --- |
| **Entrevistas** | ★★ | ★★ |
| **Questionários** | ★★ | ★★ |
| **Avaliação heurística** | ★★ | ★ |
| **Percurso cognitivo** | ★★ | ★ |
| **Inspeção semiótica** | ★ | ★★ |
| **Teste de usabilidade** | ★ | ★★ |
| **Avaliação de comunicabilidade** | ★ | ★★ |
| **Prototipação em papel** | ★★ | ★ |

**Tipos de dados produzidos**

| Método | Quantitativos | Qualitativos |
| --- | --- | --- |
| **Entrevistas** | ★ | ★★★ |
| **Questionários** | ★★★ | ★★ |
| **Avaliação heurística** | ★ | ★★★ |
| **Percurso cognitivo** | ★ | ★★★ |
| **Inspeção semiótica** | ★ | ★★★ |
| **Teste de usabilidade** | ★★★ | ★★ |
| **Avaliação de comunicabilidade** | ★ | ★★★ |
| **Prototipação em papel** | ★ | ★★★ |

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Duas grafias da mesma etiqueta:** nos slides de definição das rupturas a etiqueta é "O que é isso?", e na tabela de associação a falhas de comunicabilidade aparece como "O que é isto?". É a mesma etiqueta, agrupada em atribuição de significado.
>
> 💡 **"Socorro!" pode vir de várias categorias:** no quadro de tabulação, "Socorro!" é a última linha e se associa a E.O., A.S., Rac. e Aff. (estrutura e organização, atribuição de significado, raciocínio abandonado e *affordances*). Já "Metas não são atingidas" reúne "Para mim está bom" e "Desisto".
>
> 💡 **Falha completa pesa mais que a frequência:** uma única ocorrência de "Desisto" ou "Para mim está bom" pode comprometer toda a interação. Por isso a contagem de etiquetas não substitui a análise.
>
> 💡 **Comparativo sem legenda:** os quadros de estrelas não explicam a escala, e o rodapé segue "TCC-00.184 Interface Homem/Máquina (2011.2)". Use-os como guia de comparação, não como medida exata.
>
> 💡 **Erros de grafia nos slides:** "temporaria" (temporária) no diagrama das falhas, "executares" no lugar de "executarem" e "seções" no lugar de "sessões" de uso. A numeração interna ("Aula 23" e "Aula 24") também vem de outra versão do curso.

---

### 📚 Links & Leituras Complementares

* 📖 **BARBOSA, S. D. J.; SILVA, B. S. (2010).** *Interação Humano-Computador*. Editora Campus-Elsevier. Capítulo 10.
* 📖 Slides adaptados e elaborados pelo Prof. Leandro Augusto Frata Fernandes (UFF).
* 🖼️ Diagrama das 13 etiquetas (*Communicability Evaluation Method*): ilustração de Ugo Sangiorgi (SERG), licença Creative Commons 3.0, citada no slide.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 09: Teste de Usabilidade & First Click](../Aula_9/README.md)
* ➡️ **Próxima Aula:** *Em breve*

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
