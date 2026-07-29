
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define LINHAS 500
#define COLUNAS 500
#define NUM_THREADS 4

typedef struct {
    int começo;
    int fim;
    int *m1;
    int *m2;
    int *resultado;
} TesteThread;

int *criar_matriz(int k) {
    int *matriz;
    matriz = (int *) malloc(LINHAS * COLUNAS * sizeof(int));

    if (matriz == NULL) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            matriz[i * COLUNAS + j] = k;
            k += 2;
        }
        k += 2;
    }
    return matriz;
}

void print_matriz(int *matriz1){
    if (matriz1 != NULL) {
        printf("Matriz criada com sucesso:\n");
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                printf("%d\t", matriz1[i * COLUNAS + j]);
            }
            printf("\n");
        }
        free(matriz1);
    }
}

int* soma_matriz(int *m1, int *m2, int linhas){
    int *m3 = (int *) malloc(linhas * COLUNAS * sizeof(int));
    if (m1 == NULL || m2 == NULL ){
        printf("Erro de alocacao");
        return NULL;
    }
    int total_elem = linhas * COLUNAS;
    for(int i=0; i < total_elem; i++){
        m3[i] = m1[i] + m2[i];
    }
    return m3;
}

void *threadSoma(void *arg){
    TesteThread *dados = (TesteThread*)arg;

    int *matriz1 = dados->m1;
    int *matriz2 = dados->m2;
    int *resultado = dados->resultado;
    int inicio = dados->começo;
    int fim = dados->fim;

    for (int i = inicio; i < fim; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int idx = i * COLUNAS + j;
            resultado[idx] = matriz1[idx] + matriz2[idx];
        }
    }
    return NULL;
}

int main() {
    struct timespec start, end;
    double tempo_total_ns_semThreads;
    double tempo_total_ns_comThreads;

    int *matriz1 = criar_matriz(4);
    int *matriz2 = criar_matriz(7);

    clock_gettime(CLOCK_MONOTONIC, &start);
    int *matriz3 = soma_matriz(matriz1, matriz2, LINHAS);
    clock_gettime(CLOCK_MONOTONIC, &end);
    tempo_total_ns_semThreads = (end.tv_sec - start.tv_sec) * 1.0e9 + (end.tv_nsec - start.tv_nsec);

    pthread_t *threads = (pthread_t*)malloc(NUM_THREADS * sizeof(pthread_t));
    if (threads == NULL) {
        perror("Erro na alocacao de memoria");
        return 2;
    }

    int *resultado_threads = (int *) malloc(LINHAS * COLUNAS * sizeof(int));

    TesteThread arg_threads[NUM_THREADS];
    int linhasPorThread = LINHAS / NUM_THREADS;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for(int i = 0; i < NUM_THREADS; i++){
        arg_threads[i].m1 = matriz1;
        arg_threads[i].m2 = matriz2;
        arg_threads[i].resultado = resultado_threads;
        arg_threads[i].começo = i * linhasPorThread;

        if (i == NUM_THREADS - 1){
            arg_threads[i].fim = LINHAS;
        } else {
            arg_threads[i].fim = (i + 1) * linhasPorThread;
        }

        pthread_create(&threads[i], NULL, threadSoma, (void *)&arg_threads[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    tempo_total_ns_comThreads = (end.tv_sec - start.tv_sec) * 1.0e9 + (end.tv_nsec - start.tv_nsec);

    printf("Tempo com Threads em nanossegundos -> %.0f\n", tempo_total_ns_comThreads);
    printf("Tempo sem Threads em nanossegundos -> %.0f\n", tempo_total_ns_semThreads);

    free(matriz1);
    free(matriz2);
    free(matriz3);
    free(resultado_threads);
    free(threads);

    return 0;
}
