#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h>
#include "hashtable.h"

typedef struct Item {
    Produto *produto;
    struct Item *prox;
} Item;

typedef struct Pilha {
    Item *topo;
    int tamanho;
} Pilha;

void inicializarPilha(Pilha *pilha);

int pilhaVazia(Pilha *pilha);

void empilhar(
    Pilha *pilha,
    Produto *produto
);

Produto *desempilhar(
    Pilha *pilha
);

void liberarPilha(
    Pilha *pilha
);

#endif