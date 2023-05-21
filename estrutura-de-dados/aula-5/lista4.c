#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct No {
	int chave;
	struct No* prox;
} tNo;

tNo* aloca(int chave);
void insereInicio(tNo** ppPrim, int chave);
void imprimeLista(tNo* pAux);
void removeInicio(tNo** ppPrim);
void removeTodos(tNo** ppPrim);
void removeChave(tNo** ppPrim, int chave);
tNo* buscaItem(tNo* pAux, int chave);
tNo* buscaMaior(tNo* pAux);
tNo* buscaMenor(tNo* pAux);
void inserefinal(tNo* pPrim, int chave);
int somaItens(tNo* pPrim);
int tamanhoLista(tNo* pAux);
int frequenciaItem(tNo* pAux, int chave);
tNo* copiarLista(tNo* pAux);

int main() {
	tNo* prim = NULL;
	insereInicio(&prim, 3);
	insereInicio(&prim, 4);
	imprimeLista(prim);
	removeInicio(&prim);
	imprimeLista(prim);
	removeTodos(&prim);
	imprimeLista(prim);
	insereInicio(&prim, 5);
	imprimeLista(prim);

	tNo* achado = buscaItem(prim, 5);

	if(achado){
		printf("Achado: %d\n", achado->chave);
	} else {
		printf("Nao achado.\n");
	}

	insereInicio(&prim, 6);
	insereInicio(&prim, 1);

	tNo* maior = buscaMaior(prim);
	
	if(maior){
		printf("Maior: %d\n", maior->chave);
	} 

	tNo* menor = buscaMenor(prim);
		
	if(menor){
		printf("Menor: %d\n", menor->chave);
	}
	
	insereInicio(&prim, 8);
	insereInicio(&prim, 8);
	insereInicio(&prim, 3);
	insereInicio(&prim, 8);
	
	printf("Soma das chaves: %d\n", somaItens(prim));
	printf("Tamanho da lista: %d\n", tamanhoLista(prim));
	printf("Ocorrencias na lista: %d\n", frequenciaItem(prim, 8));

	removeChave(&prim, 1);
	imprimeLista(prim);

	tNo* lista2 = copiarLista(prim);

	printf("Lista 2:\n");
	imprimeLista(lista2);

	return 0;
}

tNo* aloca(int chave) {

	tNo* pNo;
	pNo = (tNo*) malloc(sizeof(tNo));
		
	if(pNo) {
		pNo->chave = chave;
		pNo->prox = NULL;
	} else {printf("No nao alocado.\n");}

	return pNo;
}

void insereInicio(tNo** ppPrim, int chave) {

	assert(ppPrim);

	tNo* pNovo = aloca(chave);

	if(pNovo) {
	
		tNo* pAntigo = *ppPrim;
		
		pNovo->prox = pAntigo;
		
		*ppPrim = pNovo;	
	}
}

void inserefinal(tNo* pPrim, int chave) {

	tNo* pAux = pPrim;

	//para no ultimo da lista(quando pAux->PROX = NULL)
	while(pAux->prox) {
		pAux = pAux->prox;
	}

	tNo* pNovo = aloca(chave);
	
	if(pNovo) {

		pAux->prox = pNovo;
	}
}

void imprimeLista(tNo* pAux) {

	if(pAux) {

		while(pAux) {
			printf("Chave: %d, Endereço: %p\n", pAux->chave, pAux);
			pAux = pAux->prox;	
		}
	} else {printf("Lista vazia.\n");}
}

void removeInicio(tNo** ppPrim) {

	assert(ppPrim);

	if(*ppPrim) {
	
		tNo* pAux = *ppPrim;
		*ppPrim = (*ppPrim)->prox;
		free(pAux);
		printf("Primeiro item removido com sucesso.\n");
	} else {printf("Lista vazia. \n");}
}

void removeTodos(tNo** ppPrim) {

	assert(ppPrim);
	
	if(*ppPrim) {
	
		tNo* pRmv = NULL;

		while(*ppPrim) {
			pRmv = *ppPrim;
			*ppPrim = (*ppPrim)->prox;	
			free(pRmv);
		}
		
		printf("Lista removida com sucesso.\n");
	} else {printf("Lista ja esta vazia. \n");}
}

tNo* buscaItem(tNo* pAux, int chave) {

	if(pAux) {
		
		while(pAux) {

			if(pAux->chave == chave) {
				
				return pAux;		
			} 
			
			pAux = pAux->prox;				
			
		}

		return NULL;

	} else {printf("Lista vazia. \n");}
}

tNo* buscaMaior(tNo* pAux) {

	if(pAux) {

		tNo* pMaior = pAux;

		while(pAux) {

			if(pAux->chave > pMaior->chave) {
				pMaior = pAux;
			} 
			
			pAux = pAux->prox;				
		}

		return pMaior;

	} else {printf("Lista vazia. \n");}
}

tNo* buscaMenor(tNo* pAux) {

	if(pAux) {

		tNo* pMenor = pAux;

		while(pAux) {

			if(pAux->chave < pMenor->chave) {
				pMenor = pAux;
			} 
			
			pAux = pAux->prox;				
		}

		return pMenor;

	} else {printf("Lista vazia. \n");}
}



void removeChave(tNo** ppPrim, int chave) {

	assert(ppPrim);

	if((*ppPrim)->chave == chave) {

		removeInicio(ppPrim);
	} else {

		tNo* pRmv = *ppPrim;
		tNo* pAnt = *ppPrim;

		while(pRmv) {

			if(pRmv->chave == chave) {
				pAnt->prox = pRmv->prox;	
				free(pRmv);
				return;
			}
			
			pAnt = pRmv;
			pRmv = pRmv->prox;
		}
	}
}

int somaItens(tNo* pAux) {

	if(pAux) {

		int soma = 0;
		
		while(pAux) {
			soma += pAux->chave;
			pAux = pAux->prox;				
		}

		return soma;

	} else {printf("Lista vazia. \n");}
}

int tamanhoLista(tNo* pAux) {

	if(pAux) {

		int i = 0;
		
		while(pAux) {
			i++;
			pAux = pAux->prox;				
		}

		return i;

	} else {printf("Lista vazia. \n");}
}

int frequenciaItem(tNo* pAux, int chave) {

	if(pAux) {
	
		int i = 0;
		
		while(pAux) {

			if(pAux->chave == chave) {
				i++;	
			}
			
			pAux = pAux->prox;				
		}

		return i;

	} else {printf("Lista vazia. \n");}
}

tNo* copiarLista(tNo* pAux) {

	if(pAux) {
	
		tNo* copia = NULL;

		//insere a primeira chave em copia 
		insereInicio(&copia, pAux->chave);

		//move pAux para o segundo elemento
		pAux = pAux->prox;

		//A partir do segundo, insere sucessivamente no final de copia
		while(pAux) {
			inserefinal(copia, pAux->chave);
			pAux = pAux->prox;
		}		

		return copia;
	} else {printf("Lista vazia. \n");}
}
