#include <stdio.h>
#include <stdlib.h>

// Criando tipo ContaBancaria
typedef struct {
	int agencia, numero;
	char titular[30];
	float saldo;
} ContaBancaria;

void mostrarMenu();
void alocar(int* pTam, ContaBancaria** ppContas);
ContaBancaria* buscarConta(int agencia, int numero, int pos, ContaBancaria* pContas);
void inserirRegistro(int* pPos, int tam, ContaBancaria* pContas);
void listarContas(int pos, ContaBancaria* pContas);
void consultarSaldo(int pos, ContaBancaria* pContas);
void alterarSaldo(int pos, ContaBancaria* pContas, int flag);
void desalocar(ContaBancaria** ppContas);

int main() {

	int op;
	//Ponteiro para 1byte do vetor (Banco) alocado - recebe NULL
	ContaBancaria* vetContas = NULL;
	//guarda a quantidade atual de registros de conta no vetor alocado 
	int pos = 0;
	//guarda tamanho maximo de vetContas
	int tam = 0;
	
	// mostre o menu e leia opçao enquanto opçao for diferente de 8 (sair)
	do {
		mostrarMenu();
		scanf("%d", &op);

		switch(op) {
		
			case 1:
				alocar(&tam, &vetContas);
				break;
				
			case 2:
				inserirRegistro(&pos, tam, vetContas);
				break;

			case 3:
				listarContas(pos, vetContas);
				break;
				
			case 4:
				consultarSaldo(pos, vetContas);
				break;
				
			case 5: 
				//flag 1 - deposito
				alterarSaldo(pos, vetContas, 1);
				break;
				
			case 6: 
				//flag 2 - saque
				alterarSaldo(pos, vetContas, 2);
				break;
				
			case 7:
				desalocar(&vetContas);							
				break;
				
			case 8:
				printf("Encerrando...");
				break;
				
			default:
				printf("Digite uma opçao valida.");
				break;
		}
		
	} while (op != 8);

	desalocar(&vetContas);
	return 0;
}

//mostra menu de opçoes para o usuario
void mostrarMenu() {
	printf("\n\nBanco - Escolha uma opçao\n");
	printf("1-Criar Banco\n");
	printf("2-Abrir uma conta\n");
	printf("3-Listar Contas\n");
	printf("4-Consultar Saldo\n");
	printf("5-Realizar Deposito\n");
	printf("6-Realizar Saque\n");
	printf("7-Excluir Banco criado.\n");
	printf("8-Sair\n");
}

//atualiza vetContas da main (por isso recebe endereço do ponteiro da main)
void alocar(int* pTam, ContaBancaria** ppContas) {

	printf("\nCriaçao de Banco de Contas\n");
	// Evita vazamento de memoria:
	//se vetContas ja apontar para um vetor alocado, nao deve apontar para outro sem antes aquele ser desalocado.
	if(!*ppContas) {
									
		printf("Quantas contas seu Banco deve ter?\n");
		scanf("%d", pTam);
		//aloca vetor de tam posiçoes, cada uma cabendo um registro de ContaBancaria
		//vetcontas (global) guarda endereço do 1 byte alocado
		*ppContas = (ContaBancaria*) malloc(*pTam * (sizeof(ContaBancaria)));
	
		//se pContas é NULL, o SO nao conseguiu alocar a quantidade pedida de contas
		if(!*ppContas) {
			printf("Nao foi possivel criar o Banco. Pode pedir menos contas?");
		}
		
	} else {
		printf("Ja existe um Banco. Se quiser exclui-lo para criar outro, digite opçao 8.\n");
	}
}

//busca uma conta de acordo com os parametros passados
ContaBancaria* buscarConta(int agencia, int numero, int pos, ContaBancaria* pContas) {

	int i;

	for(i = 0; i < pos; i++) {
			if(((pContas+i)->agencia == agencia) && ((pContas+i)->numero == numero)) {
				return pContas + i;
			}
	}

	return NULL;
}


void listarContas(int pos, ContaBancaria* pContas) {

	printf("\nListagem de Contas\n\n");

	if(pContas) {
		int i;
	
		for(i = 0; i < pos; i++) {
			printf("Titular: %s\n", (pContas + i)->titular);
			printf("Agencia: %d\n", (pContas + i)->agencia);
			printf("Numero: %d\n", (pContas + i)->numero);
			printf("Saldo: %f\n", (pContas + i)->saldo);
			printf("_______________________________________\n");
		}	
	} else {
		printf("Voce ainda nao criou um Banco. Digite opçao 1.\n");
	}
}

//insere um registro de conta por vez
void inserirRegistro(int* pPos, int tam, ContaBancaria* pContas) {

	printf("\nAbrir uma Conta\n");
	//se pContas nao for NULL

	if(pContas) {
		if(*pPos < tam) {
			int agencia, numero;
			ContaBancaria* pConta;
			
			//pede informaçoes do usuario
			printf("Digite a agencia:\n");
			scanf("%d", &agencia);
			printf("Digite o numero:\n");
			scanf("%d", &numero);
	
			pConta = (ContaBancaria*) buscarConta(agencia, numero, *pPos, pContas);
	
			if(!pConta) {
				// guarda na posiçao "pos" do vetor apontando por pContas
				printf("Digite o nome do titular:\n");
				setbuf(stdin, NULL);
				fgets((pContas + *pPos)->titular, 30, stdin);
	
				(pContas + *pPos)->agencia = agencia;
				(pContas + *pPos)->numero = numero;
				(pContas + *pPos)->saldo = 0;	
		
				//como foi adicionada mais uma conta, pos da main é incrementada
				(*pPos)++; 		
			} else {printf("A o numero de conta na agencia informada ja existe.\n");}	
			
		} else {printf("Nao ha mais espaço para um nova conta. Digite opçao 1 para criar outro banco.\n");}
		
	} else { printf("Voce ainda nao criou um Banco. Digite opçao 1.\n"); }
}

void consultarSaldo(int pos, ContaBancaria* pContas) {

	printf("\nConsultar Saldo\n");
		//se pContas nao for NULL
	if(pContas) {
		int agencia, numero;
		ContaBancaria* pConta;
		
		//pede informaçoes do usuario
		printf("Digite a agencia:\n");
		scanf("%d", &agencia);
		printf("Digite o numero:\n");
		scanf("%d", &numero);

		pConta = (ContaBancaria*) buscarConta(agencia, numero, pos, pContas);

		if(pConta) {
			printf("Titular: %s\n", pConta->titular);
			printf("Agencia: %d\n", pConta->agencia);
			printf("Numero: %d\n", pConta->numero);
			printf("\nSaldo: %f\n", pConta->saldo);

		} else {printf("A o numero de conta na agencia informada nao existe.\n");}
		
	} else {printf("Voce ainda nao criou um Banco. Digite opçao 1.\n");}
}

void alterarSaldo(int pos, ContaBancaria* pContas, int flag) {
			//se pContas nao for NULL
	if(pContas) {
		int agencia, numero;
		ContaBancaria* pConta;
		
		//pede informaçoes do usuario
		printf("Digite a agencia:\n");
		scanf("%d", &agencia);
		printf("Digite o numero:\n");
		scanf("%d", &numero);

		pConta = (ContaBancaria*) buscarConta(agencia, numero, pos, pContas);

		if(pConta) {
		
			printf("Titular da conta: %s\n", pConta->titular);
			printf("Saldo da conta: %f\n", pConta->saldo);
			float valor; 
			
			if(flag == 1) {
			
				printf("\nDepositar\n");
				printf("Quanto quer depositar?\n");
				scanf("%f", &valor);
				pConta->saldo += valor;
				printf("Novo Saldo: %f\n", pConta->saldo);
				
			} else if (flag == 2) {
			
				printf("\nSacar\n");
				printf("Quanto quer sacar?\n");
				scanf("%f", &valor);
				if (pConta->saldo >= valor) {
					pConta->saldo -= valor;
					printf("Novo Saldo: %f\n", pConta->saldo);
				} else { 
					printf("Saque maior que saldo.\n");
				}
			} 

		} else {
			printf("A o numero de conta na agencia informada nao existe.\n");
		}
		
	} else {
		printf("Voce ainda nao criou um Banco. Digite opçao 1.\n");
	}
}

void desalocar(ContaBancaria** ppContas) {

	printf("\nExcluindo Banco\n");
	
	if(*ppContas) {
		free(*ppContas);
		*ppContas = NULL;	
	} else {
		printf("Nao existe Banco a ser excluido.\n");
	}
}





