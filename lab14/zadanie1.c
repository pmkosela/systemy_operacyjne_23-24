#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LEN 200
#define BUFF_LEN 50

int main() {
	char path[MAX_PATH_LEN];
	memset(path, '\0', MAX_PATH_LEN);
	scanf("%s", path);
	printf("Path: %s\n", path);
	           //[O_WRONLY | O_RDONLY | O_RDWR]
	int fd_read = open(path, O_RDONLY);//file descriptor
	if (fd_read < 0) {
		perror("open");
		return -1;
	}
	
	scanf("%s", path);
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
	return 0;
}
