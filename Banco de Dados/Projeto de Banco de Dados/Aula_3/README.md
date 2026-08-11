# 🏫 Universidade Federal Fluminense (UFF) — Sistemas de Informação

## 📆 Data: 10/08/2026 | 📚 Professor: Marcos Bedo | 👨🏾‍🏫 Aluno: João Victor Labre

# ☕ Aula 03: Índices e Estruturas de Índices

### 📝 Introdução

A aula abordou o conceito de **indexação de dados**, com foco em como essas estruturas de dados auxiliam na otimização de recuperação física de registros. Entendemos que no cenário de **Cold Start** (inicialização a frio), o banco de dados começa sem carregar páginas na memória RAM (Buffer Pool), realizando os acessos diretamente no disco (memória secundária) e aquecendo o cache gradativamente. Por fim, ficou claro que a existência de um arquivo de índice é estritamente dependente da existência de uma tabela física mapeada.

---

### 💡 Conceitos Chave

* **Condição de Pesquisa (Busca):** É o predicado ou critério lógico utilizado para filtrar e selecionar quais registros do banco de dados devem ser recuperados em uma dada consulta.
* **Chave de Pesquisa (Busca):** O atributo ou conjunto de atributos (chave composta) que são avaliados na Condição de Pesquisa.
* **Arquivo de Índice:** É a estrutura de dados física auxiliar que também será persistida em disco seguindo o modelo e a abstração de um arquivo de sistema de arquivos convencional.
* **Entrada de Dados (Data Entry):** São os registros armazenados internamente em um arquivo de índice. Cada entrada de dados mapeia um valor da chave de pesquisa $\mathfrak{K}$ e contém informações suficientes e ponteiros diretos para localizar um ou mais registros de dados reais em disco com o valor correspondente de $\mathfrak{K}$.

#### 🔍 Tópico em Destaque: Classificações de Índices

* **Índice Clusterizado (Agrupado):** Não existe uma terminologia puramente padrão na literatura técnica e há divergências conceituais entre autores. No escopo da disciplina, refere-se comumente à situação na qual a ordenação física dos dados da tabela em disco reflete diretamente a ordem lógica do índice criado.
* **Índice Primário:** É o índice construído sobre uma chave de busca que determina de forma direta a **ordenação física das tuplas** nas páginas de dados do disco. Ele se divide em duas ramificações de cobertura de busca:
  * **Denso:** Quando possui **uma entrada na estrutura do índice para cada valor da chave de busca** mapeado no arquivo de dados.
  * **Esparso:** Quando possui entradas no índice mapeando apenas alguns dos registros da tabela em disco (geralmente apontando para o início de cada bloco ou página física de dados).
* **Índice Secundário:** É o índice cuja chave de busca **não determina a ordem física de gravação das tuplas** no disco, trabalhando estritamente com base na ordem lógica. Devido a essa falta de ordenação física, o índice secundário deve ser **obrigatoriamente denso**, contendo uma entrada específica para cada registro presente na tabela real.

---

### ⚠️ Pontos de Atenção & Dicas

> 💡 **Comparação de Custo Físico de Acesso (I/O) para Consulta Exata (`WHERE código = 7`):**
> Considerando uma tabela distribuída fisicamente em 4 páginas de dados em disco (PD1 a PD4):
>
> * **Sem Índice:** O SGBD faz um table scan completo, gerando **4 acessos ao disco**.
> * **Índice Primário Denso:** Permite ir direto ao ponteiro correto e carregar apenas a página de dados exata, gerando **1 acesso ao disco**.
> * **Índice Primário Esparso:** Requer buscar o bloco delimitador e depois carregar a página associada, gerando **2 acessos ao disco**.
> * **Índice Secundário:** Busca a entrada densa correspondente no índice e acessa o registro por meio do ponteiro em um único salto, gerando **1 acesso ao disco**.

> 💡 **Desempenho em Varreduras de Intervalo (`WHERE código >= 7`):**
> O comportamento das consultas de intervalo varia significativamente conforme o tipo de índice:
>
> * **Índice Primário Denso:** Pelo fato de os dados físicos estarem ordenados de forma sequencial na tabela em disco, consome apenas **2 acessos ao disco**.
> * **Índice Primário Esparso:** Exige a busca e leitura de múltiplos limites físicos de páginas, consumindo **3 acessos ao disco**.
> * **Índice Secundário:** Como os registros físicos não estão dispostos em disco ordenadamente pela chave secundária, o SGBD precisa saltar entre diferentes blocos para recuperar os dados, consumindo **3 acessos ao disco** para esta mesma consulta.

> 💡 **Custo Oculto da Indexação Excessiva:** Embora os índices acelerem consideravelmente os tempos de leitura e busca (I/O), eles trazem um custo real de processamento físico. Sempre que um registro sofre alteração (`INSERT`, `UPDATE`, `DELETE`), o SGBD precisa atualizar todas as estruturas dos índices associados no disco de maneira síncrona.

---

### 📚 Links & Leituras Complementares

* 📖 *Database Systems: The Complete Book* — Hector Garcia-Molina, Jeff Ullman, Jennifer Widom (Pearson, 2ª Edição) — Capítulo 14: *Index Structures*.
* 📖 *Fundamentals of Database Systems* — Ramez Elmasri e Shamkant B. Navathe (Pearson, 6ª Edição) — Capítulo 17: *Indexing Structures for Files*.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 2: Revisão de Arquitetura Física e Armazenamento](../Aula_2/README.md)
* ➡️ **Próxima Aula:** [Aula 4: Árvores B e B+ (B-Trees)](../Aula_4/README.md)

---

**🏠 [README PRINCIPAL](../README.md)**

Organizado por: [João Victor Labre](https://github.com/LabreCoder) | [LinkedIn](https://www.linkedin.com/in/joão-victor-labre)
