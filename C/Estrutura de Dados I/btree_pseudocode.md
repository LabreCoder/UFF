# Pseudocódigos para Remoção em Árvore B

## 1. REDISTRIBUIÇÃO DA ESQUERDA

```
ALGORITMO redistribui_esquerda(no, pos_no_pai, d)
ENTRADA: 
  - no: nó que precisa de mais chaves
  - pos_no_pai: posição do nó no array de filhos do pai
  - d: ordem da árvore B

INÍCIO
  irmao ← pai[no].p[pos_no_pai - 1]  // Obtém irmão à esquerda
  
  // Abre espaço no início do nó atual
  PARA i DE no.m ATÉ 1 FAÇA
    no.s[i] ← no.s[i-1]
    no.p[i+1] ← no.p[i]
  FIM-PARA
  no.p[1] ← no.p[0]
  
  // Move chave do pai para o nó atual
  no.s[0] ← pai[no].s[pos_no_pai - 1]
  
  // Move maior chave do irmão para o pai
  pai[no].s[pos_no_pai - 1] ← irmao.s[irmao.m - 1]
  
  // Move ponteiro mais à direita do irmão para o nó
  no.p[0] ← irmao.p[irmao.m]
  SE no.p[0] ≠ NULL ENTÃO
    pai[no.p[0]] ← no
  FIM-SE
  
  // Atualiza contadores
  irmao.m ← irmao.m - 1
  no.m ← no.m + 1
FIM
```

---

## 2. REDISTRIBUIÇÃO DA DIREITA

```
ALGORITMO redistribui_direita(no, pos_no_pai, d)
ENTRADA:
  - no: nó que precisa de mais chaves
  - pos_no_pai: posição do nó no array de filhos do pai
  - d: ordem da árvore B

INÍCIO
  irmao ← pai[no].p[pos_no_pai + 1]  // Obtém irmão à direita
  
  // Move chave do pai para o final do nó atual
  no.s[no.m] ← pai[no].s[pos_no_pai]
  
  // Move ponteiro mais à esquerda do irmão para o nó
  no.p[no.m + 1] ← irmao.p[0]
  SE no.p[no.m + 1] ≠ NULL ENTÃO
    pai[no.p[no.m + 1]] ← no
  FIM-SE
  
  // Move menor chave do irmão para o pai
  pai[no].s[pos_no_pai] ← irmao.s[0]
  
  // Remove primeira chave do irmão (desloca elementos)
  PARA i DE 0 ATÉ irmao.m - 2 FAÇA
    irmao.s[i] ← irmao.s[i + 1]
    irmao.p[i] ← irmao.p[i + 1]
  FIM-PARA
  irmao.p[irmao.m - 1] ← irmao.p[irmao.m]
  
  // Atualiza contadores
  irmao.m ← irmao.m - 1
  no.m ← no.m + 1
FIM
```

---

## 3. CONCATENAÇÃO COM IRMÃO ESQUERDO

```
ALGORITMO concatena_esquerda(no, pos_no_pai, d)
ENTRADA:
  - no: nó com deficiência de chaves
  - pos_no_pai: posição do nó no array de filhos do pai
  - d: ordem da árvore B

INÍCIO
  irmao ← pai[no].p[pos_no_pai - 1]  // Obtém irmão à esquerda
  
  // Desce chave separadora do pai para o irmão
  irmao.s[irmao.m] ← pai[no].s[pos_no_pai - 1]
  irmao.m ← irmao.m + 1
  
  // Move todas as chaves e ponteiros do nó para o irmão
  PARA i DE 0 ATÉ no.m - 1 FAÇA
    irmao.s[irmao.m] ← no.s[i]
    irmao.p[irmao.m] ← no.p[i]
    SE irmao.p[irmao.m] ≠ NULL ENTÃO
      pai[irmao.p[irmao.m]] ← irmao
    FIM-SE
    irmao.m ← irmao.m + 1
  FIM-PARA
  
  // Move último ponteiro
  irmao.p[irmao.m] ← no.p[no.m]
  SE irmao.p[irmao.m] ≠ NULL ENTÃO
    pai[irmao.p[irmao.m]] ← irmao
  FIM-SE
  
  // Remove chave separadora do pai
  remove_do_no(pai[no], pos_no_pai - 1)
  
  // Libera memória do nó atual
  libera(no)
FIM
```

---

## 4. CONCATENAÇÃO COM IRMÃO DIREITO

```
ALGORITMO concatena_direita(no, pos_no_pai, d)
ENTRADA:
  - no: nó com deficiência de chaves
  - pos_no_pai: posição do nó no array de filhos do pai
  - d: ordem da árvore B

INÍCIO
  irmao ← pai[no].p[pos_no_pai + 1]  // Obtém irmão à direita
  
  // Desce chave separadora do pai para o nó atual
  no.s[no.m] ← pai[no].s[pos_no_pai]
  no.m ← no.m + 1
  
  // Move todas as chaves e ponteiros do irmão para o nó atual
  PARA i DE 0 ATÉ irmao.m - 1 FAÇA
    no.s[no.m] ← irmao.s[i]
    no.p[no.m] ← irmao.p[i]
    SE no.p[no.m] ≠ NULL ENTÃO
      pai[no.p[no.m]] ← no
    FIM-SE
    no.m ← no.m + 1
  FIM-PARA
  
  // Move último ponteiro
  no.p[no.m] ← irmao.p[irmao.m]
  SE no.p[no.m] ≠ NULL ENTÃO
    pai[no.p[no.m]] ← no
  FIM-SE
  
  // Remove chave separadora do pai
  remove_do_no(pai[no], pos_no_pai)
  
  // Libera memória do irmão
  libera(irmao)
FIM
```

---

## 5. RESTAURAÇÃO (Função Principal de Balanceamento)

```
ALGORITMO restaura(no, d)
ENTRADA:
  - no: nó que ficou com menos chaves que o mínimo
  - d: ordem da árvore B

INÍCIO
  SE pai[no] = NULL ENTÃO  // É raiz
    RETORNA
  FIM-SE
  
  // Encontra posição do nó no array de filhos do pai
  pos_no_pai ← 0
  ENQUANTO pos_no_pai ≤ pai[no].m E pai[no].p[pos_no_pai] ≠ no FAÇA
    pos_no_pai ← pos_no_pai + 1
  FIM-ENQUANTO
  
  // Tenta redistribuir primeiro
  SE pode_emprestar_esquerda(no, pos_no_pai, d) ENTÃO
    redistribui_esquerda(no, pos_no_pai, d)
  SENÃO SE pode_emprestar_direita(no, pos_no_pai, d) ENTÃO
    redistribui_direita(no, pos_no_pai, d)
  SENÃO
    // Concatena se redistribuição não for possível
    SE pos_no_pai > 0 ENTÃO
      concatena_esquerda(no, pos_no_pai, d)
    SENÃO
      concatena_direita(no, pos_no_pai, d)
    FIM-SE
    
    // Verifica se o pai ficou deficiente
    SE pai[no].m < d - 1 E pai[pai[no]] ≠ NULL ENTÃO
      restaura(pai[no], d)
    FIM-SE
  FIM-SE
FIM
```

---

## 6. REMOÇÃO DE CHAVE (Função Principal)

```
ALGORITMO remove_chave(raiz, d, chave)
ENTRADA:
  - raiz: ponteiro para a raiz da árvore
  - d: ordem da árvore B
  - chave: valor a ser removido

SAÍDA: ponteiro para a nova raiz (pode mudar)

INÍCIO
  SE raiz = NULL ENTÃO
    RETORNA NULL
  FIM-SE
  
  // Busca o nó que contém a chave
  no ← busca(raiz, chave)
  pos ← posicao(chave, no)
  
  // Verifica se a chave existe
  SE pos = no.m OU no.s[pos] ≠ chave ENTÃO
    IMPRIME "Chave não encontrada"
    RETORNA raiz
  FIM-SE
  
  // CASO 1: Nó é folha
  SE no.p[0] = NULL ENTÃO
    remove_do_no(no, pos)
    
    // Restaura se ficou com deficiência e não é raiz
    SE no.m < d - 1 E pai[no] ≠ NULL ENTÃO
      restaura(no, d)
    FIM-SE
    
    // Ajusta se raiz ficou vazia
    SE raiz.m = 0 E raiz.p[0] ≠ NULL ENTÃO
      nova_raiz ← raiz.p[0]
      pai[nova_raiz] ← NULL
      libera(raiz)
      RETORNA nova_raiz
    FIM-SE
    
  // CASO 2: Nó interno
  SENÃO
    // Substitui por predecessor
    pred ← predecessor(no, pos)
    no.s[pos] ← pred.s[pred.m - 1]
    
    // Remove o predecessor da folha
    remove_do_no(pred, pred.m - 1)
    
    // Restaura se necessário
    SE pred.m < d - 1 E pai[pred] ≠ NULL ENTÃO
      restaura(pred, d)
    FIM-SE
    
    // Ajusta se raiz ficou vazia
    SE raiz.m = 0 E raiz.p[0] ≠ NULL ENTÃO
      nova_raiz ← raiz.p[0]
      pai[nova_raiz] ← NULL
      libera(raiz)
      RETORNA nova_raiz
    FIM-SE
  FIM-SE
  
  RETORNA raiz
FIM
```

---

## Resumo das Operações

### Quando usar cada técnica:

1. **Redistribuição da Esquerda**: Quando o nó está deficiente e o irmão à esquerda tem chaves extras (> d-1)

2. **Redistribuição da Direita**: Quando o nó está deficiente e o irmão à direita tem chaves extras (> d-1)

3. **Concatenação Esquerda**: Quando redistribuição não é possível e existe irmão à esquerda

4. **Concatenação Direita**: Quando redistribuição não é possível e só existe irmão à direita (ou é o primeiro filho)

### Complexidade:
- **Tempo**: O(log n) para todas as operações
- **Espaço**: O(1) - operações in-place