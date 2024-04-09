#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const unsigned K = 5;
const unsigned K_DELTA = 7;
const unsigned T = 1;
const unsigned M = 3;

pthread_cond_t DELIVER = PTHREAD_COND_INITIALIZER;

pthread_mutex_t PUDLO_MUTEX = PTHREAD_MUTEX_INITIALIZER;
unsigned PUDLO = 0;

void *magazynier_f(void* _) {
    while(1) {
        //pthread_mutex_lock(&PUDLO_MUTEX);
        pthread_cond_wait(&DELIVER, &PUDLO_MUTEX);
        sleep(T);
        PUDLO += K_DELTA;
        printf("Dostawa: %d\n", K_DELTA);
        //pthread_mutex_unlock(&PUDLO_MUTEX);
    }
}

void *budowniczy_f(void *_) {
    while(1) {
        sleep(1);
        pthread_mutex_lock(&PUDLO_MUTEX);
        if (PUDLO >= K) {
            PUDLO -= K;
            sleep(1);
            printf("Zbudowano, %d w pudle\n", PUDLO);
            pthread_mutex_unlock(&PUDLO_MUTEX);
        } else {
            pthread_mutex_unlock(&PUDLO_MUTEX);
            printf("Zawołano magazyniera\n");
            pthread_cond_signal(&DELIVER);
        }
    }
}

int main() {
    pthread_t budowniczy, magazynier;
    pthread_create(&magazynier, NULL, &magazynier_f, NULL);
    pthread_create(&budowniczy, NULL, &budowniczy_f, NULL);

    void *ret_val;
    pthread_join(magazynier, &ret_val);
    pthread_join(budowniczy, &ret_val);

    return 0;
}
