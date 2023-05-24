//mudar tudo para mesmo tipo, pois todos vao se apontar entre si

#include <stdio.h>
#include <stdlib.h>

typedef struct Celula Celula;
typedef struct Cabeca Cabeca;

struct Celula {

	int valor;
	int indiceLinha, indiceColuna;
	Celula* direita;
	Celula* abaixo;
};

struct Cabeca {

	Celula* primeiraLinha;
	Celula* primeiraColuna;
	Celula* ultimaLinha;
	Celula* ultimaColuna;	
};

Cabeca* criaCabeca();
Celula* insereLinha(Cabeca* cabeca, int linha);
Celula* insereColuna(Cabeca* cabeca, int coluna);
void carregarImagem(char arquivo[], Cabeca* cabeca);

int main() {

	Cabeca* matriz = criaCabeca();
	carregarImagem("castor.pgm", matriz);
	return 0;
}

Cabeca* criaCabeca() {
	
	Cabeca* cabeca = (Cabeca*) malloc(sizeof(Cabeca));

	if(cabeca) {

		cabeca->ultimaLinha = NULL;
		cabeca->ultimaColuna = NULL;
		cabeca->primeiraColuna = NULL;
		cabeca->primeiraLinha = NULL;
	}

	return cabeca;
}

Celula* insereLinha(Cabeca* cabeca, int linha) {
	
	Celula* novaLinha = (Celula*) malloc(sizeof(Celula));

	if(novaLinha) {

		novaLinha->valor = -1;
		novaLinha->indiceColuna = -1;
		novaLinha->indiceLinha = linha;
		novaLinha->direita = NULL;
		novaLinha->abaixo = NULL;

		if(cabeca->ultimaLinha) {
		
			cabeca->ultimaLinha->abaixo = novaLinha;		
		} else {

			cabeca->ultimaLinha = novaLinha;
		}
	}

	return novaLinha;
}

Celula* insereColuna(Cabeca* cabeca, int coluna) {
	
	Celula* novaColuna = (Celula*) malloc(sizeof(Celula));

	if(novaColuna) {

		novaColuna->valor = -1;
		novaColuna->indiceColuna = coluna;
		novaColuna->indiceLinha = -1;
		

		if(cabeca->primeiraColuna) {
		
			cabeca->ultimaColuna->direita = novaColuna;		

		} else {
		
			cabeca->primeiraColuna = novaColuna;
		}

		cabeca->ultimaColuna = novaColuna;
		novaColuna->direita = cabeca;
		novaColuna->abaixo = novaColuna;
	}

	return novaColuna;
}

Celula* insereCelula(Celula* linha, Celula* coluna, Celula* anterior, int valor) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));

	if(nova) {

		nova->valor = valor;
		nova->indiceColuna = coluna->indiceColuna;
		nova->indiceLinha = linha->indiceLinha;
		
		if(!anterior) {
		
			linha->direita = nova;
			coluna->abaixo = nova;
			nova->abaixo = coluna;
			nova->direita = linha; 	

		} else {

			anterior->direita = nova;
			coluna->abaixo = nova;
			nova->abaixo = coluna;
			nova->direita = linha;
		}
		
	}

	return nova;
}

void carregarImagem(char arquivo[], Cabeca* cabeca) {

	FILE* imagem = fopen(arquivo, "r");

	char formato[2];
	int nlinhas, ncolunas;

	fscanf(imagem, "%s %d %d", formato, &nlinhas, &ncolunas);

	int valor = 0;
	Celula* linha = NULL;
	Celula* coluna = NULL;
	Celula* anterior = NULL;
                                                                                                                                                                                                                                                                                                                            
	for (int j = 0; j < ncolunas; ++j) {
	
		coluna = insereColuna(cabeca, j);
	}
	
	for (int i = 0; i < nlinhas; ++i) {

		linha = insereLinha(cabeca, i);
		
		for (int j = 0; j < ncolunas; ++j) {
		
			fscanf(imagem, "%d", &valor);
			
			if(valor != 255) {
				
				anterior = insereCelula(linha, coluna, anterior, valor);
			}
		}
	}
}
