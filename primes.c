#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FD_READ 0   // file descriptrior de lectura
#define FD_WRITE 1  // file descriptor de escritur
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

void
create_filter(int read_fd)
{
	int prime;
	if (read(read_fd, &prime, sizeof(int)) <= 0) {
		// No more primes
		return;
	}

	printf("primo %i \n", prime);
	fflush(stdout);

	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if (pid == 0) {
		// Child
		close(fd[WRITE_END]);
		create_filter(fd[READ_END]);
		exit(0);
	}

	// Parent
	close(fd[READ_END]);

	int num;
	while (read(read_fd, &num, sizeof(int)) > 0) {
		if (num % prime != 0) {
			write(fd[WRITE_END], &num, sizeof(int));
		}
	}

	close(fd[WRITE_END]);
	wait(NULL);
}

int
main(int argc, char *argv[])
{
	int max = atoi(argv[1]);

	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) {
		// Child
		close(fd[WRITE_END]);
		create_filter(fd[READ_END]);
		exit(0);
	}

	// Parent
	close(fd[READ_END]);

	for (int i = 2; i <= max; i++) {
		write(fd[WRITE_END], &i, sizeof(int));
	}

	close(fd[WRITE_END]);
	wait(NULL);
	return 0;
}