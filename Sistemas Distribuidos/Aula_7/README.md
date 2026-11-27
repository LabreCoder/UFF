# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: [DD/MM/AAAA] | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 07: Replicação e Consistência

### 📝 Introdução

Esta aula trata de uma das questões centrais dos sistemas distribuídos: a **replicação de dados**, isto é, manter **várias cópias (réplicas)** do mesmo dado em máquinas diferentes. Replicamos por dois motivos: **aumentar a confiabilidade** (se uma cópia cai ou se corrompe, outra assume) e **melhorar o desempenho** (mais servidores dividem o trabalho e as cópias ficam mais perto de quem as usa).

O problema é que replicar cria uma nova dificuldade: **a consistência**. Toda vez que uma cópia é modificada, ela fica diferente das outras. A aula mostra que manter todas as cópias sempre iguais é caro, e por isso estuda:

1. **Modelos de consistência**, que são "contratos" entre os processos e o depósito de dados (consistência contínua, sequencial, causal, eventual e os modelos centrados no cliente);
2. **Ferramentas para ordenar eventos** sem relógio global (relógios físicos, NTP, relógios lógicos vetoriais);
3. **Gerenciamento de réplicas**: onde colocar servidores e conteúdo, o que propagar, quem toma a iniciativa;
4. **Protocolos de consistência**: backup primário (escrita remota e local) e escrita replicada por votação (quórum, ROWA).

Se você teve dificuldade, o caminho de estudo sugerido é: (1) entender o **dilema** (replicar ajuda, mas custa consistência); (2) entender que **consistência é um contrato com vários níveis de rigor**; (3) ver **como os protocolos** (primário/backup e quórum) cumprem esse contrato.

---

### 💡 Conceitos Chave

* **Réplica:** cópia de um dado (ou de um arquivo, banco etc.) mantida em outro servidor.
* **Confiabilidade:** capacidade de continuar funcionando mesmo com falhas. Replicar ajuda porque o trabalho continua se uma réplica cair e um dado corrompido pode ser detectado/corrigido (um valor correto pode ser retornado por no mínimo duas cópias).
* **Desempenho (escalabilidade):** replicar divide o trabalho entre vários servidores (**ampliação em quantidade**) e aproxima os dados de quem os usa, reduzindo o tempo de acesso (**ampliação geográfica**).
* **Consistência:** um conjunto de cópias é consistente se todas forem sempre iguais. Uma atualização em uma cópia precisa ser propagada para as demais.
* **Modelo de consistência:** é um **contrato** entre processos e depósito de dados: se os processos obedecerem a certas regras, o depósito promete funcionar de maneira correta.
* **Depósito de dados (data store):** pode ser memória compartilhada distribuída, banco de dados distribuído ou sistema de arquivos distribuído. Cada processo tem uma cópia local (ou próxima) e as escritas são propagadas para as outras cópias.
* **Consistência estrita:** uma leitura sempre retorna o valor escrito pela escrita **mais recente**. Exigiria um relógio global preciso, o que é impossível na prática.
* **Consistência contínua, sequencial, causal e eventual:** modelos mais flexíveis, explicados nos tópicos abaixo.
* **Relação "acontece antes" (`->`) e relógio lógico vetorial:** ferramentas para ordenar eventos por causalidade, sem depender de hora real.
* **Conit:** unidade em que a consistência contínua é medida (ex.: preço de uma ação na bolsa, temperatura em um relatório de clima).
* **Réplicas permanentes, iniciadas por servidor e iniciadas por cliente (cache):** os três tipos de réplica quanto ao posicionamento de conteúdo.
* **Protocolo de invalidação, replicação passiva (transferir estado) e replicação ativa (transferir operação):** as três formas de distribuir uma atualização.
* **Protocolos baseados em primário:** cada item `x` tem um primário que coordena as escritas (escrita remota ou local).
* **Quórum de leitura (NR) e de escrita (NW):** número mínimo de réplicas que precisam concordar para ler ou escrever (votação). Regras: `NR + NW > N` e `NW > N/2`.
* **ROWA (Read-One, Write-All):** caso particular com `NR = 1` e `NW = N`.

---

### 🔍 Tópicos em Destaque (na ordem dos slides)

#### 1. Por que replicar? Confiabilidade e desempenho

**Confiabilidade.** Se um sistema de arquivos é replicado, o trabalho continua mesmo que uma réplica caia. Além disso, há melhor proteção contra dados corrompidos: um valor correto pode ser retornado por no mínimo duas cópias.

**Desempenho.** Importante quando o sistema precisa crescer em quantidade e em área geográfica:

| Tipo de ampliação | Problema | Como a replicação ajuda |
|---|---|---|
| **Em quantidade** | Número cada vez maior de processos para um único servidor | Divide o trabalho do servidor centralizado, diminuindo o esforço de cada servidor |
| **Geográfica** | Clientes distantes demoram a acessar o dado | Cópias mais próximas dos processos reduzem o tempo de acesso, resolvendo o problema de escalabilidade |

**Dificuldades trazidas pela replicação:**

* **Gerenciamento de réplicas:** onde replicar? quando replicar?
* **Consistência entre as réplicas:** sempre que uma cópia é modificada, ela se torna diferente das restantes.

#### 2. Replicação como técnica de crescimento (o dilema)

* Suponha que um processo **P** acessa uma réplica **N** vezes por segundo e a réplica é atualizada **M** vezes por segundo. Se **N << M**, muitas versões da réplica nem serão vistas por P. Nesse caso vale avaliar se realmente é necessário instalar a réplica perto de P e se não há uma estratégia diferente para atualizá-la.
* Manter várias cópias consistentes **compromete o desempenho**: quando uma cópia é atualizada, a atualização precisa ser propagada para todas as outras. Em um sistema de larga escala isso exige **mais largura de banda** e **aumenta a latência** das atualizações.
* **O dilema:** replicação e cache amenizam problemas de escalabilidade, mas manter todas as cópias consistentes exige **sincronização global**, muito custosa. "A cura saiu pior que a doença?" Resposta do slide: **não, se pudermos relaxar as restrições de consistência**. Esse é o motivo de existirem os modelos mais fracos que veremos.

#### 3. Modelos de consistência centrados em dados

```
   Processo        Processo        Processo
      |               |               |
   [cópia local]   [cópia local]   [cópia local]
  ------------------------------------------------
          Depósito de dados distribuído
```

* Cada processo que acessa o depósito tem uma cópia local (ou próxima) do depósito inteiro; as escritas são propagadas às outras cópias.
* Um **modelo de consistência é um contrato**: se os processos seguirem as regras, o depósito funciona corretamente.
* **Consistência estrita:** se houvesse um relógio global, ordenaríamos as operações por *timestamp* e toda leitura devolveria a escrita mais recente. Mas **por que é impossível ter um relógio global preciso?** Veja os próximos tópicos.

#### 4. Relógios físicos e sincronização de relógios

* Todo computador tem circuitos que contam o tempo. Um **temporizador** é um **cristal de quartzo** lapidado que, sob tensão, oscila em uma frequência bem definida. Cada oscilação diminui uma unidade de um contador; quando o contador chega a zero, gera-se uma **interrupção** (um **ciclo do relógio**) e o contador reinicia. A cada ciclo soma-se uma unidade à hora armazenada, mantendo o relógio atualizado.
* A frequência do cristal é muito precisa, **mas não perfeita**: o erro relativo aproximado é de **10⁻⁵**.
* Em **um único computador** isso não é problema: todos os processadores usam o mesmo relógio e importam os horários **relativos**.
* Com **vários nós** é impossível garantir que todos os cristais funcionem exatamente na mesma frequência. A diferença entre os horários é a **defasagem de relógio** (*clock skew*). Como sincronizar os relógios entre si e com o tempo real?
* **NTP (Network Time Protocol):**
  1. A máquina envia uma mensagem ao **servidor de tempo** (máquina com receptor WWV ou relógio de precisão) perguntando a hora;
  2. O servidor responde o mais rápido possível com a hora corrente;
  3. Quem recebeu ajusta o próprio relógio.
* **O problema:** quando o servidor é contatado, os **atrasos das mensagens** fazem a hora recebida chegar desatualizada, e esses atrasos são **aleatórios e impossíveis de medir sem erro**.
* **Conclusão do slide:** como não dá para ter relógio global preciso, adotam-se **modelos de consistência mais flexíveis**: contínua, sequencial, causal e eventual (centrada no cliente).

#### 5. Consistência contínua

Em vez de "igual ou diferente", permite-se uma **divergência controlada** entre as réplicas. Há três tipos de desvio:

| Desvio | O que limita |
|---|---|
| **Em valores numéricos** | As cópias não podem variar mais que um valor absoluto ou relativo; ou o número de atualizações ainda não vistas por outras réplicas |
| **Em idade** | Há quanto tempo a réplica foi atualizada pela última vez |
| **Em operações de atualização** | Tolera ordenação diferente das atualizações nas réplicas: atualizações podem ser aplicadas temporariamente em uma cópia local, à espera de acordo global, e refeitas na ordem correta antes de se tornarem permanentes |

A **unidade de consistência** (onde essa medida é aplicada) é o **conit**. Exemplos do slide: o preço de uma ação na bolsa ou a temperatura em um relatório de clima.

#### 6. Ordenação consistente de operações e notação

* Alguns modelos tratam de **ordenar operações** de forma consistente em dados replicados. Ao confirmar atualizações provisórias, as réplicas precisam concordar em uma **ordenação global**. **Ordenação temporal não dá**, então se propõe uma **ordenação lógica**.
* **Notação usada nos exemplos:**
  * `Wi(x)a`: o processo **Pi escreve** o valor **a** no item de dado **x**.
  * `Ri(x)a`: o processo **Pi lê** o valor **a** do item de dado **x**.

#### 7. Consistência sequencial

* **Definição:** o resultado de qualquer execução é o mesmo que seria se as operações de leitura e escrita de **todos os processos** fossem executadas **em uma mesma ordem sequencial**.
* **Qualquer intercalação válida é aceita, mas todos os processos veem a mesma intercalação.** Nada é dito sobre o tempo e não há referência à "escrita mais recente".
* Em outras palavras: não importa **qual** ordem, importa que **todos enxerguem a mesma**.

**Exemplo dos slides (Figuras 7.6 e 7.7 do livro):** três processos concorrentes, cada um com 2 passos:

| P1 | P2 | P3 |
|---|---|---|
| `x ← 1;` `print(y, z);` | `y ← 1;` `print(x, z);` | `z ← 1;` `print(x, y);` |

A saída é a concatenação dos dois dígitos impressos por P1, P2 e P3. O slide mostra quatro sequências válidas de execução, com impressões `001011`, `101011`, `010111` e `111111`.

**Perguntas dos slides e respostas:**

| Pergunta | Resposta | Por quê (slides) |
|---|---|---|
| A saída final `000000` é válida? | **Não** | Só seria possível se os 3 executassem ao mesmo tempo, antes de todos os outros |
| P2 imprime `10` e P1 imprime `01`? | **Não** | P2 = `10` implica execução depois de P1 e antes de P3 (P1 -> P2 -> P3); P1 = `01` implica antes de P2 e depois de P3 (P3 -> P1 -> P2). Ordens incompatíveis |
| P2 e P3 imprimem `11` e P1 imprime `00`? | **Sim** | P1 (todo) -> P2 (`y=1`) -> P3 (`z=1`) -> prints de P2 e P3 |
| Quaisquer dois processos podem imprimir `00`? | **Não** | Dois processos diferentes teriam de ser o primeiro a executar |

#### 8. Ordenação lógica de eventos ("acontece antes")

Define-se a relação **acontece antes** (operador `->`):

1. Se **a** e **b** são eventos do **mesmo processo** e a ocorre antes de b: `a -> b`.
2. Se **a** é o **envio** de uma mensagem e **b** é o **recebimento** dela: `a -> b` (relação de **causalidade**).
3. **Transitividade:** se `a -> b` e `b -> c`, então `a -> c`.

Se **a** e **b** estão em processos diferentes **sem relação de causalidade**, nem `a -> b` nem `b -> a` são verdadeiros: os eventos são **concorrentes** (`a | b`).

**Exercício do slide (eventos A a K em 3 processos):** P1 tem A, B, C, D, K; P2 tem E, F, G; P3 tem H, I, J. As mensagens vão de B para F, de H para E, de G para D e de K para J.

```
P1:  A ---- B ---- C ---- D ---- K ----->
              \           ^        \
               v          |         v
P2:  ------- E ---- F ---- G         |
             ^      (B -> F chega em F)
P3:  H ------+----- I ----------- J <--+
     (H -> E)               (K -> J)
```

*(complemento: o desenho é só um esboço do diagrama do slide; vale o que está dito no texto: processos P1, P2 e P3, mensagens B->F, H->E, G->D e K->J.)*

Respostas do slide:

| Par | Relação | Caminho |
|---|---|---|
| A, B | `A -> B` | mesmo processo |
| B, F | `B -> F` | mensagem |
| H, J | `H -> J` | `H -> E -> F -> G -> D -> J` |
| H, G | `H -> G` | `H -> E -> F -> G` |
| F, J | `F -> J` | `F -> G -> D -> J` |
| A, F | `A -> F` | `A -> B -> F` |
| C, J | `C -> J` | `C -> K -> J` |
| C, F | `C \| F` | **concorrentes** |
| H, C | `H \| C` | **concorrentes** |

#### 9. Relógio lógico vetorial

É um mecanismo para **capturar causalidade potencial** sem usar hora real.

* Cada processo **Pi** mantém um **vetor VCi**:
  * `VCi[i]` = número de eventos ocorridos em Pi até agora (o relógio lógico local de Pi);
  * se `VCi[j] = k`, Pi sabe que **k eventos ocorreram em Pj** (Pi conhece o "tempo local" de Pj).
* A 1ª propriedade é mantida **incrementando `VCi[i]`** a cada evento em Pi. A 2ª é mantida por **"caronas"**: o vetor viaja junto com as mensagens.
* **Regras:**
  1. Evento **a** em Pi: `VCi[i] = VCi[i] + 1` e `ts(a) = VCi`.
  2. Pi **envia** mensagem m a Pj: `ts(m) = VCi`.
  3. Pj **recebe** m: para cada posição k, `Vj[k] = max{ Vj[k], ts(m)[k] }` (e conta o evento de recebimento, como mostra o exemplo do slide, a seguir).
* Assim, o receptor fica sabendo quantos eventos ocorreram nos outros processos antes de Pi enviar a mensagem.
* **Comparação:** `ts(a) < ts(b)` se, e somente se, para todo k `ts(a)[k] <= ts(b)[k]` e existe ao menos um índice k0 com `ts(a)[k0] < ts(b)[k0]`.
  * **Precedência** (`a -> b`): `ts(a) < ts(b)` é verdadeiro.
  * **Concorrência** (`a | b`): `ts(a) < ts(b)` é falso **e** `ts(b) < ts(a)` é falso.

**Exemplo do slide (mesmo diagrama dos eventos A a K, com 3 processos, vetores começando em (0,0,0)):**

| Processo | Evento: vetor |
|---|---|
| P1 | A: (1,0,0); B: (2,0,0); C: (3,0,0); D: (4,3,1); K: (5,3,1) |
| P2 | E: (0,1,1); F: (2,2,1); G: (2,3,1) |
| P3 | H: (0,0,1); I: (0,0,2); J: (5,3,3) |

Conferindo o evento **F** (recebimento da mensagem enviada em B): P2 estava com (0,1,1) e a mensagem trazia (2,0,0). Máximo posição a posição = (2,1,1); somando 1 na posição própria (P2) resulta em **(2,2,1)**. *(complemento: este passo a passo é só para você refazer a conta; os valores vêm do slide.)*

#### 10. Consistência causal

* É um **enfraquecimento da consistência sequencial**: distingue eventos **potencialmente relacionados por causalidade** dos que não são.
* Se o evento **b** é causado/influenciado por um evento anterior **a**, **todos** devem ver **primeiro a e depois b**.
* Exemplo do slide: se P1 escreve `x`, em seguida P2 **lê** `x` e escreve `y`, os dois primeiros eventos (a escrita de P1 e a leitura de P2) são causais, porém "as duas escritas são concorrentes". *(complemento: nos exemplos das figuras, a escrita de P2 só é considerada causalmente dependente da de P1 quando P2 **leu** o valor de P1 antes de escrever.)*
* **Regra:** escritas potencialmente relacionadas por causalidade devem ser vistas por **todos na mesma ordem**; **escritas concorrentes** podem ser vistas em **ordem diferente** em máquinas diferentes.
* **Relação com a sequencial:** se tem consistência sequencial, **também tem causal** (a recíproca não vale).

**Figura 7.8 (livro, nos slides):** sequência permitida em um depósito **causal**, mas **não sequencial**. P1 escreve `a` e depois `c`; P2 lê `a` e escreve `b`; P3 lê `a`, depois `c`, depois `b`; P4 lê `a`, depois `b`, depois `c`. Como `b` e `c` são concorrentes, P3 e P4 podem vê-las em ordens diferentes.

**Perguntas dos slides (é causal? é sequencial?):** existem dois cenários, **(a)** P1 escreve `a`, P2 lê `a` e escreve `b` (**b depende de a**, são causais) e **(b)** P1 escreve `a` e P2 escreve `b` sem ter lido `a` (**concorrentes**). Em cada cenário, avalia-se o que P3 e P4 leem:

| Leituras de P3 / P4 | Cenário (a): b depende de a | Cenário (b): a e b concorrentes |
|---|---|---|
| P3: `R(x)b R(x)a` / P4: `R(x)b R(x)a` | Nem causal nem sequencial (viola causalidade: viram b antes de a) | **Causal e sequencial** (todos veem a mesma ordem, b depois a) |
| P3: `R(x)a R(x)b` / P4: `R(x)a R(x)b` | **Causal e sequencial** | **Causal e sequencial** |
| P3: `R(x)a R(x)b` / P4: `R(x)b R(x)a` | Nem causal nem sequencial | **Causal, mas não sequencial** (ordens diferentes para escritas concorrentes) |

*(A tabela foi lida das cores dos slides 33 e 34, em que verde = vale e vermelho = não vale.)*

**Resumo da hierarquia:** sequencial ⊂ causal ⊂ (modelos mais fracos). Quanto mais fraco o modelo, mais barato, porém mais surpresas o usuário pode ver.

#### 11. Modelos de consistência centrados no cliente

Comparação com os centrados em dados:

| | Centrados em dados | Centrados no cliente |
|---|---|---|
| Objetivo | Visão consistente do depósito para todo o sistema | Consistência para **um cliente** |
| Concorrência | Processos podem atualizar o depósito simultaneamente | Depósitos caracterizados pela **ausência de atualizações simultâneas** |
| Operações típicas | Leitura e escrita | A maioria é **leitura** |
| Modelo | Mais forte | Mais fraco: **consistência eventual** |

* **Consistência eventual:** eventualmente, uma atualização será propagada para **todas** as réplicas.
* **O problema:** se o mesmo usuário opera sobre réplicas **diferentes** e a atualização ainda não chegou, ele vê inconsistências.
* **A solução barata:** garantir que o cliente **sempre acessa a mesma réplica** e que **só um processo escreve** em cada item `x`. Isso **oculta** a inconsistência global a baixo custo, mas **não há garantia para acessos concorrentes de clientes diferentes**.

#### 12. Os quatro modelos centrados no cliente

| Modelo | Garantia | Exemplo do slide |
|---|---|---|
| **Leituras monotônicas** | Se um processo leu o valor de `x`, qualquer leitura seguinte de `x` por ele retorna o **mesmo valor ou um mais recente**. Nunca "volta no tempo" | O processo viu `x` em `t` e nunca verá versão mais velha depois |
| **Escritas monotônicas** | Uma escrita de um processo em `x` é **concluída antes** de qualquer escrita seguinte do **mesmo processo** em `x` | Atualizar versões de bibliotecas substituindo uma ou mais funções |
| **Leia-suas-escritas** (*read your writes*) | O efeito de uma escrita do processo em `x` **sempre será visto** por uma leitura seguinte do mesmo processo | Contra-exemplo: atualizamos uma página no servidor, mas ao abri-la vemos a versão antiga (problema de cache) |
| **Escritas-seguem-leituras** | Uma escrita seguinte em `x` é feita sobre uma cópia **atualizada com o valor lido mais recentemente** pelo processo | Grupo de discussão: um usuário lê o artigo A e responde com B; B só é escrito em qualquer cópia **depois** de A ter sido escrito |

#### 13. Gerenciamento de réplicas

Duas perguntas distintas:

* **Posicionar servidores de réplicas:** é o **hardware**: encontrar os melhores locais para colocar um servidor que pode hospedar o depósito de dados (ou parte dele).
* **Posicionar conteúdo:** são os **dados e softwares**: encontrar o melhor servidor para colocar cada conteúdo.

**Posicionamento dos servidores.** É um **problema de otimização**: selecionar as **melhores K de N localizações**. Podem-se usar:

* heurísticas baseadas na **distância** (latência, largura de banda) entre clientes e locais; ou
* ignorar a posição dos clientes e ver a Internet como um conjunto de **Sistemas Autônomos (AS)**. Exemplo do slide: **CDN nos servidores do seu provedor de Internet**.

**Posicionamento do conteúdo.** Distinguem-se 3 tipos de réplicas organizadas logicamente:

| Tipo | Descrição |
|---|---|
| **Permanentes** | Conjunto fixo de réplicas, sempre existentes |
| **Iniciadas por servidor** | Criadas pelo servidor, por exemplo para atender a um **aumento temporário de demanda** |
| **Iniciadas por cliente** | Tipicamente chamadas de **cache**: armazenamento local usado por um cliente para guardar temporariamente uma cópia do que acabou de requisitar |

#### 14. Distribuição de conteúdo: o que propagar?

Uma questão importante de projeto é **o que enviar** às outras cópias: **só uma notificação**, **os dados (estado)** ou **a operação**.

| | Notificação (invalidação) | Transferir dados (estado) | Propagar a operação |
|---|---|---|---|
| **Também chamada** | Protocolo de invalidação | Replicação **passiva**, *backup*, *mirroring* | Replicação **ativa** |
| **O que vai pela rede** | Aviso de que o dado ficou inválido (os dados **não** são enviados) | O dado já modificado (várias modificações podem ir empacotadas numa só mensagem) | Operação e parâmetros necessários |
| **Largura de banda** | Muito pouca | Maior | Mínima (muitas vezes) |
| **Custo nas réplicas** | A cópia invalidada precisa ser atualizada antes do próximo uso, segundo o modelo de consistência | Baixo: recebe dado já processado | Pode exigir **maior capacidade de processamento** |
| **Quando usar** | Muitas atualizações e **pouca leitura** | Relação **leitura/escrita alta** (a atualização será realmente lida antes da próxima) | Quando se quer economizar banda |

#### 15. Quem toma a iniciativa de atualizar as cópias?

| Abordagem | Como funciona | Onde é comum / quando usar |
|---|---|---|
| **Baseada em envio** (*push*) | Atualizações são propagadas **sem que as réplicas peçam** | Entre réplicas permanentes e iniciadas por servidor (também em caches de clientes). Usada quando se precisa de **alto grau de consistência**: dados consistentes estão disponíveis imediatamente quando solicitados |
| **Baseada em recuperação** (*pull*) | Um servidor ou cliente **pede** a outro as atualizações que ele tiver no momento | Comum em **caches de clientes**: o cliente **sonda** o servidor para ver se é preciso atualizar |

#### 16. Protocolos de consistência baseados em primários

* Cada item de dado `x` tem um **primário** associado, responsável por **coordenar as escritas** em `x`.
* Se o primário é **fixo em um servidor remoto**: **protocolo de escrita remota**. Se o primário **se move** para o processo que quer escrever: **protocolo de escrita local**.
* Abordagem **simples e intuitiva** e que **garante consistência sequencial**.

**16.1 Backup primário (escrita remota)** (todas as escritas vão para um servidor fixo; leituras podem ser locais):

Mensagens da figura do slide (W = escrita, R = leitura):

| Passo | O que acontece |
|---|---|
| W1 | Cliente envia o pedido de escrita ao servidor ao qual está ligado |
| W2 | Esse servidor encaminha o pedido ao **primário** de `x` |
| W3 | O primário manda os **backups** atualizarem |
| W4 | Os backups confirmam a atualização ao primário |
| W5 | O primário confirma que a escrita foi concluída (de volta ao cliente) |
| R1 / R2 | Uma **leitura** é atendida **localmente**, em qualquer cópia, sem passar pelo primário |

1. O processo que quer escrever em `x` **encaminha** a operação ao primário de `x`.
2. O primário atualiza a **própria cópia** e **encaminha a atualização aos backups**.
3. Cada backup também atualiza e **envia confirmação** ao primário.
4. Quando **todos** os backups atualizaram, o primário **confirma ao processo inicial**, que informa o cliente.

* **Problema:** a escrita é **bloqueante** e portanto **muito demorada**.
* **Alternativa: escrita não bloqueante.** O cliente segue em frente logo após o primário ser atualizado, sem esperar as cópias. Exige cuidado para o cliente **não ler uma cópia antes de ela receber a sua própria escrita anterior**, o que seria **violação da consistência sequencial**.

**16.2 Protocolos de escrita local.** A **cópia primária migra** para o processo que quer escrever:

```
 W1: cliente pede escrita --> servidor local
 W2: item x é movido do primário antigo para o NOVO primário (o local)
 W3: novo primário confirma ao cliente que a escrita terminou
 W4: novo primário manda os backups atualizarem
 W5: backups confirmam a atualização
```

* Vantagem: **várias escritas seguidas** do mesmo processo são feitas **localmente**, enquanto os leitores continuam acessando sua cópia local.
* O ganho de desempenho só existe se a escrita for **não bloqueante**.

#### 17. Escrita replicada baseada em votação (quórum)

* As escritas podem ser feitas em **múltiplas réplicas** (não só em uma, como no backup primário).
* Ideia básica: o cliente **pede e obtém permissão de vários servidores** antes de ler ou escrever. Também **garante consistência sequencial**.

**Regra geral de votação (N réplicas):**

* Para **ler**: reunir um **quórum de leitura** de pelo menos **NR** servidores (quaisquer NR ou mais).
* Para **escrever**: reunir um **quórum de escrita** de pelo menos **NW** servidores.
* Restrições:

| Restrição | Evita |
|---|---|
| `NR + NW > N` | Conflitos **leitura-escrita** (todo quórum de leitura intersecta todo quórum de escrita, então a leitura vê pelo menos uma réplica atualizada) |
| `NW > N/2` | Conflitos **escrita-escrita** (dois quóruns de escrita sempre se sobrepõem, então não há duas escritas "vencendo" ao mesmo tempo) |

**Exemplo de escrita (slide):** o arquivo está replicado em N servidores. Para atualizar, o cliente contata **pelo menos metade mais um (maioria)** e obtém a concordância deles. Feita a atualização, um **novo número de versão** é associado ao arquivo, **o mesmo** para todas as cópias recém-atualizadas.

**Exemplo de leitura (slide):** o cliente contata pelo menos metade dos servidores e pede os **números de versão**. Se **todos forem iguais**, essa é a versão mais recente, porque uma tentativa de atualizar apenas os servidores restantes **falharia** por falta de servidores suficientes.

**Figura 7.32 do livro (slide 61), com N = 12 servidores (A a L):**

| Caso | NR | NW | Avaliação |
|---|---|---|---|
| (a) | 3 | 10 | **Escolha correta** de conjunto de leitura e escrita |
| (b) | 7 | 6 | Escolha que **pode levar a conflitos escrita-escrita** (NW = 6 não é maior que N/2 = 6) |
| (c) | 1 | 12 | **Correta**; é o **ROWA** |

#### 18. Read-One, Write-All (ROWA)

* `NR = 1` e `NW = N`. Confere: `NR + NW = 1 + N > N` e `NW = N > N/2`.
* **Vantagem:** leituras muito rápidas (pode-se ler **qualquer cópia**).
* **Custo:** toda **escrita** precisa atualizar **todas** as cópias.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Consistência é um contrato, não um defeito.** Modelos mais fracos existem porque a sincronização global custa banda e latência. Se o programa aceita as regras do modelo, o depósito "parece" sequencialmente consistente.
> ---
> 💡 **Sequencial não fala de tempo.** Basta que todos vejam a mesma ordem, qualquer que seja. Consistência estrita (escrita mais recente) é que exigiria relógio global.
> ---
> 💡 **Sequencial implica causal, mas não o contrário.** Na causal, só as escritas **relacionadas** têm ordem global; as **concorrentes** podem ser vistas em ordens diferentes.
> ---
> 💡 **Vetor: máximo + incremento.** Ao receber, pegue o máximo posição a posição e some 1 na sua própria posição. Dois eventos são concorrentes quando nenhum vetor é menor que o outro.
> ---
> 💡 **Quórum: duas contas decoram a regra.** `NR + NW > N` (leitura vê escrita) e `NW > N/2` (duas escritas não coexistem). Para muita leitura, use ROWA (`NR = 1`).
> ---
> 💡 **Backup primário com escrita não bloqueante é arriscado:** o cliente pode ler uma cópia ainda desatualizada e ver o próprio dado antigo, violando a consistência sequencial.
> ---
> 💡 **Centrado no cliente não resolve concorrência entre clientes diferentes.** Só oculta a inconsistência para o mesmo cliente (mesma réplica, um único escritor por item).

---

### 🧪 Exercícios e Gabarito Comentado

Resumo das 15 questões do arquivo `Aula07-gab.md`, com respostas em linguagem simples.

**1. Principal motivo para considerar modelos de consistência fracos.**
Os modelos fracos nascem da **necessidade de replicar para ganhar desempenho**. Uma replicação eficiente só é possível se evitarmos sincronizações globais, e isso se consegue **afrouxando as restrições de consistência**.

**2. Por que existe um "contrato" entre software e depósito de dados?**
Se um programa exige consistência sequencial e não aceita menos, o depósito precisa fornecê-la. Para ganhar desempenho, alguns sistemas oferecem um modelo mais fraco; então é essencial que o software **concorde em seguir as regras** desse modelo. Em geral, programas que seguem as regras enxergam algo que **parece** um depósito sequencialmente consistente.

**3. Na Fig. 7.7, a saída `001110` é legal para uma memória sequencialmente consistente?**
**Sim.** O gabarito diz que se obtém esse resultado se os processos rodam na ordem (a), (c), (b). *(complemento: conferindo pela saída, P1 imprime `00`, P2 imprime `11` e P3 imprime `10`. Uma ordem possível: P1 faz `x=1` e imprime `00`; P3 faz `z=1` e imprime `10`; P2 faz `y=1` e imprime `11`. Há uma ordem única consistente com o programa de cada processo, logo é válida.)*

**4. Arquivo replicado em 10 servidores: combinações (NR, NW) permitidas com `NR + NW` mínimo.**
Pelas regras, o mínimo de `NR + NW` é 11 (precisa ser maior que 10) e `NW > 5`. As combinações são **(1,10), (2,9), (3,8), (4,7), (5,6)**.

**5. Melhor combinação de NR e NW para N réplicas:**
* **(a) Consistência sequencial com maioria de leituras:** `NR = 1` e `NW = N`, ou seja, **ROWA** (leitura barata, escrita cara).
* **(b) Consistência sequencial com maioria de escritas:** gabarito: `NW = piso(N/2) + 1` (maioria) e `NR = N - NW`. *(complemento: pela regra do slide `NR + NW > N`, o NR precisa ser pelo menos `N - NW + 1`; por exemplo, N = 10 dá NW = 6 e NR = 5, como na questão 4. Vale confirmar essa diferença com o professor.)*
* **(c) Apenas escrita monotônica:** gabarito: `NW = piso(N/2) + 1` e `NR = 1`.

**6. Relógios vetoriais (4 processos, P1 a P4, eventos de a até u).**
O objetivo é preencher os vetores com as regras da seção "Relógio lógico vetorial": evento local soma 1 na posição própria; envio carrega o vetor; recebimento faz o máximo posição a posição e depois soma 1 na própria posição. Valores do gabarito:

| Processo | Eventos e vetores |
|---|---|
| P1 | a (1,0,0,0); b (2,1,0,0); c (3,1,0,0); d (4,1,0,0); e (5,5,1,2); f (6,5,5,4); g (7,5,5,4) |
| P2 | h (0,1,0,0); i (0,3,1,0); j (1,4,1,2); k (1,5,1,2); l (4,6,1,5) |
| P3 | m (0,0,1,0); n (0,3,2,0); o (4,3,4,4); p (4,3,5,4); q (7,5,6,4) |
| P4 | r (1,0,0,1); s (1,0,0,2); t (4,1,0,3); u (4,1,0,5) |

*(complemento: a organização por processo foi reconstruída a partir da figura, pois a tabela do gabarito vem quebrada em colunas. Conferi alguns valores à mão, como e = (5,5,1,2) a partir de d e do vetor de k, e f = (6,5,5,4) a partir de e e do vetor de p; para o conjunto completo, use a figura do gabarito como referência.)*

**7. Clientes em quantidade fixa, posição estática e geograficamente dispersos: que tipo de réplica usar?**
**Réplicas permanentes**, porque: (i) dão **baixa latência** (réplicas próximas aos clientes distantes); (ii) **balanceiam a carga** entre regiões, evitando sobrecarregar um servidor ou data center; (iii) **são estáveis**: como clientes e posições não mudam, compensa investir em réplicas de longa duração. Réplicas iniciadas por servidor ou por cliente são mais úteis com **mobilidade, clientes temporários ou padrões de acesso imprevisíveis**.

**8. Motivos para replicação de dados.**
**Confiabilidade** (sistema continua se uma réplica cair; proteção contra dados corrompidos, pois o valor correto pode vir de ao menos duas cópias) e **desempenho** (ampliação em quantidade, dividindo o trabalho do servidor central; ampliação geográfica, aproximando os dados de quem os usa e reduzindo o tempo de acesso).

**9. Compromisso entre manter cópias atualizadas e desempenho.**
Manter várias cópias consistentes **compromete o desempenho**: cada atualização deve ser propagada a todas as cópias, o que, em larga escala, **exige mais largura de banda** e **aumenta a latência** das atualizações.

**10. Quando manter consistência a qualquer custo não é viável e desperdiça recursos?**
Exemplo: **postagens em redes sociais** (milhões por minuto em plataformas globais como Facebook e Instagram). Se as réplicas não forem atualizadas na hora, nada catastrófico ocorre. Basta garantir que o cliente acesse sempre a mesma réplica (a mais próxima) para ter consistência centrada no cliente. O pior que acontece é **demorar mais para ver postagens de outros usuários**.

**11. Problema de sincronizar relógios com servidor de tempo (NTP).**
Ao contatar o servidor, os **atrasos nas mensagens** fazem a hora recebida chegar **desatualizada**; os atrasos são **aleatórios e impossíveis de medir sem erro**.

**12. O que é um modelo de consistência?**
É um **contrato entre processos e depósito de dados**: se os processos obedecerem a certas regras, o depósito promete funcionar corretamente.

**13. Os 4 modelos centrados no cliente.**
**Leituras monotônicas** (nunca ler versão mais velha do que a já lida), **escritas monotônicas** (uma escrita termina antes da próxima do mesmo processo), **leia-suas-escritas** (você sempre vê o efeito das suas escritas) e **escritas-seguem-leituras** (a escrita é feita sobre uma cópia que já contém o que você leu). Exemplos na seção "Os quatro modelos centrados no cliente".

**14. As 3 abordagens de distribuição de conteúdo.**
**(1) Notificação** (invalidação): só avisa que o dado ficou inválido; pouca banda; bom com muitas atualizações e poucas leituras. **(2) Transferir dados (estado):** envia o dado modificado, podendo empacotar várias modificações; bom quando a relação leitura/escrita é alta. **(3) Propagar a operação (replicação ativa):** envia a operação e seus parâmetros; custo mínimo de banda, mas a réplica pode precisar de mais processamento.

**15. Backup primário com escrita remota, resumidamente.**
Todas as escritas vão para **um servidor fixo** (primário) e as leituras podem ser locais. Passos: (1) o processo encaminha a escrita ao primário de `x`; (2) o primário atualiza sua cópia e envia a atualização aos backups; (3) cada backup atualiza e confirma ao primário; (4) quando todos confirmaram, o primário confirma ao processo inicial, que informa o cliente.

---

### 🧠 Perguntas de Revisão

1. **Quais são os dois motivos para replicar dados e qual é a dificuldade que isso cria?**
   Confiabilidade e desempenho. A dificuldade é manter as réplicas consistentes: cada atualização precisa ser propagada, custando banda e latência.
2. **Por que não basta usar um relógio global para ordenar as operações?**
   Porque é impossível ter um relógio global preciso: os cristais têm erro (cerca de 10⁻⁵), há defasagem entre os nós e a sincronização por NTP sofre com atrasos aleatórios de rede.
3. **Qual a diferença entre consistência sequencial e causal?**
   Na sequencial, todos veem a mesma ordem para **todas** as operações. Na causal, só as escritas relacionadas por causalidade precisam ter a mesma ordem; escritas concorrentes podem ser vistas em ordens diferentes. Sequencial implica causal.
4. **Como o relógio vetorial decide se dois eventos são concorrentes?**
   Compara os vetores posição a posição: se nenhum é menor que o outro (`ts(a) < ts(b)` e `ts(b) < ts(a)` são ambos falsos), os eventos são concorrentes.
5. **Cite os quatro modelos de consistência centrados no cliente e dê um exemplo de um deles.**
   Leituras monotônicas, escritas monotônicas, leia-suas-escritas, escritas-seguem-leituras. Exemplo: em um grupo de discussão, a resposta B só é escrita depois do artigo A (escritas-seguem-leituras).
6. **Quando usar protocolo de invalidação e quando usar transferência de dados?**
   Invalidação: muitas atualizações e poucas leituras (usa pouca banda). Transferência de dados: relação leitura/escrita alta, pois a atualização será lida antes da próxima.
7. **Quais são as duas restrições do voting e o que cada uma evita? Qual o caso ROWA?**
   `NR + NW > N` evita conflito leitura-escrita; `NW > N/2` evita conflito escrita-escrita. ROWA: `NR = 1`, `NW = N` (leitura rápida, escrita cara).
8. **Por que a escrita não bloqueante no backup primário pode violar a consistência sequencial?**
   Porque o cliente prossegue após o primário atualizar e pode ler uma cópia que ainda não recebeu a sua escrita anterior.

---

### 🔗 Conexão com o Trabalho Final

O trabalho da disciplina demonstra gRPC, REST, RabbitMQ e Apache Kafka. Esta aula se conecta principalmente aos dois últimos *(complemento, não está nos slides)*: no Kafka, as partições são replicadas em vários brokers, com uma réplica líder e seguidoras, o que lembra o **backup primário**; no RabbitMQ, filas replicadas (quorum queues) dependem de **maioria de nós**, o que lembra o **quórum** (`NW > N/2`). Em ambos, o equilíbrio entre confiabilidade, latência e consistência (inclusive **consistência eventual**) é o mesmo dilema discutido na aula.

---

### 📚 Links & Leituras Complementares

* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª Edição) — Capítulo 7 e Capítulo 6, seções 6.1 e 6.2
* 📖 *Distributed Systems: Principles and Paradigms* (Andrew S. Tanenbaum, 3ª Edição) — Capítulo 7 e Capítulo 6, seções 6.1 e 6.2
* 📄 Material da aula: `Aula07-sd-rep-cons.pdf` e gabarito `Aula07-gab.md`

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 6: Comunicação entre Processos — RPC, Mensagens, Filas (MOM), AMQP e RabbitMQ](../Aula_6/README.md)
* ➡️ **Próxima Aula:** [Aula 8: Tolerância a Falhas](../Aula_8/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
