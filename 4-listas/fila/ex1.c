#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Documento {

	char nome[30];  
	char extensao[5];  
	int tamanho; 
	struct Documento* prox;
	
} Documento; 

typedef struct Cabeca {

	Documento* inicio;
	Documento* fim;
	
} Cabeca;

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

void insereFim(Cabeca* cabeca, char nome[20], char ext[6], int tam) {

	Documento* novo = (Documento*) malloc(sizeof(Documento));

	if(novo) {

		strcpy(novo->nome, nome);
		strcpy(novo->extensao, ext);
		novo->tamanho = tam;

		if(vazia(cabeca) == 1) {

			cabeca->fim = novo;
			cabeca->inicio = novo;
		
		} else {
			
			cabeca->fim->prox = novo;
			cabeca->fim = novo;	
		}

	} else {printf("Não foi possível alocar memória\n");}

}

void imprimeFila(Documento* paux) {

	if(paux) {

		while(paux != NULL) {

			printf("%s\n", paux->nome);
			paux = paux->prox;
		}

	} else {printf("Lista vazia\n");}
}

void removeInicio(Cabeca* cabeca) {

	if (vazia(cabeca) == 0) {

		Documento* prim = cabeca->inicio;
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

int main() {

	
	return 0;
}
