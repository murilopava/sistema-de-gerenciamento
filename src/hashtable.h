#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TAM_HASH 1009

typedef struct Data {
	int dia;
	int mes;
	int ano;
} Data;

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

#endif