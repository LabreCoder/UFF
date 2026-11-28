# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 03/09/2026 | 📚 Professora: Daniela Gorski Trevisan | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 05: Teorias de IHC: Engenharia Semiótica & Engenharia Cognitiva

### 📝 Introdução

Esta aula apresentou duas **teorias de IHC**, que explicam os fenômenos da interação e auxiliam a tomada de decisão no design. A **Engenharia Semiótica** trata a aplicação como um artefato de metacomunicação, pelo qual o designer envia uma mensagem ao usuário, e introduz o conceito de signo e os tipos de signos de interface. A **Engenharia Cognitiva**, proposta por Don Norman, descreve a interação como a travessia de dois golfos, o de execução e o de avaliação. Ao final, as duas teorias foram comparadas, com base em Barbosa e Silva (2010), capítulo 3.

---

### 💡 Conceitos Chave

#### Engenharia Semiótica

* **Semiótica:** disciplina devotada ao estudo dos sinais e de como eles são utilizados na comunicação.
* **Engenharia Semiótica:** proposta originalmente como abordagem para o design de linguagens de interfaces, evoluiu para uma **teoria semiótica da IHC**. É uma teoria **explicativa e não preditiva**.
* **Artefatos de metacomunicação:** as aplicações computacionais são artefatos que comunicam uma mensagem. A teoria investiga a comunicação entre designers, usuários e sistemas, em **dois níveis**: a comunicação direta usuário-sistema e a **metacomunicação** do designer para o usuário, via interface.
* **Metamensagem do designer:** diz aos usuários como podem e devem utilizar o sistema, por quê e com que efeitos. Em essência: "este é o meu entendimento de quem você é, do que aprendi que você quer ou precisa fazer, de que maneiras prefere fazer, e por quê. Este, portanto, é o sistema que projetei para você, e esta é a forma como você pode ou deve utilizá-lo".
* **Esforço de cada lado:**

| Quem | Quando | Esforço |
| --- | --- | --- |
| **Designer** | Tempo de design | Estudar os usuários (indivíduo, atividades, ambiente); conceber sua visão sobre o que desejam ou necessitam e como usuários, atividades e ambiente podem ou devem mudar; expressar essa visão em tecnologia. O designer só tem uma chance |
| **Usuário** | Tempo de interação | Decodificar e interpretar a metamensagem; atribuir sentido aos significados codificados; responder de forma apropriada |

* **Comunicabilidade:** conceito de qualidade dos sistemas computacionais interativos. Um sistema com alta comunicabilidade ajuda os usuários a interpretar e atribuir sentido à metamensagem do designer, com sentido compatível com o pretendido. Métodos de avaliação: **método de inspeção semiótica** e **método de avaliação de comunicabilidade**.
* **Signo:** coisa que serve para vincular conhecimento de outra coisa (o objeto do signo). Pode ser imagem, diagrama, memória, sintoma etc. Para ser signo, uma representação deve ter uma **relação triádica** com seu objeto e seu interpretante.
  * **Exemplo de interface:** o objeto é a ação "salvar arquivo", o signo é o botão **Salvar** e o interpretante é a ideia "clicando nesse botão, eu consigo salvar o documento".
* **Processo de comunicação em IHC:** o designer codifica um objeto em uma mensagem (signo), enviada por um canal, e o usuário a decodifica e produz interpretantes ("sucesso!?", "não, indica erro", "tenho que tentar de novo").
* **Semiose ilimitada:** o processo interpretativo humano está em constante evolução, o significado pode ser revisto e corrigido, e o **interpretante é por si só um signo**. No exemplo do slide, "clicando aqui eu salvo o arquivo" leva a "com o arquivo salvo posso desligar o computador". O processo não pode ser completamente determinado, apenas motivado.

#### 🔍 Tópico em Destaque

**Tipos de signos de interface**

| Tipo | O que expressa | Característica | Exemplos do slide |
| --- | --- | --- | --- |
| **Estáticos** | O estado do sistema | Interpretados independentemente das relações causais e temporais da interface; podem ser interpretados a partir de um *screenshot* | Janela principal do aplicativo, menu Arquivo, janela de configuração de página |
| **Dinâmicos** | O comportamento do sistema | Envolvem aspectos temporais e causais da interface | Barra de progresso, escolha de um item de menu |
| **Metalinguísticos** | Os próprios significados codificados no sistema | Principalmente verbais; referem-se a outros signos da interface e comunicam explicitamente os significados aos usuários | Mensagens de ajuda e de erro, alertas, diálogos, dicas |

* **Exemplo de identificação de signos (ICDL):** os slides analisam uma biblioteca digital infantil e listam signos como a lista de idiomas da interface, os botões de categoria de livros, o botão "mais opções", a lista de idiomas do livro, a caixa de busca por palavra-chave, o título e idioma do livro, as resenhas e os livros em destaque. Também mostram que o ícone "Read Book" foi escolhido como meio de acesso a "Simple Search".

#### Engenharia Cognitiva

* **Definição:** proposta por **Don Norman (1986)**, é uma ciência cognitiva aplicada, que busca aplicar o que se sabe dessa ciência no design e na construção de artefatos computacionais.
* **Objetivos:** entender as questões envolvidas no uso de computadores; mostrar como tomar decisões melhores; mostrar os custos e benefícios de privilegiar um aspecto em detrimento de outro.
* **Duas famílias de abordagens de IHC:**

| Baseadas em | Surgiram nos | Característica |
| --- | --- | --- |
| **Psicologia experimental** | Anos 50 | Permitem mensurar e modelar o comportamento humano e prever o desempenho |
| **Psicologia cognitiva aplicada** | Anos 80 | Centradas nos aspectos cognitivos da interação |

* **Modelo de interação:** o **designer** tem um modelo mental do sistema, que se desdobra no modelo conceitual (modelo de design, composto por modelo de tarefas e modelo de usuário) e no **modelo implementado**, a imagem do sistema. O **usuário** forma, a partir da imagem percebida, seu próprio modelo mental, o modelo de uso. Tudo ocorre em um contexto, e o diagrama distingue a **imagem pretendida** pelo designer da **imagem percebida** pelo usuário.
* **Teoria da Ação (Norman e Draper, 1986):** o usuário parte de um **objetivo** e percorre um ciclo em dois golfos.

| Golfo | Estágios |
| --- | --- |
| **Golfo de Execução** | 1. Formulação da intenção; 2. Especificação da sequência de ações; 3. Execução das ações |
| **Golfo de Avaliação** | 4. Percepção do estado do sistema; 5. Interpretação do estado do sistema; 6. Avaliação em relação à intenção |

  * **Exemplo do slide:** objetivo de fazer uma animação para uma apresentação PowerPoint. Execução: formular a intenção (criar o arquivo com o personagem e simular a animação), determinar o plano (abrir arquivo novo, escolher o personagem, associar efeito de animação) e executar as ações (clicar no ícone de novo documento, escolher o layout, incluir a figura, associar o efeito de movimento). Avaliação: perceber o estado resultante (reconhecer comandos, observar a animação), interpretar (reconhecer a animação desejada) e decidir se a intenção foi realizada.
  * **Outro exemplo:** buscar a referência completa de um livro em um sistema (intenção), selecionar o comando de busca (especificação), preencher os campos e confirmar (execução), ver a nova tela de dados (percepção), conferir se os dados correspondem à busca (interpretação) e concluir que encontrou o que queria (avaliação).
* **Distâncias nos golfos:**

| Distância | Ocorre entre | Pergunta | Golfo associado |
| --- | --- | --- | --- |
| **Semântica** | Dois estágios mentais | "Dado que tenho uma intenção, quão próxima ela está das funcionalidades oferecidas pelo sistema?" e "dado que tenho uma interpretação da imagem do sistema, quão próxima estou da minha meta?" | Intenção e funcionalidades (execução); interpretação e meta (avaliação) |
| **Articulatória** | Um estágio mental e um estágio físico | "Dado que tenho um plano de ação, quão diretamente posso executá-lo?" e "dado que percebo a imagem do sistema, quão fácil é atribuir a ela uma interpretação?" | Plano de ação e execução (execução); percepção e interpretação (avaliação) |

* **Golfo de execução:** o sistema oferece ações que correspondem às intenções do usuário? As funcionalidades disponíveis são um mapeamento direto das intenções?
* **Golfo de avaliação:** reflete o esforço do usuário para interpretar o estado físico do sistema e determinar quão bem as expectativas e intenções foram alcançadas.
* **Problemas ao atravessar os golfos:** o usuário pode formar um objetivo inadequado, não encontrar o elemento de interface correto (por exemplo, um *label* ou ícone incompreensível), não saber como especificar ou executar a ação desejada, ou receber *feedback* inapropriado.
* **Papel do designer:** diminuir os golfos, determinando as ações e estruturas de comandos mais indicadas, selecionando os elementos de interface mais eficientes para transmitir a informação e escolhendo os *feedbacks* mais representativos.

#### Engenharia Semiótica × Engenharia Cognitiva

| Aspecto | Engenharia Cognitiva | Engenharia Semiótica |
| --- | --- | --- |
| **Em comum** | O fator determinante para iniciar o design é o modelo mental da aplicação criado pelo designer, que guia a implementação; depois, o usuário forma seu próprio modelo mental na interação | O mesmo |
| **Foco** | A relação entre usuário e sistema (segunda etapa do processo): o sistema, o produto do processo e como o usuário o interpreta | Reúne as duas etapas, com ponto de vista mais abstrato: o envio de uma metamensagem do designer ao usuário |
| **Objetivo** | Fornece ferramentas para desenvolver um produto compatível com a cognição do usuário | A relação usuário-sistema deixa de ser a principal preocupação e cede lugar ao projetista e ao processo de criação de sistemas |
| **Presença do designer** | Em **tempo de design** | Em **tempo de interação** |
| **Relação entre as teorias** | Resultados da engenharia cognitiva também valem para a semiótica | Inclui a engenharia cognitiva e se afasta um pouco do processo de design |

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Teoria explicativa, não preditiva:** a Engenharia Semiótica explica a comunicação, mas não prevê desempenho como as abordagens da psicologia experimental (Hick-Hyman, Fitts, Miller, da Aula 4).
>
> 💡 **Distância semântica × articulatória:** a primeira compara intenção e funcionalidades (ou interpretação e meta), isto é, dois estágios mentais; a segunda compara o plano de ação e o que pode ser executado (ou o que é percebido e como se interpreta), isto é, um estágio mental e um estágio físico. Os slides apresentam as duas perguntas de cada distância sobre o mesmo diagrama dos golfos, por isso a associação com cada golfo na tabela foi organizada a partir do desenho.
>
> 💡 **Signo é sempre triádico:** objeto, signo e interpretante. E o interpretante também é um signo, o que explica a semiose ilimitada.
>
> 💡 **Erros de grafia nos slides:** o slide de Engenharia Cognitiva traz "Treivsan", e o de Engenharia Semiótica usa "Capitulo 3", sem acento. O nome correto é Trevisan.
>
> 💡 **Atividade proposta nos slides (Atividade 3):** baixar o jogo JECRIPE e identificar os signos estáticos, dinâmicos e metalinguísticos nas telas de entrada, de escolha dos ambientes, Casa das Bolhas, Casa bebê Samuca, Casa da Música e de saída. O envio é pelo INTERAGIR, com prazo de 1 semana.

---

### 📚 Links & Leituras Complementares

* 📖 **BARBOSA, S. D. J.; SILVA, B. S. (2010).** *Interação Humano-Computador*. Editora Campus-Elsevier. Capítulo 3.
* 📖 **NORMAN, D.; DRAPER, S. (1986).** *User Centred System Design*, fonte dos diagramas da Teoria da Ação.
* 📖 **SALGADO, L. C. C.; DE SOUZA, C. S.; LEITÃO, C. F. (2009).** *A Semiotic Inspection of ICDL*. Em C. J. P. Lucena (ed.), Monografias em Ciência da Computação n. 31/09. Departamento de Informática, PUC-Rio. 14 p.
* 🔗 [JECRIPE](http://jecripe.wordpress.com/), jogo usado na atividade da aula.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 04: Análise da Situação Atual & Psicologia Experimental e Cognitiva Aplicada](../Aula_4/README.md)
* ➡️ **Próxima Aula:** [Aula 06: Personas, Cenários & Análise de Tarefas](../Aula_6/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
