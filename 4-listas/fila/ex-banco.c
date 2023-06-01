#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Fila Fila;
typedef struct No No; 

struct Fila {

	No* inicio;
	No* fim;
};

struct No {

	int senha;
	int atendimento;
	No* prox;
};

int cont = 1;

Fila* criaFila();
void insereFim(Fila* fila);
void imprimeFila(No* paux);
void removeInicio(Fila* fila);
void divideFila(Fila* fila, Fila* fila2);
void removeTodos(Fila* fila);

int main() {

	Fila* fila = criaFila();
	Fila* fila2 = criaFila();
	int op = 0, opFila = 0;

	while(op != 5) {

		printf("\n1 - Gerar senha\n");	
		printf("2 - Realizar atendimento\n");	
		printf("3 - Dividir fila em 2\n");
		printf("4 - Exibe fila(s)\n");
		printf("5 - Sair\n");
		scanf("%d", &op);

		switch(op) {

			case 1:
				printf("====================\n");	
				insereFim(fila);
				printf("====================\n");
			break;
			case 2:

				printf("==============================\n");
				printf("Qual fila deseja atender?\n");
				printf("1 - Fila 1\n");
				printf("2 - Fila 2\n");	

				scanf("%d", &opFila);

				if(opFila == 1) {
					removeInicio(fila);
				} else {
					removeInicio(fila2);	
				}
				printf("==============================\n");

			break;
			case 3:
				divideFila(fila, fila2);
			break;
			case 4:
				printf("====================\n");
				printf("Fila 1:\n");
				imprimeFila(fila->inicio);		
				printf("\nFila 2:\n");
				imprimeFila(fila2->inicio);
				printf("====================\n");				
			break;
			case 5:
				removeTodos(fila);
				removeTodos(fila2);
			break;
		}
	}

	return 0;
}

Fila* criaFila() {

	Fila* fila = (Fila*) malloc(sizeof(Fila));

	if(fila) {

		fila->inicio = NULL;
		fila->fim = NULL;

	} else {printf("Não foi possível alocar memória.\n");}

	return fila;
}

void insereFim(Fila* fila) {

	No* novo = (No*) malloc(sizeof(No));

	if(novo) {

		int at;

		printf("Qual tipo de senha deseja gerar? (0 - Normal, 1 - Prioritário)\n");
		scanf("%d", &at);

		novo->senha = cont++;
		novo->atendimento = at;
		novo->prox = NULL;

		if(!fila->inicio) {

			fila->fim = novo;
			fila->inicio = novo;
		
		} else {
			
			fila->fim->prox = novo;
			fila->fim = novo;	
		}

	} else {printf("Não foi possível alocar memória\n");}
}

void imprimeFila(No* aux) {

	if(aux) {

		while(aux != NULL) {

			printf("Senha %d - Atendimento %d\n", aux->senha, aux->atendimento);
			aux = aux->prox;
		}

	} else {printf("Fila vazia\n");}
}

void removeInicio(Fila* fila) {

	if(fila->inicio) {

		int at;

		printf("Qual tipo de atendimento deseja realizar? (0 - Normal, 1 - Prioritário)\n");
		scanf("%d", &at);

		No* aux = fila->inicio;

		if (at == 0 || aux->atendimento == 1) {

			fila->inicio = aux->prox;
			free(aux);

			if(!fila->inicio) {

				fila->fim = NULL; 
			}

		} else if(at == 1){

			No* ant = fila->inicio;

			while(aux != NULL)  {
				
				if(aux->atendimento == 1) {
					break;
				}

				ant = aux;
				aux = aux->prox;
			}

			if(aux == NULL) {

				printf("Nao existe cliente prioritário\n");
				return;
			}

			ant->prox = aux->prox;
			free(aux);

			if (ant->prox == NULL){

				fila->fim = ant;
			}

		} else {

			printf("Opção inválida\n");
		}

	} else {printf("Fila vazia\n");}
}

void divideFila(Fila* fila, Fila* fila2) {

	if(fila->inicio) {

		int num = ceil(cont / 2);

		No* ant = fila->inicio;
		No* aux = fila->inicio;

		for (int i = 1; i <= num; ++i) {
			
			ant = aux;
			aux = aux->prox;
		}		

		ant->prox = NULL;
		fila->fim = ant;

		fila2->inicio = aux;
		fila2->fim = fila->fim;

	} else {

		printf("Fila vazia\n");
	}
}

void removeTodos(Fila* fila) {

	if (fila->inicio) {

		No* aux = fila->inicio;

		fila->inicio = aux->prox;
		free(aux);

		if(!fila->inicio) {

			fila->fim = NULL; 
		}

	} else {printf("Fila vazia\n");}
}
