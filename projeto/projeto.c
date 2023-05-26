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
	carregarImagem("teste.pgm", matriz);

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

		if(cabeca->ultimaLinha) {
		
			cabeca->ultimaLinha->abaixo = novaLinha;	

		} else {

			cabeca->primeiraLinha = novaLinha;
		}

		cabeca->ultimaLinha = novaLinha;
		novaLinha->direita = novaLinha;
		novaLinha->abaixo = cabeca->primeiraLinha;
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
		novaColuna->direita = cabeca->primeiraColuna;
		novaColuna->abaixo = novaColuna;
	}

	return novaColuna;
}

Celula* insereCelula(int valor, int linha, int coluna, int nlinhas, int ncolunas, Cabeca* cabeca) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));

	if(nova) {

		nova->valor = valor;
		nova->indiceColuna = coluna;
		nova->indiceLinha = linha;
		
		Celula* linhaAchada = cabeca->primeiraLinha;
		Celula* colunaAchada = cabeca->primeiraColuna;

		do {

			linhaAchada = linhaAchada->abaixo;
		
		} while(linhaAchada != cabeca->primeiraLinha && linhaAchada->indiceLinha != linha);

		do {

			colunaAchada = colunaAchada->direita;
		
		} while(colunaAchada != cabeca->primeiraColuna && colunaAchada->indiceColuna != coluna);

		if(linhaAchada->direita == linhaAchada) {

			linhaAchada->direita = nova;
			nova->direita = linhaAchada;
		
		} else {

			Celula* pauxlinha = linhaAchada->direita;

			do {
				pauxlinha = pauxlinha->direita;
			} while (pauxlinha->direita != linhaAchada->direita);

			pauxlinha->direita = nova;
			nova->direita = linhaAchada;

		}
		
		if(colunaAchada->abaixo == colunaAchada) {

			colunaAchada->abaixo = nova;
			nova->abaixo = colunaAchada;
		
		} else {

			Celula* pauxcoluna = colunaAchada->abaixo;

			do {
				pauxcoluna = pauxcoluna->abaixo;
			} while (pauxcoluna->abaixo != colunaAchada->abaixo);

			pauxcoluna->abaixo = nova;
			nova->abaixo = colunaAchada;
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
    int pixel = 0;

    Celula* celula = NULL;

	for (int i = 0; i < ncolunas; ++i) {

		insereColuna(cabeca, i);
	}

	for (int i = 0; i < nlinhas; ++i) {

		insereLinha(cabeca, i);	

		for (int j = 0; j < ncolunas; ++j){
			
			fscanf(imagem, "%d", &pixel);

			if(pixel != 255) {

				celula = insereCelula(pixel, i, j, nlinhas, ncolunas, cabeca);
				printf("[%d %d %d] ", celula->valor, celula->indiceLinha, celula->indiceColuna);
			}
		}
	}
}
