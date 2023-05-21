#include <stdio.h>
#include <stdlib.h>

typedef struct No No;

struct No {

	int chave;
	No* prox;
};

void insereInicio(No** pultimo, int k);
void imprimeLista(No* ultimo);
void removeInicio(No** pultimo);
void removeChave(No** pultimo, int k);
void rotacionaHorario(No** pultimo);
void rotacionaAntiHorario(No** pultimo);
void insereFim(No** pultimo, int k);

int main() {

	No* ultimo = NULL;

	insereInicio(&ultimo, 3);
	insereInicio(&ultimo, 2);
	insereInicio(&ultimo, 1);

	/*
	imprimeLista(ultimo);
	
	removeChave(&ultimo, 2);
	imprimeLista(ultimo);
	removeChave(&ultimo, 1);
	imprimeLista(ultimo);
	removeChave(&ultimo, 3);

	imprimeLista(ultimo); */

	/*rotacionaHorario(&ultimo);
	imprimeLista(ultimo);

	rotacionaAntiHorario(&ultimo);*/
	insereFim(&ultimo, 4);
	insereFim(&ultimo, 5);

	imprimeLista(ultimo);

	return 0;
}

void insereInicio(No** pultimo, int k) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {
	
		novo->chave = k;

		if(!*pultimo) {

			*pultimo = novo;
			novo->prox = novo;	

		} else {
		
			novo->prox = (*pultimo)->prox;
			(*pultimo)->prox = novo;	
		}
	} else {printf("memoria nao pode ser alocada.\n");}
}

void imprimeLista(No* ultimo) {

	if(ultimo) {

		No* paux = ultimo->prox; 

		do {

			printf("%d\n", paux->chave);
			paux = paux->prox;
			
		} while (paux != ultimo->prox);
		
	} else {printf("Lista vazia\n");}
}

void removeInicio(No** pultimo) {

	if(*pultimo) {

		if(*pultimo == (*pultimo)->prox) {

			free(*pultimo);
			*pultimo = NULL;

		} else {
		
			No* prim = (*pultimo)->prox;
			(*pultimo)->prox = prim->prox;
			free(prim);	
		}
		
	} else {printf("Lista vazia\n");}
}

void removeChave(No** pultimo, int k) {

	if(*pultimo) {

		No* paux = (*pultimo)->prox;
		
		if(paux->chave == k) {

			removeInicio(pultimo);

		} else {

			No* pant = (*pultimo)->prox;

			do {

				if(paux->chave == k) {
					break;
				}

				pant = paux;
				paux = paux->prox;
				
			} while(paux != (*pultimo)->prox);

			pant->prox = paux->prox;

			if(paux == (*pultimo)) {
			
				*pultimo = pant;
			}
			
			free(paux);	
		}
		
	} else {printf("Lista vazia\n");}
}

void rotacionaHorario(No** pultimo) {

	if(*pultimo) {

		*pultimo = (*pultimo)->prox;
			
	} else {printf("Lista vazia\n");}
}

void rotacionaAntiHorario(No** pultimo) {

	if(*pultimo) {

		No* paux = (*pultimo)->prox;
		
		do {
			paux = paux->prox;	
		} while (paux->prox != *pultimo);

		*pultimo = paux; 
			
	} else {printf("Lista vazia\n");}
}

void insereFim(No** pultimo, int k) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {
	
		novo->chave = k;

		if(!*pultimo) {

			*pultimo = novo;
			novo->prox = novo;	
			
		} else {

			novo->prox = (*pultimo)->prox;
			(*pultimo)->prox = novo;
			*pultimo = novo;
		}
		
	} else {printf("memoria nao pode ser alocada.\n");}
}
