#ifndef BST_H
#define BST_H

#include "data.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Venda {
	int id;
	float valor_total;
	Data data;

	struct Venda *esq;
	struct Venda *dir;
} Venda;

Venda *criarNo(int id, float valor_total, Data data);

Venda *inserir(Venda *raiz, int id, float valor_total, Data data);

Venda *buscar(Venda *raiz, int id);

void emOrdem(Venda *raiz);

void liberarArvore(Venda *raiz);

Venda *emOrdemArray(Venda *raiz, int *tamanho);

int contarNos(Venda *raiz);

#endif