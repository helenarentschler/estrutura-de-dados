#include <stdio.h>

double * max(double * pvet, int size);

int main() {

	double vetor[5] = {5, 9.6, 0.3, 8.4, 7};

	double * pmaior = NULL;
		
	pmaior = max(vetor, 5);

	printf("%f", *pmaior);
	
	return 0;
}

double * max(double * pvet, int size) {

	int i;
	double * pmaior = pvet;

	if (pvet) {
	
		for(i = 0; i < size; i++) {
			if(*(pvet+i) > *pmaior) {
				pmaior = pvet+i;
			}
		}
		return pmaior;
		
	} else {
	
		return NULL;	
		
	}

}

