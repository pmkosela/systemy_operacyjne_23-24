#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define BUFF_SIZE 100

void parent(int *deskryptory) {
	char *data = "data";
	write(deskryptory[1], data, strlen(data));
	close(deskryptory[1]);
}

void first_child(int *deskryptory, int nr_dziecka) {
	char buffer[BUFF_SIZE];
	read(deskryptory[0], buffer, BUFF_SIZE);
	printf("Dziecko %d: %s\n", nr_dziecka, buffer);
}

void second_child(int *deskryptory, int nr_dziecka) {
	first_child(deskryptory, nr_dziecka);
}

int main() {
	int deskryptory[2];
	pipe(deskryptory);
	if (fork()) {
		if (fork()) {
			parent(deskryptory);
		} else {
			first_child(deskryptory, 1);
		}

	} else {
		second_child(deskryptory, 2);
	}
	return 0;
}
