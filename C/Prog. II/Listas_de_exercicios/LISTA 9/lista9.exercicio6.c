#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pessoa {
    int codigo;
    char nome[81];
};
typedef struct pessoa Pessoa;

Pessoa *busca(int n, Pessoa** vet, int codigo);

int main(){
    
    int n = 7;
    
    Pessoa **cadastro = (Pessoa**)malloc(n * sizeof(Pessoa*));
    if (cadastro == NULL) return 1;
    
    int codigos[] = {0, 1, 2, 3, 4, 5, 6}; // Agora bate com n = 7
    char *nomes[] = {"Carlos", "André", "Bruno", "Carla", "Luiza", "Bea", "João"};
    
    for (int i = 0; i < n; i++) {
        cadastro[i] = (Pessoa*)malloc(sizeof(Pessoa));
        if (cadastro[i] == NULL) return 1;
        cadastro[i]->codigo = codigos[i];
        strcpy(cadastro[i]->nome, nomes[i]);
    }
    
    int num_busca;
    printf("Por favor, digite o código que deseja verificar: ");
    scanf("%d", &num_busca);
    
    Pessoa *resultado = busca(n, cadastro, num_busca);

    if (resultado != NULL) {
        printf("Pessoa encontrada: %s (Código %d)\n", resultado->nome, resultado->codigo);
    } else {
        printf("Pessoa com código %d não encontrada.\n", num_busca);
    }
    
    for (int i = 0; i < n; i++) {
        free(cadastro[i]);
    }
    free(cadastro);

    return 0;
}

Pessoa *busca(int n, Pessoa** vet, int codigo){
    int ini = 0;
    int fim = n - 1;
    
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        
        if (vet[meio]->codigo == codigo) {
            return vet[meio];
        } 
        else if (vet[meio]->codigo > codigo) {
            fim = meio - 1;
        } 
        else {
            ini = meio + 1;
        }
    }
    return NULL;
}
