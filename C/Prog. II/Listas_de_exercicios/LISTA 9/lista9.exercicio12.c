#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro {
    int ano;
    char titulo[100];
    char autor[100];
    int nVolume;
    float preco;
} Livro;

typedef struct Biblioteca {
    Livro **V;
    int nLivros;
} Biblioteca;

// (A)
Livro *fillLivro() {
    Livro *l = (Livro *) malloc(sizeof(Livro));
    if (l == NULL) {
        printf("Erro ao alocar memória para o livro!\n");
        exit(1);
    }
    while(getchar() != '\n');

    printf("Digite o título do livro: ");
    fgets(l->titulo, sizeof(l->titulo), stdin);
    l->titulo[strcspn(l->titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets(l->autor, sizeof(l->autor), stdin);
    l->autor[strcspn(l->autor, "\n")] = '\0';

    printf("Digite o ano do livro: ");
    scanf("%d", &l->ano);

    printf("Digite o número de exemplares (nVolume): ");
    scanf("%d", &l->nVolume);

    printf("Digite o preço do livro: ");
    scanf("%f", &l->preco);

    return l;
}

// (B)
Biblioteca *fillBiblioteca(int numLivros) {
    Biblioteca *b = (Biblioteca *) malloc(sizeof(Biblioteca));
    if (b == NULL) {
        printf("Erro ao alocar memória para a biblioteca!\n");
        exit(1);
    }
    b->nLivros = numLivros;
    b->V = (Livro **) malloc(numLivros * sizeof(Livro *));
    if (b->V == NULL) {
        printf("Erro ao alocar memória para os livros da biblioteca!\n");
        exit(1);
    }
    for (int i = 0; i < numLivros; i++) {
        printf("\n--- Preenchendo dados do Livro %d ---\n", i + 1);
        b->V[i] = fillLivro();
    }
    return b;
}

// (C)
void valorBiblioteca(Biblioteca *b1, int numLivros) {
    float total = 0.0;
    for (int i = 0; i < numLivros; i++) {
        total += b1->V[i]->preco * b1->V[i]->nVolume;
    }
    printf("\nValor total gasto na biblioteca: R$ %.2f\n", total);
}

// (D)
Livro *maiorBiblioteca(Biblioteca *b1, int numLivros) {
    if (numLivros == 0)
        return NULL;

    Livro *maior = b1->V[0];
    for (int i = 1; i < numLivros; i++) {
        if (b1->V[i]->nVolume > maior->nVolume) {
            maior = b1->V[i];
        }
    }
    return maior;
}

int main() {
    int numLivros;
    printf("Digite o número de livros que a biblioteca terá: ");
    scanf("%d", &numLivros);

    Biblioteca *biblioteca = fillBiblioteca(numLivros);
    valorBiblioteca(biblioteca, numLivros);

    Livro *livroMaior = maiorBiblioteca(biblioteca, numLivros);
    if (livroMaior != NULL) {
        printf("\nLivro com o maior número de exemplares:\n");
        printf("Título: %s\n", livroMaior->titulo);
        printf("Autor: %s\n", livroMaior->autor);
        printf("Ano: %d\n", livroMaior->ano);
        printf("Número de exemplares: %d\n", livroMaior->nVolume);
        printf("Preço: R$ %.2f\n", livroMaior->preco);
    }

    for (int i = 0; i < numLivros; i++) {
        free(biblioteca->V[i]);
    }
    free(biblioteca->V);
    free(biblioteca);

    return 0;
}
