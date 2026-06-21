#include "stack.h"

void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

void empilhar(
    Pilha *pilha,
    Produto *produto
) {
    Item *novo =
        (Item *) malloc(sizeof(Item));

    if (novo == NULL) {
        return;
    }

    novo->produto = produto;
    novo->prox = pilha->topo;

    pilha->topo = novo;
    pilha->tamanho++;
}

Produto *desempilhar(
    Pilha *pilha
) {
    if (pilhaVazia(pilha)) {
        return NULL;
    }

    Item *temp =
        pilha->topo;

    Produto *produto =
        temp->produto;

    pilha->topo =
        temp->prox;

    free(temp);

    pilha->tamanho--;

    return produto;
}

void liberarPilha(
    Pilha *pilha
) {
    while (!pilhaVazia(pilha)) {
        desempilhar(pilha);
    }
}