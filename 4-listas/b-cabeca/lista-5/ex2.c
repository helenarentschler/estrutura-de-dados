#include <stdio.h>
#include <stdlib.h>

typedef struct Soldado Soldado;

struct Soldado {

	int chave;
	Soldado* prox;	
};

void insereInicio(Soldado** ultimo, int chave);
void imprimeLista(Soldado* ultimo);
void insereFinal(Soldado** ultimo, int chave);

int main() {

	Soldado* ultimo = NULL;

	for(int i = 1; i <= 10; i++) {

		insereFinal(&ultimo, i);
	
	}	

	imprimeLista(ultimo);
	
	return 0;
}

void insereInicio(Soldado** ultimo, int chave) {
	
	Soldado* novo = (Soldado*) malloc(sizeof(Soldado));

	if(novo) {

		novo->chave = chave;

		if(*ultimo) {

			novo->prox = (*ultimo)->prox;
			(*ultimo)->prox = novo;	
			
		} else {
		
			novo->prox = novo;
			*ultimo = novo;		
		}
	}
};

void insereFinal(Soldado** ultimo, int chave) {

	if(!*ultimo) {

		insereInicio(ultimo, chave);
		
	} else {
	
		Soldado* novo = (Soldado*) malloc(sizeof(Soldado));

		if(novo) {

			novo->chave = chave;

			novo->prox = (*ultimo)->prox;
			(*ultimo)->prox = novo;
			(*ultimo) = novo;
		}
	}
}

void imprimeLista(Soldado* ultimo) {

	if(ultimo) {

		Soldado* paux = ultimo->prox;
		
		do {

			printf("%d\n", paux->chave);
			paux = paux->prox;
			
		} while(paux != ultimo->prox);
		
	} else {printf("Lista vazia.\n");}
}
