#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_LEN 100
#define DELIMITER " "
#define PIPE "|"

unsigned count_tokens(char *buffer,
		      char *delimiter) {
	char *token = strtok(buffer, delimiter);
	unsigned count = 0;
	while (token != NULL) {
		++count;
		token = strtok(NULL, delimiter);
	}
	return count;
}

void tokenize_command(char *buffer,
		      char *delimiter,
		      char **out_tokens) {
	char *token = strtok(buffer, delimiter);
	unsigned i = 0;
	while (token != NULL) {
		out_tokens[i++] = token;
		token = strtok(NULL, delimiter);
	}
}

void execute_command(char *buffer) {
	unsigned no_tokens;
	char buffer_copy[BUFFER_LEN];
	strcpy(buffer_copy, buffer);
        no_tokens = count_tokens(buffer_copy,
		      	         DELIMITER);
	
	unsigned token_bytes = sizeof(char *) *
			       (no_tokens + 1);
	char **tokens = malloc(token_bytes);
	tokenize_command(buffer,
			 DELIMITER,
			 tokens);
	tokens[no_tokens] = NULL;

	if (fork()) {
		// parent
		int s;
		wait(&s);
	} else {
		// child
		//execlp(buffer, "--", NULL);
		/*execvp(char *plik_wykonywalny,
		      char **tablica_argumentów // <-- null terminated*/
		execvp(tokens[0], tokens);
	}
}

void console() {
	char buffer[BUFFER_LEN];
	fgets(buffer, BUFFER_LEN, stdin);
	unsigned nl_pos = strlen(buffer) - 1;
	buffer[nl_pos] = '\0';

	unsigned no_commands;
	char buffer_copy[BUFFER_LEN];
	strcpy(buffer_copy, buffer);
        no_commands = count_tokens(buffer_copy,
		      	           PIPE);

	unsigned token_bytes = sizeof(char *) * no_commands;
	char **tokens = malloc(token_bytes);
	strcpy(buffer_copy, buffer);
	tokenize_command(buffer_copy, DELIMITER, tokens);

	if (no_commands == 1) { 
		execute_command(buffer);
	} else {
		const unsigned no_pipes = no_commands - 1;
		int *pipes = malloc(no_pipes * 2 * sizeof(int));
		const unsigned pipes_len = no_pipes * 2;
		for (unsigned i = 0; i < pipes_len; i += 2)
			pipe(pipes + i);

		for (unsigned i = 0; i < no_commands; ++i) {
			if (fork()) {
				// parent
				int s;
				for (unsigned i = 0; i < no_commands; ++i) {
					wait(&s);
				}
			} else {
				// child
				execute_command(tokens[i]);
				exit(0);
			}
		}
	}

}

int main() {
	while (1)
		console();
	return 0;
}
