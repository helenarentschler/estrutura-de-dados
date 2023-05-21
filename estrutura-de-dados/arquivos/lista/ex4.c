#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char continente[20];
	char pais[20];
	char capital[20];
} tReg;

int main() {
	FILE* arquivo = fopen("dados.csv", "r");
	
	if(arquivo) {
		int ret = 0;
		char linha[100], *itemLinha = NULL;
		
		while(ret != EOF) {

			ret = fscanf(arquivo, "%s", linha);

			itemLinha = strtok(linha, ";");	
			
			do {
				printf("%s - ", itemLinha);
				itemLinha = strtok(NULL, ";");		
			} while (itemLinha);

			printf("\n");
		}
	}
	
	fclose(arquivo);
	return 0;
}
