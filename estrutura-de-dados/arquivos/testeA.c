//criar registro
//criar vetores e contadores an main
//criar menu
//carregar vetores
//carregar matriz: carrega matriz com o primeiro vetor, depois com o segundo comparando
//criar desaloca
//criar busca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct veiculo {
	char modelo[30];
	float valor;
	int qnt;
	int filial;
} tVeiculo;

void carregarFilial(tVeiculo** pvet, int* tam, char arquivo[]);
void descarregarMatriz(tVeiculo** pmatriz, int* ptam, tVeiculo* f1, tVeiculo* f2, int t1, int t2);

int main() {

	int op = 0;
	
	tVeiculo *f1=NULL, *f2=NULL, *matriz=NULL;
	int tam1=0, tam2=0, tMatriz=0;

	while(op!=3) {

		printf("1-Carregar vetor matriz\n");
		printf("2-Buscar por filial\n");
		printf("3-Sair\n");
		scanf("%d", &op);
		
		switch(op) {
			case 1:
				carregarFilial(&f1, &tam1, "bcx_pg1.txt");
				descarregarMatriz(&matriz, &tMatriz, f1, f2, tam1, tam2);
			break;
			case 2:
			break;
			case 3:
			break;	
		}
	} 
	return 0;
}

void carregarFilial(tVeiculo** pvet, int* tam, char arquivo[]) {

	if(!*pvet) {

		FILE* arq = fopen(arquivo, "r");

		if(arq) {
		
			int ret = 0;
			tVeiculo veiculo;

			while(ret != EOF) {
				ret = fscanf(arq, "%s %f %d %d", veiculo.modelo, &(veiculo.valor), &(veiculo.qnt), &(veiculo.filial));
				(*tam)++;
			}

			(*tam)--;

			*pvet = (tVeiculo*) malloc((*tam)*sizeof(tVeiculo));

			if(*pvet) {
			
				rewind(arq);
				int i = 0;

				while(i < *tam) {
					fscanf(arq, "%s %f %d %d", (*pvet+i)->modelo, &(*pvet+i)->valor, &(*pvet+i)->qnt, &(*pvet+i)->filial);
					printf("%s %f %d %d", (*pvet+i)->modelo, (*pvet+i)->valor, (*pvet+i)->qnt, (*pvet+i)->filial);
					i++;
				}
				
			}
		}

		fclose(arq);
	}
}

void descarregarMatriz(tVeiculo** pmatriz, int* ptam, tVeiculo* f1, tVeiculo* f2, int t1, int t2) {

	if(f1 && f2) {

		int i, j;
		
		*pmatriz = (tVeiculo*) malloc((t1+t2) * sizeof(tVeiculo));

		if(*pmatriz) {

			for(i=0; i<t1; i++) {
				*(*pmatriz+i) = *(f1+i);
				(*ptam)++;
			}

			int repetido = 0;

			for(i=0; i<t2; i++) {

				repetido = 0;
				
				for(j=0; j< *ptam; j++) {

					if(strcmp((f2+i)->modelo, (*pmatriz+i)->modelo) == 0) {
						repetido = 1;
						(*pmatriz+i)->qnt += (f2+i)->qnt;
					}	
				}

				if(!repetido) {

					*(*pmatriz + *ptam) = *(f2+i);
					(*ptam)++; 
				}
			}

			*pmatriz = (tVeiculo*) realloc(*pmatriz, (*ptam) * sizeof(tVeiculo));

			FILE* arq = fopen("matrizteste.txt", "w");

			if(arq) {

				for(i=0; i< *ptam; i++) {
					printf("teste");
					fprintf(arq, "%s %f %d %d\n", (*pmatriz+i)->modelo, (*pmatriz+i)->valor, (*pmatriz+i)->qnt, (*pmatriz+i)->filial);
				}
			}
		}
	}
}



 
