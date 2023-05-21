#include <stdio.h>
#include <stdlib.h>

int contarLinhas(FILE* arq);

int main() {
	FILE* arq = fopen("arquivo.txt", "r");
	
	printf("%d", contarLinhas(arq));
	
	fclose(arq);
	return 0;
}

int contarLinhas(FILE* arq) {
	
	if(arq) {
		int soma=0;
		char c;
		
		do {
			c = getc(arq);
			if(c == '\n') {
				soma++;		
			}
		} while(!feof(arq));
		
		return soma;
	} else {
		return -1;
	}
}
