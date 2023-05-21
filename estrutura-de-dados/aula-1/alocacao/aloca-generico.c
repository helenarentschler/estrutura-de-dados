#include <stdio.h>
#include <stdlib.h>

void alocar(void** pp, int* ptam, int flag);
void inicializar(void* p, int tam, int flag);
void imprimir(void* p, int tam, int flag);
void desalocar(void** pp);

int main() {
	int tam1 = 0, tam2 = 0, tam3 = 0;
	void *vetor1=NULL, *vetor2=NULL, *vetor3=NULL;

	alocar(&vetor1, &tam1, 1);
	alocar(&vetor2, &tam2, 2);
	alocar(&vetor3, &tam3, 3);

	inicializar(vetor1, tam1, 1);
	inicializar(vetor2, tam2, 2);
	inicializar(vetor3, tam3, 3);

	imprimir(vetor1, tam1, 1);
	imprimir(vetor2, tam2, 2);
	imprimir(vetor3, tam3, 3);	

	return 0;
}

void alocar(void** pp, int* ptam, int flag) {

	if(!*pp) {
		printf("Quantas posiçoes deseja alocar?\n");
		scanf("%d", ptam);
		
		if(flag == 1) {
			*pp = (char*) malloc(*ptam * sizeof(char));
		} else if (flag == 2) {
			*pp = (int*) malloc(*ptam * sizeof(int));
		} else if (flag == 3){
			*pp = (float*) malloc(*ptam * sizeof(float));
		}	
	}

	if(!*pp) {
		printf("Nao foi possivel alocar o vetor.\n");
	}
}

void inicializar(void* p, int tam, int flag) {

	if(p) {
		int i;
		
		printf("Com qual valor deseja inicializar o vetor?\n");

		if(flag == 1) {
		
			char valorc, *pc = (char*)p;
			setbuf(stdin, NULL);
			scanf("%c", &valorc);
			
			for(i=0; i<tam; i++){
				*(pc+i) = valorc;
			}
			
		} else if (flag == 2) {
		
			int valori, *pi = (int*)p;
			scanf("%d", &valori);

			for(i=0; i<tam; i++){
				*(pi+i) = valori;
			}
			
		} else if (flag == 3){
		
			float valorf, *pf = (float*)p;
			scanf("%f", &valorf);

			for(i=0; i<tam; i++){
				*(pf+i) = valorf;
			}
			
		}	
		
	} else {printf("Vetor nao existe.\n");}
}

void imprimir(void* p, int tam, int flag) {

	if(p) {

		int i;

		if(flag == 1) {
		
			char *pc = (char*)p;
			
			for(i=0; i<tam; i++){
				printf("%c\n", *(pc+i));
			}
			
		} else if (flag == 2) {
		
			int *pi = (int*)p;

			for(i=0; i<tam; i++){
				printf("%d\n", *(pi+i));
			}
			
		} else if (flag == 3){
		
			float *pf = (float*)p;

			for(i=0; i<tam; i++){
				printf("%f\n", *(pf+i));
			}
			
		}	
		
	} else {printf("Vetor nao existe.\n");}
}

void desalocar(void** pp) {
	if(*pp) {
		free(*pp);
		*pp = NULL;
	}
}

