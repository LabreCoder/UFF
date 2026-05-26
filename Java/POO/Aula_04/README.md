## 📆 Data: 23/03/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 🧮 Aula 04: Operadores Aritméticos e Relacionais

### 📝 Introdução
A quarta aula cobriu o funcionamento dos operadores dentro do Java. Eles formam a base para a construção de qualquer lógica, equações matemáticas ou verificações condicionais dentro do software.

---

### 🔢 1. Operadores Aritméticos
Utilizados para realizar cálculos matemáticos padrão e manipulação de variáveis numéricas:

```java
// Adição (+) - Soma dois valores
int soma = 10 + 5; // resultado = 15

// Subtração (-) - Subtrai um valor do outro
int subtracao = 10 - 5; // resultado = 5

// Multiplicação (*) - Multiplica dois valores
int multiplicacao = 10 * 5; // resultado = 50

// Divisão (/) - Divide um valor pelo outro
int divisao = 10 / 5; // resultado = 2

// Módulo (%) - Retorna o resto da divisão inteira
int resto = 10 % 3; // resultado = 1 (pois 10 dividido por 3 dá 3 e sobra 1)

// Incremento (++) - Soma 1 ao valor atual da variável
int numeroInc = 10;
numeroInc++; // agora numeroInc = 11

// Decremento (--) - Subtrai 1 ao valor atual da variável
int numeroDec = 10;
numeroDec--; // agora numeroDec = 9
```

---

### ⚖️ 2. Operadores Relacionais (Verificação)

Utilizados para comparar dois valores. O retorno dessas operações é sempre um valor booleano (`true` ou `false`):

```java
int a = 10;
int b = 5;

// Igualdade (==) - Verifica se dois valores são iguais
boolean eIgual = (a == 10); // true

// Diferente (!=) - Verifica se dois valores são distintos
boolean eDiferente = (a != b); // true

// Maior que (>) - Verifica se o valor da esquerda é maior que o da direita
boolean eMaior = (a > b); // true

// Menor que (<) - Verifica se o valor da esquerda é menor que o da direita
boolean eMenor = (b < a); // true

// Maior ou igual (>=) - Verifica se é maior ou igual
boolean eMaiorOuIgual = (a >= 10); // true

// Menor ou igual (<=) - Verifica se é menor ou igual
boolean eMenorOuIgual = (b <= a); // true
```

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 03: Primeiros Passos no Laboratório](../Aula_03/README.md)
* ➡️ **Próxima Aula:** [Aula 05: Estruturas Condicionais](../Aula_05/README.md)