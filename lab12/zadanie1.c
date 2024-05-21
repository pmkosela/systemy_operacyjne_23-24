#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void child(int id) {
	// przypinamy stworzony segment do pamięci procesu
	// 	      shmAT
	int *shared = shmat(id, NULL, 0); // <-- to też robi malloc()!
	/*int zmienna;
	int *shared = shmat(id, &zmienna, 0); // <-- to nie działa
	zmienna == segment współdzielony*/
	if (shared == NULL) {
		perror("shmat");
		return;
	}

	// korzystamy
	*shared = 11;
	
	// odpinamy
	//	     shmDeTach
	char error = shmdt(shared);
	if (error) { 
		perror("shmdt");
		return;
	}
}

void parent(int id) {
	// przypinamy stworzony segment do pamięci procesu
	int *shared = shmat(id, NULL, 0);
	if (shared == NULL) {
		perror("shmat");
		return;
	}

	// korzystamy
	sleep(1);
	printf("zmienna: %d\n", *shared);

	// odpinamy
	shmdt(shared);
}
//shmctl <- m.in. usuwanie segment współdzielony


int main() {
	// prosimy system o stworzenie segmentu współdzielonego
	int id = shmget(11235813, sizeof(int), IPC_CREAT | 0600);
	//int id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
	if (id < 0) {
		perror("shmget");
	}

	if (fork()) {
		parent(id);
	} else {
		child(id);
	}
}
