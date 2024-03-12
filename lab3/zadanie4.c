#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <pthread.h> // POSIX

unsigned  X;

void *func(void *p) {
	X = 1;
	printf("hello thread\n");
}

int main() {
	X = 7;
	pthread_t id;
	pthread_create(&id, NULL, func, NULL);
	unsigned s;
	pthread_join(id, &s);
	printf("X: %d\n", X); //1
}
