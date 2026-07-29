#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

void *imprime_info_thread(void *threadid){
    long tid;
    tid = (long)threadid;
    printf("Olá, eu sou a thread com TID #%ld com YY = ", tid+1);
    
    long YY = pthread_self();    
    printf("%lu e ZZ = ", YY);
    
    long ZZ = syscall(SYS_gettid);
    printf("%ld!\n", ZZ);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int NUM_THREADS = 0;
    printf("Por favor, informe a quantidade de Threads desejadas: ");
    scanf("%d", &NUM_THREADS);
    
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("Estou creating thread %ld\n", t+1);
        rc = pthread_create(&threads[t], NULL, imprime_info_thread, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    pthread_join(threads[t], NULL);
    }
    /* Last thing that main() should do */
    pthread_exit(NULL);
}
