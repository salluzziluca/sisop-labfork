#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FD_READ 0   // file descriptrior de lectura
#define FD_WRITE 1  // file descriptor de escritura

int
main(int argc, char *argv[])
{
	int numero = atoi(argv[1]);
	if (numero < 0) {
		printf("no se aceptan numeros menores a 0");
	}
	pid_t pid = fork();

	if (pid == 0) {
		// hijo
		// usa el primer numero que le llega como filtro (ese numero que le llega tmb es primo)
	} else {
		// padre
	}

	int *filedescs_padre_hijo[2];
	int *filedescs_hijo_padre[2];
	pipe(filedescs_padre_hijo);
	pipe(filedescs_hijo_padre);

	for (int i = 0; i < numero; i++) {
		printf("%i \n", i + 2);
		if ((i + 2) % 2 != 0) {
			write(filedescs_padre_hijo[FD_WRITE], i + 2, sizeof(i + 2));
		}

		return 0;
	}
}