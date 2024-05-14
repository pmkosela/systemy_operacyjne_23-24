#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define QUEUE_ID 11235813

// typ > 0!
#define MSG_DEF 1
struct my_msg {
	// long -- koniecznie pierwsze
	long type;
	unsigned value; //unsigned
};

int main() {
	// int
	//int queue_id = msgget(QUEUE_ID, IPC_CREAT | 0666);
	int queue_id = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
	if (queue_id < 0) {
		perror("msgget");
		return -1;
	}
	if (fork()) {
		// parent
		struct my_msg message = {MSG_DEF, 17};
		unsigned bytes = msgsnd(queue_id,
				        &message,
				        sizeof(unsigned),
				        0);
		if (bytes < 0) {
			perror("msgsnd");
			return -1;
		}
	} else {
		// child
		struct my_msg message;
		unsigned bytes = msgrcv(queue_id,
					&message,
					sizeof(unsigned),
					0,
					0);
		if (bytes < 0) {
			perror("msgrcv");
			return -1;
		} else {
			printf("Wczytano %d bajtów\n", bytes);
			printf("Liczba: %d\n", message.value);
		}

		// msgctl(...) -- zarządzanie kolejkami
	}
	return 0;
}
