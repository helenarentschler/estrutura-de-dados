#include <stdio.h>
#include <stdlib.h>

typedef struct Celula Celula;

struct Celula {

	float valor;
	int linha, coluna;
	Celula* direita;
	Celula* abaixo;
};

void carregarImagem(char arquivo[]);

int main() {

	Celula* matriz = NULL;
	carregarImagem("castor.pgm");
	return 0;
}

void carregarImagem(char arquivo[]) {

	FILE* imagem = fopen(arquivo, "r");

	char formato[2];
	int linhas, colunas;

	fscanf(imagem, "%s %d %d", formato, &linhas, &colunas);
	printf("%s %d %d\n", formato, linhas, colunas);

	int i = 0, j = 0;
	int valor = 0;

	for (int i = 0; i < linhas; ++i) {
		//crialista para cada linha ou coluna?
		for (int j = 0; j < colunas; ++i) {
			
			fscanf(imagem, "%d", valor);

			if(valor != 255) {

				insereMatriz(valor, i, j);
			}
		}
	}
}

void insereMatriz(int valor, int linha, int coluna) {

}