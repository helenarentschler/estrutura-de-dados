#include <stdio.h>

int main() {
	char str[] = "abc", *c = str;

	printf("Endereço %p: %c\n", c, *c);
	c++;
	printf("Endereço %p: %c\n", c, *c);
	c++;
	printf("Endereço %p: %c\n", c, *c);
	c++;
	printf("Endereço %p: %c\n", c, *c);
	return 0;
}
