#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char nome[30], email[30], curso[20];
	int ra, telefone;
} tAluno;

void cadastrar(int n);

int main() {

	int n;
	
	printf("Quantos alunos deseja cadastrar?\n");
	scanf("%d", &n);

	cadastrar(n);
	
	return 0;
}

void cadastrar(int n) {

	FILE* arquivo = fopen("alunos.txt", "w");
	tAluno aluno;
	int i=0;

	while(i < n) {
		printf("Nome: \n");
		setbuf(stdin, NULL);
		fgets(aluno.nome, 30, stdin);
		printf("Email: \n");
		setbuf(stdin, NULL);
		fgets(aluno.email, 30, stdin);
		printf("Curso: \n");
		setbuf(stdin, NULL);
		fgets(aluno.curso, 20, stdin);
		printf("RA: \n");
		scanf("%d", &aluno.ra);
		printf("Telefone: \n");
		scanf("%d", &aluno.telefone);

		fprintf(arquivo,"%s %s %s %d %d\n", aluno.nome, aluno.email, aluno.curso, aluno.ra, aluno.telefone);
		printf("%s %s %s %d %d\n", aluno.nome, aluno.email, aluno.curso, aluno.ra, aluno.telefone);

		i++;
	}

	fclose(arquivo);
}
