#include <stdio.h>
#include <stdlib.h>
#define L 3
#define C 4

void calcular_medias(float * pnotas, float * pmedias);

int main() {

	int i, j;
	
	float* notas = (float*) malloc(L*C*sizeof(float));
	float* medias = (float*) malloc(L*sizeof(float));

	for(i = 0; i < L; i++) {
		for(j = 0; j < C; j++) {
			printf("Digite a %d nota do %d aluno: \n", j, i);
			scanf("%f", notas + i*C + j);
		}
	}

	calcular_medias(notas, medias);

	for(i = 0; i < L; i++) {
		printf("Media aluno %d: %f\n", i, *(medias+i));
	}
	
	return 0;
}

void calcular_medias(float * pnotas, float * pmedias) {

	int i, j, soma;
	
	for(i = 0; i < L; i++) {
		soma = 0;
		for(j = 0; j < C; j++) {
			soma = soma + *(pnotas + i*C + j);
		}
		*(pmedias+i) = soma / 4;
	}
}

