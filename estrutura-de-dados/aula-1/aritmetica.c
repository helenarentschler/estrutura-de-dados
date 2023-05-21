#include <stdio.h>

int main() {
	int x=1, *p;

	p = &x;

	printf("%p\n\n", p);

	p++;

	printf("%p\n", p);

	p++;

	printf("%p\n", p);

	return 0;
}
