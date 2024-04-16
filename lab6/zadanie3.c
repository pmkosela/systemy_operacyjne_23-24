#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define BUFF_SIZE 100

void parent(int *deskryptory) {
	char buffer[BUFF_SIZE];
	for (unsigned i = 0; i < 2; ++i) {
		unsigned read_s = 0;
		read_s = read(deskryptory[0], buffer, BUFF_SIZE);
		//printf("Dziecko %d: %s\n", nr_dziecka, buffer);
		printf("%d: %s\n", read_s, buffer);
	}
}

void first_child(int *deskryptory, int nr_dziecka) {
	char *data = "data";
	write(deskryptory[1], data, strlen(data));
	close(deskryptory[1]);
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
