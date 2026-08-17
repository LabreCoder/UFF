# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 04/08/2026 | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 01: Introdução aos Sistemas Distribuídos

### 📝 Introdução

A aula inicial apresenta as diretrizes e o planejamento para a disciplina **TCC00362 — Sistemas Distribuídos para Sistemas de Informação**, ministrada pelo **Prof. Raphael Guerra**. O objetivo principal do curso é capacitar os alunos nos conceitos de **computação em nuvem, arquiteturas distribuídas, internet das coisas (IoT)** e no **gerenciamento de réplicas, consistência e tolerância a falhas**. Para isso, foram apresentados o cronograma de conteúdo programático, as ferramentas de comunicação oficial, os critérios de avaliação da matéria e as bibliografias sugeridas.

---

### 💡 Conceitos Chave

* **Sistema Distribuído:** Coleção de componentes autônomos que colaboram entre si e se apresentam aos usuários como um sistema único e coerente.
* **Autonomia dos Nós:** Cada computador (nó) possui seu próprio processador e memória, funcionando independentemente de fazer parte ou não do sistema distribuído. A comunicação ocorre por meio de canais de rede e troca de mensagens.
* **Transparência:** Capacidade de ocultar a complexidade e a distribuição física dos recursos (como armazenamento e processamento) para o usuário final ou desenvolvedor, fornecendo uma interação uniforme.
* **Middleware:** Camada de software que atua como um gerenciador de recursos distribuídos em rede, fornecendo uma interface padronizada e unificada para suportar componentes heterogêneos. Ele oferece serviços como descoberta de recursos, comunicação entre processos, transações atômicas e confiabilidade.
* **Abertura (Openness):** Característica de sistemas com interfaces totalmente especificadas e publicadas (de forma completa e neutra) para interagir com outros sistemas. Promove a **interoperabilidade** (sistemas heterogêneos cooperando), a **portabilidade** (execução multiplataforma) e a **extensibilidade** (adição de novas funções).
* **Escalabilidade:** Capacidade do sistema de expandir mantendo seu desempenho satisfatório. É medida em três dimensões: tamanho (usuários/recursos), geografia (distâncias geográficas) e administração (gerenciamento entre diferentes domínios e organizações).

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Premissas Falsas de Rede:** No projeto de sistemas distribuídos, nunca assuma premissas incorretas: a rede não é necessariamente confiável, segura ou homogênea; a latência não é zero; a largura de banda não é infinita; a topologia muda; o custo de transporte não é zero; e raramente há apenas um administrador.

--

> 💡 **Tipos de Transparência:** Atente-se às diferenças entre os vários níveis de transparência (acesso, localização, migração, relocação, replicação, concorrência e falhas). A transparência de falhas é particularmente complexa de implementar, pois o sistema frequentemente não consegue distinguir entre um recurso que falhou ("morto") e um que está apenas muito lento.

--

> 💡 **Técnicas de Escalabilidade:** Para combater gargalos de escalabilidade em sistemas centralizados e latências geográficas de conexões WAN, utilizam-se técnicas como a **ocultação de latência** (através de comunicação assíncrona/não-bloqueante e programação multithread), o **particionamento e distribuição** (como subdivisão de tabelas de banco de dados e resolução hierárquica do DNS), e a **replicação** (que, contudo, gera desafios de consistência e sincronização dos dados).

--

> 💡 **Classificação dos Sistemas Distribuídos:** Os SDs são tradicionalmente classificados em três grandes categorias:
>
> 1. **Alto Desempenho (High-Performance):** Voltados para processamento paralelo e computação paramétrica ou científica de alta demanda computacional (como previsões de tempo ou processamento de redes neurais).
> 2. **Sistemas de Informação Distribuídos:** Essencialmente transacionais (ACID), lidando com alto volume de transações simultâneas (como e-commerce e operações financeiras).
> 3. **Sistemas Distribuídos Pervasivos:** Sistemas móveis, embutidos e altamente cooperativos baseados em Internet das Coisas (IoT), caracterizados por restrições severas de bateria, memória e banda (como Waze e monitoramento médico).

---

### 📚 Links & Leituras Complementares

* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª e 3ª Edições) — Capítulo 1
* 📖 *Sistemas Distribuídos: Conceitos e Projeto* (G. Coulouris et al., 5ª Edição) — Capítulo 1

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** *Primeira aula do curso*
* ➡️ **Próxima Aula:** [Aula 2: Grids e Clusters — Em busca de maior capacidade de processamento](../Aula_2/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
