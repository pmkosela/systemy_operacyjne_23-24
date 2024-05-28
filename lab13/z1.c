#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

/*struct sembuf {
	   unsigned short sem_num;  semaphore number 
           short          sem_op;   semaphore operation
           short          sem_flg;  operation flags 
}*/

void lock(int id) {
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	semop(id, &buf, 1);
	//semop(id, [buf1, buf2, buf3...], 3);
}

void unlock(int id) {
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	semop(id, &buf, 1);
}

void parent(int id) {
	while (1) {
		lock(id);
		printf("rodzic zajmuje\n");
		sleep(2);
		unlock(id);
		printf("rodzic odblokował\n");
	}
}

void child(int id) {
	while (1) {
		lock(id);
		printf("potomek zajmuje\n");
		sleep(2);
		unlock(id);
		printf("potomek odblokował\n");
	}
}

int main() {
	int id = semget(11235813, 1, IPC_CREAT | 0666);
	semctl(id, 0, SETVAL, 1);
	if (fork()) {
		parent(id);
	} else {
		child(id);
	}
}
