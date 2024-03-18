#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define FD_READ 0   // file descriptrior de lectura
#define FD_WRITE 1  // file descriptor de escritura


int
main(void)
{
	pid_t pid = fork;

	int filedescs_padre_hijo[2];
	int filedescs_hijo_padre[2];
	pipe(filedescs_padre_hijo);
	pipe(filedescs_hijo_padre);


	printf("Hola, soy PID <%d>:\n", getpid());
	printf("IDs del primer pipe: [%d, %d]:\n",
	       filedescs_padre_hijo[FD_READ],
	       filedescs_padre_hijo[FD_WRITE]);
	printf("IDs del segundo pipe: [%d, %d]:\n",
	       filedescs_hijo_padre[FD_READ],
	       filedescs_hijo_padre[FD_WRITE]);
	if (pid == 0) {
		// es elhijo
		long int hijo_value;
		close(filedescs_padre_hijo[FD_WRITE]);
		close(filedescs_hijo_padre[FD_READ]);
		read(filedescs_padre_hijo[FD_READ],
		     &hijo_value,
		     sizeof(hijo_value));
		printf("Donde fork me devuelve 0 \n");
		printf("recibo valor %ld via fd =%d\n",
		       hijo_value,
		       filedescs_padre_hijo[FD_READ]);
		printf("reenvio valor en fd=%d y termino\n",
		       filedescs_hijo_padre[FD_WRITE]);
		write(filedescs_hijo_padre[FD_WRITE],
		      &hijo_value,
		      sizeof(hijo_value));

		close(filedescs_padre_hijo[FD_READ]);
		close(filedescs_hijo_padre[FD_WRITE]);
	} else {
		// es el padre
		long int valor = 34;
		long int padre_valor;
		close(filedescs_padre_hijo[FD_WRITE]);
		close(filedescs_hijo_padre[FD_READ]);
		printf("Donde fork me devuelve %d \n", pid);
		printf("Valor %ld\n", valor);
		printf("envio valor %ld a traves de fd = %d\n",
		       valor,
		       filedescs_padre_hijo[FD_WRITE]);
		write(filedescs_padre_hijo[FD_WRITE], &valor, sizeof(valor));
		read(filedescs_hijo_padre[FD_WRITE],
		     &padre_valor,
		     sizeof(padre_valor));

		printf("Hola de nuevo, PID: %d\n", getpid());
		printf("recibi valor %ld via fd =%d\n",
		       padre_valor,
		       filedescs_hijo_padre[FD_READ]);

		close(filedescs_padre_hijo[FD_WRITE]);
		close(filedescs_hijo_padre[FD_READ]);
	}
	return 0;
}