#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
	int numero = atoi(argv[1]);
	if (numero < 0) {
		printf("no se aceptan numeros menores a 0");
	}
	int *numeros = malloc(sizeof(int) * numero);
	for (int i = 0; i < numero; i++) {
		numeros[i] = i + 2;
		printf("%i \n", numeros[i]);
	}
	free(numeros);


	return 0;
}