#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define BUFF_SIZE 100

void parent(int *deskryptory) {
	char napis[BUFF_SIZE];
	//char *napis = "tesT";
	scanf("%s", napis);
	unsigned sent = 0;
	unsigned total = 0;
	for (unsigned i = 0; i < 100; ++i) {
		sent = write(deskryptory[1], napis, strlen(napis));
		total += sent;
		printf("W%d", total);
	}
	//close(deskryptory[1]);
}

void child(int *deskryptory) {
	printf("I am child\n");
	char bufor[BUFF_SIZE];
	int read_size = 1;
	read_size = read(deskryptory[0], bufor, BUFF_SIZE);
	printf("%s", bufor);
	printf("R%d", read_size);
	unsigned total = 0;
	while (read_size > 0) {
		read_size = read(deskryptory[0], bufor, BUFF_SIZE);
		printf("%s", bufor);
		total += read_size;
		printf("R%d", total);
	}
	printf("koncze dzialanie");
}

int main() {
	int deskryptory[2];
	pipe(deskryptory);
	if (fork()) {
		parent(deskryptory);
		int status;
		wait(&status);
	} else {
		child(deskryptory);
	}
	return 0;
}
