#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int COUNTER = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment(void* _x) {
    for (int i = 0; i < 10; ++i) {
        // - lock
        printf("Zajmowanie locka\n");
        pthread_mutex_lock(&mutex);
        int local = COUNTER;
        usleep(500);
        printf("Inkrementacja\n");
        // - inkrementacja
        local += 1;
        COUNTER = local;
        // - zdjecie locka
        printf("Zdjecie locka\n");
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, &increment, NULL);
    pthread_create(&thread2, NULL, &increment, NULL);

    void *ret_val;
    pthread_join(thread1, &ret_val);
    pthread_join(thread2, &ret_val);

    printf("Counter = %d\n", COUNTER);
    return 0;
}
