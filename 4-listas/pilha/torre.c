#include <stdio.h>
#include <stdlib.h>

//disco
typedef struct celula_str {
	//peso
	int chave;
	struct celula_str *prox;
} TipoCelula;

//torre
typedef struct inicio_fim {

	TipoCelula *inicio;
	int qtde;
} InicioFim;

InicioFim *Cabeca();
void ordenaH(InicioFim * pa, InicioFim * pb, InicioFim * pc);
int vazia(InicioFim *p);
void empilha(InicioFim *p, int k);
int topo(InicioFim *p);
void desempilha(InicioFim *p);
void desempilhaTodos(InicioFim *p);
void imprime(TipoCelula *a);
void desempilha_empilha(InicioFim *p, InicioFim *p1);

int main() {
	
	InicioFim *pa=Cabeca(), *pb=Cabeca(),*pc=Cabeca();

	empilha(pa,11);
	empilha(pa,10);
	empilha(pa,9);
	empilha(pa,8);
	empilha(pa,7);
	empilha(pa,6);
	empilha(pa,5);
	empilha(pa,4);
    empilha(pa,3);
    empilha(pa,2);
    empilha(pa,1);
    
	ordenaH(pa,pb,pc);
	
	imprime(pa->inicio);
	printf("\n");
	imprime(pb->inicio);
	printf("\n");
	imprime(pc->inicio);

	return 0;
}

InicioFim *Cabeca() {

	InicioFim *aux = (InicioFim *)malloc(sizeof(InicioFim));
	
	if(aux) {

		aux->qtde = 0;
		aux->inicio = NULL;
		return aux;
	}

	return NULL;
}

int vazia(InicioFim *p) {
	
	if(p->inicio==NULL)
		return 1;
	else
		return 0;
}

void empilha(InicioFim *p, int k) {//push 
	
	TipoCelula *novo=(TipoCelula *)malloc(sizeof(TipoCelula));
	
	if(novo) {
		novo->chave=k;
		novo->prox=p->inicio;
		p->inicio=novo;
		p->qtde++;
	}
}

int topo(InicioFim *p) {

	if(vazia(p))
		return -1;
	else
		return p->inicio->chave;
}

void desempilha(InicioFim *p) {

	TipoCelula *aux=p->inicio;

	if(vazia(p)==1) {

		printf("\nPilha vazia!");
		return;
	}

	p->inicio = p->inicio->prox;
	p->qtde--;
	free(aux);
	aux=NULL;
}

void desempilhaTodos(InicioFim *p) {

	if(p->inicio==NULL) return;

	while(vazia(p)!=1)
		desempilha(p);	
}

void imprime(TipoCelula *a) {
	
	if(a==NULL)	printf("\nPilha vazia!");
	
	while(a) {
		printf("\n%d", a->chave);
		a=a->prox;	
	}	
}

void desempilha_empilha(InicioFim *p, InicioFim *p1) {
	
	while(vazia(p)!=1) {
	
		empilha(p1, p->inicio->chave);
		desempilha(p);
	}
}

void ordenaH(InicioFim* pa, InicioFim* pb, InicioFim* pc){
    
	//se existem as cabeças 
	if(pa && pb && pc) {

		//contador de movimentos
		int moves = 0;
		//ultima pilha que recebeu um disco movido
		char ultima = 'x';

		while (moves < 10000){

			//se existe pelo menos 1 elemento em pa e o ultimo disco movido nao tenha sido para a pilha a 
			if(pa->inicio && ultima != 'a'){
				
				//se pc estiver vazia ou o disco no topo de C for maior que o disco no topo de A
				if(vazia(pc) || topo(pc) > topo(pa)){

					//movendo topo de a para c
					empilha(pc,topo(pa));
					desempilha(pa);
					ultima = 'c';
					continue;

				// se pb estiver vazia ou o disco no topo de B for maior que o disco no topo de A
				} else if (vazia(pb) || topo(pb) > topo(pa)){

					//movendo topo de a para b
					empilha(pb,topo(pa));
					desempilha(pa);
					ultima = 'b';
					continue;
				}

			}

			//mesma verificaçao para mover elemento de c para uma pilha
			if(pc->inicio && ultima != 'c'){

				if(vazia(pb) || topo(pb) > topo(pc)){

					empilha(pb,topo(pc));
					desempilha(pc);
					ultima = 'b';
					continue;

				} else if (vazia(pa) || topo(pa) > topo(pc)){

					empilha(pa,topo(pc));
					desempilha(pc);
					ultima = 'a';
					continue;

				}
			}

			//mesma verificaçao para mover elemento de b para uma pilha
			if(pb->inicio && ultima != 'b'){

				if(vazia(pa) || topo(pa) > topo(pb)){

					empilha(pa,topo(pb));
					desempilha(pb);
					ultima = 'a';
					continue;

				} else if (vazia(pc) || topo(pc) > topo(pb)){

					empilha(pc,topo(pb));
					desempilha(pb);
					ultima = 'c';
					continue;
				}

			}
			moves++;
		}  
	}}

