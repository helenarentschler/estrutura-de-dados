#include "minha-biblio.h"

int fatorial(int num) {
	int fat = 1, i;
	for(i = 1; i <= num; i++){
		fat = fat*i;
	}
	return fat;
}

