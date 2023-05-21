#include <stdio.h>
#include <stdlib.h>

// dividir em 2

typedef struct No {
	int chave;
	struct No* prox; 
} tNo;

void insereInicio(tNo** pplista, int k);
void imprimeLista(tNo* paux) ;
tNo* buscaNo(tNo* paux, int k);
void insereFinal(tNo** pplista, int k);
tNo* buscaMaior(tNo* paux);
tNo* buscaMenor(tNo* paux);
int somarNos(tNo* paux);
int tamanho(tNo* paux);
int frequencia(tNo* paux, int k);
void removeInicio(tNo** pplista);
void removerNo(tNo** pplista, int k);
tNo* geraCopia(tNo* paux);
void desalocarLista(tNo** pplista);
tNo* geraCopiaInvertida(tNo* paux);
int compararListas(tNo* aux1, tNo* aux2);
int juntarListas(tNo* lista1, tNo* lista2);

int main() {
	
	tNo* lista = NULL;
	
	insereInicio(&lista, 1);
	insereInicio(&lista, 2);
	insereInicio(&lista, 3);
	imprimeLista(lista);

	tNo* achado = buscaNo(lista, 3);

	if(achado) {

		printf("No achado: %d\n", achado->chave);
		
	} else {printf("Nao encontrado.\n");}

	insereFinal(&lista, 4);

	imprimeLista(lista);

	tNo* maior = buscaMaior(lista);

	printf("Maior da lista: %d\n", maior->chave);

	tNo* menor = buscaMenor(lista);
	
	printf("Menor da lista: %d\n", menor->chave);


	printf("Soma: %d\n", somarNos(lista));

	insereFinal(&lista, 9);
	
	printf("Tamanho da lista: %d\n", tamanho(lista));

	insereFinal(&lista, 9);
	insereFinal(&lista, 9);

	printf("Frequencia do elemento %d: %d\n", 9, frequencia(lista, 9));

	removerNo(&lista, 3);

	imprimeLista(lista);

	removerNo(&lista, 9);
	imprimeLista(lista);
	
	removerNo(&lista, 8);

	tNo* lista2 = geraCopia(lista);

	imprimeLista(lista2);

	//desalocarLista(&lista);

	imprimeLista(lista);

	tNo* invertida = geraCopiaInvertida(lista2);

	imprimeLista(invertida);

	int bool = compararListas(lista, lista2);
	int bool2 = compararListas(lista2, invertida);

	if(bool == 1) {
		printf("Listas iguais\n");
	} else {
		printf("Listas diferentes\n");
	}

	if(bool2 == 1) {
		printf("Listas iguais\n");
	} else {
		printf("Listas diferentes\n");
	}

	
	juntarListas(lista, invertida);

	imprimeLista(lista);
	return 0;  
}

//pp pois altera ponteiro lista da main
void insereInicio(tNo** pplista, int k) {

	tNo* novo = (tNo*) malloc(sizeof(tNo));

	if(novo) {

		novo->chave = k;
		novo->prox = *pplista;
		*pplista = novo;
		
	} else {printf("falha na alocaçao\n");}
}

void imprimeLista(tNo* paux) {

	if(paux) {

		printf("\n");
		
		while(paux != NULL) {

			printf("%d\n", paux->chave);

			paux = paux->prox;	
		}
		
	} else {printf("Lista vazia\n");}
}

tNo* buscaNo(tNo* paux, int k) {

	if(paux) {
		
		while(paux != NULL) {

			if(paux->chave == k) {

				return paux;
			}

			paux = paux->prox;	
		}
		
		return NULL;
		
	} else { printf("Lista vazia\n");}
}

void insereFinal(tNo** pplista, int k) {

	if(!*pplista) {

		insereInicio(pplista, k);

	} else {

		tNo* paux = *pplista;

		while(paux->prox != NULL) {
		
			paux = paux->prox;	
		}

		tNo* novo = (tNo*) malloc(sizeof(tNo));

		novo->chave = k;
		paux->prox = novo;
		novo->prox = NULL;
		
	}
}

tNo* buscaMaior(tNo* paux) {

	if(paux) {

		tNo* maior = paux;
		
		while(paux != NULL) {

			if(paux->chave > maior->chave) {

				maior = paux;
			}

			paux = paux->prox;	
		}
		
		return maior;
		
	} else {printf("Lista vazia\n");}
}

tNo* buscaMenor(tNo* paux) {

	if(paux) {

		tNo* menor = paux;
		
		while(paux != NULL) {

			if(paux->chave < menor->chave) {

				menor = paux;
			}

			paux = paux->prox;	
		}
		
		return menor;
		
	} else {printf("Lista vazia\n");}
}

int somarNos(tNo* paux) {

	if(paux) {

		int soma = 0;
		
		while(paux != NULL) {

			soma += paux->chave;

			paux = paux->prox;	
		}

		return soma;
		
	} else {printf("Lista vazia\n");}
}

int tamanho(tNo* paux) {

	if(paux) {

		int tam = 0;
		
		while(paux != NULL) {

			tam++;

			paux = paux->prox;	
		}

		return tam;
		
	} else {printf("Lista vazia\n");}
}

int frequencia(tNo* paux, int k) {

	if(paux) {
	
		int freq = 0;

		while(paux != NULL) {

			if(paux->chave == k) {

				freq++;
			}

			paux = paux->prox;	
		}
		
		return freq;
		
	} else { printf("Lista vazia\n");}
}

void removeInicio(tNo** pplista) {

	if(*pplista) {

		tNo* paux = *pplista;
		*pplista = paux->prox;
		free(paux);
		
	} else {printf("Lista vazia\n");}
}

void removerNo(tNo** pplista, int k) {

	if(*pplista) {

		tNo* paux = *pplista;

		//remoçao no inicio
		if(paux->chave == k) {

			removeInicio(pplista);

		} else {

			tNo* pant = *pplista;

			while(paux != NULL) {

				if(paux->chave == k) {

					pant->prox = paux->prox;
					free(paux);	
					return;
				}
				
				pant = paux;
				paux = paux->prox;
			}	

			printf("No nao encontrado\n");
		}
	} else {printf("Lista vazia\n");}
}

tNo* geraCopia(tNo* paux) {

	if(paux) {

		tNo* copia = NULL;
		
		while(paux != NULL) {
		
			insereFinal(&copia, paux->chave);	
			paux = paux->prox;
		}

		return copia;
		
	} else {printf("Lista vazia\n");}
}

void desalocarLista(tNo** pplista) {

	if(*pplista) {

		while(*pplista != NULL) {

			removeInicio(pplista);
		}
		 
	} else {printf("Lista vazia\n");}
}

tNo* geraCopiaInvertida(tNo* paux) {

	if(paux) {

		tNo* copia = NULL;
		
		while(paux != NULL) {
		
			insereInicio(&copia, paux->chave);	
			paux = paux->prox;
		}

		return copia;
		
	} else {printf("Lista vazia\n");}
}

int compararListas(tNo* aux1, tNo* aux2) {

	if(tamanho(aux1) != tamanho(aux2)) {
		return 0;
	}
	
	while(aux1 != NULL) {

		if(aux1->chave != aux2->chave) {
			return 0;
		}
		
		aux1 = aux1->prox;
		aux2 = aux2->prox;
	}

	return 1;
}

int juntarListas(tNo* lista1, tNo* lista2) {

	if(lista1 && lista2) {
	
		tNo* paux = lista1;

		//para no ultimo da lista 1
		while(paux->prox != NULL) {
			paux = paux->prox;
		}
	
		paux->prox = lista2;	
		
	} else {printf("Lista vazia\n");}
}

int dividirLista(tNo* lista1, tNo* lista2) {

/**/
}
