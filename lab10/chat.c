#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>

/*
 * Czat dla dwóch użytkowników
 */

#define BUFF_SIZE 100
#define FIRST_READ_FIFO "/tmp/f1"
#define FIRST_WRITE_FIFO "/tmp/f2"

int main() {
	unsigned jestem_pierwszy = 1;

	struct stat s;
	if (stat(FIRST_READ_FIFO, &s) == 0) {
		if (S_ISFIFO(s.st_mode)) {
			jestem_pierwszy = 0;
		}
	}

	if (jestem_pierwszy) {
		printf("tworze kolejki\n");
		//stwórz kolejkę
		unsigned ret = mkfifo(FIRST_READ_FIFO, 0666);
		if (ret) {
			printf("błąd\n");
			return -1;
		}
		ret = mkfifo(FIRST_WRITE_FIFO, 0666);
		if (ret) {
			printf("błąd\n");
			return -1;
		}
	}

	if (fork()) {
		// zapis
		int write_fd;
		if (jestem_pierwszy)
			write_fd = open(FIRST_WRITE_FIFO, O_WRONLY);
		else
			write_fd = open(FIRST_READ_FIFO, O_WRONLY);
		if (write_fd < 0) {
			printf("błąd\n");
			return -1;
		}

		char buffer[BUFF_SIZE];
		memset(buffer, '\0', BUFF_SIZE);
		while (1) {
			scanf("%s", buffer);
			unsigned bytes = write(write_fd,
					buffer,
					strlen(buffer));
			//printf("Wysłanych: %d", bytes);
		}
		// usuwanie kolejki -- unlink(...)
	} else {
		// odczyt
		int read_fd;
		if (jestem_pierwszy)
			read_fd = open(FIRST_READ_FIFO, O_RDONLY);
		else
			read_fd = open(FIRST_WRITE_FIFO, O_RDONLY);
		if (read_fd < 0) {
			printf("błąd\n");
			return -1;
		}

		//odczytuj i drukuj
		char buffer[BUFF_SIZE];
		memset(buffer, '\0', BUFF_SIZE);
		while (1) {
			unsigned bytes = read(read_fd,
					buffer,
					BUFF_SIZE);
			if (bytes != 0)
				printf("%s\n", buffer);
		}
	}
}
