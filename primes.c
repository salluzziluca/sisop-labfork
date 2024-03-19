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

	int filedescs_padre_hijo[2];
	int filedescs_hijo_padre[2];
	pipe(filedescs_padre_hijo);
	pipe(filedescs_hijo_padre);

	pid_t pid = fork();

	if (pid == 0) {
		close(filedescs_padre_hijo[FD_WRITE]);
		int numero_filtro;
		int numero_actual;
		if (numero_actual % numero_filtro != 0) {
		}
		read(filedescs_padre_hijo[FD_READ],
		     &numero_filtro,
		     sizeof(numero_filtro));
		printf("primo: %i \n", numero_filtro);

		// hijo
		// usa el primer numero que le llega como filtro (ese numero que le llega tmb es primo)
	} else {
		for (int i = 0; i < numero; i++) {
			close(filedescs_padre_hijo[FD_READ]);
			int numero_actual = i + 2;
			if ((numero_actual) % 1 == 0) {
				write(filedescs_padre_hijo[FD_WRITE],
				      &numero_actual,
				      sizeof(numero_actual));
			}

			return 0;
		}
		// padre
	}
}