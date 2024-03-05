#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void child() {
	// Kod dziecka
	printf("%d: jestem potomkiem\n", getpid());
	sleep(2);
	exit(0);
}

void parent() {
	// Kod przodka
	printf("%d: jestem przodkiem\n", getpid());
	int status;
	pid_t child_pid;
	//pid_t child_pid = wait(&status);
	child_pid = waitpid(-1, &status, WNOHANG);
	if (child_pid == 0) {
		// Brak zakończonych potomków
	} else if (child_pid < 0) {
		// Błąd funkcji wait
	} else {
		// funkcja zwróciła pid zakończonego
		// potomka
	}
	printf("potomek %d zakończył działanie\n",
		child_pid);
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
