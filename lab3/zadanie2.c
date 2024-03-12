#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

const unsigned N = 5;

void parent() {
	unsigned s;
	unsigned count = 0;
	while (1) {
		sleep(1);
		printf("-\n");
		pid_t child_pid = waitpid(-1, &s, WNOHANG);
		//child_pid == 0 <- żadne dziecko nie skończyło
		//child_pid != 0 <- pid dziecka
		if (child_pid) {
			printf("PID %d skończył.\n", child_pid);
			count += 1;
		}
		if (count == N)
			break;
	}
}

void child(unsigned my_id) {
	unsigned time = (my_id + 1) * 3;
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
