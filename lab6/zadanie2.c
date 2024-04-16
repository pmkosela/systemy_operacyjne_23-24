#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define BUFF_SIZE 100

void parent(int *deskryptory) {
	char napis[BUFF_SIZE];
	close(deskryptory[0]);
        
        while(1) {
                char in = ' ';
                unsigned i = 0;
                // pętla nie kończy wczytywać po spacji
                while (in != '\n') {
                        in = getc(stdin);
                        napis[i] = in;
                        ++i;
                }
                write(deskryptory[1], napis, strlen(napis));
        }
	close(deskryptory[1]);
}

void child(int *deskryptory) {
	close(deskryptory[1]);// <-- winowajca
	char bufor[BUFF_SIZE];
	int read_size = 1;
	while (read_size > 0) {
		read_size = read(deskryptory[0], bufor, BUFF_SIZE);
                if (read_size > 0)
	                printf("%s", bufor);

	}
	printf("%s", bufor);
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
