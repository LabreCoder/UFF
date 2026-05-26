## 📆 Data: 06/04/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 📊 Aula 08: Estruturas de Dados — Vetores e Matrizes (Arrays)

### 📝 Introdução
A oitava aula teve como objetivo compreender o funcionamento das variáveis compostas homogêneas, conhecidas como **Arrays**. Abordamos tanto as estruturas unidimensionais (**Vetores**) quanto as multidimensionais (**Matrizes**). 

Até o momento, trabalhamos com objetos utilitários como `Scanner` e `String`. Agora, avançamos para o uso de Arrays para manipular coleções de dados de forma indexada na memória.

---

### 📐 Vetores (Arrays Unidimensionais)

Um vetor é uma estrutura de dados linear que armazena uma coleção de elementos do mesmo tipo, acessíveis por meio de um índice numérico que sempre inicia em `0`.

#### 1. Declaração
Para declarar um vetor, informamos o tipo dos elementos seguido de colchetes `[]`:
```java
int[] vetorDeInteiros;
float[] notas;
```

#### 2. Inicialização e Definição de Tamanho

É obrigatório definir o tamanho do vetor no momento da criação para que o Java reserve o espaço correto na memória:

```java
// Forma separada
float[] notas;
notas = new float[10];

// Forma direta (Recomendada)
float[] notas = new float[10];
```

> ⚠️ **Nota sobre Valores Default:** Caso você não atribua valores logo após a inicialização, o Java preenche o vetor automaticamente com valores padrão: `0` para tipos numéricos, `false` para `boolean` e `null` para objetos.

#### 3. Atribuição Direta de Valores

Podemos criar e preencher o vetor simultaneamente utilizando chaves `{}`:

```java
// O Java infere o tamanho do vetor com base na quantidade de elementos inseridos
float[] notas = {8.8f, 9.0f, 10.0f}; 
```

#### 4. Percorrendo o Vetor com `for-each`

O laço `for-each` é uma sintaxe simplificada para ler todos os elementos de um Array do início ao fim, sem a necessidade de controlar variáveis de índice.

```java
float[] notas = {8.8f, 9.0f, 10.0f};

for (float nota : notas) {
    System.out.println(nota);
}
```

* **Aviso importante:** O `for-each` serve **apenas para leitura**. Ele não permite modificar ou atualizar os valores armazenados dentro do vetor, apenas acessar uma cópia temporária de cada elemento.

---

### 🔲 Matrizes (Arrays Multidimensionais)

Uma matriz é uma estrutura de dados bidimensional, organizada em uma grade composta por **linhas e colunas** (como uma tabela ou planilha).

#### 1. Declaração

Adicionamos dois pares de colchetes `[][]` ao tipo da variável:

```java
int[][] matrizDeInteiros;
float[][] tabelaNotas;
```

#### 2. Inicialização

Devemos especificar o número de linhas (primeiro colchete) e de colunas (segundo colchete):

```java
// Criando uma matriz com 3 linhas e 4 colunas
float[][] notas = new float[3][4];
```

#### 3. Atribuição de Valores Manual

Podemos preencher a matriz informando cada linha de forma aninhada:

```java
float[][] notas = new float[][] {
    {8.8f, 9.0f, 10.0f, 7.5f}, // Linha 0
    {6.5f, 8.0f, 9.5f, 10.0f}, // Linha 1
    {7.0f, 7.5f, 8.5f, 9.0f}   // Linha 2
};
```

#### 4. Percorrendo a Matriz com `for` Tradicional

Para ler ou manipular os dados de uma matriz, precisamos aninhar dois laços de repetição: o primeiro controla as linhas e o segundo controla as colunas.

```java
for (int i = 0; i < notas.length; i++) { // Percorre as linhas
    for (int j = 0; j < notas[i].length; j++) { // Percorre as colunas da linha atual
        System.out.print(notas[i][j] + " ");
    }
    System.out.println(); // Quebra de linha ao fim de cada linha da matriz
}
```

* `i` representa o índice da linha atual.
* `j` representa o índice da coluna atual.
* `notas.length` retorna a quantidade total de linhas.
* `notas[i].length` retorna a quantidade de colunas que aquela linha específica possui.

---

### 🎯 Conclusão

O uso de vetores e matrizes otimiza o código evitando a criação de dezenas de variáveis avulsas (ex: em vez de criar `nota1`, `nota2`, `nota3`, criamos apenas `notas[]`). Compreender o funcionamento dos índices e os limites de tamanho do array é crucial para evitar o famoso erro `ArrayIndexOutOfBoundsException`.

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 07: Laboratório de Fixação — Listas de Exercícios 2 e 3](../Aula_07/README.md)
* ➡️ **Próxima Aula:** [Aula 09: Laboratório Prático — Lista de Exercícios 04 (Arrays)](../Aula_09/README.md)