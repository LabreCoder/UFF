## O que é static?

O static em Java é um modificador que indica que algo pertence à classe, e não a um objeto específico.

Ou seja:

- Não precisa criar um objeto para usar
- É compartilhado por todas as instâncias

### Exemplo 

Exemplo prático:

```
public class Calculadora {
    
    public static int somar(int a, int b) {
        return a + b;
    }
}
```

Aqui:

1. O método somar é static
2. Você pode usar direto pela classe, sem criar objeto:
> int resultado = Calculadora.somar(5, 3);

Outro exemplo (pra ficar bem claro):
```
public class Contador {
    static int total = 0;

    public Contador() {
        total++;
    }
}
```

Se você fizer:

```
new Contador();
new Contador();
new Contador();
```

**System.out.println(Contador.total);**

O resultado será:

> 3
