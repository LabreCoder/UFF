#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int *array;
    long *size;
} ArrayData;

sem_t array_sem;

//funções auxiliares: memcpy, memmove, memcmp, srand, rand

// Função memcpy: copia dados de uma área de memória para outra
// Função memmove: similar ao memcpy, mas segura para áreas sobrepostas
// Função memcmp: compara duas áreas de memória byte a byte
// Função srand: inicializa o gerador de números aleatórios
// Função rand: gera números aleatórios

// Imprime array completo ou resumido conforme tamanho
void print_array(int *arr, long len, const char *label) {
    printf("\n========= %s (tamanho: %ld) =========\n", label, len);
    
    if (len <= 100) {
        for (long i = 0; i < len; i++) {
            printf("%d ", arr[i]);
            if ((i + 1) % 20 == 0) printf("\n");
        }
    } else {
        printf("Primeiros 20: ");
        for (int i = 0; i < 20; i++) printf("%d ", arr[i]);
        printf("\n...\n\nÚltimos 20: ");
        for (long i = len - 20; i < len; i++) printf("%d ", arr[i]);
    }
    printf("\n\n");
}

// Remove elemento no índice e desloca restante para esquerda
void remove_element(int *arr, long *size, long idx) {
    if (idx < 0 || idx >= *size) return;
    //printf(" %d -> ", arr[idx]);      // essa linha pode ser descomentada para debug
    memmove(&arr[idx], &arr[idx + 1], (*size - idx - 1) * sizeof(int));
    
    (*size)--;
}

// Thread: remove números pares percorrendo do fim ao início
void *remove_even_numbers(void *arg) {
    ArrayData *data = (ArrayData *)arg;
    long removed_count = 0;

    for (long i = *data->size - 1; i >= 0; ) {
        sem_wait(&array_sem);
        
        if (i >= *data->size) {
            i = *data->size - 1;
            sem_post(&array_sem);
            if (i < 0) break;
            continue;
        }
        
        if (data->array[i] % 2 == 0) {
            remove_element(data->array, data->size, i);
            removed_count++;
        }
        i--;
        
        sem_post(&array_sem);
        //usleep(1000);
    }

    printf("Thread pares: %ld removidos\n", removed_count);
    return NULL;
}

// Thread: remove múltiplos de 5 percorrendo do fim ao início
void *remove_multiples_of_five(void *arg) {
    ArrayData *data = (ArrayData *)arg;
    long removed_count = 0;

    for (long i = *data->size - 1; i >= 0; ) {
        sem_wait(&array_sem);
        
        if (i >= *data->size) {
            i = *data->size - 1;
            sem_post(&array_sem);
            if (i < 0) break;
            continue;
        }
        
        if (data->array[i] % 5 == 0) {
            remove_element(data->array, data->size, i);
            removed_count++;
        }
        i--;
        
        sem_post(&array_sem);
    }

    printf("Thread múltiplos de 5: %ld removidos\n", removed_count);
    return NULL;
}

// Aloca e preenche array com números aleatórios de 1 a 100
int* create_random_array(long len) {
    int *arr = malloc(len * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Erro ao alocar memória!\n");
        exit(1);
    }
    
    srand(time(NULL));
    for (long i = 0; i < len; i++) 
        arr[i] = (rand() % 100) + 1;
    
    return arr;
}

// Valida resultado comparando com processamento sequencial
// Retorna 1 se correto, 0 se incorreto
int validate_result(int *original, long orig_len, int *result, long result_len) {
    int *temp = malloc(orig_len * sizeof(int));
    if (!temp) exit(1);
    
    memcpy(temp, original, orig_len * sizeof(int));
    long len = orig_len;

    // Remove pares sequencialmente
    for (long i = len - 1; i >= 0; i--) {
        if (temp[i] % 2 == 0) {
            memmove(&temp[i], &temp[i + 1], (len - i - 1) * sizeof(int));
            len--;
        }
    }
    
    // Remove múltiplos de 5 sequencialmente
    for (long i = len - 1; i >= 0; i--) {
        if (temp[i] % 5 == 0) {
            memmove(&temp[i], &temp[i + 1], (len - i - 1) * sizeof(int));
            len--;
        }
    }

    // Compara resultados
    int is_valid = (len == result_len && memcmp(temp, result, len * sizeof(int)) == 0);

    if (!is_valid) {
        printf("\n❌ VALIDAÇÃO FALHOU!\n");
        printf("Esperado: %ld | Obtido: %ld\n", len, result_len);
        print_array(temp, len, "Esperado");
        print_array(result, result_len, "Obtido");
    } else {
        printf("\n-------------------\n✓ VALIDAÇÃO PASSOU!\n-------------------\n");
        print_array(result, result_len, "Resultado");
        printf("Tamanho final: %ld elementos\n", result_len);
    }

    free(temp);
    return is_valid;
}

int main() {
    long initial_size = 1000000;
    
    // Cria array original e cópias para processamento e validação
    int *original = create_random_array(initial_size);
    int *backup = malloc(initial_size * sizeof(int));
    int *working_array = malloc(initial_size * sizeof(int));
    
    if (!backup || !working_array) {
        perror("malloc");
        exit(1);
    }
    
    memcpy(backup, original, initial_size * sizeof(int));
    memcpy(working_array, original, initial_size * sizeof(int));
    long current_size = initial_size;

    // Inicializa semáforo binário (exclusão mútua)
    sem_init(&array_sem, 0, 1);

    ArrayData data = {working_array, &current_size};
    //printf("Tamanho inicial: %ld elementos\n", initial_size);
    print_array(original, initial_size, "Array Original");

    // Cria threads e mede tempo de execução
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t thread_even, thread_mult5;
    pthread_create(&thread_even, NULL, remove_even_numbers, &data);
    pthread_create(&thread_mult5, NULL, remove_multiples_of_five, &data);

    pthread_join(thread_even, NULL);
    pthread_join(thread_mult5, NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    print_array(working_array, current_size, "Array Final");
    printf("Tamanho final após remoções: %ld elementos\n", current_size);
    printf("\nTempo de realização das threads: %.6f segundos\n", elapsed);


    // Valida resultado
    struct timespec start_valid, end_valid;
    clock_gettime(CLOCK_MONOTONIC, &start_valid);
    validate_result(backup, initial_size, working_array, current_size);

    clock_gettime(CLOCK_MONOTONIC, &end_valid);
    double elapsed_valid = (end_valid.tv_sec - start_valid.tv_sec) + (end_valid.tv_nsec - start_valid.tv_nsec) / 1e9;
    printf("Tempo de realização da validação: %.6f segundos\n", elapsed_valid);

    // Libera recursos
    free(original);
    free(backup);
    free(working_array);
    sem_destroy(&array_sem);

    return 0;
}
