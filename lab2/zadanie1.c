#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void child() {
	// Kod dziecka
	printf("%d: jestem potomkiem\n", getpid());
	pid_t pid = fork();
	while(1);
}

void parent() {
	// Kod przodka
	printf("%d: jestem przodkiem\n", getpid());
	pid_t pid = fork();
	if (!pid)
		child();
	while(1);
}

int main() {
	pid_t pid = fork();
	if (pid) {
		parent();
	} else {
		child();
	}
	return 0;
}
