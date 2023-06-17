//Trabalho estrutura de dados: Helena Rentschler e Paulo Adriano Lupepsa
#include <stdio.h>
#include <stdlib.h>

typedef struct Celula Celula;
typedef struct Cabeca Cabeca;

//struct define celulas cabeça de cada linha e cada coluna (indice -1) e também as celulas que contém valores de pixel
struct Celula {

	int valor;
	int indiceLinha, indiceColuna;
	Celula* direita;
	Celula* abaixo;
};

//cabeça que aponta para celulas cabeça de linha e coluna
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
void imprimeMatriz(Cabeca* cabeca);
int limiarMetodoOtsu(int* histograma, int nPixels);

int main() {

	//vetor histograma - indice = tom de cinza / valor = quantidade de pixels com aquele tom
	int histograma[256];
	int nPixels = 0;
	//tom de cinza predominante a ser ignorado na matriz esparsa
	int predominante = 0;
	
	Cabeca* matriz = criaCabeca();

	preencherHistograma("teste.pgm", &nPixels, histograma, &predominante);
	carregarImagem("teste.pgm", matriz, &predominante);

	imprimeMatriz(matriz);

	limiarMetodoOtsu(histograma, nPixels);
	
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

//insere celula correspondente ao pixel no 
Celula* insereCelula(int valor, int linha, int coluna, Cabeca* cabeca) {

	Celula* nova = (Celula*) malloc(sizeof(Celula));
	
	if(nova) {

		nova->valor = valor;
		nova->indiceColuna = coluna;
		nova->indiceLinha = linha;

		//auxiliares que vao buscar as cabeças correspondentes a linha e coluna
		Celula* linhaAchada = cabeca->primeiraLinha;
		Celula* colunaAchada = cabeca->primeiraColuna;

		//busca da cabeça da linha
		do {

			if(linhaAchada->indiceLinha == linha) {
				break;	
			}	

			linhaAchada = linhaAchada->abaixo;	
				
		} while(linhaAchada != cabeca->primeiraLinha);	

		//busca da cabeça da coluna
		do {

			if(colunaAchada->indiceColuna != coluna) {
				break;
			}
			
			colunaAchada = colunaAchada->direita;
		
		} while(colunaAchada != cabeca->primeiraColuna);

		//ou seja, a linha esta vazia
		if(linhaAchada->direita == linhaAchada) {
			
			linhaAchada->direita = nova;
			nova->direita = linhaAchada;
		
		} else {

			Celula* pauxlinha = linhaAchada->direita;

			do {
				pauxlinha = pauxlinha->direita;
				//final da linha
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

// percorre o arquivo e preenche o vetor histograma com os valores correnpondentes
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

	//atualiza numero de pixels na main
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

	//le primeiras 2 linhas: formato e tamanho da imagem
	fscanf(imagem, "%s %d %d", formato, &nlinhas, &ncolunas);

    Celula* celula = NULL;

	for (int i = 0; i < ncolunas; ++i) {

		//insere celulas cabeça de coluna
		insereColuna(cabeca, i);
	}

	for (int i = 0; i < nlinhas; ++i) {

		//insere celulas cabeca de coluna
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

//funçao de teste que imprime a matriz linha a linha
void imprimeMatriz(Cabeca* cabeca) {

	Celula* auxLinha = cabeca->primeiraLinha;
	Celula* aux = cabeca->primeiraLinha;

	do {
		//se a linha for vazia, nao imprime
		if(auxLinha->direita != auxLinha) {
			//começa pela primeira celula
			aux = auxLinha->direita; 
					
			do {
			
				printf("valor %d\n", aux->valor);		
				aux = aux->direita;		
				
			} while(aux != auxLinha);	
		}
		
		auxLinha = auxLinha->abaixo;

	} while(auxLinha != cabeca->primeiraLinha);
	 
}


int limiarMetodoOtsu(int* histograma, int nPixels) {
	
	float wb, wf, mf, mb, delta, deltamax = 0.0;
	int limiarotimo = 0;
	
	for(int i = 0; i < 256; i++) {

		wb = 0.0;
		wf = 0.0; 
		
		for(int j = 0; j < i; j++) {

			wb += histograma[j] / nPixels;
		
		}
		
		wf = 1 - wb;

		mb = 0.0;
		mf = 0.0;

		if(wb != 0) {
			for(int j = 0; j <= i; j++) {
				mb += (j * histograma[j] / (nPixels * wb));		
			}
		}
		if(wf != 0) {
			for(int j = i + 1; j < 256; j++){
				mf += (j * histograma[j] / (nPixels * wf));	
			}	
		}
		
		delta = wb*wf*(mb-mf)*(mb-mf);

		if(delta > deltamax) {
			deltamax = delta;
			limiarotimo = i;
		}
	}	

	printf("Limiar otimo em %d, valor: %f", limiarotimo, deltamax);
	
}
