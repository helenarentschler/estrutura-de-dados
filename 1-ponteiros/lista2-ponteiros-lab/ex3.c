#include <stdio.h>

void troca(int * pa, int * pb);
void ordene(int * pa, int * pb, int * pc);

int main() {
	int a = 0, b = 0, c = 0;

	printf("Digite um numero inteiro: \n");
	scanf("%d", &a);
	printf("Digite outro numero inteiro: \n");
	scanf("%d", &b);
	
	printf("a = %d, b = %d\n", a, b);
	
	troca(&a, &b);

	printf("TROCA a = %d, b = %d\n", a, b);

	printf("Digite um terceiro numero inteiro: \n");
	scanf("%d", &c);

	ornene(&a, &b, &c);
	
	return 0;
}

void troca(int * pa, int * pb) {
	int aux = 0;

	aux = *pa;
	*pa = *pb;
	*pb = aux;
}

void ordene(int * pa, int * pb, int * pc) {
	int aux = 0;
	
	
}
