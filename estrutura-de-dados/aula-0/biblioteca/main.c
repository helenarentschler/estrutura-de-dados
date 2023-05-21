#include <stdio.h>
#include "minha-biblio.h"


int main() {
	int res, n;
	printf("Insira um numero: ");
	scanf("%d", &n);
	res = fatorial(n);
	printf("O fatorial de %d é %d", n, res);
	return 0;
}
