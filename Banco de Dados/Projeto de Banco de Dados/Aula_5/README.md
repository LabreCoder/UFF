# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 17/08/2026 | 📚 Professor: Marcos Bedo | 👨🏾🏫 Aluno: João Victor Labre

# ☕ Aula 05: Estruturas de Índices Baseadas em Árvores (Árvores B e B+)

### 📝 Introdução

Esta aula abordou as estruturas de indexação baseadas em **Árvores de Pesquisa Balanceadas (Árvores B e B+)**, projetadas especificamente para gerenciar grandes volumes de dados armazenados em dispositivos de armazenamento secundário (discos). Aprendemos como essas estruturas minimizam os acessos físicos a disco (I/O) ao manterem o balanceamento perfeito da árvore, garantindo caminhos de busca de tamanho uniforme para qualquer registro. Também comparamos o comportamento estrutural e operacional das Árvores B tradicionais com o das Árvores B+, que são o padrão de fato nos SGBDs modernos devido à alta eficiência em consultas de intervalo.

---

### 💡 Conceitos Chave

* **Árvores B (B-Trees):** Desenvolvidas por Rudolf Bayer e Edward McCreight em 1972 enquanto trabalhavam na Boeing. São árvores de busca balanceadas multiníveis em que cada página física (nó) possui múltiplas chaves e ponteiros, proporcionando rápido acesso a arquivos volumosos com custo mínimo de overhead. Ao contrário de árvores binárias, as páginas possuem alta capacidade de ramificação (fan-out), o que reduz drasticamente a sua altura global.
* **Árvore B+:** É uma variação altamente otimizada em relação à árvore B clássica. Ela possui duas características fundamentais que melhoram o desempenho em SGBDs lógicos relacionais:
  1. **Separação de Dados e Índices:** Armazena os dados físicos (tuplas ou TIDs) **exclusivamente nas folhas**, enquanto os nós internos contêm apenas chaves de busca e ponteiros que funcionam estritamente como guias de roteamento.
  2. **Encadeamento de Folhas:** Todos os nós folhas estão encadeados horizontalmente em uma lista duplamente ligada, facilitando a execução de varreduras sequenciais e consultas de intervalo de forma linear e de altíssimo desempenho, sem precisar realizar caminhamentos recursivos (backtracking) pelos níveis superiores da árvore.
* **Definição de Ordem (\(m\)):** De acordo com a classificação clássica de Knuth (1973), a ordem de uma árvore é o número máximo de ponteiros (descendentes) que uma página pode conter. O número máximo de chaves em um nó é dado por \\(m - 1\\).
* **Taxa de Ocupação Mínima:** Para evitar a degradação e o desperdício de espaço, a árvore impõe uma taxa mínima de ocupação das páginas (com exceção da raiz). Cada página interna deve ter no mínimo \\(\lceil m/2 \rceil\\) descendentes e no mínimo \\(\lceil m/2 \rceil - 1\\) chaves. A raiz deve ter pelo menos 2 descendentes, garantindo que a árvore se expanda de forma perfeitamente balanceada e cresça apenas "para cima" quando ocorrem divisões estruturais.

#### 🔍 Tópico em Destaque: As Regras de Ouro da Inserção (Split)

* **Split de Folha (Com Cópia):** Quando uma inserção em uma folha cheia causa um transbordamento (*overflow*) de chaves (ultrapassando \\(m-1\\) chaves), o nó é dividido ao meio. A **chave central sobe para o nó pai COM CÓPIA**, permanecendo na folha da direita para garantir que o encadeamento horizontal sequencial da lista ligada continue íntegro e contenha todas as chaves existentes.
* **Split de Nó Interno (Sem Cópia):** Quando uma divisão ocorre em um nó interno que ultrapassou a capacidade de roteadores, a **chave central sobe para o nó pai SEM CÓPIA**. Como os nós internos servem apenas para navegação hierárquica, a chave promovida é retirada do nível intermediário e mantida exclusivamente no pai.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Por que as Árvores B+ dominam os SGBDs lógicos de mercado?**
> Ao concentrar todas as tuplas lógicas exclusivamente nos nós folhas, a Árvore B+ consegue acomodar muito mais chaves de navegação nos nós internos de tamanho fixo (por exemplo, 8KB). Isso aumenta substancialmente o *fan-out* da estrutura, mantendo a altura global da árvore em apenas 3 ou 4 níveis, mesmo para tabelas com bilhões de registros. Isso assegura que qualquer busca exata exija no máximo 3 ou 4 leituras de disco.
>
> ---
>
> 💡 **O Diferencial de Consultas de Intervalo (B vs. B+):**
> Em uma Árvore B convencional, uma varredura de intervalo (ex: `WHERE id BETWEEN 10 AND 100`) exige percorrer recursivamente vários caminhos de nós superiores e subárvores. Na Árvore B+, basta encontrar a folha que contém a primeira chave (`id = 10`) e simplesmente seguir os ponteiros horizontais da lista ligada até alcançar o valor limite (`id = 100`), executando leituras sequenciais extremamente rápidas de blocos adjacentes.
>
> ---
>
> 💡 **Tratamento de Exclusão (Underflow):**
> Quando chaves são removidas de uma folha e uma página cai abaixo da taxa de ocupação mínima (\\(\lceil m/2 \rceil - 1\\) chaves), a estrutura não se desbalanceia. Em vez disso, o SGBD realiza operações dinâmicas de **redistribuição** de chaves com as páginas irmãs adjacentes ou a **concatenação (merge)** de duas páginas vizinhas, propagando os ajustes de ponteiro para os níveis hierárquicos superiores se necessário.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 14: *B-Trees*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 17: *B-Trees and B+-Trees as Search Indexes*.
* 🔗 [B+ Tree Visualization Tool (USFCA)](https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html) — Excelente ferramenta interativa para simular inserções, splits e exclusões de chaves na prática.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 04: Índice Hash (Hashing Estático e Linear)](../Aula_4/README.md)
* ➡️ **Próxima Aula:** [Aula 06: Índices no PostgreSQL](../Aula_6/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
