#include <stdio.h>

int main(){
	char vetor[3] = {'A','B','C'};
	char * j = vetor;
	char aux;

	aux = *++j;

	printf("%d %c", aux, aux);
}
