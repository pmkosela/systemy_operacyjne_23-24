#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	printf("[1] procesy\n");
	printf("[2] katalog\n");
	unsigned choice;
	scanf("%d", &choice);
	if (choice == 1) {
		execlp("ps", "--", NULL);
	} else if (choice == 2) {
		execlp("ls", "--", NULL);
	} else {
		printf("błąd\n");
	}
}
