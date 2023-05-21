#include <stdio.h>
#include <math.h>

typedef struct {
	int x;
	int y;
} ponto;

float calcularDistancia(ponto a, ponto b) {
	return sqrt( pow( (b.x - a.x) , 2) + pow( (b.y - a.y) , 2) );
}

int main() {
	float dist;
	ponto a;
	ponto b;

	a.x = 1;
	a.y = 9;

	b.x = 2;
	b.y = 7;
	
	dist = calcularDistancia(a, b); 

	printf("%f", dist);
	return 0;
}
