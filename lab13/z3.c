#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define FRACTION_OF_WRITERS 0.1
#define LIB_CAPACITY 10

#define READER_OP 1
#define WRITER_OP 10

void modify_fork(int id, short op) {
	struct sembuf buf;
	buf.sem_flg = 0;
	buf.sem_op = op;
	buf.sem_num = 0;
	semop(id, &buf, 1);
}

void lock(int id, short op) {
	modify_fork(id, -op);
}

void unlock(int id, short op) {
	modify_fork(id, op);
}

void reader(int sem_id) {
	printf("Czytelnik próbuje wejść...\n");
	lock(sem_id, READER_OP);
	printf("Czytelnik czyta...\n");
	sleep(1);
	unlock(sem_id, READER_OP);
	printf("Czytelnik wyszedł\n");
}

void writer(int sem_id) {
	printf("Pisarz próbuje wejść...\n");
	lock(sem_id, WRITER_OP);
	printf("Pisarz pisze...\n");
	sleep(1);
	unlock(sem_id, WRITER_OP);
	printf("Pisarz wyszedł\n");
}

void status(int id) {
	while (1) {
		int queue = semctl(id, 0, GETNCNT, NULL);
		sleep(1);
		printf("-- QUEUED: %d\n", queue);
	}
}

int main() {
	int id = semget(123581321, 1, IPC_CREAT | 0666);
	semctl(id, 0, SETVAL, LIB_CAPACITY);

	if (!fork()) {
		status(id);
		return 0;
	}
	
	while (1) {
		char is_writer = rand() % 100 < 100 * FRACTION_OF_WRITERS;
		if (!fork()) {
			if (is_writer)
				writer(id);
			else
				reader(id);
		}
		sleep(5);
	}
}
