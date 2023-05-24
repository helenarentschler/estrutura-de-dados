#include <stdio.h>
#include <stdlib.h>

typedef struct Cabeca Cabeca;
typedef struct No No; 

struct Cabeca {

	No* inicio;
	No* fim;	
};

struct No {

	int chave;
	No* prox;
};

int vazia(Cabeca* cabeca);
Cabeca* criaCabeca();
void insereFila(Cabeca* cabeca, int chave);
void removeFila(Cabeca* cabeca);
void empilha(Cabeca* cabeca, int k);
void desempilha(Cabeca* cabeca);
void imprime(No* paux);
void filaParaPilha(Cabeca* fila, Cabeca* pilha);
void pilhaParaFila(Cabeca* pilha, Cabeca* fila);

int main() {

	Cabeca* fila = criaCabeca();
	Cabeca* pilha = criaCabeca();

	insereFila(fila, 1);
	insereFila(fila, 2);
	insereFila(fila, 3);
	insereFila(fila, 4);

	imprime(fila->inicio);

	filaParaPilha(fila, pilha);

	imprime(pilha->inicio);

	imprime(fila->inicio);

	pilhaParaFila(pilha, fila);

	imprime(pilha->inicio);

	imprime(fila->inicio);

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
		cabeca->fim = NULL;

	} else {printf("Não foi possível alocar memória.\n");}

	return cabeca;
}

void insereFila(Cabeca* cabeca, int chave) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {

		novo->chave = chave;
		novo->prox = NULL;

		if(vazia(cabeca) == 1) {

			cabeca->fim = novo;
			cabeca->inicio = novo;
		
		} else {
			
			cabeca->fim->prox = novo;
			cabeca->fim = novo;	
		}

	} else {printf("Não foi possível alocar memória\n");}

}

void removeFila(Cabeca* cabeca) {

	if (vazia(cabeca) == 0) {

		No* prim = cabeca->inicio;
		cabeca->inicio = prim->prox;
		free(prim);

		if(vazia(cabeca) == 1) {

			cabeca->fim = NULL; 
		}

	} else {printf("Lista vazia\n");}
}

void empilha(Cabeca* cabeca, int k) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {

		novo->chave = k;
		novo->prox = cabeca->inicio;
		cabeca->inicio = novo;

	} else {printf("Não foi possível alocar memória.\n");}
}

void desempilha(Cabeca* cabeca) {

	if(vazia(cabeca) == 0) {

		No* aux = cabeca->inicio;
		cabeca->inicio = cabeca->inicio->prox;
		free(aux);

	} else {printf("Pilha vazia\n");}
}


void imprime(No* paux) {

	if(paux) {

		while(paux != NULL) {

			printf("%d\n", paux->chave);
			paux = paux->prox;
		}

	} else {printf("Fila/Pilha vazia\n");}
}

void filaParaPilha(Cabeca* fila, Cabeca* pilha) {

	if (fila->inicio) {
		
		while(fila->inicio) {

			empilha(pilha, fila->inicio->chave);
			removeFila(fila);
		}
	} else {printf("Fila vazia\n");}
}

void pilhaParaFila(Cabeca* pilha, Cabeca* fila) {

	if(pilha->inicio) {

		while(pilha->inicio) {

			insereFila(fila, pilha->inicio->chave);
			desempilha(pilha);
		}

	} else {printf("Pilha vazia\n");}
}