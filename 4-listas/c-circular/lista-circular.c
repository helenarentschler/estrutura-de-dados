#include <stdio.h>
#include <stdlib.h>

typedef struct No {
	int chave;
	struct No* prox;
} Tno;

void insereInicio(Tno** ppult, int chave);
void imprimeLista(Tno* pult);
Tno* buscaNo(Tno* pult, int chave);
void removeInicio(Tno** ppult);
void removeChave(Tno** ppult, int chave);
void removeTodos(Tno** ppult);

int main() {
	Tno* ult = NULL;

	insereInicio(&ult, 1);
	insereInicio(&ult, 2);
	insereInicio(&ult, 3);
	insereInicio(&ult, 4);

	removeChave(&ult, 1);
	printf("ultimo e prim: %d %d\n", ult->chave, ult->prox->chave);
	imprimeLista(ult);

	removeTodos(&ult);

 	imprimeLista(ult);

	return 0;
}

void insereInicio(Tno** ppult, int chave) {

	Tno* novo = (Tno*) malloc(sizeof(Tno));
	
	if(novo) {

		novo->chave = chave;

		if(!*ppult) {

			novo->prox = novo;
			*ppult = novo;
			
		} else {
			novo->prox = (*ppult)->prox;
			(*ppult)->prox = novo;
		}
		
	} else {printf("Memoria nao alocada\n");}
}

void imprimeLista(Tno* pult) {

	if(pult) {

		Tno* paux = pult->prox;

		do {
		
			printf("No {chave: %d, endereço: %p}\n", paux->chave, paux);

			paux = paux->prox;
			
		} while(paux != pult->prox);
		
	} else {printf("Lista vazia\n");}
}

Tno* buscaNo(Tno* pult, int chave) {

	if(pult) {

		Tno* paux = pult->prox;

		do {
		
			if(paux->chave == chave) {

				return paux;
			}

			paux = paux->prox;
			
		} while(paux != pult->prox);

		return NULL;
		
	} else {printf("Lista vazia\n");}
}

void removeInicio(Tno** ppult) {

	if(*ppult){

		Tno* pprim = (*ppult)->prox;
		(*ppult)->prox = pprim->prox;
		free(pprim);
		
	} else {printf("Lista vazia\n");}
}

void removeChave(Tno** ppult, int chave) {

	if(*ppult) {

		//lista tem mais de 1 elem
		if(*ppult != (*ppult)->prox){

			//é o primeiro da lista
			if((*ppult)->prox->chave == chave) {

				removeInicio(ppult);
				
			} else {
			
				Tno* paux = (*ppult)->prox;
				Tno* pant = (*ppult)->prox;
	
				do {
					pant = paux;
					paux = paux->prox;
				} while(paux->chave != chave);
	
				pant->prox = paux->prox; 

				//é o ultimo da lista
				if(paux == *ppult) 
					*ppult = pant;
				
				free(paux);	
			}

		} else {

			free(*ppult);
			*ppult = NULL;
		}
		
	} else {printf("Lista vazia\n");}
}

