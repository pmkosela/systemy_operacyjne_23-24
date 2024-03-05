#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

const int NO_CHILDREN = 5;

void child() {
	while(1);
}

void parent() {
	/*for (unsigned i = 0; i < NO_CHILDREN; ++i) {
		int status;
		pid_t child_pid = wait(&status);
		printf("%d: skończył działanie\n", child_pid);
	}*/
}

int main() {
	//int *no_children = malloc(sizeof(int));
	pid_t *children_pids = malloc(sizeof(pid_t) * NO_CHILDREN);

	unsigned i_am_child = 0; //false
	for (unsigned i = 0; i < NO_CHILDREN; ++i) {
		pid_t pid = fork();
		children_pids[i] = pid;
		if (!pid) {
			i_am_child = 1;
			break;
		}
	}

	if (i_am_child) {
		child();
	} else {
		parent();
	}
	

	return 0;
}
