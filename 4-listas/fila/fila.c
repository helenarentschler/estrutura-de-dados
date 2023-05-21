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
void insereFim(Cabeca* cabeca, int chave);
void imprimeFila(No* paux);
void removeInicio(Cabeca* cabeca);
void removeTodos(Cabeca* cabeca);
void uneFilas(Cabeca* c1, Cabeca* c2);

int main() {

	Cabeca* fila = criaCabeca();

	insereFim(fila, 1);	
	insereFim(fila, 2);
	insereFim(fila, 3);

	imprimeFila(fila->inicio);

	removeInicio(fila);

	imprimeFila(fila->inicio);
	
	//removeTodos(fila);

	imprimeFila(fila->inicio);	

	Cabeca* fila2 = criaCabeca();
	
	insereFim(fila2, 8);	
	insereFim(fila2, 0);
	insereFim(fila2, 2);

	imprimeFila(fila2->inicio);	

	uneFilas(fila, fila2);

	printf("Filas concatenadas: \n");
	imprimeFila(fila->inicio);		

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

void insereFim(Cabeca* cabeca, int chave) {

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

void imprimeFila(No* paux) {

	if(paux) {

		while(paux != NULL) {

			printf("%d\n", paux->chave);
			paux = paux->prox;
		}

	} else {printf("Lista vazia\n");}
}

void removeInicio(Cabeca* cabeca) {

	if (vazia(cabeca) == 0) {

		No* prim = cabeca->inicio;
		cabeca->inicio = prim->prox;
		free(prim);

		if(vazia(cabeca) == 1) {

			cabeca->fim = NULL; 
		}

	} else {printf("Lista vazia\n");}
}

void removeTodos(Cabeca* cabeca) {

	if (vazia(cabeca) == 0) {

		while(cabeca->inicio) {

			removeInicio(cabeca);
		}

	} else {printf("Lista vazia\n");}
}

void uneFilas(Cabeca* c1, Cabeca* c2) {

	if(vazia(c1) == 1 || vazia(c2) == 1) {

		printf("Uma das listas está vazia.\n");

	} else {

		c1->fim->prox = c2->inicio;
		c1->fim = c2->fim;
		c2->inicio = NULL;
		c2->fim = NULL;
	}
}