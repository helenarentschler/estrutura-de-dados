#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct No {
	int chave;
	//ponteiro autorreferenciado: prox* guarada endereço do proximo no
	struct No* prox;
} tNo;

//retorna endereço do primeiro no
tNo* alocaNo(int k);
void insereInicio(tNo** ppPrim, int k);

int main() {
	//lista aponta para primeiro no
	tNo* prim = NULL;

	insereInicio(&prim, 13);
	insereInicio(&prim, 2);
	
	return 0;
}

tNo* alocaNo(int k) {
	//ponteiro de no
	tNo* pNo;
	//recebe endereço de um no
	pNo = (tNo *) malloc(sizeof(tNo));
	//chave do endereço alocado recebe k
	pNo->chave = k;
	//proxima é NULL, pois so tem 1 item
	pNo->prox = NULL;

	return pNo;
}

void insereInicio(tNo** ppPrim, int k) {

	assert(ppPrim);
	
	tNo* pNovo;
	pNovo = alocaNo(k);

	//campo prox de pNovo aponta para aquele que era o primeiro e agora sera o segundo;
	pNovo->prox = *ppPrim;
	//o ponteiro prim da main recebe endereço do novo no, que agora é o primeiro;
	*ppPrim = pNovo;
}

void removeInicio(tNo** ppPrim) {

	assert(ppPrim);

	if(!*ppPrim) return;

	//paux recebe endereço do primeiro (que sera removido)
	tNo* paux = *ppPrim;

	//prim da main recebe endereço do segundo (agora se torna primeiro)
	*ppPrim = (*ppPrim)->prox;

	//desaloco o primeiro
	free(paux);
}
