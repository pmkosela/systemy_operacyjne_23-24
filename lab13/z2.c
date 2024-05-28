#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define NO_PHILOSOPHERS 4

void modify_fork(int id, int fork_id, short op) {
	struct sembuf buf;
	buf.sem_flg = 0;
	buf.sem_op = op;
	buf.sem_num = fork_id;
	semop(id, &buf, 1);
}

void unlock_fork(int id, int fork_id) {
	modify_fork(id, fork_id, 1);
}

void lock_fork(int id, int fork_id) {
	modify_fork(id, fork_id, -1);
}

void philosopher(int sem_id, int phil_id) {
	printf("i am philosopher %d\n", phil_id);
	int left = phil_id - 1;
	int right = phil_id % NO_PHILOSOPHERS;
	while (1) {
		printf("phil %d thinks\n", phil_id);
		sleep(1);
		lock_fork(sem_id, left);
		//sleep(1);
		lock_fork(sem_id, right);
		printf("phil %d eats\n", phil_id);
		sleep(1);
		unlock_fork(sem_id, left);
		unlock_fork(sem_id, right);
	}
}

int main() {
	int id = semget(1123581321, NO_PHILOSOPHERS, IPC_CREAT | 0666);
	unsigned short sem_vals[NO_PHILOSOPHERS];
	for (unsigned i = 0; i < NO_PHILOSOPHERS; ++i)
		sem_vals[i] = 1;
	semctl(id, 0, SETALL, sem_vals);
	
	for (unsigned i = 0; i < NO_PHILOSOPHERS; ++i) {
		if (!fork()) {
			philosopher(id, i + 1);
			break;
		}
	}
	while (1);
}
