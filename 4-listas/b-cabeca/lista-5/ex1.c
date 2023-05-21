//removeInicio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct funcionario Funcionario;
typedef struct departamento Departamento;

struct funcionario {  

	char cpf[12];  
	char nomeCompleto[25];  
	char telefone[15];  
	char email[25];  
	double salario; 
	Funcionario* prox;
};

struct departamento {  

	char setor[50];  
	int qnt_func; 
	Funcionario* lista;  
};

Departamento* criaDepartamento(char setor[]);
Funcionario* criaFuncionario(char cpf[], char nomeCompleto[], char telefone[], char email[], double salario);
void insereFuncionarioInicio(Departamento* dep, char cpf[], char nomeCompleto[], char telefone[], char email[], double salario);
void imprimeFuncionarios(Funcionario* paux);
void buscaFuncionario(Funcionario* paux, char nome[]);
void removeInicio(Departamento* dep);
void removeFuncionario(Departamento* dep, char cpf[]);

int main() {

	Departamento* dainf = criaDepartamento("Informatica");

	insereFuncionarioInicio(dainf, "119090539", "Paula Souza", "90082076", "paula@gmail.com", 3000.0);

	insereFuncionarioInicio(dainf, "229392838", "Ana Clara Matos", "30861036", "ana@gmail.com", 7000.0);	
	
	imprimeFuncionarios(dainf->lista);

	buscaFuncionario(dainf->lista, "Paula Souza");
	buscaFuncionario(dainf->lista, "Carlos Souza");

	removeInicio(dainf);

	imprimeFuncionarios(dainf->lista);

	insereFuncionarioInicio(dainf, "437246374", "Carlos Moreira", "25091287", "carlos@gmail.com", 3000.0);	

	insereFuncionarioInicio(dainf, "21093756", "Janaina Campos", "92763076", "jana@gmail.com", 15000.0);	

	imprimeFuncionarios(dainf->lista);

	removeFuncionario(dainf, "437246374");

	imprimeFuncionarios(dainf->lista);

	removeFuncionario(dainf, "119090539");

	imprimeFuncionarios(dainf->lista);

	removeFuncionario(dainf, "21093756");
	
	imprimeFuncionarios(dainf->lista);
	
	return 0;
}

Departamento* criaDepartamento(char setor[]) {

	Departamento* dep = (Departamento*) malloc(sizeof(Departamento));

	if(dep) {

		strcpy(dep->setor, setor);
		dep->qnt_func = 0;
		dep->lista = NULL;
		
	} else {printf("Nao foi possivel alocar departamento.\n");}
}

Funcionario* criaFuncionario(char cpf[], char nomeCompleto[], char telefone[], char email[], double salario) {

	Funcionario* novo = (Funcionario*) malloc(sizeof(Funcionario));
	
	if(novo) {

		strcpy(novo->cpf, cpf);
		strcpy(novo->nomeCompleto, nomeCompleto);
		strcpy(novo->telefone, telefone);
		strcpy(novo->email, email);
		novo->salario = salario;

		novo->prox = NULL;	
	}

	return novo;
}

void insereFuncionarioInicio(Departamento* dep, char cpf[], char nomeCompleto[], char telefone[], char email[], double salario) {

	Funcionario* novo = criaFuncionario(cpf, nomeCompleto, telefone, email, salario);
	
	if(novo) {

		novo->prox = dep->lista;
		dep->lista = novo;
		
	} else {printf("Nao foi possivel alocar funcionario.\n");}
}

void imprimeFuncionarios(Funcionario* paux) {

	if(paux) {

		printf("=== LISTAGEM DE FUNCIONARIOS ===\n");

		while(paux != NULL) {
		
			printf("Nome: %s\n", paux->nomeCompleto);
			printf("CPF: %s\n", paux->cpf);
			printf("Telefone: %s\n", paux->nomeCompleto);
			printf("Email: %s\n", paux->email);
			printf("Salario: %f\n", paux->salario);
			printf("==========================\n");

			paux = paux->prox;	
		}
		
	} else {printf("Nenhum funcionario cadastrado\n");}
}


void buscaFuncionario(Funcionario* paux, char nome[]) {

	if(paux) {

		while(paux != NULL) {

			if(strcmp(nome, paux->nomeCompleto) == 0) {

				printf("====== FUNCIONARIO =======\n");
				printf("Nome: %s\n", paux->nomeCompleto);
				printf("CPF: %s\n", paux->cpf);
				printf("Telefone: %s\n", paux->nomeCompleto);
				printf("Email: %s\n", paux->email);
				printf("Salario: %f\n", paux->salario);
				printf("==========================\n");

				return;
			}

			paux = paux->prox;	
		}

		printf("Funcionario nao encontrado.\n");
		
	} else {printf("Nenhum funcionario cadastrado\n");}
}

void removeInicio(Departamento* dep) {

	if(dep->lista) {

		Funcionario* paux = dep->lista;
		dep->lista = dep->lista->prox;
		free(paux);
		
	} else {printf("Nenhum funcionario cadastrado\n");}
}

void removeFuncionario(Departamento* dep, char cpf[]) {

	if(dep->lista) {

		Funcionario* paux = dep->lista;
		
		if(strcmp(paux->cpf, cpf) == 0) {

			removeInicio(dep);

		} else {

			Funcionario* pant = dep->lista;
			
			while(paux != NULL) {

				if(strcmp(paux->cpf, cpf) == 0) {

					pant->prox = paux->prox;
					free(paux);
					return;
				}

				pant = paux;
				paux = paux->prox;
			}	
		}
		
	} else {printf("Nenhum funcionario cadastrado\n");}
}
