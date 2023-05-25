#include <stdio.h>
#include <stdlib.h>

typedef struct Cabeca Cabeca;
typedef struct No No; 

struct Cabeca {

	No* inicio;
	int qnt;
};

struct No {

	int chave;
	No* prox;
};

int vazia(Cabeca* cabeca);
Cabeca* criaCabeca();
void empilha(Cabeca* cabeca, int k);
void desempilha(Cabeca* cabeca);
void imprime(No* aux);
int topo(Cabeca* cabeca);

int main() {

	Cabeca* pilhaA = NULL;
	Cabeca* pilhaB = NULL;
	Cabeca* pilhaC = NULL;

	empilha(pilhaA, 3);
	empilha(pilhaA, 2);
	empilha(pilhaA, 1);

	return 0;
}

int vazia(Cabeca* cabeca) {

	if(!cabeca->inicio) {

		return 1;

	} else {

		return 0;
	}
}

Cabeca* criaCabeca() {

	Cabeca* cabeca = (Cabeca*) malloc(sizeof(Cabeca));

	if(cabeca) {

		cabeca->inicio = NULL;
		cabeca->qnt = 0;

	} else {printf("Não foi possível alocar memória.\n");}

	return cabeca;
}

void empilha(Cabeca* cabeca, int k) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {

		novo->chave = k;
		novo->prox = cabeca->inicio;
		cabeca->inicio = novo;
		(cabeca->qnt)++;

	} else {printf("Não foi possível alocar memória.\n");}
}

void desempilha(Cabeca* cabeca) {

	if(vazia(cabeca) == 0) {

		No* aux = cabeca->inicio;
		cabeca->inicio = cabeca->inicio->prox;
		free(aux);
		(cabeca->qnt)--;

	} else {printf("Pilha vazia\n");}
}

int topo(Cabeca* cabeca) {

	if (vazia(cabeca) == 1) {
		
		return -1;
	
	} else {
	
		return cabeca->inicio->chave;
	}
}

void imprime(No* aux) {

	if(aux) {

		while(aux != NULL) {

			printf("%d\n", aux->chave);
			aux = aux->prox;
		}

	} else {printf("Pilha vazia\n");}
}


void ordenaRanoi(Cabeca* pilhaA, Cabeca* pilhaB, Cabeca* pilhaC) {

	if (topo(pilhaA)) {
		
	}
}