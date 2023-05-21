#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct veiculo {
	char modelo[30];
	float valor;
	int qnt;
	int filial;
} tVeiculo;

void carregaFiliais(tVeiculo** pfilial, int* ptam, char arquivo[]);
void descarregaMatriz(tVeiculo **pmatriz, tVeiculo *filial1, tVeiculo *filial2, int *ptam, int t1, int t2);
void buscaPorFilial();
void buscaPorModelo();

int main() {

	tVeiculo *filial1 = NULL, *filial2 = NULL, *matriz = NULL;
	int tam1 = 0, tam2 = 0, tMatriz = 0;
	
	int op = 0;

	while(op != 4) {

		printf("1-Descarregar vetor matriz\n");
		printf("2-Buscar por filial\n");
		printf("3-Buscar por modelo\n");
		printf("4-Sair\n");
		scanf("%d", &op);

		switch(op) {
			case 1:
				carregaFiliais(&filial1, &tam1, "bcx_pg1.txt");
				carregaFiliais(&filial2, &tam2, "bcx_pg2.txt");
				descarregaMatriz(&matriz, filial1, filial2, &tMatriz, tam1, tam2);
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;		
		}
	}
	
	return 0;
}

void carregaFiliais(tVeiculo** pfilial, int* ptam, char arquivo[]) {

	if(!*pfilial) {

		FILE* arq = fopen(arquivo, "r");

		if(arq) {

			int ret = 0;
			tVeiculo carro;

			while(ret != EOF) {

				ret = fscanf(arq, "%s %f %d %d", carro.modelo, &carro.valor, &carro.qnt, &carro.filial);
				(*ptam)++;
			}	

			(*ptam)--;

			*pfilial = (tVeiculo*) malloc(sizeof(tVeiculo)*(*ptam));

			if(*pfilial) {

				int i = 0;
				rewind(arq);

				while(i < (*ptam)) {
					fscanf(arq, "%s %f %d %d", (*pfilial+i)->modelo, &(*pfilial+i)->valor, &(*pfilial+i)->qnt, &(*pfilial+i)->filial);
					i++;
				}
				
			} else {printf("Nao foi possivel alocar memoria\n");}
		} else {printf("Nao foi possivel abrir arquivo\n");}
		fclose(arq);
	} else {printf("filial ja carregada\n");}
}

void descarregaMatriz(tVeiculo **pmatriz, tVeiculo *filial1, tVeiculo *filial2, int *ptam, int t1, int t2) {

	if(!*pmatriz) {

		int i, j;

		*pmatriz = (tVeiculo*) malloc(sizeof(tVeiculo)*(t1+t2));

		if(*pmatriz) {
		
			for(i = 0; i < t1; i++) {

				*(*pmatriz+i) = *(filial1+i);
				(*ptam)++;
			}

			int repetido = 0; 

			for(i = 0; i < t2; i++) {

				repetido = 0;
				
				for(j = 0; j < t1; j++) {
					if(strcmp( (filial2+i)->modelo, (*pmatriz+j)->modelo ) == 0) {
						repetido = 1;
						(*pmatriz+j)->qnt += (filial2+i)->qnt;	
					}					
				}

				if(!repetido) {
					*(*pmatriz + *ptam) = *(filial2+i);
					(*ptam)++;
				}
			}

			FILE* arq = fopen ("matriz.txt", "w");

			if(arq) {
			
				for(i = 0; i < (*ptam); i++) {
				
					fprintf(arq, "%s %f %d %d\n", (*pmatriz+i)->modelo, (*pmatriz+i)->valor, (*pmatriz+i)->qnt, (*pmatriz+i)->filial);
				}
				
			} else {printf("Nao foi possivel abrir arquivos\n");}
		} else {printf("Nao foi possivel alcoar memoria\n");}
	} else {printf("matriz ja carregada \n");}
}
