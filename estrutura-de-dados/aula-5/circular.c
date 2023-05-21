#include <stdio.h>
#include <stdlib.h>

typedef struct No {
	int chave;
	struct No* prox;
} Tno;

void insereInicio(Tno** ppult, int chave);
void insereFinal(Tno** ppult, int chave);
void imprimeLista(Tno* pult);
void removeInicio(Tno** ppult);
void removeChave(Tno** ppult, int chave);
Tno* concatenaListas(Tno* p1, Tno* p2);

int main() {
	Tno* ult = NULL;

	insereFinal(&ult, 1);
	insereFinal(&ult, 2);
	insereFinal(&ult, 3);
	insereFinal(&ult, 4);

	imprimeLista(ult);

	removeInicio(&ult);
	removeInicio(&ult);
	removeInicio(&ult);
	removeInicio(&ult);

	imprimeLista(ult);

	return 0;
}

void insereInicio(Tno** ppult, int chave) {

	Tno* novo = (Tno*) malloc(sizeof(Tno));
	
	if(novo) {

		novo->chave = chave;

		//lista vazia
		if(!*ppult) {

			novo->prox = novo;
			*ppult = novo;
			
		} else {
			//novo olha para primeiro
			novo->prox = (*ppult)->prox;
			//ultimo olha para o novo
			(*ppult)->prox = novo;
		}
		
	} else {printf("Memoria nao alocada\n");}
}

void insereFinal(Tno** ppult, int chave) {

	Tno* novo = (Tno*) malloc(sizeof(Tno));
		
	if(novo) {

		novo->chave = chave;

		//lista vazia
		if(!*ppult) {

			novo->prox = novo;
			*ppult = novo;
			
		} else {
			//novo olha para primeiro
			novo->prox = (*ppult)->prox;
			//ultimo olha para o novo
			(*ppult)->prox = novo;
			// o utimo agora é o novo
			*ppult = novo;
		}
		
	} else {printf("Memoria nao alocada\n");}
}


void imprimeLista(Tno* pult) {

	if(pult) {
		//começa do primeiro
		Tno* paux = pult->prox;

		//executa uma vez
		do {
			printf("%d\n", paux->chave);
			paux = paux->prox;
		//enquanto paux dif do primeiro
		} while (paux != pult->prox);
		
	} else {printf("Lista vazia\n");}
}

void removeInicio(Tno** ppult) {
	
	if(*ppult) {
		
		if(*ppult == (*ppult)->prox) {

			free(*ppult);
			*ppult = NULL;

		} else {
		
			Tno* paux = (*ppult)->prox;		
			(*ppult)->prox = paux->prox;
			free(paux);
		}
			
	} else {printf("Lista vazia\n");}
}

void removeChave(Tno** ppult, int chave) {

	Tno* paux = (*ppult)->prox;		
	
	if(paux->chave == chave) {

		removeInicio(ppult);

	} else {

		Tno* pant = (*ppult)->prox;

		do {

			if(paux->chave == chave) {
				pant->prox = paux->prox;
				free(paux);
			}
			
			pant = paux;
			paux = paux->prox;
			
		} while (paux != (*ppult)->prox);
		
	}
}
