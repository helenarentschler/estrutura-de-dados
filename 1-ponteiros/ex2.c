#include <stdio.h>

int main() {
	int a = 1, b = 44, *pa = &a, *pb = &b, maior;
	
	if (*pa > *pb) {
		printf("%p", pa);
		printf("%p", pb);
	} else {
		printf("%p", pb);
		printf("%p", pa);
	}
	return 0;
}
