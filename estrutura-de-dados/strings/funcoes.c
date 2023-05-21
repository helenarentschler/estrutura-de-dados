#include <stdio.h>
#include <string.h>

int main(){
	char str[100], str1[100];

	printf("Insira uma frase: \n");
	setbuf(stdin, NULL);
	scanf("%[^\n]", str);
	printf("Insira outra: \n");
	setbuf(stdin, NULL);
	fgets(str1, 100, stdin);

	printf("O tamanho da primeira string é: %ld\n", strlen(str));
	printf("O tamanho da segunda string é: %ld\n", strlen(str1));
	strcat(str,str1);
	printf("A concatenaçao entre elas é: %s\n", str);

	if(strcmp(str, str1) > 0) {
		printf("a primeira é maior\n");
	} else if (strcmp(str, str1) == 0){
		printf("sao iguais\n");
	} else {
		printf("a segunda é maior.\n");
	}

	strcpy(str, str1);

	printf("Novo valor da primeira: %s\n", str);

	return 0;
}
