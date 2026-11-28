# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 09/10/2026 | 📚 Professor: Flávio Seixas | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 07: Análise Qualitativa de Processos

### 📝 Introdução

Esta aula iniciou a fase de **análise** do ciclo de BPM, usando o modelo AS-IS para entender *por que* o processo tem desempenho abaixo do desejado. A análise qualitativa reúne técnicas que não dependem de medições precisas: classificação das etapas por valor agregado, identificação dos sete desperdícios, busca da causa-raiz (5 porquês e diagrama de causa e efeito), análise das partes interessadas e, por fim, o registro e a priorização dos problemas encontrados (Pareto e matriz PICK). O exemplo recorrente foi o **processo de aluguel de equipamento** de uma construtora.

---

### 💡 Conceitos Chave

* **Análise de Valor Agregado:** Cada etapa do processo é classificada em uma de três categorias:
  * **VA (valor agregado):** produz valor para o cliente. Critérios: o cliente pagaria por essa etapa? Concordaria que ela é necessária? Perceberia o produto menos valioso se ela fosse removida? (ex.: confirmar a data de entrega, entregar os produtos).
  * **BVA (valor agregado ao negócio):** necessária ou útil para o negócio funcionar, para coletar receita, reduzir riscos ou cumprir requisitos regulatórios (ex.: verificar o pedido de compra, verificar o crédito do cliente, emitir fatura, receber pagamento).
  * **NVA (sem valor agregado):** todo o resto: transferências, trocas de contexto, esperas, atrasos, retrabalho e correção de defeitos (ex.: encaminhar a ordem de compra ao depósito, reenviar confirmação).
* **Análise de Desperdício (Lean):** Inspirada em Taiichi Ohno, busca reduzir a linha do tempo entre o pedido do cliente e o recebimento do dinheiro eliminando desperdícios que não agregam valor.
* **Análise de Causa-Raiz:** Técnicas para ir dos sintomas às causas, com o objetivo de tratar a origem do problema e não apenas o efeito.
* **Análise das Partes Interessadas:** Coleta de dados por entrevistas com diferentes tipos de *stakeholders*, conciliando seus pontos de vista sobre o desempenho do processo.
* **Gestão dos Problemas:** Manter, organizar e priorizar as fraquezas percebidas do processo, que podem vir de uma demanda de modelagem, da melhoria contínua, da descoberta do processo ou da análise de valor/desperdício.

#### 🔍 Tópico em Destaque

**Os sete desperdícios aplicados a processos**

| Grupo | Desperdício | Descrição e exemplo |
| --- | --- | --- |
| **Mover** | **Transporte** | Enviar ou receber materiais/documentos como entrada ou saída do processo (ex.: aluno que baixa, assina e envia por correio o formulário de admissão) |
| **Mover** | **Movimentação** (*motion*) | Deslocamento interno de recursos, mais comum na manufatura (ex.: funcionário que circula pela organização coletando assinaturas) |
| **Reter** | **Inventário** | Materiais e trabalho em andamento (WIP) acumulados (ex.: ~3.000 inscrições tratadas simultaneamente) |
| **Reter** | **Espera** (*waiting*) | Tarefa aguardando recurso ou recurso ocioso (ex.: solicitação aguardando o aprovador) |
| **Excesso** | **Defeitos** | Erros que geram retrabalho (ex.: equipamento errado entregue e devolvido ao fornecedor) |
| **Excesso** | **Superprocessamento** (*over-processing*) | Tarefas desnecessárias ou perfeccionismo (ex.: aprovações de viagem rejeitadas ao final por falta de orçamento) |
| **Excesso** | **Superprodução** (*over-production*) | Instâncias desnecessárias de processo (ex.: 50% das cotações emitidas não geram pedido) |

**Aplicação no processo de aluguel de equipamento**

* **Transporte:** o engenheiro de obra envia o pedido ao funcionário, que repassa ao engenheiro responsável, que devolve ao funcionário (três *handoffs*).
* **Inventário:** equipamento mantido por mais tempo que o necessário.
* **Espera:** aguardar a disponibilidade do engenheiro para aprovar.
* **Defeitos:** equipamento indisponível (busca de alternativa) ou entregue incorretamente.
* **Superprocessamento:** pedido aprovado e depois cancelado pelo engenheiro de obra.
* **Superprodução:** equipamento alugado e nunca utilizado.

**Técnicas de causa-raiz**

* **5 Porquês:** Pergunta-se "por quê?" sucessivamente. Exemplo: engenheiros mantêm o equipamento por mais tempo → temem que não esteja disponível depois → o tempo entre pedido e entrega é longo → gasta-se muito tempo para achar o equipamento e aprovar a solicitação (contato sequencial com fornecedores e espera pela verificação do engenheiro).
* **Diagrama de Causa-Efeito (espinha de peixe):** Organiza as causas contribuintes de um problema em categorias, os **6 Ms**:

| Categoria | Fatores |
| --- | --- |
| **Equipamento** | Tecnologia: falta de funcionalidade, interface ruim, falta de integração entre sistemas |
| **Método** | Forma como o processo é projetado, entendido ou executado: responsabilidades e instruções pouco claras, treinamento insuficiente, falta de comunicação oportuna |
| **Material** | Dados de entrada ausentes, incorretos ou desatualizados |
| **Pessoa** | Falta de treinamento, de motivação ou exigências excessivas sobre os trabalhadores |
| **Medição** | Estimativas imprecisas e erros de cálculo |
| **Meio** | Fatores fora do escopo do processo: atrasos de atores externos, picos de carga |

**Partes interessadas e suas preocupações típicas**

| Parte interessada | Preocupação principal |
| --- | --- |
| **Clientes do processo** | Ciclo lento, defeitos, falta de transparência e de rastreabilidade |
| **Participantes do processo** | Alta utilização e estresse, defeitos vindos de *handoffs*, desperdícios |
| **Partes externas** (fornecedores, subcontratados) | Fluxo constante de trabalho, planejamento antecipado, cumprimento de contratos |
| **Dono do processo e gerentes operacionais** | Tempos de ciclo e processamento, defeitos, desperdícios e conformidade com políticas e regulamentos |
| **Patrocinador e executivos** | Alinhamento estratégico, contribuição para os KPIs e capacidade de adaptação ao mercado |

**Registro e priorização dos problemas**

* **Registro:** cada problema recebe nome, descrição, premissas, impacto qualitativo e impacto quantitativo. Exemplo: "equipamento mantido por mais tempo que o necessário" → 3.000 aluguéis por ano × 10% dos casos × 2 dias extras × custo de 100/dia = **60.000 por ano**.
* **Gráfico de Pareto:** barras ordenadas pelo impacto de cada problema, com curva de impacto percentual acumulado; ajuda a priorizar.
* **Matriz PICK:** priorização bidimensional (impacto × esforço) para decidir o que atacar primeiro.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Referência bibliográfica corrigida (atualização 2026.2):** Na 2ª edição de Dumas et al. (2018), a análise qualitativa é o **capítulo 6** (valor agregado, desperdícios, *stakeholders*, documentação de problemas e causa-raiz). O **capítulo 7** trata da análise quantitativa e é a base da Aula 08. A indicação corrige a divergência existente no calendário publicado.
>
> ⚠️ Os slides alternam a sigla de atividade sem valor entre **NVA** e **NAD**; ambas se referem à mesma categoria.

---

### 📚 Links & Leituras Complementares

* 📖 **DUMAS, M. et al. (2018).** *Fundamentals of Business Process Management*, 2ª edição, capítulo 6.
* 📖 **ABPMP BRASIL (2013).** *BPM CBOK V3.0*, capítulo 4.
* 📖 **ANTONY, J.; VINODH, S.; GIJO, E. V.** *Lean Six Sigma for Small and Medium Sized Enterprises*. CRC Press, capítulo 7.
* 📖 **PYZDEK, T.; KELLER, P. (2009).** *The Six Sigma Handbook*, 3ª edição. McGraw-Hill.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 06: Modelagem de Processos de Negócio com BPMN — Habilidades](../Aula_6/README.md)
* ➡️ **Próxima Aula:** [Aula 08: Análise Quantitativa de Processos](../Aula_8/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
