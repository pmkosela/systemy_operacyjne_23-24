#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

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

	unsigned i = 0;
	while(1) {
		sleep(1);
		if (i) {
			strcpy(shared, STR1);
		} else {
			strcpy(shared, STR2);
		}
		i = (i + 1) % 2;
	}
}
