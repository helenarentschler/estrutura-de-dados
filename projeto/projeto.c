//Trabalho estrutura de dados: Helena Rentschler e Paulo Adriano Lupepsa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void preencherHistograma(char arquivo[], int* nPixels, int* histograma, int* predominante, int* nlinhas, int* colunas);
void carregarImagem(char arquivo[], Cabeca* cabeca);
void limiarMetodoOtsu(int* histograma, int nPixels, int* limiarEscolhido);
void binarizarImagem(Cabeca* cabeca, int limiar, int predominante, int nlinhas, int ncolunas);
void desalocaMatriz(Cabeca* cabeca,int nLinhas, int nColunas);

int main() {

	//vetor histograma - indice = tom de cinza / valor = quantidade de pixels com aquele tom
	int histograma[256];
	int nPixels = 0;
	//tom de cinza predominante a ser ignorado na matriz esparsa
	int predominante = 0;
	int limiar = 0;
	int nlinhas = 0;
	int ncolunas = 0;

	char arquivo[20];
	
	Cabeca* matriz = criaCabeca();

	printf("Insira o nome do arquivo de imagem a ser binarizado (sem extensao): \n");
	scanf("%s", arquivo);

	strcat(arquivo, ".pgm");

	carregarImagem(arquivo, matriz);

	if(matriz->primeiraColuna) {

		preencherHistograma(arquivo, &nPixels, histograma, &predominante, &nlinhas, &ncolunas);
		
		limiarMetodoOtsu(histograma, nPixels, &limiar);
	
		binarizarImagem(matriz, limiar, predominante, nlinhas, ncolunas);
	
		desalocaMatriz(matriz,nlinhas,ncolunas);	

	}
	
	return 0;
}

Cabeca* criaCabeca() {
	
	Cabeca* cabeca = (Cabeca*) malloc(sizeof(Cabeca));

	if(cabeca) {

		cabeca->ultimaLinha = NULL;
		cabeca->ultimaColuna = NULL;
		cabeca->primeiraColuna = NULL;
		cabeca->primeiraLinha = NULL;
		
	} else {printf("Nao foi possivel alocar memoria");}

	return cabeca;
}

void insereLinha(Cabeca* cabeca, int linha) {

	if(cabeca) {

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
			
		} else {printf("Nao foi possivel alocar memoria\n");}	
	} else {printf("Matriz vazia.\n");}
}

void insereColuna(Cabeca* cabeca, int coluna) {

	if(cabeca) {
		
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
			
		} else {printf("Nao foi possivel alocar memoria\n");}	
	} else {printf("Matriz vazia.\n");}
}

//insere celula correspondente ao pixel no 
Celula* insereCelula(int valor, int linha, int coluna, Cabeca* cabeca) {

	if(cabeca) {
		
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

		} else {printf("Nao foi possivel alocar memoria\n");}	

		return nova;

	} else {printf("Matriz vazia.\n");}
}

// percorre o arquivo e preenche o vetor histograma com os valores correspondentes
void preencherHistograma(char arquivo[], int* nPixels, int* histograma, int* predominante, int* nlinhas, int* ncolunas) {

	FILE* imagem = fopen(arquivo, "r");

	if(imagem) {

		char formato[2];
		int ret = 0;
		int pixel = 0;
	
		for (int i = 0; i < 256; ++i) {
			histograma[i] = 0;
		}
	
		//le primeiras 2 linhas: formato e tamanho da imagem
		fscanf(imagem, "%s %d %d %d", formato, nlinhas, ncolunas, predominante);
	
		//atualiza numero de pixels na main
		(*nPixels) = (*nlinhas)*(*ncolunas);
	
		while(ret != EOF) {
		
			ret = fscanf(imagem, "%d", &pixel);
			(histograma[pixel])++;			
		}	

		fclose(imagem);
		
	} else {printf("Erro a abrir a imagem.\n");}
}

//funçao que carrega uma imagem na matriz esparsa
void carregarImagem(char arquivo[], Cabeca* cabeca) {

	if(cabeca) {
		
		FILE* imagem = fopen(arquivo, "r");

		if(imagem) {

			char formato[2];
			int nlinhas, ncolunas;
			int predominante = 0;
			int pixel = 0;
		
			//le primeiras 2 linhas: formato e tamanho da imagem
			fscanf(imagem, "%s %d %d %d", formato, &nlinhas, &ncolunas, &predominante);
		
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
		
					if(pixel != predominante) {
		
						celula = insereCelula(pixel, i, j, cabeca);
						printf("%d %d %d", celula->indiceLinha, celula->indiceColuna, celula->valor);
					}
				}
			}

			fclose(imagem);

		} else {printf("Erro a abrir a imagem.\n");}		
	} else {printf("Matriz vazia\n");}	

}

void limiarMetodoOtsu(int* histograma, int nPixels, int* limiarEscolhido) {

	if(nPixels) {
		
		double varianciaMaxima = 0.0;
	    int limiarOtimo = 0;

	    for (int limiar = 0; limiar < 256; limiar++) {
	        // Calcula a probabilidade de pixels abaixo e acima do limiar
	        double probabilidadeAbaixo = 0.0;
	        double probabilidadeAcima = 0.0;

	        for (int i = 0; i <= limiar; i++) {
	            probabilidadeAbaixo += (double) histograma[i] / nPixels;
	        }
	        probabilidadeAcima = 1.0 - probabilidadeAbaixo;

	        // Calcula as médias dos pixels abaixo e acima do limiar
	        double mediaAbaixo = 0.0;
	        double mediaAcima = 0.0;

	        if (probabilidadeAbaixo != 0.0) {
	            for (int i = 0; i <= limiar; i++) {
	                mediaAbaixo += (i * histograma[i]) / (nPixels * probabilidadeAbaixo);
	            }
	        }
	        if (probabilidadeAcima != 0.0) {
	            for (int i = limiar + 1; i < 256; i++) {
	                mediaAcima += (i * histograma[i]) / (nPixels * probabilidadeAcima);
	            }
	        }

	        // Calcula a variância entre as classes abaixo e acima do limiar
	        double variancia = probabilidadeAbaixo * probabilidadeAcima * (mediaAbaixo - mediaAcima) * (mediaAbaixo - mediaAcima);

	        // Atualiza o limiar ótimo se a variância for maior
	        if (variancia > varianciaMaxima) {
	            varianciaMaxima = variancia;
	            limiarOtimo = limiar;
	        }
	    }

	    *limiarEscolhido =  limiarOtimo;

	 }else {printf("Matriz vazia\n");}		
}

void binarizarImagem(Cabeca* cabeca, int limiar, int predominante, int nlinhas, int ncolunas) {

	if(cabeca) {
		
		FILE* binarizada = fopen("binarizada.pgm", "w");

		if(binarizada) {

			if(predominante > limiar) {
				
				predominante = 255;
				
			} else {
			
				predominante = 0;
			}
		
			Celula* auxLinha = cabeca->primeiraLinha;
			Celula* aux = NULL;
			int j = 0;
		
			fprintf(binarizada, "P2\n");
			fprintf(binarizada, "%d %d\n%d\n", nlinhas, ncolunas, predominante);
			
			do {
				j = 0;	
				aux = auxLinha->direita;
				do {			
					if(aux->indiceColuna == j) {
		
						if(aux->valor > limiar) {
						
							fprintf(binarizada, "%d\n", 255);
							
						} else {
		
							fprintf(binarizada, "%d\n", 0);
						}
						
						aux = aux->direita;		
						
					} else {
					
						fprintf(binarizada, "%d\n", predominante);
						
					}
					
					j++;
				
				} while(j < ncolunas);
				
				auxLinha = auxLinha->abaixo;
				
			} while(auxLinha != cabeca->primeiraLinha);	

			fclose(binarizada);

		} else {printf("Erro ao abrir a imagem");}
	} else {printf("Matriz vazia\n");}	
}

void desalocaMatriz(Cabeca* cabeca,int nLinhas, int nColunas){

	if(cabeca){

		if (cabeca->primeiraColuna && cabeca->primeiraLinha){

			Celula* auxColuna = cabeca->primeiraColuna;
			Celula* auxLinha = cabeca->primeiraLinha;
			Celula* aux = NULL;

			for(int i = 0;i<nColunas;i++){

				while(aux != auxColuna){

					aux = auxColuna->abaixo;
					if(aux != auxColuna){
						auxColuna->abaixo = aux->abaixo;
						free(aux);
					}
				}

				cabeca->primeiraColuna = auxColuna->direita;
				free(auxColuna);
				auxColuna = cabeca->primeiraColuna;

			}

			for(int j = 0;j<nLinhas;j++){

				cabeca->primeiraLinha = auxLinha->abaixo;
				free(auxLinha);
				auxLinha = cabeca->primeiraLinha;

			}
		} 

		free(cabeca);

	} else { printf("Matriz vazia\n");}
}

