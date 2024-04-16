#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define BUFF_SIZE 100
/*
	pipe_read
	pipe_write
	stdin --> wc

	stdin	0
	stdout	1
	stderr	2

	ls --> stdout --> pipe_write --> pipe_read --> stdin --> wc
*/

void parent(int *deskryptory, char *plik) {
	//int t = dup(deskryptory[0]);
	//dup2(deskryptory[0], 1);
	dup2(1, deskryptory[1]);
	execlp(plik, "--", NULL);
}

void child(int *deskryptory, char *plik) {
	dup2(deskryptory[0], 0);
	execlp(plik, "--", NULL);
}

int main() {
	int deskryptory[2];
	pipe(deskryptory);
	if (fork()) {
		parent(deskryptory, "ls");
	} else {
		child(deskryptory, "wc");
	}
	return 0;
}
