#include <stdio.h>

typedef struct aluno {
	int RA;
	char nome[30];
	float rendaf;
} taluno;

int main() {
	taluno a1;
	printf("%ld\n", sizeof(taluno)); //pareamento
	printf("%ld\n", sizeof(a1.RA));
	scanf("%d", &a1.RA);
	setbuf(stdin, NULL);
	fgets(a1.nome, 30, stdin);
	scanf("%f", &a1.rendaf);
	printf("%d %s %f\n", a1.RA, a1.nome, a1.rendaf);
	return 0;
}
