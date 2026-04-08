#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct_ALUNO {
    char nome[81];
    float nota1, nota2;
} ALUNO;

void mostrarAprovados(FILE *arq) { // a)
    ALUNO alu;
    rewind(arq);
    while(fread(&alu, sizeof(ALUNO), 1, arq) == 1) {
        if((alu.nota1 + alu.nota2)/2 >= 6.0)
            printf("%s %.2f %.2f\n", alu.nome, alu.nota1, alu.nota2);
    }
}

void incluirAluno(FILE *arq) {
    ALUNO alu;
    fseek(arq, 0, SEEK_END);
    scanf(" %[^\n]", alu.nome);
    scanf("%f %f", &alu.nota1, &alu.nota2);
    fwrite(&alu, sizeof(ALUNO), 1, arq);
}

void consultarAluno(FILE *arq) {
    char nome[81];
    ALUNO alu;
    scanf(" %[^\n]", nome);
    rewind(arq);
    int achou = 0;
    while(fread(&alu, sizeof(ALUNO), 1, arq) == 1) {
        if(strcmp(alu.nome, nome) == 0) {
            printf("%s %.2f %.2f\n", alu.nome, alu.nota1, alu.nota2);
            achou = 1;
            break;
        }
    }
    if(!achou)
        printf("Aluno nao encontrado\n");
}

void alterarAluno(FILE *arq) {
    char nome[81];
    ALUNO alu;
    scanf(" %[^\n]", nome);
    rewind(arq);
    while(fread(&alu, sizeof(ALUNO), 1, arq) == 1) {
        if(strcmp(alu.nome, nome) == 0) {
            fseek(arq, -sizeof(ALUNO), SEEK_CUR);
            scanf(" %[^\n]", alu.nome);
            scanf("%f %f", &alu.nota1, &alu.nota2);
            fwrite(&alu, sizeof(ALUNO), 1, arq);
            return;
        }
    }
    printf("Aluno nao encontrado\n");
}

void excluirAluno(FILE *arq) {
    FILE *temp = fopen("temp.bin", "wb");
    if(temp == NULL){
        printf("ERRO");
        exit(1);
    }
    char nome[81];
    ALUNO alu;
    scanf(" %[^\n]", nome);
    rewind(arq);
    while(fread(&alu, sizeof(ALUNO), 1, arq) == 1) {
        if(strcmp(alu.nome, nome) != 0)
            fwrite(&alu, sizeof(ALUNO), 1, temp);
    }
    fclose(arq);
    fclose(temp);
    remove("alunos.bin");
    rename("temp.bin", "alunos.bin");
}

int main(){
    FILE *arq = fopen("alunos.bin", "rb+");
    if(arq == NULL) {
        arq = fopen("alunos.bin", "wb+");
        if(arq == NULL){
            printf("ERRO");
            exit(1);
        }
    }
    int op, rodando = 1;
    while(rodando){
        scanf("%d", &op);
        switch(op){
            case 1:
                incluirAluno(arq);
                break;
            case 2:
                alterarAluno(arq);
                break;
            case 3:
                consultarAluno(arq);
                break;
            case 4:
                excluirAluno(arq);
                arq = fopen("alunos.bin", "rb+");
                break;
            case 5:
                mostrarAprovados(arq);
                break;
            case 6:
                rodando = 0;
                break;
        }
    }
    fclose(arq);
    return 0;
}
