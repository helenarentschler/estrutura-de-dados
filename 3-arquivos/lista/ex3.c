#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int contarOcorrencias(char palavra[20]);

int main() {

	char palavra[20];
	
	printf("Digite a palavra que deseja pesquisar: \n");
	setbuf(stdin, NULL);
	scanf("%s", palavra);

	int ocorrencias = contarOcorrencias(palavra);

	printf("Constatou-se %d ocorrencias da palavra %s\n", ocorrencias, palavra);
	
	return 0;
}

int contarOcorrencias(char palavra[20]) {

	FILE* arquivo = fopen("texto.txt", "r");

	if(arquivo) {
		int ret = 0, soma = 0;
		char str[30];
	
		while(ret != EOF) {
			ret = fscanf(arquivo,"%s", str);
			printf("%s\n", str);
			if(strcmp(palavra,str) == 0){
				soma++;
			}
		}	
		
		fclose(arquivo);

		return soma;
	} else {
		printf("Nao foi possivel abrir o arquivo.\n");
		return 0;
	}
}
