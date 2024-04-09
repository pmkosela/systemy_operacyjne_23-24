#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *cat_f(void* _) {
    pthread_mutex_lock(&mutex);
    // mutex zajęty
    pthread_cond_wait(&cond_var, &mutex); // mutex wolny
    // mutex znowu zajęty
    printf("Cat works\n");
}

void *alarm_f(void *_) {
    sleep(3);
    // obudzenie kota
    pthread_cond_signal(&cond_var);
}

int main() {
    pthread_t alarm, cat;
    pthread_create(&alarm, NULL, &alarm_f, NULL);
    pthread_create(&cat, NULL, &cat_f, NULL);

    void *ret_val;
    pthread_join(alarm, &ret_val);
    pthread_join(cat, &ret_val);

    return 0;
}
