#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

void *func(void *arg) {
	while(1);
}

void stop() {
	char buff[100];
	scanf("%s", buff);
}

int main() {
	stop();
	pthread_t id;
	pthread_create(&id, NULL, &func, NULL);
	stop();
	void *result;
	//pthread_join(id, result);
	stop();
	return 0;
}
