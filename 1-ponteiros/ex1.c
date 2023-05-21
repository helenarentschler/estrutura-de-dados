#include <stdio.h>

int main() {
	int x = 0, *px = &x;
	float y = 0.0, *py = &y;

	printf("%p\n %d\n", px, *px);
	printf ("%p\n %f\n", py, *py);
	
	return 0;
}
