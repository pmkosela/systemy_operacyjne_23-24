#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>

#define STR1 "kot"
#define STR2 "pies"

int main() {
	size_t size;
	if (strlen(STR1) > strlen(STR2))
		size = strlen(STR1);
	else
		size = strlen(STR2);
	int id = shmget(1123581321, size, IPC_CREAT | 0600);
	char *shared = shmat(id, NULL, 0);
	
	while (1) {
		if (!strcmp(shared, STR1) && !strcmp(shared, STR2)) {
			printf("%ld err\n", time(NULL));
		}
	}
}
