#include <stdio.h>
#include <stdlib.h>

void mostrarMenu();
void criarBanco();
int buscarConta(int numero, int agencia, char titular[30]);
void listarContas();
void inserirConta();

int main() {

	int op;
		
	do {
		mostrarMenu();
		scanf("%d", &op);

		switch(op) {
		
			case 1:
				criarBanco();
				break;
				
			case 2:
				inserirConta();
				break;

			case 3:
				listarContas();
				break;
				
			case 4:
				//consultarSaldo();
				break;
				
			case 5: 
				//flag 1 - deposito
				//alterarSaldo(1);
				break;
				
			case 6: 
				//flag 2 - saque
				//alterarSaldo(2);
				break;
				
			case 7:
				//desalocar();							
				break;
				
			case 8:
				printf("Encerrando...");
				break;
				
			default:
				printf("Digite uma opçao valida.");
				break;
		}
		
	} while (op != 8);
	
	return 0;
}

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

void criarBanco() {

	FILE* pBanco = NULL;
	
	printf("\nCriaçao de Banco de Contas\n");

	//como checar se ja existe arquivo em memoria?			
	pBanco = fopen("banco.txt", "w");

	if(!pBanco) {
		printf("Erro na criaçao do arquivo.\n");
	}

	fclose(pBanco);	
}

int buscarConta(int numero, int agencia, char titular[30]) {

	FILE* pBanco = NULL;
	
	int num = 0;
	int ag = 0; 
	char titu[30];
	float saldo = 0;
	
	pBanco = fopen("banco.txt", "r");

	if(pBanco) {
		while(!feof(pBanco)) {
			fscanf(pBanco, "%d %d %s %f", &ag, &num, titu, &saldo);
			if(numero == num && agencia == ag && titular == titu) {
				return 1;
			}
		}
		return 0;		
	}

	return 2;
	
	fclose(pBanco);
}

void inserirConta() {

	printf("\nAbrir uma Conta\n");
	
	int agencia, numero, achou;
	char titular[30];
		
	printf("Digite a agencia:\n");
	scanf("%d", &agencia);
	printf("Digite o numero:\n");
	scanf("%d", &numero);	
	printf("Digite o nome do titular: \n");
	setbuf(stdin, NULL);
	fgets(titular, 30, stdin);

	achou = buscarConta(agencia, numero, titular);

	if(achou == 0) {

		FILE* pBanco = NULL;

		pBanco = fopen("banco.txt", "a");

		if(pBanco) {
			fprintf(pBanco, "\n%d %d %s %f", agencia, numero, titular, 0.0);	
		} else {
			printf("Nao foi possivel criar conta.\n");
		}

		fclose(pBanco);	
		
	} else if (achou == 1) {
		printf("A conta ja existe.\n");
	} else {
		printf("Nao foi possivel criar conta.\n");
	}
	
}

void listarContas() {

	printf("\nListagem de Contas\n\n");

	FILE* pBanco = NULL;

	int num = 0;
	int ag = 0; 
	char titu[30];
	float saldo = 0;

	pBanco = fopen("banco.txt", "r");

	if(pBanco) {
		while(fscanf(pBanco, "%d %d %s %f", &ag, &num, titu, &saldo) != 0) {
			printf("\n%d %d %s %f", ag, num, titu, saldo);
		}		
	} else {
		printf("Nao foi possivel listar contas.");
	}

	fclose(pBanco);	
}

void consultarSaldo() {

	printf("\nConsultar Saldo\n");

}

void alterarSaldo() {

	int agencia, numero;
	
	printf("Digite a agencia:\n");
	scanf("%d", &agencia);
	printf("Digite o numero:\n");
	scanf("%d", &numero);

}

void desalocar() {

	printf("\nExcluindo Banco\n");
	
}
