#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//carregar informaçoes em 2 vetores filiais
//compara-los e unir as informaçoes em 1 vetor matriz
// busca por filial

typedef struct veiculo {

	char modelo[30];
	float valor;
	int qnt;
	int filial;
	
} tVeiculo;

void carregarVetor(char nomearq[], tVeiculo** pVetor, int* tam) {

	if(!*pVetor) {
	
		FILE* arq = fopen(nomearq, "r");

		if(arq) {
			int ret = 0;
			tVeiculo veiculo;
			
			while(ret != EOF) {
				ret = fscanf(arq, "%s %f %d %d", veiculo.modelo, &(veiculo.valor), &(veiculo.qnt), &(veiculo.filial));
				(*tam)++;
			}
			
			*tam -= 1;
			*pVetor = (tVeiculo*) malloc(sizeof(tVeiculo)*(*tam));

			if(pVetor) {
			
				int i = 0;
				rewind(arq);
				
				while(i < *tam) {
					fscanf(arq, "%s %f %d %d", (*pVetor + i)->modelo, &(*pVetor + i)->valor, &(*pVetor + i)->qnt, &(*pVetor + i)->filial);
					i++;
				}	
			} else {printf("Nao foi possivel alocar vetor");}
		} else {printf("Nao foi possivel abrir arq\n");}
		fclose(arq);
	} else {printf("Vetor ja carregado\n");}
}

int carregarMatriz(tVeiculo* f1, tVeiculo* f2, int tam1, int tam2, tVeiculo** pMatriz) {

	int i, j;
	int posMatriz = 0;
	
	*pMatriz = (tVeiculo*) malloc(sizeof(tVeiculo) * (tam1 + tam2));

	for(i = 0; i < tam1; i++) {
		*(*pMatriz+i) = *(f1+i);
		posMatriz++;
	}

	int repetido = 0;
	
	for(i = 0; i < tam2; i++) {

		repetido = 0;
		
		for(j = 0; j < posMatriz; j++) {
			if(strcmp((f2+i)->modelo, (*pMatriz+j)->modelo) == 0) {
				repetido = 1;
				(*pMatriz+j)->qnt += (f2+i)->qnt;
			} 
		}
		
		if(!repetido) {
			*(*pMatriz+posMatriz) = *(f2+i);
			posMatriz++;
		}

	}

	*pMatriz = realloc(*pMatriz, sizeof(tVeiculo) * posMatriz);

	if(*pMatriz) {
	
		FILE* arq = fopen("matriz.txt", "w");
		
		for(i = 0; i < posMatriz; i++) {
			fprintf(arq, "%s %f %d %d\n", (*pMatriz+i)->modelo, (*pMatriz+i)->valor, (*pMatriz+i)->qnt, (*pMatriz+i)->filial);
		}	

		fclose(arq);
	}

	return posMatriz;
}

void buscarPorFilial(tVeiculo* matriz, int tam) {

	if(matriz) {
	
		int i, filial;
		
		printf("Insira numero da filial: \n");
		scanf("%d", &filial);
		
		for(i = 0; i < tam; i++) {
			if((matriz+i)->filial == filial) {
				printf("%s %f %d %d\n", (matriz+i)->modelo, (matriz+i)->valor, (matriz+i)->qnt, (matriz+i)->filial);
			}
		}	
	} else {printf("Vetor matriz nao carregado\n");}

}

void desalocar(tVeiculo** pVetor) {

	free(*pVetor);
	*pVetor = NULL;

}

int main() {

	int op = 0;
	tVeiculo* f1 = NULL, *f2 = NULL, *matriz = NULL;
	int tam1 = 0, tam2 = 0, tamMatriz = 0;

	while (op != 3) {

		printf("1-Carregar vetor matriz\n");
		printf("2-Buscar por filial\n");
		printf("3-Sair\n");
		scanf("%d", &op);

		switch(op) {
			case 1:
				carregarVetor("bcx_pg1.txt", &f1, &tam1);
				carregarVetor("bcx_pg2.txt", &f2, &tam2);
				tamMatriz = carregarMatriz(f1, f2, tam1, tam2, &matriz);
			break;
			case 2:
				buscarPorFilial(matriz, tamMatriz);
			break;
			case 3:
				desalocar(&f1);
				desalocar(&f2);
				desalocar(&matriz);
			break;
		}
	}
	return 0;
}

