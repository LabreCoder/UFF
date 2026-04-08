#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    char nome[81];
    char matricula[20];
    float nota;
    struct aluno *prox;
} Aluno;

Aluno* carregarArquivo(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if(arq == NULL) {
        printf("ERRO");
        exit(1);
    }
    Aluno *lst = NULL, *fim = NULL, *novo;
    while(1) {
        novo = (Aluno*) malloc(sizeof(Aluno));
        if(novo == NULL)
            exit(1);
        if(fgets(novo->nome, 81, arq) == NULL) {
            free(novo);
            break;
        }
        novo->nome[strcspn(novo->nome, "\n")] = '\0';
        if(fgets(novo->matricula, 20, arq) == NULL) {
            free(novo);
            break;
        }
        novo->matricula[strcspn(novo->matricula, "\n")] = '\0';
        if(fscanf(arq, "%f%*c", &novo->nota) != 1) {
            free(novo);
            break;
        }
        novo->prox = NULL;
        if(lst == NULL) {
            lst = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
    }
    fclose(arq);
    return lst;
}

void imprimir(Aluno *lst) {
    while(lst != NULL) {
        printf("Nome: %s\nMatricula: %s\nNota: %.2f\n", lst->nome, lst->matricula, lst->nota);
        lst = lst->prox;
    }
}

Aluno* incluir(Aluno *lst) {
    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
    if(novo == NULL)
        exit(1);
    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]", novo->nome);
    printf("Digite a matricula do aluno: ");
    scanf(" %[^\n]", novo->matricula);
    printf("Digite a nota do aluno: ");
    scanf("%f", &novo->nota);
    novo->prox = NULL;
    if(lst == NULL)
        return novo;
    else {
        Aluno *temp = lst;
        while(temp->prox != NULL)
            temp = temp->prox;
        temp->prox = novo;
        return lst;
    }
}

Aluno* excluir(Aluno *lst, const char *matricula) {
    Aluno *atual = lst, *ant = NULL;
    while(atual != NULL) {
        if(strcmp(atual->matricula, matricula) == 0) {
            if(ant == NULL) {
                lst = atual->prox;
                free(atual);
                return lst;
            } else {
                ant->prox = atual->prox;
                free(atual);
                return lst;
            }
        }
        ant = atual;
        atual = atual->prox;
    }
    return lst;
}

void alterar(Aluno *lst, const char *matricula) {
    while(lst != NULL) {
        if(strcmp(lst->matricula, matricula) == 0) {
            printf("Digite novo nome: ");
            scanf(" %[^\n]", lst->nome);
            printf("Digite nova matricula: ");
            scanf(" %[^\n]", lst->matricula);
            printf("Digite nova nota: ");
            scanf("%f", &lst->nota);
            return;
        }
        lst = lst->prox;
    }
    printf("Aluno nao encontrado.\n");
}

int main(){
    Aluno *lista = carregarArquivo("alunos.txt");
    int op;
    char mat[20];
    do {
        printf("\n1- Imprimir\n2- Incluir\n3- Excluir\n4- Alterar\n5- Sair\n");
        scanf("%d", &op);
        switch(op) {
            case 1:
                imprimir(lista);
                break;
            case 2:
                lista = incluir(lista);
                break;
            case 3:
                printf("Digite a matricula do aluno a excluir: ");
                scanf("%s", mat);
                lista = excluir(lista, mat);
                break;
            case 4:
                printf("Digite a matricula do aluno a alterar: ");
                scanf("%s", mat);
                alterar(lista, mat);
                break;
        }
    } while(op != 5);
    while(lista != NULL) {
        Aluno *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
    return 0;
}
