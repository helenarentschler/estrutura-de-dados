#include <stdio.h>

float perimetro(float * ph, float * pb);

int main() {
	float h = 3;
	float b = 6;
	float per = 0.0;
	
	per = perimetro(&h, &b);

	printf("per %f, h nova %f b nova %f", per, h, b);

	return 0;
}

float perimetro(float * ph, float * pb) {

	float perim = 0.0; 

	perim = 2 * *ph + 2 * *pb;

	*ph = 2 * *ph;
	*pb = 2 * *pb;
	
	return perim;
}
