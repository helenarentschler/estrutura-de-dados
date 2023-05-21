#include <stdio.h>
#include <stdlib.h>

int * alocar(int nPos);
void inicializar(int nPos, int valor, int * vet);
void imprimir(int nPos, int * vet);
void desalocar(int ** pVet);
int * desalocaAlt(int * vet);
void imprimirGenerico(void * vet, int nPos, int flag);

int main() {

	int * vet;
	int * vet1;
	int n = 0, valor = 0;
	
	printf("Quantas posiçoes deseja alocar?");
	
	scanf("%d", &n);

	vet = alocar(n);

	printf("Endereço dos primeiros 4 bytes alocados: %p \n", vet);

	printf("Com qual valor deseja inicializar o vetor?");

	scanf("%d", &valor);

	inicializar(n, valor, vet);

	imprimir(n, vet);

	desalocar(&vet);

	return 0;
}

int * alocar(int nPos) {

	int * vet;

	vet = (int *) malloc(nPos * sizeof(int));

	if(!vet) {
		printf("SO nao alocou memoria.\n");
	}

	return vet;
}

void inicializar(int nPos, int valor, int * vet) {

	if(vet) {
	
		int i;
			
		for(i = 0; i < nPos; i++){
			*(vet+i) = valor;
		}	
	} else {

		printf("vetor é nulo.");
	}
}

void imprimir(int nPos, int * vet) {

	if(vet) {
	
		int i;

		for(i = 0; i < nPos; i++) {
			printf("%p : %d \n", vet+i, *(vet+i));
		}
	} else {
	
		printf("vetor é nulo.");
	}
}

void desalocar(int ** pVet) {

	if(*pVet) {
	
		free(*pVet);
		*pVet = NULL;
	}
}

int * desalocaAlt(int * vet) {

	if(vet) {

		free(vet);
		return NULL;
	}
}

void imprimeGenerico(void * vet, int nPos, int flag) {

	if(vet) {
		if(flag == 1) {

			for(i = 0; i < nPos; i++){
				printf("%c", (char *)(vet+i));
			}
			
		} else if (flag == 2){
			
		}
	}
}
