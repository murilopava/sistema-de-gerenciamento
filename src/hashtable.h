#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TAM_HASH 1009

#include "data.h"

typedef struct Produto {
	int codigo;
	char nome[100];
	int quantidade;
	float preco;
	Data dataRegistro;

	struct Produto *prox;
} Produto;

// Tabela Hash
extern Produto *tabelaHash[TAM_HASH];

// Funções
void inicializarHash();

int hash(int codigo);

void inserirProduto(Produto produto);

Produto *buscarProduto(int codigo);

int removerProduto(int codigo);

void carregarProdutos(const char *nomeArquivo);

void listarProdutos();

void liberarHash();
// soma a quantidade de todas as unidades em estoque para o dashboard do menu
int  contarProdutos();

#endif