#include <stdio.h>

int main() {
	int a = 1;
	int *p = NULL;
	int **p2 = NULL;

	p = &a; 
	p2 = &p;

	if (&p == p2)
		printf("%d %d", *p, **p2);

	if (*&p == p) 
		printf("%d %d", **&p, **p2);
		
	return 0;
}
