#include <stdio.h>
#include <stdlib.h>

typedef struct Celula Celula;

struct Celula {
	
	int valor;
	int indiceLinha;
	int indiceColuna;
	Celula* direita;
	Celula* abaixo;
};


int main() {

	Celula* matriz = criaCabeca();

	carregarImagem("castor.pgm", matriz);

	return 0;
}

Celula* criaCabeca() {

	Celula* cabeca = (Celula*) malloc(sizeof(Celula));

	if(cabeca) {

		cabeca->valor = -1;
		cabeca->indiceColuna = -1;
		cabeca->indiceLinha = -1;
		cabeca->abaixo = cabeca;
		cabeca->direita = cabeca; 	
	}

	return cabeca;
}


void insereLinhaColuna(int valor, int ilinha, int icoluna, Celula* linha, Celula* coluna) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));

	if(nova) {

		nova->valor = valor;
		nova->indiceColuna = icoluna;
		nova->indiceLinha = ilinha;

		if(ilinha == -1) {

			nova->abaixo = nova;
			nova->direita = linha;
			
		} else if (coluna) {
			

		}

		nova->abaixo = coluna;
		nova->direita = linha; 	
	}
}

void carregarImagem(char arquivo[], Celula* cabeca) {

	FILE* imagem = fopen(arquivo, "r");

	char formato[2];
	int nlinhas, ncolunas;

	fscanf(imagem, "%s %d %d", formato, &nlinhas, &ncolunas);

	int valor = 0;
                                                                                                                                                                                                                                                                                                                            
	for (int i = 0; i < ncolunas; ++i) {
	
		insereCelula(-1, -1, i, cabeca, NULL);
	}
	
	for (i = 0; i < nlinhas; ++i) {
	
		insereCelula(-1, i, -1, NULL, cabeca);
	}
}
