#include <stdio.h>

int main() {
	int mat[4] = {0,6,8,3}, *p, x;

	x = (*mat)++; 
	printf("%d", x);
}
