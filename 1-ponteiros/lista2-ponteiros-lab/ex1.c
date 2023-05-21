#include <stdio.h>

int main(){
	int a = 32 ;
	float b = 10.6 ;
	char c = 'w' ;
	int *pa = &a ;
	float *pb = &b ;
	char *pc = &c ;

	*pa = 50;
	*pb = 70.7;
	*pc = 'h';

	printf("a: conteudo  %d,endereço  %p,tamanho  %li\n", a, &a, sizeof(a));
	printf("b: conteudo  %f,endereço  %p,tamanho  %li\n", b, &b, sizeof(b));
	printf("c: conteudo  %c,endereço  %p,tamanho  %li\n", c, &c, sizeof(c));
	printf("pa: conteudo  %p,endereço  %p,tamanho  %li\n", pa, &pa, sizeof(pa));
	printf("pb: conteudo  %p,endereço  %p,tamanho  %li\n", pb, &pb, sizeof(pb));
	printf("pc: conteudo  %p,endereço  %p,tamanho  %li\n", pc, &pc, sizeof(pc));

	return 0;
}
