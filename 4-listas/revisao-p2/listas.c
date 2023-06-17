#include <stdio.h>
#include <stdlib.h>


typedef struct No {
	int chave;
	struct No* prox;
} No;

void insereInicio(No** prim, int k);
void imprime(No* aux);
void insereFim(No** prim, int k);
void removeInicio(No** prim);
void removeUltimo(No** prim);
void removeFim(No** prim);
void imprimeRecursivo(No* aux);
void imprimeRecursivoInvertido(No* aux);
void insereFimRecursivo(No** prim, int k);

int main() {

	No* listaSimples = NULL;

	insereFim(&listaSimples, 1);
	insereFim(&listaSimples, 2);
	insereFim(&listaSimples, 3);

	imprimeRecursivo(listaSimples);
	imprimeRecursivoInvertido(listaSimples);
	insereFimRecursivo(&listaSimples, 4);
		imprimeRecursivo(listaSimples);

	return 0;
}

void insereInicio(No** prim, int k) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {

		novo->chave = k;
		novo->prox = *prim;
		(*prim) = novo;
	}
}

void imprime(No* aux) {

	if(aux) {

		while(aux) {
			printf("%d\n", aux->chave);
			aux = aux->prox;
		}
	}
}

int soma(No* paux) {

	if(!paux) {
		return 0;
	}

	return paux->chave + soma(paux->prox);
}

void imprimeRecursivo(No* aux) {

	if(!aux) {
		return;
	}

	printf("%d\n", aux->chave);
	imprimeRecursivo(aux->prox);
}

void imprimeRecursivoInvertido(No* aux) {

	if(!aux) {
		return;
	}

	imprimeRecursivoInvertido(aux->prox);
	printf("%d\n", aux->chave);
}

void insereFim(No** prim, int k) {
	
	if(!*prim) {
		insereInicio(prim, k);
	} else {

		No* aux = *prim;

		while(aux->prox) {
			aux = aux->prox;
		}

		No* novo = (No*) malloc(sizeof(No));

		if(novo) {

			novo->chave = k;
			novo->prox = NULL;
			aux->prox = novo;
		}
	}
}

void insereFimRecursivo(No** prim, int k) {

	No* aux = *prim;

	if(aux) {
	
		if(aux->prox == NULL) {

			No* novo = (No*) malloc(sizeof(No));
			
			if(novo) {
	
				novo->chave = k;
				novo->prox = NULL;
				aux->prox = novo;
			}
		}
		
		insereFimRecursivo(&aux->prox, k);

	} else {

		insereInicio(prim,k);
	}
}

void removeInicio(No** prim) {

	if(*prim) {

		No* aux = *prim;
		*prim = aux->prox;
		free(aux);
	}
}

void removeChave(No** prim, int k) {

	if(*prim) {

		if((*prim)->chave == k) {

			removeInicio(prim);

		} else {

			No* aux = *prim;
			No* ant = *prim;
			
			while(aux) {

				if(aux->chave == k) {

					ant->prox = aux->prox;
					free(aux);

					return;
				}

				ant = aux;
				aux = aux->prox;
			}
		}
	}
}

void removeFim(No** prim) {

	if(*prim) {

		No* aux = *prim;
		
		while(aux->prox->prox) {
			aux = aux->prox;
		}
		
		free(aux->prox);
		aux->prox = NULL;		
	}
}
