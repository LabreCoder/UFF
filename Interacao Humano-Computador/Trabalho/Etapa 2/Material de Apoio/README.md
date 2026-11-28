# UFFa — Achados e Perdidos UFF (Grupo G1 • IHC)

Projeto da disciplina de Interação Humano-Computador (UFF), Profª Daniela Gorski Trevisan.

O site do grupo existe em dois lugares: **Figma** e **localhost**. Ele passa a ter **duas seções**, uma por etapa de entrega.

| Seção | Status | O que contém |
|---|---|---|
| **Etapa 1** | Concluída e congelada | Tudo que já foi construído para a primeira entrega |
| **Etapa 2** | Em construção | O conteúdo novo que vamos produzir daqui para frente |

---

## Instrução para o Claude (copie e cole no início da conversa)

```text
CONTEXTO DO PROJETO
Estamos no projeto "Achados e Perdidos UFF" (UFFa), disciplina de IHC, grupo G1.

ETAPA 1 (ENCERRADA)
Todos os comandos e pedidos anteriores desta conversa se referem à entrega da Etapa 1.
Isso inclui: pesquisa desk (matriz CSD), análise competitiva, mapa de empatia,
entrevistas, relatório consolidado de pesquisa, personas, cenários-problema e tarefas.
A Etapa 1 está pronta e deve ser tratada como FINALIZADA.

ETAPA 2 (INÍCIO AGORA)
A partir de agora começamos a preparar a entrega da Etapa 2.
Qualquer pedido novo se refere à Etapa 2, a menos que eu diga explicitamente o contrário.

ESTRUTURA DO SITE (Figma e localhost)
O site terá duas seções de navegação:
1. "Etapa 1": ao clicar, mostra exatamente o que já está construído,
   SEM NENHUMA ALTERAÇÃO (conteúdo, layout, textos e links idênticos ao atual).
2. "Etapa 2": ao clicar, leva ao conteúdo novo que ainda vamos construir.
   Por enquanto pode ser uma página/frame vazio ou com placeholder.

REGRAS
- NÃO modifique, mova, renomeie nem reescreva nada da Etapa 1.
- Todo trabalho novo entra somente na seção Etapa 2.
- A navegação entre Etapa 1 e Etapa 2 deve funcionar em ambos os ambientes
  (Figma e localhost) e se manter consistente entre eles.
- Se uma decisão de arquitetura ou estrutura for necessária (rotas, organização de
  pastas, páginas do Figma, como congelar a Etapa 1), me pergunte antes de decidir.
- Antes de escrever código, explique o conceito e a abordagem.
- Ao entregar arquivos, inclua um CHECKLIST.md de integração.
```

---

## Estrutura proposta

```text
Site UFFa
├── Home / navegação  → botões "Etapa 1" e "Etapa 2"
├── /etapa-1          → conteúdo atual, intocado (ver resultados-etapa-1.md)
└── /etapa-2          → nova construção (vazia por enquanto)
```

- **Figma:** uma página (ou seção de frames) para cada etapa, com protótipo ligando os botões de navegação.
- **Localhost:** uma rota para cada etapa, com o conteúdo atual movido para `/etapa-1` sem edição de conteúdo.

## Decisões que ainda precisam ser tomadas pelo grupo

1. **Como congelar a Etapa 1:** tag/branch no Git, cópia da pasta ou duplicação da página no Figma.
2. **Home:** criar uma tela inicial com os dois botões ou usar um menu fixo no topo.
3. **Rotas:** `/etapa-1` e `/etapa-2`, ou outro padrão de nomes.
4. **O que a Etapa 2 vai conter** (a definir com a professora/roteiro da disciplina).

## Arquivos deste pacote

- `README.md`: este arquivo, com a instrução de contexto.
- `resultados-etapa-1.md`: personas, cenários-problema e tarefas da Etapa 1.
- `CHECKLIST.md`: checklist de integração.
