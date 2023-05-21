#include <stdio.h>
#define nA 2

typedef struct Aluno {
	char nome[30];
	int RA;
	short int idade;
} taluno;

void cadastrar(taluno* pA);


int main() {

	taluno alunos[nA];
	
	cadastrar(alunos);
	
	return 0;
}

void cadastrar(taluno* pA) {

	int i;

	for(i = 0; i < nA; i++){
		printf("Insira o nome do aluno %d: \n", i);
		setbuf(stdin, NULL);
		fgets((pA+i)->nome, 30, stdin);
		printf("Insira o RA do aluno %d: \n", i);
		scanf("%d", &(pA+i)->RA);
		printf("Insira a idade do aluno %d: \n", i);
		scanf("%hd", &(pA+i)->idade);
	}

	printf("%d", (pA+1)->RA);
	printf("%p", &(pA+1)->RA);
}
