#include <stdio.h>

int main(){
	int *p, *p1, x, y;

	p = &x;
	p1 = &y;

	(p > p1) ? printf("p > p1") : printf("p < p1");
	 
	return 0;
}
