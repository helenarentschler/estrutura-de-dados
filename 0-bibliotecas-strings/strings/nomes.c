#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char criancas[4][10], c;
	int i, j,n=0;

	for(i=0; i<4; i++){
		printf("Quantos caracteres o nome %d deve ter?\n", i);
		scanf("%d", &n);

		for(j=0; j < n; j++) {
			c = 'a' + rand()%26;
			strcat(criancas[i], &c);
		}
		
		printf("Nome da criança %d: %s\n", i, criancas[i]);
	}
	return 0;
}
