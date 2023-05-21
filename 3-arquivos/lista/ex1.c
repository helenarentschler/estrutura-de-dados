#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int qnt;
	char nome[20];
	float valor;
} tItem;

void carregar(tItem** ppItens, int* ptam);
void listar(tItem** ppItens, int* ptam);
void calcularTotal(tItem** ppItens, int* ptam);

int main() {

	tItem* vetorItens = NULL;
	int tam = 0;
	
	int op;

	do {
		printf("\n1 - Listar Itens comprados");
		printf("\n2 - Calcular valor total da compra");
		printf("\n3 - Encerrar");
		scanf("%d", &op);

		switch (op) {
			case 1:
				listar(&vetorItens, &tam);
			break;
			case 2:
				calcularTotal(&vetorItens, &tam);
			break;
			case 3:
				printf("\nEncerrando..."); 
			break;
		}
	} while (op != 3);
	
	return 0;
}

void carregar(tItem** ppItens, int* ptam) {

	if(!*ppItens) {

		FILE* arquivo = fopen("itens.txt", "r");

		if(arquivo) {
			tItem item;
			int ret;	
			
			//le arquivo para contar linhas, guarda em tam
			while(ret != EOF) {
				ret = fscanf(arquivo, "%d %s %f", &item.qnt, item.nome, &item.valor);
				(*ptam)++;
			}
	
			// aloca vetor cujo tamanho é o mesmo da quantidade de linhas do arquivo
			*ppItens = (tItem*) malloc(*ptam * sizeof(tItem)); 

			if(*ppItens) {
				int i = 0;
				//como o ponteiro esta no final do arquivo depois da ultima leitura, deve retornar ao inicio
				rewind(arquivo);

				//le arquivo para guardar valores no vetor *ppItens (vetorItens da main)
				while(i < *ptam) {	
					fscanf(arquivo, "%d %s %f", &((*ppItens+i)->qnt), (*ppItens+i)->nome, &((*ppItens+i)->valor));
					i++;
				}
						
			} else {printf("\nNao foi possivel alocar o vetor.");}	
			
		} else {printf("\nNao foi possivel abrir o arquivo.");}	

		fclose(arquivo);
		
	} else {printf("\nVetor ja foi carregado.");}
}


void listar(tItem** ppItens, int* ptam) {

	if(!*ppItens) {carregar(ppItens, ptam);}
	
	if(*ppItens) {
		int i;
		
		for(i = 0; i < *ptam; i++) {
			printf("\nQuantidade:%d, nome:%s, valor:%f", (*ppItens+i)->qnt, (*ppItens+i)->nome, (*ppItens+i)->valor);	
		}
	} else {printf("\nNao foi possivel listar itens.");}
}

void calcularTotal(tItem** ppItens, int* ptam) {

	if(!*ppItens) {carregar(ppItens, ptam);}

	if(*ppItens) {
		int i;
		float soma = 0;	
		
		for(i = 0; i < *ptam; i++) {
			soma += (*ppItens+i)->valor;
		}

		printf("\nSoma dos preços: %f", soma);
		
	} else {printf("\nNao foi possivel somar preços.");}
}
