#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct No {
	int chave;
	struct No* prox;
} tNo;

tNo* alocaNo(int k);
tNo* criaCabeca();
tNo* insereInicio(tNo* pcabeca, int k);
void imprimeLista(tNo* paux);
tNo* buscaNo(tNo* paux, int k);
void removeInicio(tNo* pcabeca);

int main() {

	tNo* cabeca = criaCabeca();
	tNo* achado = NULL;

	printf("\n%d", cabeca->chave);
		
	insereInicio(cabeca, 1);
	insereInicio(cabeca, 2);
	insereInicio(cabeca, 3);

	imprimeLista(cabeca->prox);
	achado = buscaNo(cabeca->prox, -1); 

	if(achado) {
		printf("Achado: %d\n", achado->chave);		
	} else {
		printf("Nao encontrado.\n");
	}

	removeInicio(cabeca);
	imprimeLista(cabeca->prox);

	return 0;
}

tNo* alocaNo(int k) {

	tNo* pnovo = (tNo*) malloc(sizeof(tNo));

	if(pnovo) {
		pnovo->chave = k;
		pnovo->prox = NULL;
		return pnovo;
	}

	return NULL;
}

tNo* criaCabeca() {

	tNo* pcabeca = alocaNo(-1);

	return pcabeca;
}

tNo* insereInicio(tNo* pcabeca, int k) {

	if(pcabeca) {

		tNo* pnovo = alocaNo(k);	

		if(pnovo) {
			pnovo->prox = pcabeca->prox;	
			pcabeca->prox = pnovo;	
		} else {printf("Nao foi possivel alocar novo no\n");}
		
	} else {printf("Nao existe no cabeça\n");}
}

void imprimeLista(tNo* paux) {

	if(paux) {

		while(paux) {
		
			printf("Chave: %d, Endereço: %p\n", paux->chave, paux);
			paux = paux->prox;	
		}
		
	} else {printf("Lista vazia.\n");}
}

tNo* buscaNo(tNo* paux, int k) {

	if(paux) {

		while(paux) {
		
			if(paux->chave == k) {
				return paux;
			}
			
			paux = paux->prox;	
		}

		return NULL;		
		
	} else {
	
		printf("Lista vazia.\n");
		return NULL;
	}
}

void removeInicio(tNo* pcabeca) {

	if(pcabeca) {
	
		if(pcabeca->prox) {
		
			tNo* paux = pcabeca->prox;
			pcabeca->prox = paux->prox;
			free(paux);
			paux = NULL;
			printf("Primeiro item removido com sucesso.\n");
				
		} else {printf("Lista vazia.\n");}
		
	} else {printf("Nao existe no cabeça\n");}
}
