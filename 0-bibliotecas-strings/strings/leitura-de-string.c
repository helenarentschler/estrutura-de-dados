#include <stdio.h>

int main() {
	char nome[50], nomeCompleto[50];
	printf("Escreva seu nome: ");
	//nao guarda letra apos espaço em branco
	scanf("%s", nome);
	printf("Seu nome é %s", nome);
	//guarda espaços em branco
	printf("Escreva seu nome completo: ");
	fflush(stdin);
	fgets(nomeCompleto, 50, stdin);
	printf("Seu nome completo é %s", nomeCompleto);
	
	return 0;
}
