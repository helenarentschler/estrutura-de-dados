#include <stdio.h>

int maior(int a, int b);

int main() {

	int a = 7, b = 5, maiorN = 0;
	
	maiorN = maior(a, b);

	printf("maior: %d, a: %d, b: %d", maiorN, a, b);
	
	return 0;
}

int maior(int a, int b) {

	if(a > b) {
		return a;
	} else {
		return b;
	}
}
