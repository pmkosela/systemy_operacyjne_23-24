#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 8
#define M 8

int matrix[N][M];
pthread_mutex_t dont_touch = PTHREAD_MUTEX_INITIALIZER;
unsigned global_sum = 0;

// Zadanie 2
int sum_items() {
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			sum += matrix[i][j];
		}
	}
	return sum;
}

// Zadanie 3
void *sum_row(void *arg) {
	int row_num = *((int *)arg);
	int *sum = malloc(sizeof(int));
	*sum = 0;
	for (unsigned i = 0; i < M; ++i) {
			*sum += matrix[row_num][i];
	}
	return sum;
}

// Zadanie 4
void *sum_row_global(void *arg) {
	int row_num = *((int *)arg);
	// Zadanie 5

	// 		Zadanie 6 -- nie działa
	/*while(dont_touch);
	dont_touch = 1;*/
    pthread_mutex_lock(&dont_touch); // <-- blokuje!
    //if(!pthread_mutex_trylock(&dont_touch)) {
    int current_sum = global_sum;

    for (unsigned i = 0; i < M; ++i) {
            current_sum += matrix[row_num][i];
    }
    sleep(current_sum % 3);

    global_sum = current_sum;
    //dont_touch = 0;
    pthread_mutex_unlock(&dont_touch);
}

int main() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			matrix[i][j] = rand() % 20;
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	// Zadanie 3, jeden wiersz
	/*pthread_t id;
	int row_num = 1;
	pthread_create(&id, NULL, &sum_row, &row_num);
	void *row_sum;
	pthread_join(id, &row_sum);
	unsigned row_sum_tmp = *((int *)row_sum);*/
	pthread_t ids[N];
	for (unsigned i = 0; i < N; ++i) {
		int *my_i = malloc(sizeof(int));
		*my_i = i;
		// Zad3: pthread_create(&ids[i], NULL, &sum_row, my_i);
		pthread_create(&ids[i], NULL, &sum_row_global, my_i);
		// wyciek pamięci!
	}
	int sum = 0;
	for (unsigned i = 0; i < N; ++i) {
		void *row_sum;
		pthread_join(ids[i], &row_sum);
		//sum += *((int *)row_sum);
	}

	printf("Matrix sum: %d\n", sum_items());
	//printf("1st row sum: %d\n", row_sum_tmp);
	// printf("Threaded sum: %d\n", sum);
	printf("Threaded sum global: %d\n", global_sum);
	return 0;
}
