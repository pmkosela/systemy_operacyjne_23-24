#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

const unsigned N = 5;

void parent() {
	for (unsigned i = 0; i < 5; ++i) {
		unsigned s;
		pid_t child_pid;
		child_pid = wait(&s);
		printf("PID %d zakończył działanie.\n", child_pid);
	}
}

void child(unsigned my_id) {
	unsigned time = (my_id + 1) * 2;
	sleep(time);
}

int main() {
	unsigned i_am_child = 0;
	for (unsigned i = 0; i < N; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			i_am_child = 1;
			child(i);
			break;
		}
	}
	if (!i_am_child)
		parent();
}
