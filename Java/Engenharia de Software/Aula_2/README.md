# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 17/08/2026 | 📚 Professora: Rebeca Motta | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 02: Modelos de Ciclo de Vida — Métodos Tradicionais

### 📝 Introdução

A segunda aula apresenta as diretrizes teóricas e conceituais sobre os **Modelos de Ciclo de Vida de Software.** O objetivo principal do encontro é capacitar a compreensão sobre a importância de estruturar e gerenciar o desenvolvimento de sistemas complexos de maneira profissional, disciplinada e economicamente viável, otimizando recursos como tempo, custos e pessoal. Para isso, foi revisada a tríade fundamental da engenharia de software (**processos, métodos e ferramentas**), detalhando como um processo de software define atividades, papéis e artefatos em fluxos preestabelecidos de trabalho.

Em seguida, a aula aprofundou-se no estudo do ciclo de vida do software — o caminho que o produto percorre desde a sua concepção inicial até a sua descontinuidade e morte. Foi apresentada a taxonomia clássica de modelos de processo de software, classificando-os em três grandes famílias: **modelos sequenciais** (Cascata e V), **modelos incrementais** (Iterativo Incremental e RAD) e **modelos evolutivos** (Evolucionário, Espiral e Prototipagem). Foram analisadas a dinâmica de funcionamento de cada abordagem, seus respectivos benefícios e limitações, bem como exemplos práticos de aplicação no mercado real para fundamentar a tomada de decisão técnica sobre qual ciclo de vida escolher para diferentes cenários de projeto.

---

### 💡 Conceitos Chave

* **Ciclo de Vida de Software (Representação Abstrata):** Descreve as etapas lógicas pelas quais um produto de software passa ao longo de sua existência. Serve para estruturar o processo, habilitar o controle de qualidade, facilitar a comunicação entre os interessados e mitigar riscos de mudança. Suas fases genéricas baseiam-se em: Planejamento, Requisitos, Projeto, Implementação, Testes, Entrega/Implantação e Operação/Manutenção.



* **Modelos Sequenciais (Cascata e V):**
* *Modelo Cascata (Clássico):* Proposto por Winston Royce em 1970. Funciona de maneira estritamente linear, onde uma fase só começa após o término e documentação detalhada da anterior. É ideal para projetos muito pequenos e de requisitos estáticos (como o projeto do Boeing 777). No entanto, sua rigidez dificulta acomodar mudanças tardias, gerando gargalos.
* *Modelo em V:* Foca na relação direta entre as fases de especificação (lado esquerdo) e as fases equivalentes de teste (lado direito), dividindo o fluxo entre **Verificação** (o produto está sendo feito corretamente?) e **Validação** (o produto correto está sendo feito?). É amplamente utilizado em indústrias altamente regulamentadas, como a de dispositivos médicos (FDA/UE).



* **Modelos Incrementais (Iterativo Incremental e RAD):**
* *Iterativo Incremental:* Divide o desenvolvimento em módulos funcionais (incrementos operacionais) entregues de forma faseada ao cliente. O usuário recebe partes úteis mais cedo e fornece feedback contínuo. É o modelo adotado pela Netflix para testar e refinar novos conteúdos com base em dados de usuários.
* *RAD (Rapid Application Development):* Modelo incremental focado em ciclos de desenvolvimento extremamente curtos (tipicamente até 90 dias). Baseia-se no paralelismo massivo de equipes separadas construindo módulos altamente independentes. Exige alto custo de recursos humanos e forte acoplamento modular (conforme ilustrado no famoso MVP inicial do Dropbox).



* **Modelos Evolutivos (Evolucionário, Espiral e Prototipagem):**
* *Evolucionário:* Desenvolve gradativamente a especificação junto com o cliente. Porém, modificações constantes tendem a corromper a estrutura lógica do software e degradar a documentação.
* *Modelo Espiral:* Proposto por Barry Boehm em 1988, é o modelo clássico **orientado a riscos**. Cada iteração é dividida em quatro quadrantes: definição de objetivos, avaliação e redução de riscos, desenvolvimento/validação e planejamento da próxima fase. É ideal para sistemas grandes, complexos e críticos (como o Advanced Traffic Management System - ATMS).
* *Prototipagem:* Constrói simulações rápidas e descartáveis para elicitar e validar requisitos obscuros com o cliente antes de codificar a solução definitiva.

#### 🔍 Tópico em Destaque

**Verificação × Validação (Modelo em V)**

* **Verificação:** Avalia se o software está sendo construído corretamente de acordo com as especificações técnicas estabelecidas em cada etapa prévia do desenvolvimento ("Estamos construindo o produto corretamente?").
* **Validação:** Garante que o software atende às reais necessidades e expectativas operacionais do cliente e dos usuários finais ("Estamos construindo o produto correto?").

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Curiosidade Histórica (Royce e a Cascata):** No artigo seminal de 1970 sobre gerenciamento de grandes sistemas de software, Winston Royce **nunca utilizou o termo "Cascata"**. Além disso, ele descreveu o fluxo linear estrito para apontá-lo como "arriscado e um convite ao fracasso", propondo, na verdade, uma abordagem mais interativa com ciclos de feedback entre as etapas.
>
> 📌 **O Perigo da Prototipagem Rápida:** Ao final do ciclo de prototipagem, o cliente frequentemente adquire a falsa impressão de que o software final está praticamente pronto. O desenvolvedor deve ser cauteloso para não ceder à pressão de reaproveitar códigos "remendados" do protótipo na solução definitiva, mantendo o compromisso com os critérios formais de qualidade.

---

### 📚 Links & Leituras Complementares

* 📖 **Leitura Seminal:** Royce, Winston W. (1970). *Managing the Development of Large Software Systems*.
* 🎥 **Dropbox Demo (RAD & MVP):** [Dropbox MVP Demo (YouTube)](https://www.youtube.com/watch?v=7QmCUDHpOmE) — Exemplo histórico de como um MVP visual validou hipóteses complexas de mercado de forma ágil.
* 📖 **Artigo de Referência (Dispositivos Médicos):** McCaffery, Fergal et al. (2004). *A Software Process Development, Assessment and Improvement Framework for the Medical Device Industry*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 1: Introdução à Engenharia de Software &amp; Apresentação](../Aula_1/README.md)
* ➡️ **Próxima Aula:** [Aula 3:](../Aula_3/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
