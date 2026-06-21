#include "bst.h"

Venda *criarNo(int id, float valor_total, Data data)
{
	Venda *novo = malloc(sizeof(Venda));

	if (novo == NULL) {
		return NULL;
	}

	novo->id = id;
	novo->valor_total = valor_total;
	novo->data = data;

	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

Venda *inserir(Venda *raiz, int id, float valor_total, Data data)
{
	if (raiz == NULL) {
		return criarNo(id, valor_total, data);
	}

	if (id < raiz->id) {
		raiz->esq = inserir(raiz->esq, id, valor_total, data);
	} else if (id > raiz->id) {
		raiz->dir = inserir(raiz->dir, id, valor_total, data);
	}

	return raiz;
}

Venda *buscar(Venda *raiz, int id)
{
	if (raiz == NULL) {
		return NULL;
	}

	if (id == raiz->id) {
		return raiz;
	}

	if (id < raiz->id) {
		return buscar(raiz->esq, id);
	}

	return buscar(raiz->dir, id);
}

void emOrdem(Venda *raiz)
{
	if (raiz == NULL) {
		return;
	}

	emOrdem(raiz->esq);

	printf("ID: %d | Valor: %.2f\n", raiz->id, raiz->valor_total);

	emOrdem(raiz->dir);
}

void liberarArvore(Venda *raiz)
{
	if (raiz == NULL) {
		return;
	}

	liberarArvore(raiz->esq);

	liberarArvore(raiz->dir);

	free(raiz);
}