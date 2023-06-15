
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
void insereLinha(Cabeca* cabeca, int linha);
void insereColuna(Cabeca* cabeca, int coluna);
Celula* insereCelula(int valor, int linha, int coluna, Cabeca* cabeca);
void preencherHistograma(char arquivo[], int* nPixels, int* histograma, int* predominante);
void carregarImagem(char arquivo[], Cabeca* cabeca, int* predominante);
int limiarMetodoOtsu(int* histograma, int nPixels);

int main() {

	int histograma[256];
	int nPixels = 0;
	int predominante = 0;
	
	Cabeca* matriz = criaCabeca();

	preencherHistograma("teste.pgm", &nPixels, histograma, &predominante);
	carregarImagem("teste.pgm", matriz, &predominante);

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

void insereLinha(Cabeca* cabeca, int linha) {
	
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

}

void insereColuna(Cabeca* cabeca, int coluna) {
	
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
}

Celula* insereCelula(int valor, int linha, int coluna, Cabeca* cabeca) {

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
			} while (pauxlinha->direita != linhaAchada);

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
			} while (pauxcoluna->abaixo != colunaAchada);

			pauxcoluna->abaixo = nova;
			nova->abaixo = colunaAchada;
		}

	}

	return nova;
}

void preencherHistograma(char arquivo[], int* nPixels, int* histograma, int* predominante) {

	FILE* imagem = fopen(arquivo, "r");
	
	char formato[2];
	int nlinhas, ncolunas;
	int ret = 0;
	int pixel = 0;
	int maior = 0;

	for (int i = 0; i < 256; ++i) {
		histograma[i] = 0;
	}

	//le primeiras 2 linhas: formato e tamanho da imagem
	fscanf(imagem, "%s %d %d", formato, &nlinhas, &ncolunas);

	//atualiza numeor de pixels na main
	(*nPixels) = nlinhas*ncolunas;

	while(ret != EOF) {
	
		ret = fscanf(imagem, "%d", &pixel);
		(histograma[pixel])++;			
	}

	for(int i = 0; i < 256; i++){

		if(histograma[i] > maior) {
			maior = i;
		}
	}

	
	*predominante = maior;
}

//funçao que carrega uma imagem na matriz esparsa
void carregarImagem(char arquivo[], Cabeca* cabeca, int* predominante) {

	FILE* imagem = fopen(arquivo, "r");

	char formato[2];
	int nlinhas, ncolunas;
	int pixel = 0;

	//li primeiras 2 linhas: formato e tamanho da imagem
	fscanf(imagem, "%s %d %d", formato, &nlinhas, &ncolunas);

    Celula* celula = NULL;

	for (int i = 0; i < ncolunas; ++i) {

		insereColuna(cabeca, i);
	}

	for (int i = 0; i < nlinhas; ++i) {

		insereLinha(cabeca, i);	
	}

	for (int i = 0; i < nlinhas; ++i) {

		for (int j = 0; j < ncolunas; ++j){
			
			fscanf(imagem, "%d", &pixel);

			if(pixel != *predominante) {

				celula = insereCelula(pixel, i, j, cabeca);
				printf("[%d %d %d] ", celula->valor, celula->indiceLinha, celula->indiceColuna);
			}
		}
	}
}



/*int limiarMetodoOtsu(int* histograma, int nPixels) {
	
	float wb, wf, mf, mb, delta;
	float limiares[256];
	
	for(int i = 0; i < 256; i++) {

		wb = 0;
		wf = 0; 
		mf = 0; 
		mb = 0;
		delta = 0;
		
		for(int j = 0; j < i; j++) {

			wb += histograma[j];
			mb +=  histograma[j]*j;	
		
		}

		for(int k = i; k < 256; k++){

			wf += histograma[k];
			mf +=  histograma[k]*k;
		}

		if(wb && wf) {
			mb = mb/wb;’¢
			mf = mf/wf;
			wb = wb/nPixels;
			wf = wf/nPixels;	
		}
		
		delta = wb*wf*(mb-mf)*(mb-mf);

		printf("i %d, mb %f, wb %f, mf %f, wf %f, delta %f\n",i, mb, wb, mf, wf, delta);	

		limiares[i] = delta;
	}	
}*/
