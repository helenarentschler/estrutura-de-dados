#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct site {
	char nome[20], home[40];
	int nacessos;
	struct site* prox;
} tSite;

typedef struct cabeca {
	int qnt;
	tSite* prim;
	tSite* mais; //mais recente
} tCabeca;

tCabeca* criaLista();
void insereInicio(tCabeca* pcabeca, char nome[], char home[]);
void imprimeLista(tSite* paux);
void buscaSite(tCabeca* pcabeca, char nome[]);
void removeInicio(tCabeca* pcabeca);

int main() {

	tCabeca* cabeca = criaLista();

	insereInicio(cabeca, "americanas", "www.americanas.com.br");
	insereInicio(cabeca, "submarino", "www.submarino.com.br");
	insereInicio(cabeca, "netflix", "www.netflix.com.br");

	imprimeLista(cabeca->prim);

	buscaSite(cabeca, "netflix");
	buscaSite(cabeca, "netflix");

	buscaSite(cabeca, "hbo");

	removeInicio(cabeca);

	imprimeLista(cabeca->prim);

	return 0;
}

tCabeca* criaLista() {

	tCabeca* cabeca = (tCabeca*) malloc(sizeof(tCabeca));

	if(cabeca) {
		cabeca->qnt = 0;
		cabeca->prim = NULL;
		cabeca->mais = NULL;
	}
	
	return cabeca;
}

void insereInicio(tCabeca* pcabeca, char nome[], char home[]) {

	if(pcabeca) {

		tSite* novo = (tSite*) malloc(sizeof(tSite));

		if(novo) {

			novo->nacessos = 0;
			strcpy(novo->nome, nome);	
			strcpy(novo->home, home);	

			novo->prox = pcabeca->prim;
			pcabeca->prim = novo;

			(pcabeca->qnt)++;
			
		} else { printf("site nao alocado.\n");}
		
	} else { printf("nao existe cabeça\n");}
}

void imprimeLista(tSite* paux) {

	if(paux) {

		while(paux) {
			printf("%s %s %d\n", paux->nome, paux->home, paux->nacessos);
			paux = paux->prox;	
		}
		
	} else { printf("Lista de sites vazia.\n");}
}

void buscaSite(tCabeca* pcabeca, char nome[]) {

	tSite* paux = pcabeca->prim; 

	if(paux) {

		if(pcabeca->mais) {
		
			if(strcmp(pcabeca->mais->nome, nome) == 0) {
							
				paux = pcabeca->mais;
				(paux->nacessos)++;
				printf("Ja foi acessado antes: %s %s %d\n", paux->nome, paux->home, paux->nacessos);
				return;
			}	
		}
		
		while(paux) {

			if(strcmp(paux->nome, nome) == 0) {

				(paux->nacessos)++;
				printf("%s %s %d\n", paux->nome, paux->home, paux->nacessos);
				pcabeca->mais = paux;
				
				return;
			}
			
			paux = paux->prox;	
		}

		printf("Site %s nao encontrado\n", nome);
			
	} else { printf("Lista de sites vazia.\n");}
	
}

void removeInicio(tCabeca* pcabeca) {

	tSite* paux = pcabeca->prim;

	if(paux) {

		if(pcabeca->mais == paux) {
			pcabeca->mais = NULL;
		}
		pcabeca->prim = paux->prox;
		free(paux);
		paux = NULL;
		
	} else { printf("Lista de sites vazia.\n");}
}
