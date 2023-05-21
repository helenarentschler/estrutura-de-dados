#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No No;

struct No {

	int chave;
	No* prox;
};

void insereInicio(No** pultimo, int k);
void imprimeLista(No* ultimo);
void removeChave(No** pultimo, int k);
void sorteio(No** partida);

int main() {

	srand(time(NULL));
	
	No* ultimo = NULL; 

	for(int i = 1; i <= 10; i++) {

		insereInicio(&ultimo, i);
	}

	imprimeLista(ultimo);

	sorteio(&ultimo->prox);


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


void sorteio(No** partida) {

	int random = (rand() % 10) + 1;
					
	No* paux = (*partida);

	for(int i = 1; i <= random; i++) {

		paux = paux->prox;	
	}	
	
	No* proximo = paux->prox;

	printf("Soldado Eliminado: %d\n", paux->chave);

	removeChave(partida, paux->chave);
	
	if(*partida == (*partida)->prox) {

		printf("Soldado final: %d\n", (*partida)->chave);

	} else {

		return sorteio(&proximo);
	}
}




