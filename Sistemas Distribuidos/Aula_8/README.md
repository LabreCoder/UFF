# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: [DD/MM/AAAA] | 📚 Professor: Raphael Guerra | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 08: Tolerância a Falhas

### 📝 Introdução

A oitava aula trata de **tolerância a falhas** em sistemas distribuídos. Um sistema distribuído é formado por várias máquinas e processos, então é normal que **alguma parte falhe enquanto o resto continua funcionando**. A pergunta da aula é: como construir o sistema para que ele **continue funcionando de forma aceitável** e **se recupere sozinho** dessas falhas?

O roteiro (na ordem dos slides):

1. **Falha parcial**: o que diferencia um sistema distribuído de um sistema de uma só máquina.
2. **Objetivo e requisitos** de um sistema tolerante a falhas: confiabilidade, disponibilidade, proteção e capacidade de manutenção.
3. **Métricas**: MTTF, MTTR, MTBF e a fórmula da disponibilidade.
4. **Vocabulário**: defeito, erro e falha.
5. **Tipos de falha**: transiente, intermitente, permanente e a classificação por comportamento do servidor (queda, omissão, temporização, resposta).
6. **Recuperação**: retroativa (*backward*, com *checkpoints*) e para frente (*forward*).

> 🎯 **Ideia central:** não dá para impedir que falhas aconteçam. O objetivo é **detectar, mascarar e se recuperar** delas sem derrubar o sistema inteiro.

---

### 💡 Conceitos Chave

#### 1. Falha parcial: o que torna os sistemas distribuídos diferentes

* Uma característica que **distingue** sistemas distribuídos de sistemas de uma única máquina é a noção de **falha parcial**.
* A falha parcial acontece quando **um componente** do sistema distribuído falha. Ela pode **afetar a operação de alguns componentes e deixar outros completamente ilesos**.
* Em um sistema de uma máquina só, a falha é **quase sempre total**: afeta todos os componentes (se o computador cai, tudo cai).

```
 Máquina única:      [ A  B  C  D ]  --falha-->  tudo parado (falha total)

 Sistema distribuído:  [A]--[B]--[C]--[D]
                                 X  (C falhou)
                       A, B e D continuam funcionando (falha parcial)
```
*(ilustração de apoio, complemento)*

#### 2. Objetivo de um sistema distribuído e requisitos

* **Objetivo:** construir o sistema para que ele **se recupere automaticamente de falhas parciais sem afetar seriamente o desempenho global**.
* Sempre que ocorrer uma falha, o sistema deve **continuar funcionando de maneira aceitável enquanto se recupera**. Ou seja, deve ser **tolerante a falhas**.
* Para isso, quatro **requisitos** (propriedades a serem buscadas):

| Requisito | Pergunta que ele responde |
|---|---|
| **Confiabilidade** | O sistema funciona **continuamente, sem falhar**? |
| **Disponibilidade** | O sistema está **pronto para uso agora**? |
| **Proteção** (*safety*) | Se o sistema parar de funcionar corretamente, **algo catastrófico** acontece? |
| **Capacidade de manutenção** | É **fácil consertar** o sistema depois que ele falhou? |

#### 3. Confiabilidade e MTTF

* **Confiabilidade** é a propriedade de o sistema **funcionar continuamente sem falhas**. Um sistema de alta confiabilidade continua executando **sem interrupção por um longo período**.
* **Métrica:** **MTTF** (*Mean Time to Failure*, tempo médio até falhar). Quanto maior o MTTF, mais confiável.

#### 4. Disponibilidade, MTTR e MTBF

* **Disponibilidade** é a **probabilidade de o sistema estar pronto para ser usado imediatamente**.
* É a razão entre o tempo médio até falhar e o tempo médio entre falhas:

```
 Disponibilidade = MTTF / MTBF            onde   MTBF = MTTF + MTTR
```

| Sigla | Nome | Significado |
|---|---|---|
| **MTTF** | *Mean Time to Failure* | Tempo médio **até** o sistema falhar (funcionando) |
| **MTTR** | *Mean Time To Repair* | Tempo médio **para reparar** (sistema fora do ar) |
| **MTBF** | *Mean Time Between Failures* | Tempo médio **entre** duas falhas (MTTF + MTTR) |

Linha do tempo do slide:

```
     falha            reinício                       falha
       |-----MTTR-------|---------MTTF-----------------|
       |------------------------MTBF-------------------|
```

* Depois da falha, o sistema fica parado durante o **MTTR** (reparo) até o **reinício**; então roda por um tempo **MTTF** até falhar de novo. O ciclo completo é o **MTBF**.
* **Exemplo numérico** *(complemento, números inventados só para treinar a fórmula)*: se MTTF = 99 h e MTTR = 1 h, então MTBF = 100 h e disponibilidade = 99/100 = **99%**.
* Observação importante: **reduzir o MTTR (consertar mais rápido) aumenta a disponibilidade**, mesmo sem mudar o MTTF.

#### 5. Confiabilidade x disponibilidade (não são a mesma coisa)

Os slides dão dois exemplos extremos:

| Sistema | Confiabilidade | Disponibilidade |
|---|---|---|
| Fica fora do ar **1 milissegundo a cada hora** | **Muito baixa** (cai o tempo todo) | **Altíssima**: slide diz "mais de 99,99999%" |
| **Nunca cai**, mas é desligado por **duas semanas por ano** | **Alta** | Apenas **96%** |

> ⚠️ Conferindo as contas *(complemento)*: 1 ms por hora é 1/3.600.000 de indisponibilidade, ou seja, cerca de 99,99997% de disponibilidade. Duas semanas em 52 semanas dão cerca de 3,8% de indisponibilidade, ou cerca de 96%. A ideia do slide permanece: o valor exato do primeiro caso é menos importante que a conclusão.

**Como lembrar:** confiabilidade fala de **quanto tempo seguido** funciona sem falhar; disponibilidade fala de **que fração do tempo total** está funcionando.

#### 6. Proteção e capacidade de manutenção

* **Proteção (*safety*):** refere-se à situação em que, se o sistema deixar de funcionar corretamente por algum tempo, **nada catastrófico acontece**. Pense na diferença entre um site de notícias fora do ar e o sistema de controle de uma usina *(exemplo, complemento)*.
* **Capacidade de manutenção:** a facilidade com que um sistema que falhou pode ser **consertado**. Sistemas com alta capacidade de manutenção também podem ter alta disponibilidade, especialmente se as falhas puderem ser **detectadas e reparadas automaticamente**.

#### 7. Defeito x Erro x Falha

Esta distinção é muito cobrada. A cadeia causal é **falha → erro → defeito**:

| Termo | Definição do slide | Exemplo do slide |
|---|---|---|
| **Falha** (*fault*) | É a **causa** de um erro | Um meio de transmissão ruim ou errado que pode danificar pacotes |
| **Erro** (*error*) | **Estado incorreto** do sistema gerado por uma falha | Pacotes danificados transmitidos |
| **Defeito** (*failure*) | O sistema **não consegue cumprir suas promessas** | O serviço entrega dados errados ou não entrega |

* Falhas **fáceis de reconhecer**: um meio de transmissão ruim (basta trocá-lo).
* Falhas **difíceis de remover**: erros de transmissão causados por **más condições atmosféricas**.

```
  FALHA (causa)  ---->  ERRO (estado incorreto)  ---->  DEFEITO (promessa não cumprida)
  cabo ruim             pacotes danificados             serviço indisponível/incorreto
```
*(o terceiro quadro é complemento, deduzido da definição de defeito)*

> ⚠️ **Cuidado com a tradução:** em inglês são *fault* (falha), *error* (erro) e *failure* (defeito). Em português, "falha" é usada informalmente para tudo. Nesta aula, **falha = causa**, **erro = estado incorreto**, **defeito = serviço não cumprido**. Note que o título da aula, "Tolerância a **Falhas**", usa o sentido de *fault*.

#### 8. Tipos de falhas

##### 8.1 Por duração/comportamento no tempo

| Tipo | Como se comporta | Observação |
|---|---|---|
| **Transiente** | Ocorre **uma vez e desaparece**. Se a operação for repetida, a falha **não acontece de novo**. | Repetir a operação (*retry*) resolve *(complemento)* |
| **Intermitente** | Ocorre, **para por um período indeterminado, reaparece**, e assim por diante. | **Difícil de diagnosticar** |
| **Permanente** | **Continua existindo até que o componente faltoso seja substituído**. | Exige reparo ou troca |

##### 8.2 Por comportamento do servidor (tabela do slide)

| Tipo de falha | Descrição |
|---|---|
| **Falha por queda** (*crash*) | O servidor **para de funcionar**, mas estava funcionando corretamente até parar. |
| **Falha por omissão** | O servidor **não consegue responder a requisições** que chegam. |
| ↳ *Omissão de recebimento* | O servidor não consegue **receber** as mensagens que chegam. |
| ↳ *Omissão de envio* | O servidor não consegue **enviar** mensagens. |
| **Falha de temporização** | A resposta do servidor está **fora do intervalo de tempo** esperado. |
| **Falha de resposta** | A **resposta do servidor está incorreta**. |
| ↳ *Falha de valor* | O **valor** da resposta está errado. |
| ↳ *Falha de transição de estado* | O servidor **se desvia do fluxo de controle correto**. |

**Dica para memorizar:** pense no que o cliente observa.

* Queda: silêncio total depois de funcionar bem.
* Omissão: algumas mensagens somem (não entram ou não saem).
* Temporização: a resposta vem, mas **tarde demais** (ou cedo demais).
* Resposta: a resposta vem **no tempo certo, mas errada** (valor errado, ou o servidor faz algo fora do fluxo correto).

#### 9. Recuperação

* Quando ocorre uma falha, **não basta identificá-la**: é preciso **recuperar-se e voltar a um estado correto**.
* Existem **duas maneiras** principais:

| | **Retroativa** (*Backward Recovery*) | **Para frente** (*Forward Recovery*) |
|---|---|---|
| Ideia | **Volta para um estado anterior** à falha | Leva o sistema a um **novo estado correto** e continua |
| Precisa de | Gravar o estado de tempos em tempos (**checkpoints**) | Saber **de antemão quais erros podem ocorrer** e como corrigi-los |
| Limitação | Às vezes **não é possível** voltar a um estado sem erros | Só funciona para erros previstos |

##### 9.1 Recuperação retroativa (*Backward Recovery*)

* Retorna o sistema a um **estado que antes estava correto** e continua a execução depois da recuperação.
* É preciso **gravar o estado do sistema de tempos em tempos**: o chamado **ponto de verificação** (***checkpointing***).
* Quando ocorre falha, o estado é **restaurado para o momento do último ponto de verificação**.
* Checkpoints podem ser **mecanismos caros ou tão simples quanto *logs***.
* **Em alguns casos não é possível** voltar a um estado sem erros (por exemplo, quando efeitos já saíram para o mundo externo) *(exemplo, complemento)*.

```
 tempo ---->
  CP1 -------- CP2 ----------- CP3 ---- X (falha)
                                 ^------- restaura o estado do CP3 e retoma
```
*(ilustração de apoio, complemento)*

##### 9.2 Recuperação para frente (*Forward Recovery*)

* Em vez de voltar, **tenta-se levar o sistema para um novo estado correto**.
* É preciso **conhecer de antemão quais erros podem ocorrer**.
* Conhecendo **todos** os erros e como levar o sistema a um estado correto, é possível **recuperar totalmente** o sistema.
* Exemplo clássico *(complemento)*: códigos de correção de erros, que reconstroem o dado correto a partir de informação redundante, sem precisar retransmitir.

---

### 🔍 Tópico em Destaque: Confiabilidade x Disponibilidade e as métricas MTTF/MTTR/MTBF

Este é o ponto mais "de prova" da aula, porque junta definição e conta:

* **Confiabilidade** = quanto tempo o sistema funciona **sem interrupção** → medida por **MTTF**.
* **Disponibilidade** = fração do tempo em que o sistema está **pronto para uso** → **MTTF / MTBF**, com **MTBF = MTTF + MTTR**.
* Um sistema pode ter **alta disponibilidade e baixa confiabilidade** (cai por 1 ms a cada hora, mas volta instantaneamente) e o contrário (**alta confiabilidade e disponibilidade menor**: nunca cai, mas passa duas semanas por ano desligado, ou seja, 96%).
* Para aumentar a disponibilidade: aumentar o MTTF (falhar menos) **ou** diminuir o MTTR (consertar mais rápido, de preferência automaticamente).

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Falha parcial é o ponto de partida:** a tolerância a falhas só faz sentido em sistemas distribuídos porque as partes podem falhar **independentemente**. Em uma máquina só, a falha costuma ser total.

> 💡 **Falha, erro e defeito não são sinônimos:** a falha (causa) gera um erro (estado incorreto) que pode levar a um defeito (serviço não cumprido). Tolerar falhas é impedir que a falha vire defeito.

> 💡 **Qual falha é mais difícil?** Pela tabela da aula, as intermitentes são "difíceis de diagnosticar", e falhas de resposta (resposta errada) são mais difíceis de detectar que uma queda, pois o servidor continua "respondendo" *(a segunda parte é complemento)*.

> 💡 **Backward x forward:** backward = voltar ao último estado bom (precisa de *checkpoints*/logs); forward = seguir para um novo estado bom (precisa conhecer os erros possíveis).

---

### 🧠 Perguntas de Revisão

1. **O que é falha parcial e por que ela diferencia um sistema distribuído de um sistema de uma máquina?** É a falha de apenas um componente, deixando outros funcionando. Em uma máquina só a falha costuma ser total.
2. **Quais são os quatro requisitos de um sistema tolerante a falhas?** Confiabilidade, disponibilidade, proteção e capacidade de manutenção.
3. **Como se calcula a disponibilidade?** Disponibilidade = MTTF / MTBF, com MTBF = MTTF + MTTR.
4. **Dê um exemplo de sistema com alta disponibilidade e baixa confiabilidade.** Um sistema que fica fora do ar 1 ms a cada hora: quase sempre disponível, mas falha o tempo todo.
5. **Diferencie falha, erro e defeito.** Falha é a causa (ex.: meio de transmissão ruim); erro é o estado incorreto resultante (pacotes danificados); defeito é o sistema não cumprir suas promessas.
6. **Qual a diferença entre falha transiente, intermitente e permanente?** Transiente ocorre uma vez e some; intermitente vai e volta e é difícil de diagnosticar; permanente dura até o componente ser substituído.
7. **Diferencie falha por queda, por omissão, de temporização e de resposta.** Queda: o servidor para. Omissão: não recebe ou não envia mensagens. Temporização: responde fora do tempo. Resposta: responde errado (valor errado ou fluxo de controle incorreto).
8. **Como funcionam as recuperações retroativa e para frente?** A retroativa restaura o último *checkpoint* (estado anterior correto); a para frente leva o sistema a um novo estado correto, mas exige conhecer de antemão os erros possíveis.

---

### 🔗 Conexão com o Trabalho Final

*(complemento; a conexão não aparece nos slides)* Os quatro protocolos do trabalho lidam com falhas parciais de formas diferentes. Em **gRPC e REST**, uma chamada pode sofrer falha de temporização ou queda do servidor, e o cliente pode tentar de novo (falha transiente). Em **RabbitMQ e Kafka**, o broker ajuda a tolerar a queda de consumidores e produtores, pois as mensagens ficam guardadas até serem processadas. Vale usar o vocabulário da aula (tipos de falha, MTTR, disponibilidade) ao demonstrar o comportamento dos protocolos quando um componente cai.

---

### 📚 Links & Leituras Complementares

* 📖 *Sistemas Distribuídos: Princípios e Paradigmas* (Andrew S. Tanenbaum, 2ª Edição) — Capítulo 8, Seções 8.1 e 8.6
* 📖 *Distributed Systems: Principles and Paradigms* (Andrew S. Tanenbaum, 3ª Edição) — Capítulo 8, Seções 8.1 e 8.6

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 7: Replicação e Consistência](../Aula_7/README.md)
* ➡️ **Próxima Aula:** *Aula 9 ainda não disponível*

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
