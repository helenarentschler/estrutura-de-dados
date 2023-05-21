# include <stdio.h>

void * criptografia(char * text, char * novoText);

int main() {
	char text[30];
	char novoText[30];
	
	printf("Digite uma frase: ");
	fgets(text, 30, stdin);
	criptografia(text, novoText);
	printf("Texto criptografado: %s", novoText);
}

void * criptografia(char * text, char * novoText) {
	char alfa[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i, j;

	for(i = 0; i < 30; i++){
		for(j = 0; j < 26; j++) {
			if(*(alfa+j) == *(text+i)) {
				*(novoText+i) = *(alfa+j+3);
			}
		}
	}
}
