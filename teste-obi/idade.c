#include <stdio.h>
#include <stdlib.h>

int idadeCamila(int n1, int n2, int n3);

int main() {

	int idade1, idade2, idade3;

	scanf("%d", &idade1);
	scanf("%d", &idade2);
	scanf("%d", &idade3);

	printf("Idade Camila: %d", idadeCamila(idade1, idade2, idade3));
	return 0;
}

int idadeCamila(int n1, int n2, int n3) {

	if(n1 > n2 && n1 > n3) {

		if(n2 > n3) {

			return n2;
			
		} else {
		
			return n3;
		}
		
	} else if(n2 > n1 && n2 > n3) {

		if(n1 > n3) {
		
			return n1;

		} else {

			return n3;	
		} 

	} else if(n3 > n1 && n3 > n2) {

		if(n1 > n2) {

			return n1;

		} else {

			return n2;	
		}
	}
}
