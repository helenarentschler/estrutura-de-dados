#include <stdio.h>

typedef struct aluno {
	int RA;
	char nome[30];
	float rendaf;
	float notas[4];
} taluno;

void armazenar(taluno * p, int nPos) {

	int i, j;
	
	for(i = 0; i < nPos; i++){
		printf("Informe idade: \n");
		scanf("%d", &(p+i)->RA);
		setbuf(stdin, NULL);
		printf("Informe nome: \n");
		scanf("%[^\n]", (p+i)->nome);
		printf("Informe renda familiar: \n");
		scanf("%f", &(p+i)->rendaf);
		for(j = 0; j < 4; j++) {
			printf("Insira a %d nota: \n", j);
			scanf("%f", &(p+i)->notas[j]);
		}
	}	

}

int main() {

	int i, j;
	
	taluno vetAlunos[3];

	armazenar(vetAlunos, 3);
	
	for(i = 0; i < 3; i++){
		printf("idade: %d\n", vetAlunos[i].RA);
		printf("nome: %s\n", vetAlunos[i].nome);
		printf("Renda familiar: %f\n", vetAlunos[i].rendaf);

		for(j = 0; j < 4; j++) {
			printf("Nota %d: %f", j, vetAlunos[i].notas[j]);
		}
	}

	printf("%ld\n", sizeof(taluno));
	
	return 0;
}
