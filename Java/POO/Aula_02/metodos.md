## O que são métodos?

Um método em Java é um bloco de código estruturado dentro de uma classe, projetado para realizar uma tarefa específica (uma "ação" ou "comportamento") e que pode ser reutilizado em todo o programa.

### Exemplo prático:

``` 
public class Calculadora { 
    // Método que soma dois números 
    public int somar(int a, int b) { 
        return a + b; 
    } 
}
```

- O método somar recebe dados, processa e devolve um resultado. Ele é ativo — executa uma tarefa.

### Atributo (estado do objeto)

O atributo é aquilo que o objeto é ou possui. Representa suas características, seus dados, sua essência.

- É como o peso, a cor ou o nome de algo — qualidades que permanecem armazenadas.

Exemplo simples:
```
public class Calculadora {
    int memoria; // atributo
}
```
- Aqui, memoria guarda um valor. Não executa nada — apenas armazena.

### Diferença essencial
- Atributo → estado (dados armazenados)
- Método → comportamento (ações executadas)

Imagine uma calculadora física sobre a mesa:

> Os atributos são como o valor exibido na tela ou armazenado na memória.\
> Os métodos são os botões que você pressiona: somar, subtrair, limpar.

- Sem atributos, nada há para manipular.\
- Sem métodos, nada acontece.

Ambos coexistem em harmonia — como tradição e ação — formando objetos completos, úteis e vivos dentro do código.

Clique *[aqui](../Aula_02/README.md)* para retornar.