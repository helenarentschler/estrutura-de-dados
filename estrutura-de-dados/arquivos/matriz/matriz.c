#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nome[20];
	int qnt;
	float valor;
	int filial;
} tCarro;

//carrega do arquivo para o vetor
void carregarInfos(tCarro** ppCarros, int* ptam);
//carrega do vetor para um arquivo de acordo com a filial
void imprimirVetor(tCarro* pCarros, int tam);
void inserirCarro(tCarro** ppCarros, int* ptam);
void descarregarInfos(tCarro* pCarros, int tam);
void desalocar(tCarro** ppCarros);

int main() {

	tCarro* vetCarros = NULL;
	int tam = 0;
	int op = 0;

	while(op != 5) {

		printf("1-Recuperar Informaçoes do Arquivo \n");
		printf("2-Imprimir Carros\n");
		printf("3-Inserir novo carro\n");
		printf("4-Atualizar arquivo\n");
		printf("5-Sair\n");

		scanf("%d", &op);

		switch (op) {

			case 1:
				carregarInfos(&vetCarros, &tam);
			break;
			case 2:
				imprimirVetor(vetCarros, tam);
			break;
			case 3:
				inserirCarro(&vetCarros, &tam);
			break;
			case 4:
				descarregarInfos(vetCarros, tam);
			break;
			case 5:
			break;
		}
	}
	
	desalocar(&vetCarros);
	return 0;
}

void carregarInfos(tCarro** ppCarros, int* ptam) {

	if(!*ppCarros) {

		FILE* arq = fopen("matriz.txt", "r");

		if(arq) {

			tCarro carro;
			int ret = 0;

			while(ret != EOF) {

				ret = fscanf(arq, "%s %d %f %d", carro.nome, &carro.qnt, &carro.valor, &carro.filial);
				//**********************ATENçAO
				if(feof(arq)) break;
				//**********************ATENçAO
				(*ptam)++;
				
			}

			*ppCarros = (tCarro*) malloc(*ptam * sizeof(tCarro));

			if (*ppCarros) {
				int i = 0;
				//**********************ATENçAO
				rewind(arq);

				while(i < *ptam) {
					ret = fscanf(arq, "%s %d %f %d", (*ppCarros+i)->nome, &(*ppCarros+i)->qnt, &(*ppCarros+i)->valor, &(*ppCarros+i)->filial);
					i++;
				}

			} else {printf("Alocação não pôde ser feita.\n");}

		} else  {printf("Arquivo não pôde ser aberto.\n");}

		fclose(arq);

	} else {printf("Vetor ja foi carregado.\n");}
}


void imprimirVetor(tCarro* pCarros, int tam) {

	if (pCarros) {

		int i;

		for (i = 0; i < tam; i++){
			printf("%s %d %f %d\n", (pCarros+i)->nome, (pCarros+i)->qnt, (pCarros+i)->valor, (pCarros+i)->filial);
		}

	} else {printf("Vetor não foi carregado.\n");}
}


void inserirCarro(tCarro** ppCarros, int* ptam) {

	if (*ppCarros) {

		//vai receber o realloc
		tCarro* pAux = NULL;

		(*ptam)++;

		pAux = (tCarro*) realloc(*ppCarros, *ptam * sizeof(tCarro));

		if(pAux) {

			*ppCarros = pAux;
			int lastPos = *ptam - 1; 

			printf("\nInforme modelo:");
			scanf("%s",(*ppCarros+lastPos)->nome);
			printf("\nInforme quantidade:");
			scanf("%d",&(*ppCarros+lastPos)->qnt);
			printf("\nInforme valor:");
			scanf("%f",&(*ppCarros+lastPos)->valor);
			printf("\nInforme filial:");
			scanf("%d",&(*ppCarros+lastPos)->filial);

		} else {printf("Nao foi possível aumentar memoria.\n");}

	} else {printf("Vetor não foi carregado.\n");}
}

void descarregarInfos(tCarro* pCarros, int tam) {
	
	if(pCarros) {

		FILE * arq = fopen("matriz.txt", "a");
		FILE * arq0 = fopen("filial0.txt", "a");
		FILE * arq1 = fopen("filial1.txt", "a");

		if(arq0 && arq1 && arq) {
		
			int i;
			
			for(i = 0; i < tam; i++) {

				fprintf(arq, "%s %d %f %d\n", (pCarros+i)->nome, (pCarros+i)->qnt, (pCarros+i)->valor, (pCarros+i)->filial);
				
				if((pCarros+i)->filial == 0) {

					fprintf(arq0, "%s %d %f %d\n", (pCarros+i)->nome, (pCarros+i)->qnt, (pCarros+i)->valor, (pCarros+i)->filial);	

				} else if ((pCarros+i)->filial == 1) {

					fprintf(arq1, "%s %d %f %d\n", (pCarros+i)->nome, (pCarros+i)->qnt, (pCarros+i)->valor, (pCarros+i)->filial);
				}	
			}	
			
		} else {printf("Erro ao abrir arquivos.\n");}

		fclose(arq0);
		fclose(arq1);
		fclose(arq);
		
	} else {printf("Vetor não foi carregado.\n");}
}

void desalocar(tCarro** ppCarros) {

	if(*ppCarros) {
	
		free(*ppCarros);
		*ppCarros = NULL;
		
	} else {printf("Nao ha vetor a ser desalocado.\n");}
}
