#include <stdio.h>
#include <stdlib.h>

typedef struct No No;

struct No {

	int chave;
	No* prox;
	No* ant;
};

void insereInicio(No** prim, int k);
void imprime(No* aux);
void removeInicio(No **prim);

int main() {

	No* prim = NULL;
	
	insereInicio(&prim, 1);

	imprime(prim);

	removeInicio(&prim);

	imprime(prim);
	return 0;
}

void insereInicio(No** prim, int k) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {

		novo->chave = k;
		
		if(*prim == NULL) {
	
			novo->prox = NULL;
			novo->ant = NULL;
			*prim = novo;

		} else {

			novo->prox = *prim;
			novo->ant = NULL;
			(*prim)->ant = novo;
			*prim = novo;	
		}
		
	} else {printf("Nao foi possivel alocar memoria\n");}
}

void imprime(No* aux) {

	if(aux) {

		while(aux != NULL) {

			printf("%d\n", aux->chave);
			aux = aux->prox;
		}
	} else {printf("Lista vazia\n");}
}

void removeInicio(No **prim) {

	if(*prim) {

		//se tiver um unico No
		if((*prim)->prox == NULL) {

			No* aux = *prim;
			*prim = NULL;
			free(aux);

		} else {

			*prim = (*prim)->prox;
			free((*prim)->ant);
			(*prim)->ant = NULL;	
		}

	} else {printf("Lista vazia\n");}
}

void removeChave(No **prim, int k) {

	if(*prim) {

		if((*prim)->chave == k) {

			removeInicio(prim);
		}
		
	} else {printf("Lista vazia\n");}
}
