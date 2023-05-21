#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char nome[20];
	int RA;	
} tAluno;

void alocaAlunos(tAluno** ppalunos);
void inicializaImprime(tAluno* palunos);

int main() {

	tAluno* alunos = NULL;

	alocaAlunos(&alunos);
 	inicializaImprime(alunos);

	
}

void alocaAlunos(tAluno** ppalunos) {

	if(!*ppalunos) {
	
		*ppalunos = (tAluno*) malloc(sizeof(tAluno)*8);

		if(!ppalunos) {
			printf("nao foi possivel alocar.");
		}
	}
}

void inicializaImprime(tAluno* palunos) {

	if(palunos) {

		int i;

		for(i=0; i<8; i++) {
			scanf("%d", &(palunos+i)->RA);
			setbuf(stdin, NULL);
			scanf("%[^\n]", (palunos + i)->nome);
			printf("RA: %d\n", (palunos+i)->RA);
			printf("Nome: %s", (palunos + i)->nome);
		}	
	}
}
