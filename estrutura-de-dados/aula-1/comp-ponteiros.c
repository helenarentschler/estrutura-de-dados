#include <stdio.h>

int main() {
	int *p, *p1, x, y;
	p = &x;
	p1 = &y;

	if(p1 == p)
		printf("Ponteiros iguais");
	else 
		printf("Ponteiros diferentes");
	return 0;
}
