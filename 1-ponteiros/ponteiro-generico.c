#include <stdio.h>

int main() {
	void *v;
	int *p, x = 1;

	v = &x;
	p = &x;

	printf("%p %d\n", v, *(int*)v);
	printf("%p %d\n", p, *p);
	
	return 0;
}
