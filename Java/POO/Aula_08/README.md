## 📆 Data - 06/04/2026    |  📚 Professora: Rebeca    |   👨🏾‍🏫 Aluno: João Victor Labre

### Introdução

- A oitava aula teve como objetivo abordar os **Vetores**, assim como as variáveis compostas **unidimensionais** e també as variáveis compostas **multidimensionais**, como as **Matrizes**.

- Até o momento já abordarmos alguns objetos, como Scanner, String e agora os **Arrays**.

### Exemplos de Vetor

Declaramos os tupos de um vetor e acrescentamos **'[]'** e o nome do vetor, exemplo:

```
int[] vetor;
float[] notas;
```
<hr>

Precisameros iniciar esse vetor, exemplo:

```
float[] notas;
notas = new float[10];

OU

float[] notas = new float[10];
```

<hr>

Para passar os valores, podemos fazer da seguinte forma: 

```
notas = {8.8, 9.0, 10.0, ...}
```

- Caso não seja passado nenhuma informação de valor para esse vetor, ele irá iniciar com o valor default.

Também abordar o **'for each'**, onde temos a estrutura:

```
for (int n : v){
    System.out.println(n);
}
```

- Lembrando que nesse caso do <b>*for each*</b>, ele não irá manipular os dados dentro do vetor, apenas realizar uma leitura.

<hr>

### Exemplos de Matriz

Declaramos os tipos de uma matriz acrescentando '[][]' ao tipo, indicando duas dimensões:

```
int[][] matriz;
float[][] notas;
```

<hr>

#### Inicialização da matriz

É necessário definir o tamanho da matriz, informando linhas e colunas:

```
float[][] notas;
notas = new float[3][4];

OU

float[][] notas = new float[3][4];
```

- Nesse exemplo, temos 3 linhas e 4 colunas.

<hr>

#### Atribuição de valores

Podemos preencher a matriz diretamente:

```
notas = new float[][] {
    {8.8, 9.0, 10.0, 7.5},
    {6.5, 8.0, 9.5, 10.0},
    {7.0, 7.5, 8.5, 9.0}
};
```

- Cada conjunto {} representa uma linha da matriz.

- Caso nenhum valor seja informado, a matriz será preenchida com valores default.

<hr>

#### Percorrendo a matriz com for tradicional

Para manipular os dados, utilizamos dois laços:

```
for (int i = 0; i < notas.length; i++) {
    for (int j = 0; j < notas[i].length; j++) {
        System.out.println(notas[i][j]);
    }
}
```

- i representa a linha
- j representa a coluna

Assim como no vetor, o for each não permite alterar diretamente os valores, apenas acessá-los

<hr>

### Link para a aula anterior

- Retornar para *[Aula 07](../Aula_07/README.md)*.

- Caso queira ver o conteúdo da aula seguinte, basta clicar <b>[aqui](../Aula_09/README.md)</b>.