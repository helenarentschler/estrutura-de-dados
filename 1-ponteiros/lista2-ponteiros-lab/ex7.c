#include <stdio.h>

void somar(int * pa, int b);

int main() {
	int a = 15, b = 5;

	somar(&a, b);

	printf("Soma: %d, b: %d", a, b);
	
	return 0;
}

void somar(int * pa, int b) {
	*pa = *pa + b;
}
