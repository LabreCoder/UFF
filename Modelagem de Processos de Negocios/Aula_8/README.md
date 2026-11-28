# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 16/10/2026 | 📚 Professor: Flávio Seixas | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 08: Análise Quantitativa de Processos

### 📝 Introdução

Esta aula complementou a análise qualitativa com **técnicas quantitativas** para medir o desempenho do processo em tempo, custo e qualidade. Foram vistos o cálculo do tempo de ciclo por **análise de fluxo**, a utilização de recursos, a relação entre trabalho em andamento e tempo de ciclo (**Lei de Little**), a **teoria de filas** e, por fim, a **simulação de processos**, que supera as limitações das técnicas anteriores. A aula fechou diferenciando *cycle time*, *lead time* e *takt time*.

---

### 💡 Conceitos Chave

* **Dimensões de Desempenho:** Tempo, qualidade e custo. A análise quantitativa combina o modelo do processo com o desempenho de cada atividade.
* **Tempo de Ciclo (*Cycle Time*):** Tempo entre o início e o término de uma instância do processo. É a soma do **tempo de processamento** (atividades de valor agregado) com o **tempo de espera** (atividades sem valor agregado).
* **Eficiência do Tempo de Ciclo:** `Tempo de processamento ÷ Tempo de ciclo`. Mostra a fração do tempo em que o processo está de fato agregando valor.
* **Utilização de Recurso:** `Tempo usado do recurso no processo ÷ Tempo disponível do recurso`. Uma utilização de 60% significa que, em média, o recurso fica ocioso 40% do tempo alocado.
* **Trabalho em Processo (WIP):** Número médio de casos iniciados e ainda não concluídos (ex.: pedidos ativos e não atendidos em um processo *order-to-cash*). É uma forma de desperdício.
* **Lei de Little:** `WIP = λ × Lead Time`, em que λ é a taxa de chegada de novos casos. Formulada por John Little (MIT) em 1961, correlaciona WIP e tempo de ciclo e mostra que reduzir o *lead time* reduz o WIP e, com ele, os custos.

#### 🔍 Tópico em Destaque

**1. Análise de fluxo: cálculo do tempo de ciclo (CT)**

| Estrutura | Fórmula | Exemplo da aula |
| --- | --- | --- |
| **Sequência** | `CT = T1 + T2 + … + Tn` | 10 + 20 = **30** |
| **Caminhos alternativos** (probabilidades p) | `CT = p1·T1 + p2·T2 + … + pn·Tn` | 10 + (20 + 10)/2 = **25** (50% cada) |
| **Caminhos paralelos** | `CT = max(T1, T2, …, Tn)` | 10 + 20 = **30** |
| **Laço** (probabilidade r de repetir) | `CT = T / (1 − r)` | 10 + 20/0,8 = **35** (20% de retorno) |

* **Exemplo combinado:** laço `1/0,8 = 1,25` + paralelo `max(1, 3) = 3` + sequência `3` + alternativo `0,6·1 + 0,4·2 = 1,4` → **8,65 dias**.
* **Eficiência:** com tempo de processamento de 8,9 horas, a eficiência do tempo de ciclo é de **12,9%**.
* A análise de fluxo também calcula custo médio por instância, número médio de execuções de cada atividade, carga unitária de cada tarefa, utilização por pool de recursos e a capacidade teórica do processo "como está".
* **Limitações:** nem tudo é representável de forma estruturada no modelo e a análise **não considera a taxa de chegada nem o número de recursos disponíveis** (mais chegadas com capacidade fixa geram contenção, filas maiores e tempos de ciclo maiores).

**2. Utilização de recurso × tempo de espera**

Em geral, quando a utilização passa de ~**90%**, o tempo de espera cresce de forma acentuada. Utilização próxima de 100% é insustentável, pois gera filas muito longas.

**3. Lei de Little na prática**

* **Exemplo da padaria:** chegam 10 clientes por hora (λ = 10) e cada um permanece 0,5 hora; logo, `L = 10 × 0,5 = 5` clientes dentro da padaria em média.
* **Cuidados:** unidades consistentes; taxa média de chegada igual à de partida; todo trabalho que entra é concluído e sai do sistema; quantidade e tempo do WIP consistentes.

**4. Análise de filas**

* Problemas de capacidade são comuns e fator-chave de redesenho: é preciso equilibrar o custo de ampliar a capacidade com os ganhos de produtividade e de serviço (ex.: sala de emergência de hospital com um ou dois médicos de plantão).
* Se as chegadas são regulares ou bem espaçadas, não há fila; a **variabilidade** nas chegadas e nos tempos de serviço é que gera interferência e espera.
* **Processo de Poisson:** modelo usual para chegadas; os tempos entre chegadas são independentes e exponenciais, `P(chegada < t) = 1 − e^(−λt)`, ou seja, a criação de um caso é independente dos demais.
* **Parâmetros:** λ (taxa média de chegada), μ (taxa média de serviço por servidor) e c (número de servidores). A partir deles se calculam a taxa de ocupação ρ, o tempo médio na fila (Wq), o tempo médio no sistema (W, o tempo de ciclo), o número médio na fila (Lq) e o número médio no sistema (L, o WIP).
* **Fila M/M/1:** um servidor, chegadas e atendimentos exponenciais, disciplina FIFO e `ρ = λ/μ` (demanda ÷ capacidade disponível).
* **Limitações:** analisa tempos de espera, mas não custo nem qualidade, e é adequada para **uma única atividade por pool de recursos**, não para processos ponta a ponta. A simulação resolve isso.

**5. Simulação de processos**

* Método versátil para análise do processo no estado atual e para análises hipotéticas (*what-if*): executa-se um grande número de instâncias, coletam-se dados de desempenho (custo, tempo, uso de recursos) e calculam-se estatísticas.
* **Etapas:** modelar o processo → definir o cenário de simulação → executar → analisar os resultados → repetir para cenários alternativos.
* **Elementos de um cenário:** tempos de processamento das atividades; probabilidades de ramificação condicional; taxa de chegada e sua distribuição (com calendário, ex.: segunda a sexta, 9h às 17h, ou 24/7); pools de recursos (nome, tamanho, custo por unidade de tempo e calendário); e atribuição das atividades aos pools.
* **Distribuições para tempos de atividade:** **fixa** (rara; ex.: tarefa executada por software), **normal** (atividades repetitivas, como verificar a operação de um aplicativo) e **exponencial** (atividades complexas com análise ou decisão, como avaliar um aplicativo).
* **Ferramentas:** ARIS, Bizagi Process Modeler, Signavio + BIMP, Oracle BPA, ProSim, entre outras. O **BIMP** aceita BPMN 2.0, usa formulário simples para o cenário e gera KPIs e *logs* em MXML importáveis no ProM (mineração de processos).
* **Armadilhas:** (1) **estocástica**: resultados variam entre execuções, então use período longo, várias execuções e intervalos de confiança; (2) **qualidade dos dados**: o resultado é tão confiável quanto a entrada, então valide simulando o cenário "como está" e comparando com observações reais; (3) **suposições simplificadoras**: o modelo é seguido à risca, sem desvios, multitarefa ou lotes, e recursos trabalham sem parar, sem cansaço ou distrações.

**6. *Cycle time* × *Lead time* × *Takt time***

| Conceito | Definição | Exemplo |
| --- | --- | --- |
| ***Cycle Time*** | Tempo para completar uma única iteração do processo | 5 minutos para montar cada unidade |
| ***Lead Time*** | Tempo total do início ao fim, incluindo esperas entre etapas | Pedido online entregue em 2 dias |
| ***Takt Time*** | Ritmo de produção necessário para atender à demanda: tempo disponível ÷ unidades demandadas | 8 h para 400 unidades = 1 unidade por minuto |

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Hipóteses quantitativas (atualização 2026.2):**
>
> * Toda estimativa deve declarar **unidade, janela de observação, população/amostra e hipóteses** do modelo.
> * **Médias isoladas ocultam variação**: distribuições, percentis e intervalos são mais informativos.
> * Resultados de fila e simulação devem ser **validados contra dados reais** e com análise de sensibilidade.
> * A Lei de Little só vale em **regime estável** e com unidades compatíveis.
>
> ⚠️ **Sobre a eficiência de 12,9%:** o slide compara 8,9 horas com 8,65 dias; o resultado só fecha considerando dias de trabalho de **8 horas** (8,65 × 8 = 69,2 h; 8,9 ÷ 69,2 ≈ 12,9%).

---

### 📚 Links & Leituras Complementares

* 📖 **DUMAS, M. et al. (2018).** *Fundamentals of Business Process Management*, 2ª edição, capítulo 7.
* 📖 **ABPMP BRASIL (2013).** *BPM CBOK V3.0*, capítulo 6.
* 📖 **HARMON, P. (2019).** *Business Process Change*, 4ª edição, capítulos 5 e 11.
* 📖 **PYZDEK, T.; KELLER, P. (2009).** *The Six Sigma Handbook*, 3ª edição, capítulos 3, 7 e 10.
* 🔗 [BIMP — simulador de processos BPMN](https://bimp.cs.ut.ee/)

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 07: Análise Qualitativa de Processos](../Aula_7/README.md)
* ➡️ **Próxima Aula:** [Aula 09: Redesenho e Melhoria de Processos de Negócio](../Aula_9/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
