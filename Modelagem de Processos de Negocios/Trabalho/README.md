# 📊 Trabalho Prático: Mapeamento de Processos de Negócio

Trabalho em grupo da disciplina **Modelagem de Processos de Negócio** (UFF, Sistemas de Informação, Prof. Flávio Seixas, 2026.2).

**Grupo:** João Victor Labre · Luiz Miguel Vianna · Felipe Giron

**Tema:** formatação e entrega de computador a um novo colaborador, um processo de TI do dia a dia dentro do macro processo **Contratação de novo colaborador**.

---

## 🎯 Objetivo

Percorrer o ciclo de BPM em três entregas: escolher e delimitar um processo real, mapeá-lo como ele é hoje (**AS-IS**) e, por fim, analisá-lo e redesenhá-lo (**TO-BE**), usando BPMN 2.0.

---

## 🗂️ Estrutura

```text
Trabalho/
├── 00_Enunciado/        → modelos de apresentação fornecidos pelo professor
├── Entrega_1_Tema/      → apresentação do tema
├── Entrega_2_AS-IS/     → mapeamento do estado atual
└── Entrega_3_TO-BE/     → análise qualitativa e redesenho
```

| Entrega | Foco | Conteúdo | Arquivos principais |
| --- | --- | --- | --- |
| **1. Tema** | Problema, escopo do processo, estrutura preliminar e estratégia de descoberta | Escolha do processo de provisionamento de máquina, dono, papéis e fontes de informação | [PDF](./Entrega_1_Tema/Apresentacao_Tema.pdf) · [PPTX](./Entrega_1_Tema/Apresentacao_Tema.pptx) |
| **2. AS-IS** | Mapeamento do estado atual | Macro processo ampliado em três processos: **Área solicitante** (gerencial), **RH** (principal) e **TI** (principal), cada um em BPMN | [PDF](./Entrega_2_AS-IS/Apresentacao_AS-IS_Contratacao_Novo_Colaborador.pdf) · [BPMN](./Entrega_2_AS-IS/bpmn/AS-IS_Contratacao_Novo_Colaborador.bpmn) · [Imagens](./Entrega_2_AS-IS/imagens/) |
| **3. TO-BE** | Análise qualitativa e redesenho | Redesenho do **Processo 03 (TI)** com base nas Aulas 07 e 09 | [Análise](./Entrega_3_TO-BE/ANALISE_TO-BE.md) · [BPMN](./Entrega_3_TO-BE/bpmn/TO-BE_P3_Provisionamento_TI.bpmn) · [Slides](./Entrega_3_TO-BE/imagens/) |

> 🔒 Dados internos da empresa foram tratados de forma genérica, sem nomes de pessoas, sistemas ou informações sensíveis.

---

## 🔄 Resumo por entrega

### Entrega 1: Tema
O processo de TI foi escolhido porque o procedimento (POP) está desatualizado e parte da execução depende do conhecimento tácito do analista. A entrega define o fim a fim, o evento de início e de término, o cliente, o dono do processo e a estratégia de descoberta (analista de infraestrutura e gerente de TI como especialistas).

### Entrega 2: AS-IS
O escopo foi ampliado do processo de TI para o macro processo de contratação, mostrando as passagens entre as três áreas. Entregou-se o diagrama BPMN completo, uma imagem de cada processo e os comentários finais (lições aprendidas, dificuldades e contribuições).

Pastas de apoio:
- `rascunhos/`: versões anteriores do AS-IS (somente TI e sem a Diretoria).
- `NOTAS_AS-IS.md` e `CHECKLIST_AS-IS.md`: notas de trabalho de uma fase antiga, mantidas só como histórico. **A referência oficial é a apresentação e o BPMN final.**

### Entrega 3: TO-BE
Foco no Processo 03 (TI), que concentra as esperas do AS-IS.

- **Análise qualitativa (Aula 07):** valor agregado (7 de 21 elementos são NVA), desperdícios, 5 porquês e matriz PICK.
- **Heurísticas (Aula 09):** resequenciamento, eliminação de contatos, *knock-out*, paralelismo e padronização do POP.
- **Principais mudanças:**
  1. Chamado já traz perfil de acessos e foto.
  2. Conferência de completude na triagem.
  3. Acessos e máquina em paralelo logo após a triagem.
  4. RH avisado assim que usuário, e-mail e assinatura existem.
  5. Preparação da máquina segue o POP atualizado.
- **Resultado:** as trocas de mensagem no caminho normal caem de 8 para 4 e deixa de haver espera por outras áreas. A análise é qualitativa, pois não há dados de tempo levantados.

---

## 🛠️ Ferramentas

* **BPMN 2.0:** diagramas abertos em modelador BPMN (os arquivos `.bpmn` são editáveis).
* **Apresentações:** PowerPoint e PDF.
* **Referências da disciplina:** Aulas [4](../Aula_4/README.md) (descoberta), [5](../Aula_5/README.md) e [6](../Aula_6/README.md) (BPMN), [7](../Aula_7/README.md) (análise qualitativa), [9](../Aula_9/README.md) (redesenho) e [10](../Aula_10/README.md) (monitoramento).

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
