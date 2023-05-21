#include <stdio.h>

void imprimirEnderecosVetor(float * pvet);
void imprimirValoresVetor(float * pvet);

int main() {

	float vetor[10] = {2.65, 7.4, 9.3, 89.7, 0.5, 21.7, 7.8, 63.4, 59.43, 0.2};
	
	imprimirEnderecosVetor(vetor);
	imprimirValoresVetor(vetor);
	
	return 0;
}

void imprimirEnderecosVetor(float * pvet) {
	int i;

	for(i = 0; i < 10; i++) {
		printf("%p\n", pvet+i);
	};
}

void imprimirValoresVetor(float * pvet) {
	int i;
	
	for(i = 0; i < 10; i++) {
		printf("%f\n", *(pvet+i));
	};
}
