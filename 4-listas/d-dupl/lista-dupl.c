#include <stdio.h>
#include <stdlib.h>

typedef struct no {

	int info;
	struct no* ant;
	struct no* prox;
	
} tNo;

void insereInicio(tNo** pplista, int info);
void imprimeLista(tNo* plista);
void remover(tNo** pplista, int info);

int main() {

	tNo* lista = NULL;

	insereInicio(&lista, 12);
	insereInicio(&lista, 13);
	insereInicio(&lista, 14);

	imprimeLista(lista);

	remover(&lista, 13);

	printf("\n");
	
	imprimeLista(lista);

	return 0;
}

/* tNo* insereInicio(tNo* plista, int info) {

	tNo* novo = (tNo*) malloc(sizeof(tNo));

	if(novo) {

		novo->info = info;
		novo->ant = NULL;
		novo->prox = plista;	
	}

	//se lista nao vazia
	if(plista) {
		plista->ant = novo;
	}

	return novo;
} */

void insereInicio(tNo** pplista, int info) {

	tNo* novo = (tNo*) malloc(sizeof(tNo));

	if(novo) {

		novo->info = info;
		novo->ant = NULL;
		novo->prox = *pplista;	
	}

	//se lista nao vazia
	if(*pplista) {
	
		(*pplista)->ant = novo;
	}

	(*pplista) = novo;
}

void imprimeLista(tNo* paux) {

	if(paux) {

		for(; paux != NULL; paux = paux->prox) {
			printf("Info: %d\n", paux->info);
		}
	} else {printf("Lista vazia\n");}
}

void removeInicio(tNo** pplista){

	if(*pplista) {

		(*pplista) = (*pplista)->prox;
		free((*pplista)->ant);
		(*pplista)->ant = NULL;
				
	} else {printf("Lista vazia\n");}
}

void remover(tNo** pplista, int info) {

	if(*pplista) {
		//if((*pplista->info == info))
		if(!(*pplista)->ant) {

			removeInicio(pplista);
			
		} else {

			tNo* paux = *pplista; 
			tNo* pant = *pplista; 

			while(paux != NULL) {

				if(paux->info == info) {

					pant->prox = paux->prox;

					//se nao é o ultimo	
					if(paux->prox)
						paux->prox->ant = paux->ant;

					free(paux); 

					return;
				} 

				pant = paux;
				paux = paux->prox;
			}

			printf("Informaçao nao encontrada\n");
		}	
	} else {printf("Lista vazia\n");}
}
