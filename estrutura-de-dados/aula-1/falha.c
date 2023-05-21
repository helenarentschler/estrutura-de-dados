#include <stddef.h>
#include <stdio.h>

int main() {
	int *p = NULL;

	if (p)
		*p = 4;
	else
		printf("Ponteiro nao aponta para endereço nenhum");
	return 0;
}
