
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char titulo[100], autor[30];
	int ano;
} tLivro;

void carregar(tLivro** pplivros, int* ptam);
void cadastrarLivro(tLivro** pplivros, int* ptam);
void listarLivros(tLivro** pplivros, int* ptam);
void pesquisarLivro(tLivro** pplivros, int* ptam);
void desalocar(tLivro** pplivros, int* ptam);

int main() {

	printf("Biblioteca\n");
	
	tLivro* vetorLivros = NULL;
	int tam = 0;
	
	int op;

	do {
		printf("\n1-Cadastrar Livro\n");
		printf("2-Listar Livros\n");
		printf("3-Pesquisar Livro\n");
		printf("4-Sair\n");
		scanf("%d", &op);

		switch (op) {
			case 1:
				cadastrarLivro(&vetorLivros, &tam);	
			break;
			case 2:
				listarLivros(&vetorLivros, &tam);
			break;
			case 3:
				pesquisarLivro(&vetorLivros, &tam);
			break;
			case 4:
				printf("saindo...\n");
			break;
			default:
			break;
		}
	} while(op!=4);

	desalocar(&vetorLivros, &tam);
	
	return 0;
}

void carregar(tLivro** pplivros, int* ptam) {

	if(!*pplivros) {
		FILE* arquivo = fopen("acervo.txt", "r");

		if(arquivo){
			int ret = 0;
			tLivro livro;

			while(ret != EOF) {
				ret = fscanf(arquivo, "%s %s %d", livro.titulo, livro.autor, &livro.ano);
				(*ptam)++;
			}
				
			(*ptam)--; // descontar linha extra
			
			*pplivros = (tLivro*) malloc(*ptam * (sizeof(tLivro)));

			if(*pplivros) {
				int i = 0;
				rewind(arquivo);
	
				while(i < *ptam) {
					fscanf(arquivo, "%s %s %d", (*pplivros+i)->autor, (*pplivros+i)->titulo, &((*pplivros+i)->ano));
					i++;
				}
				
			} else {printf("Nao foi possivel alocar o vetor.\n");}
				
		} else {printf("Nao foi possivel abrir o arquivo.\n");}

		fclose(arquivo);
		
	} else {printf("Vetor ja foi carregado.\n");}
}

void cadastrarLivro(tLivro** pplivros, int* ptam) {

	FILE* arquivo = fopen("acervo.txt", "a");

	if(arquivo) {
		tLivro livro;
		
		printf("Qual o titulo da obra?\n");
		setbuf(stdin, NULL);
		scanf("%s", livro.titulo);
		printf("Qual o autor da obra?\n");
		setbuf(stdin, NULL);
		scanf("%s", livro.autor);
		printf("Qual o ano de publicaçao da obra?\n");
		scanf("%d", &livro.ano);

		fprintf(arquivo, "%s %s %d\n", livro.autor, livro.titulo, livro.ano);

		fclose(arquivo);

		desalocar(pplivros, ptam);
		
		carregar(pplivros, ptam);		
		
	} else {printf("Nao foi possivel cadastrar novo livro\n");}
}

void listarLivros(tLivro** pplivros, int* ptam) {

	if(!*pplivros){carregar(pplivros, ptam);}

	if(*pplivros){
		int i;

		for(i=0; i < *ptam; i++){
			printf("Titulo: %s, Autor: %s, Ano de publicaçao: %d\n", (*pplivros+i)->titulo, (*pplivros+i)->autor, (*pplivros+i)->ano);
		}
	} else {printf("Nao foi possivel listar livros.\n");}
}

void pesquisarLivro(tLivro** pplivros, int* ptam) {

	if(!*pplivros){carregar(pplivros, ptam);}

	if(*pplivros) {
	
		char titulo[100];
		int i, achei = 0;
		
		printf("Qual o titulo do livro que deseja pesquisar?\n");
		setbuf(stdin, NULL);
		scanf("%s", titulo);		

		for(i=0; i < *ptam; i++) {
			if(strcmp((*pplivros+i)->titulo,titulo) == 0) {
				achei = 1;
				break;
			}
		}

		if(achei == 1) {
			printf("O livro %s esta diponivel para emprestimo\n", (*pplivros+i)->titulo);
		} else {
			printf("Livro nao encontrado.\n");
		}
		
	} else {printf("Nao foi possivel fazer a pesquisa.\n");}
}

void desalocar(tLivro** pplivros, int* ptam) {
	if(*pplivros) {
		free(*pplivros);
		*pplivros = NULL;
		*ptam = 0;
	} else {printf("Nao a vetor a ser desalocado.\n");}
}