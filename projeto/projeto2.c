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

}

void insereCelula(int valor, int ilinha, int icoluna, Celula* linha, Celula* coluna) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));

	if(nova) {

		nova->valor = valor;
		nova->indiceColuna = icoluna;
		nova->indiceLinha = ilinha;
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
                                                                                                                                                                                                                                                                                                                            
	for (int j = 0; j < ncolunas; ++j) {
	
		insereColuna(-1, -1, j, cabeca, NULL);
	}

}
