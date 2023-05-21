#include <stdio.h>

void troca(int * pa, int * pb);

int main() {
	int a = 6;
	int b = 7;

	troca(&a, &b);

	printf("a: %d \n", a);
	printf("b: %d \n", b);
	
	return 0;
}

void troca(int * pa, int * pb) {
	int aux;
	aux = *pa;
	*pa = *pb;
	*pb = aux;
}
