#include <stdio.h>

int main() {

	int num = 3;
	int *p;

	p = &num;

	*p = 6;

	printf("%p\n", p);
	//printf("%x\n", p);
	printf("%d\n", *p);
	
	return 0;
}

