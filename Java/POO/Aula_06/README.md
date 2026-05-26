## 📆 Data: 30/03/2026 | 📚 Professora: Rebeca | 👨🏾‍🏫 Aluno: João Victor Labre

# 🔄 Aula 06: Estruturas de Repetição (Laços de Repetição)

### 📝 Introdução
A sexta aula teve como objetivo abordar as estruturas de repetição dentro do Java: **while**, **do...while** e **for**. Esses recursos são fundamentais para a construção de lógicas que exigem a execução contínua ou controlada de determinadas ações, permitindo automatizar tarefas, reduzir redundâncias no código e estruturar soluções de forma elegante e eficiente.

---

### 🔍 Estruturas Abordadas e Sintaxe

O **while** e o **for** funcionam de forma semelhante ao que já foi visto em linguagens como Python, porém com a sintaxe e as particularidades próprias do Java, utilizando chaves `{}` para delimitar o bloco.

#### 1. O Laço `while`
Utilizado quando não sabemos exatamente quantas vezes o bloco de código precisará ser repetido, dependendo puramente de uma condição lógica ser verdadeira.
```java
int contador = 0;
while (contador < 5) {
    System.out.println("Contagem: " + contador);
    contador++; // Incremento obrigatório para evitar loop infinito
}
```

#### 2. O Laço `do...while`

A professora destacou sua principal diferença em relação ao `while` tradicional: a garantia de que o bloco de código será executado **ao menos uma vez** antes da verificação da condição lógica ocorrer.

```java
int numero = 10;
do {
    System.out.println("Isso será impresso uma vez, mesmo a condição sendo falsa.");
} while (numero < 5);
```

#### 3. O Laço `for`

Evidencia sua aplicação em cenários onde se conhece previamente o limite ou a quantidade exata de repetições. Sua estrutura é muito limpa e organizada, pois reúne três conceitos na mesma linha: **inicialização**, **condição** e **incremento**.

```java
// Ideal para contagens e percursos sequenciais bem definidos
for (int i = 0; i < 5; i++) {
    System.out.println("Índice do For: " + i);
}
```

---

### 🧭 Navegação

* ⬅️ **Aula Anterior:** [Aula 05: Laboratório Prático de Operadores](../Aula_05/README.md)
* ➡️ **Próxima Aula:** [Aula 07: Laboratório de Fixação](../Aula_07/README.md)