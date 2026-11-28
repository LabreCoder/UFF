# Resultados da Etapa 1: Achados e Perdidos UFF (UFFa)

Base: Relatório Consolidado de Pesquisa, com 5 entrevistados da equipe administrativa do Instituto de Computação (Praia Vermelha): Secretaria (P01–P03) e Portarias (P04–P05). Todos consentiram via TCLE, e as anotações foram feitas sob anonimato.

> **Atenção:** as respostas de P01 e P02 foram **inferidas** a partir de P03 (símbolo † no relatório). Citações literais só de P03, P04 e P05.

---

## 1. Personas

### Quantas e por quê: 3 personas

| # | Persona | Base nos dados |
|---|---|---|
| 1 | Atendente da Secretaria (o custodiante) | P01–P03 |
| 2 | Porteiro (a triagem) | P04–P05 |
| 3 | Aluno que perdeu um objeto (o dono) | **Hipótese**, sem entrevista direta ainda |

### Por que essas e não outras

- **Secretaria vira uma persona só.** P01, P02 e P03 têm o mesmo setor e a mesma rotina, e o próprio relatório inferiu P01 e P02 a partir de P03.
- **Portaria vira uma persona só.** P04 segura o item por cerca de 1h e P05 repassa de imediato, mas o objetivo e a dor são os mesmos. A diferença aparece como variação dentro da persona.
- **O aluno entra** porque é quem usa o sistema para recuperar o objeto. Sem o dono, o fluxo não fecha. Deve ser marcada como "baseada em relatos indiretos" até haver entrevistas com alunos.
- **Direção/Almoxarifado fica fora.** É stakeholder que só recebe o destino final (doação patrimonial), então entra no mapa de stakeholders.
- **Quem acha o objeto fica fora.** Não há dado sobre esse perfil. Pode virar 4ª persona se houver entrevistas com alunos.

---

## 2. Cenários-problema

| # | Cenário | Persona | Problema |
|---|---|---|---|
| C1 | Balcão cheio | Atendente | O item chega no meio da fila e recebe só uma fita com data e local. Não há registro, e o caderno foi abandonado. |
| C2 | Troca de turno | Aluno | Esquece algo em sala, e a sala é trancada. Precisa pedir à portaria que chame o zelador com as chaves. |
| C3 | Sem saber onde procurar | Aluno | O objeto passa da Portaria 02 para a 01 e depois para a Secretaria. O aluno não sabe onde perguntar e descreve o item oralmente. |
| C4 | Item que repassa sem rastro | Porteiro | Recebe o item, pergunta dados, repassa, e ninguém registra o caminho. |
| C5 | Retirada sem comprovante | Atendente / Aluno | A devolução depende de "reconhecer e detalhar". Não há termo de saída, e um erro não deixa evidência. |

---

## 3. Tarefas

**Atendente da Secretaria**
- Cadastrar item em até 3 cliques (foto rápida → categoria → local)
- Gerar etiqueta/QR code para substituir a fita manuscrita
- Registrar a retirada e gerar recibo de saída
- Delegar a custódia a um posto centralizador

**Porteiro**
- Cadastrar item rapidamente ao receber
- Emitir recibo de entrada
- Registrar o documento de quem retira

**Aluno**
- Navegar pelo catálogo público (apenas foto e categoria)
- Reivindicar um item
- Comprovar a posse
- Retirar o item

---

## 4. Tensões de design a considerar

- **Privacidade × validação de posse:** a interface pública mostra só categoria e foto genérica, e a área restrita exige matrícula/CPF na retirada.
- **Conflito de atribuições:** a Secretaria absorve a custódia sem ser seu papel formal, então o sistema não deve fixá-la como dona única do processo.
- **Troca de turno:** é o ponto crítico de perda de objetos.

## 5. Pendências

- [ ] Decidir: persona do aluno como hipótese ou entrevistar 1–2 alunos
- [ ] Decidir: Portaria como 1 persona ou 2 (P04 e P05)
- [ ] Conferir no relatório: P01 aparece como "Analista TI" no quadro e como "Secretaria" na codificação
- [ ] Tratar a retenção de ~6 meses como convenção informal do IC, não norma da UFF
