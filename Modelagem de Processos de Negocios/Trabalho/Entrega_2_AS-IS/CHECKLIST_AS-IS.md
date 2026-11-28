# CHECKLIST — Mapeamento AS-IS (Contratação de Novo Colaborador)

## Antes de desenhar os BPMNs
- [ ] Confirmar com o RH se a TI devolve o chamado quando faltam dados
- [ ] Confirmar os cargos exatos do dono e do sponsor do macro processo
- [ ] Confirmar o nome de cada raia e pool com a nomenclatura usada na empresa (de forma genérica)

## Ao desenhar (todos os BPDs)
- [ ] Um evento de início e ao menos um evento de fim por pool
- [ ] Pools externos como caixa preta, ligados por fluxos de mensagem (linha tracejada)
- [ ] Gateways exclusivos com todas as saídas rotuladas
- [ ] Gateway paralelo de junção sempre pareado com o de divisão
- [ ] Nomes de tarefas no formato verbo + objeto
- [ ] Nenhum fluxo de sequência cruzando pools

## Específico de cada BPD
- [ ] **Área solicitante:** pool com uma raia (Gestor); mensagens para o RH (solicitação) e para/da TI (consulta e resposta)
- [ ] **RH:** pool com uma raia (Analista de RH); subprocesso recolhido "Processo seletivo"; mensagens para a TI (chamado e foto) e da TI (aviso)
- [ ] **TI:** pool único com duas raias (Analista de Infraestrutura e Assistente de Suporte de TI)
- [ ] **TI:** 22 elementos da tabela do README representados na mesma numeração
- [ ] **TI:** ramo A (foto e assinatura) em paralelo ao ramo B (máquina), com junção antes do aviso ao RH
- [ ] **TI:** objetos de dados (chamado, termo) e repositório (sistema documental) incluídos
- [ ] **TI:** fluxos de mensagem: RH→1, 4→Área solicitante, Área solicitante→5, RH→11, 18↔Novo colaborador, 22→RH

## Modelos
- [ ] Modelo descritivo dos três processos revisado
- [ ] Modelo analítico (qualitativo) dos três processos revisado; itens marcados como hipótese apresentados como hipótese

## Sigilo
- [ ] Nada de nomes de sistemas internos, pessoas ou dados sensíveis da empresa
- [ ] Termos genéricos mantidos ("aplicativos padrão", "demais ajustes")
