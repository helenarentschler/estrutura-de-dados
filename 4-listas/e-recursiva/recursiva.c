//removerNo
//removertodos
//tamanhodalista

#include <stdio.h>
#include <stdlib.h>

typedef struct No No;

struct No {

	int chave;
	No* prox;	
};

void insereInicio(No** prim, int k);
void imprimeLista(No* paux);
void imprimeListaInverso(No* paux);
int soma(No* paux);
int multiplica(No* paux);
void adicionarFinal(No** prim, int k);
No* busca(No* paux, int k);

int main() {

	No* prim = NULL;

	insereInicio(&prim, 1);
	insereInicio(&prim, 2);
	insereInicio(&prim, 3);
	insereInicio(&prim, 4);

	//imprimeLista(prim);
	imprimeListaInverso(prim);

	int total = soma(prim);

	printf("total: %d\n", total);

	int produto = multiplica(prim);

	printf("produto: %d\n", produto);

	adicionarFinal(&prim, 5);

	imprimeLista(prim);

	No* achado = busca(prim, 4);

	printf("achado: %d\n", achado->chave);

}

void insereInicio(No** prim, int k) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {

		novo->chave = k;
		novo->prox = *prim;
		*prim = novo;

	} else {printf("Nao foi possivel alocar memoria\n");}
}

void imprimeLista(No* paux) {
 
	if(paux == NULL) {
		return;
	}

	printf("%d\n", paux->chave);
	imprimeLista(paux->prox);
}

void imprimeListaInverso(No* paux) {
 
	if(paux == NULL) {
		return;
	}

	imprimeListaInverso(paux->prox);
	printf("%d\n", paux->chave);
}

int soma(No* paux) {

	if(paux == NULL) {
		return 0;
	}
	
	return paux->chave + soma(paux->prox);
}

int multiplica(No* paux) {

	if(paux == NULL) {
		return 1;
	}

	return paux->chave * multiplica(paux->prox);
}

void adicionarFinal(No** prim, int k) {

	if(*prim) {
	
		No* paux = *prim;
		
		if(paux->prox == NULL) {
		
			No* novo = (No*) malloc(sizeof(No));
	
			if(novo) {
	
				novo->chave = k;
				novo->prox = NULL;
				paux->prox = novo;
	
				return;
				
			} else {
	
				printf("Nao foi possivel alocar memoria\n");
				return;
			}
		}
	
		adicionarFinal(&paux->prox, k);		

	} else {

		insereInicio(prim, k);	
	}
}

No* busca(No* paux, int k) {

	if(paux == NULL || paux->chave == k) {

		return paux;
	} 

	//usa return?
	busca(paux->prox, k);
}

void removeTodos() {
	
}
