#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LEN 200
#define BUFF_LEN 50

int main(int argc, char **argv) {
	printf("%s\n", argv[0]);// argv[0] -> char * <=> string
	if (argc < 3) {
		printf("Too few arguments\n");
		return -1;
	}
	//char path[MAX_PATH_LEN];
	char *path;
	//memset(path, '\0', MAX_PATH_LEN); <-- tak nie robimy
	//scanf("%s", path);
	path = argv[1]; // może lepiej skopiować
	//path[1] = 'u'; <-- tak też nie robimy
	printf("Path: %s\n", path);
	           //[O_WRONLY | O_RDONLY | O_RDWR]
	int fd_read = open(path, O_RDONLY);//file descriptor
	if (fd_read < 0) {
		perror("open");
		return -1;
	}
	//scanf("%s", path);
	path = argv[2];
	int fd_write = open(path, O_WRONLY | O_CREAT, 0666);
	if (fd_write < 0) {
		perror("write");
		return -1;
	}
	char buffer[BUFF_LEN];
	memset(buffer, '\0', BUFF_LEN);
	unsigned bytes;
	while ((bytes = read(fd_read, buffer, BUFF_LEN - 1))) {
		printf("%s\n---\n", buffer);
		write(fd_write, buffer, strlen(buffer));
		memset(buffer, '\0', BUFF_LEN);
	}
	close(fd_write);
	close(fd_read);
	return 0;
}
