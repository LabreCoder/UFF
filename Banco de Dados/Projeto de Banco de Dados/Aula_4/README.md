# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 12/08/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 04: Índice Hash (Hashing Estático e Linear)

### 📝 Introdução

Esta aula abordou o conceito de **Índice Hash**, detalhando o funcionamento de estruturas de busca baseadas em funções de espalhamento para otimização de consultas de igualdade (*Exact Match*). Discutimos o funcionamento clássico do **Hashing Estático**, seus fatores geradores de colisão e overflow, e a transição necessária para algoritmos de armazenamento dinâmico como o **Hashing Linear**, que gerenciam de forma incremental o crescimento físico do banco de dados sem exigir bloqueios prolongados do sistema.

---

### 💡 Conceitos Chave

* **Índice Hash:** Uma estrutura de índice organizada como uma tabela hash em que pares `<chave de busca, ponteiro de dados>` são mapeados para locais físicos específicos.
* **Bucket (Balde):** Unidade de armazenamento em disco que representa e comporta um conjunto de entradas do índice (páginas de índice).
* **Função de Hash ($h: K \to B$):** Função matemática responsável por mapear o conjunto de todas as chaves de busca lógicas ($K$) para o conjunto de endereços físicos de todos os buckets ($B$).
* **Exact Match (Consulta Exata):** A principal finalidade prática do Índice Hash, sendo extremamente eficiente para implementar operações de `SELECT` com predicados de igualdade (`=`) sobre atributos chave sem repetição.

#### 🔍 Tópico em Destaque: Classificações e Métodos de Hashing

* **Hashing Estático:** Técnica em que o número de buckets ($B$) é fixado no momento de criação do índice. Pode sofrer colisões quando duas chaves distintas $x \neq y$ resultam no mesmo endereço de bucket $h(x) = h(y)$. É possível tratar colisões usando encadeamento exterior, encadeamento interior ou encadeamento aberto.
* **Métodos de Espalhamento Comuns:**
* **Método de Divisão:** $h(x) = x \bmod m$.
* **Método de Multiplicação:** $h(x) = (x^2 \text{ div } 2^{(b-k)/2}) \bmod 2^k$.
* **Hashing Dinâmico (Linear e Extensível):** Estruturas que permitem o crescimento dinâmico e flexível do espaço físico do índice conforme novos dados são inseridos, evitando reorganizações completas e pesadas em disco.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **O Problema do Erro de Dimensionamento:**
> A escolha incorreta do tamanho de $B$ no Hashing Estático compromete severamente a performance. Um $B$ muito grande gera desperdício de espaço em disco, enquanto um $B$ muito pequeno gera constantes overflows. Resolver um overflow no modelo estático exige selecionar uma nova função hash e reorganizar todo o índice físico, uma operação demorada que bloqueia qualquer acesso aos dados.
>
> ---
>
> 💡 **Axiomas e Regras do Hashing Linear (Tolerância Zero):**
> O Hashing Linear elimina a necessidade de reorganizações em massa utilizando as seguintes regras de estado:
>
> ---
>
> 1. **Regra 1 (Inserção):** Toda nova chave é mapeada por $h_L(k)$. Se o endereço gerado for menor que o ponteiro de split $p$, usa-se $h_{L+1}(k)$.
> 2. **Regra 2 (Tolerância Zero):** Nenhuma página de cadeia de overflow (*overflow chain*) de longa permanência é permitida.
> 3. **Regra 3 (Gatilho de Split):** Havendo estouro de capacidade máxima ($c$) de registros em qualquer bucket, o bucket apontado pelo ponteiro de split $p$ é dividido, independentemente de onde o overflow ocorreu.
> 4. **Regra 4 (Persistência):** Os splits continuam de forma consecutiva e o ponteiro $p$ avança uma posição. Quando $p$ atinge o limite máximo $2^L \cdot N$, o nível $L$ é incrementado e $p$ reinicia em 0.
>
> ---
>
> 💡 **Inadequação para Intervalos:**
> Como o espalhamento de hash é projetado para distribuir as chaves de forma uniforme e pseudo-aleatória, os índices hash **não** conseguem otimizar consultas de intervalo (ex: `WHERE codigo >= 10`), já que registros logicamente vizinhos são salvos em buckets físicos completamente distintos em disco.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 14: *Hash Table Indexes*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 17: *Dynamic Hashing*.
* 📖 *Algoritmos: Teoria e Prática* — Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein (LTC, 3ª Edição) — Capítulo 11: *Tabelas Hash*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 3: Índices e Estruturas de Índices](../Aula_3/README.md)
* ➡️ **Próxima Aula:** [Aula 5: Estruturas de Índices Baseadas em Árvores (Árvores B e B+)](../Aula_5/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
