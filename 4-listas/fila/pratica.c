#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct celula Celula;
typedef struct cabeca Cabeca;

struct celula {

	int chave;
	Celula* prox;
};

struct cabeca {

	Celula* inicio;
	Celula* fim;	
};

//FUNCOES COMUNS

Cabeca* criaCabeca() {

	Cabeca* cabeca = (Cabeca*) malloc(sizeof(Cabeca));

	if(cabeca) {

		cabeca->inicio = NULL;
		cabeca->fim = NULL;	
		
	} else {printf("Nao foi possivel alocar\n");}

	return cabeca;
}

int vazia(Cabeca* cabeca) {

	if(cabeca->inicio) {

		return 0;
		
	} else {

		return 1;
	}
}

void imprime(Celula* aux) {

	if(aux) {

		while(aux != NULL) {

			printf("%d\n", aux->chave);
			aux = aux->prox;
		}
		
	} else {printf("vazia!\n");}
}

//FUNCOES FILA

void insereFim(Cabeca* cabeca, int k) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));

	if(nova) {

		nova->chave = k;
		nova->prox = NULL;
		
		if(vazia(cabeca)) {

			cabeca->inicio = nova;
			cabeca->fim = nova;	
		
		} else {

			cabeca->fim->prox = nova;
			cabeca->fim = nova;
		}	
	}
}

void removeInicio(Cabeca* cabeca) {

	if(!vazia(cabeca)) {

		Celula* aux = cabeca->inicio;
		cabeca->inicio = aux->prox;
		free(aux);

		if(vazia(cabeca)) {

			cabeca->fim = NULL;	
		}
		
	} else { printf("Fila vazia!\n");}
}

void removeTodos(Cabeca* cabeca) {

	if(!vazia(cabeca)) {

		while(!vazia(cabeca)) {

			removeInicio(cabeca);	
		}
		
	} else {printf("Fila vazia!\n");}
}

void uneFilas(Cabeca* fila1, Cabeca* fila2) {

	if(!vazia(fila1)) {
	
		fila1->fim->prox = fila2->inicio;
		fila1->fim = fila2->fim; 	

	} else {printf("Fila 1 vazia!");}
}

//FUNCOES PILHA

void empilha(Cabeca* cabeca, int k) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));

	if(nova) {

		nova->chave = k;
		nova->prox = cabeca->inicio;
		cabeca->inicio = nova;
	}	
}

void desempilha(Cabeca* cabeca) {

	if(!vazia(cabeca)) {

		Celula* aux = cabeca->inicio;
		cabeca->inicio = cabeca->inicio->prox;
		free(aux);
		
	} else {printf("pilha vazia\n");}
}

int topo(Cabeca* cabeca) {

	if(vazia(cabeca)) {

		return -1;
		
	} else {

		return cabeca->inicio->chave;
	}
}

void desempilhaTodos(Cabeca* cabeca) {

	if(!vazia(cabeca)) {
	
		while(!vazia(cabeca)) {

			desempilha(cabeca);	
		}
		
	} else {printf("pilha vazia!\n");}
}

void desempilhaEmpilha(Cabeca* pilha1, Cabeca* pilha2) {

	while(!vazia(pilha1)) {
	
		empilha(pilha2, pilha1->inicio->chave);
		desempilha(pilha1);
	}
}

//FUNCOES INTERACAO PILHA-FILA

void pilhaParaFila(Cabeca* fila, Cabeca* pilha) {

	while(!vazia(pilha)) {

		insereFim(fila, pilha->inicio->chave);
		desempilha(pilha);
	}
}

void filaParaPilha(Cabeca* fila, Cabeca* pilha) {

	while(!vazia(fila)) {

		empilha(pilha, fila->inicio->chave);
		removeInicio(fila);
	}
}

void divideFila(Cabeca* fila1, Cabeca* fila2) {

	if(!vazia(fila1)) {

		int tam = 0;

		Celula* paux = fila1->inicio;
		
		while(paux != NULL) {

			tam++;
			paux = paux->prox;
		}

		int valor = ceil(tam / 2);

		int i = 0;
		
		while(i < valor) {

			insereFim(fila2, fila1->inicio->chave);
			removeInicio(fila1);
			i++;
		}
		
	}
}

void inverteFila(Cabeca* cabeca) {

	Celula* aux = cabeca->inicio;
	Celula* ant = cabeca->inicio;

	while(aux) {
		
		ant = aux;
		aux = aux->prox;
	}
}

int main() {

	Cabeca* fila = criaCabeca();	
	Cabeca* fila2 = criaCabeca();
	insereFim(fila, 1);
	insereFim(fila, 2);
	insereFim(fila, 3);

	imprime(fila->inicio);

	/*removeInicio(fila);
	imprimeFila(fila->inicio);
	removeInicio(fila);
	imprimeFila(fila->inicio);
	removeInicio(fila);
	imprimeFila(fila->inicio);*/

	removeTodos(fila);
	imprime(fila->inicio);

	/*insereFim(fila, 1);
	insereFim(fila, 2);
	insereFim(fila, 3);
	insereFim(fila2, 4);
	insereFim(fila2, 5);
	insereFim(fila2, 6);*/
	
	uneFilas(fila, fila2);

	imprime(fila->inicio);
	printf("Fila 2: \n");
	imprime(fila2->inicio);

	Cabeca* pilha = criaCabeca();

	empilha(pilha, 1);
	empilha(pilha, 2);
	empilha(pilha, 3);

	imprime(pilha->inicio);

	desempilhaTodos(pilha);

	imprime(pilha->inicio);

	Cabeca* novaFila = criaCabeca();

	insereFim(fila, 1);
	insereFim(fila, 2);
	insereFim(fila, 3);
	insereFim(fila, 4);
	insereFim(fila, 5);
	
	divideFila(fila, novaFila);

	printf("fila original: \n");
	imprime(fila->inicio);
	printf("nova fila: \n");
	imprime(novaFila->inicio);

	return 0;
}
