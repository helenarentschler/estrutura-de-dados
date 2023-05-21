#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {   

	int dia;   
	int mes; 
	
} Data;

typedef struct Contato {   

	char nome[45];   
	char telefone[12];   
	Data dataAniversario;   
	struct Contato *prox;  
	
} Contato;

typedef struct Agenda {  
 
	int qnt_cont;   
	Contato* contatos; 
	
} Agenda;

Agenda* criarAgenda();
void inserirContato(Agenda* agenda);
void exibirContatos(Contato* paux);
void buscarContato(Contato* paux);

int main() {

	Agenda* agenda = criarAgenda();
	
	int op = 0;

	while(op != 6) {

		printf("1 - Adicionar novo contato\n2 - Exibir contatos\n3 - Pesquisar contato\n4 - Remover contato\n5 - Apagar todos os registros\n6 - Sair");
		scanf("%d", &op);

		switch(op) {
			case 1:
				inserirContato(agenda);
			break;
			case 2:
				exibirContatos(agenda->contatos);
			break;
			case 3:
				buscarContato(agenda->contatos);
			break;
			case 4:
			break;
			case 5:
			break;
			case 6:
			break;
		}
	
	}
	return 0;
}

Agenda* criarAgenda() {

	Agenda* agenda = (Agenda*) malloc(sizeof(Agenda));

	if(agenda) {

		agenda->qnt_cont = 0;
		agenda->contatos = NULL;

	} else {printf("Nao foi possivel criar agenda.\n");}

	return agenda;
}

void inserirContato(Agenda* agenda) {

	Contato* novo = (Contato*) malloc(sizeof(Contato));

	if(novo) {

		printf("Insira Nome: \n");
		scanf("%s", novo->nome);
		printf("Insira Telefone: \n");
		scanf("%s", novo->telefone);
		printf("Insira dia de aniversario: \n");
		scanf("%d", &novo->dataAniversario.dia);
		printf("Insira mes de aniversario: \n");
		scanf("%d", &novo->dataAniversario.mes);
		
		novo->prox = agenda->contatos;
		agenda->contatos = novo;
		
	} else {printf("Nao foi possivel adicionar contato.\n");}
}

void exibirContatos(Contato* paux) {

	if(paux) {

		printf("======= CONTATOS =======\n");

		while(paux != NULL) {

			printf("Nome: %s\n", paux->nome);
			printf("Telefone: %s\n", paux->telefone);
			printf("Aniversario: %d / %d\n", paux->dataAniversario.dia, paux->dataAniversario.mes);
			printf("===========================\n");
			
			paux = paux->prox;
		}
		
	} else {printf("Agenda vazia.\n");}
}

void buscarContato(Contato* paux) {

	if(paux) {

		char nome[45];
		
		printf("Insira o nome que deseja buscar: ");
		scanf("%s", nome);
		
		while(paux != NULL) {

			if(strcmp(paux->nome, nome) == 0) {

				printf("==== INFORMACOES DO CONTATO ====\n");
				printf("Nome: %s\n", paux->nome);
				printf("Telefone: %s\n", paux->telefone);
				printf("Aniversario: %d / %d\n", paux->dataAniversario.dia, paux->dataAniversario.mes);
				printf("===========================\n");	

				return;
			}
			
			paux = paux->prox;
		}

		printf("Contato nao encontrado.\n");
		
	} else {printf("Agenda vazia.\n");}
}

void removerContato(Agenda* agenda) {

	if(agenda->contatos){

		Contato *paux = agenda->contatos;
		char nome[45];
		
		printf("Insira o contato que deseja remover: ");
		scanf("%s", nome);

		if
		while(paux != NULL) {

			if(strcmp(paux->nome, nome) == 0) {

				return;
			}
			
			paux = paux->prox;
		}

		
	} else { printf("Agenda vazia.\n");}
}
