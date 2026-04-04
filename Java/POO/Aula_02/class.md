## O que são classes?

Uma classe em Java é como um “molde” ou “planta” usada para criar objetos. Ela define atributos (dados) e métodos (ações) que os objetos criados a partir dela terão.

### Exemplo

Pensa assim:

- Classe = modelo
- Objeto = instância desse modelo

Exemplo prático:

```
public class Pessoa {
    String nome;
    int idade;

    public void falar() {
        System.out.println("Olá!");
    }
}
```

Nesse caso:

- Pessoa é a classe
- nome e idade são atributos
- falar() é um método

Você pode criar objetos dessa classe depois:

- Pessoa p1 = new Pessoa();
- p1.nome = "João";
- p1.idade = 20;
- p1.falar();

Clique *[aqui](../Aula_02/README.md)* para retornar.