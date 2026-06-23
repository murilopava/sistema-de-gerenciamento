#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

Produto *tabelaHash[TAM_HASH];

int hash(int codigo)
{
	return codigo % TAM_HASH;
}

void inicializarHash()
{
	for (int i = 0; i < TAM_HASH; i++) {
		tabelaHash[i] = NULL;
	}
}

void inserirProduto(Produto produto)
{
	int indice = hash(produto.codigo);

	Produto *novo = (Produto *)malloc(sizeof(Produto));

	if (novo == NULL) {
		return;
	}

	*novo = produto;
	novo->prox = tabelaHash[indice];

	tabelaHash[indice] = novo;
}

Produto *buscarProduto(int codigo)
{
	int indice = hash(codigo);

	Produto *aux = tabelaHash[indice];

	while (aux != NULL) {
		if (aux->codigo == codigo) {
			return aux;
		}

		aux = aux->prox;
	}

	return NULL;
}

int removerProduto(int codigo)
{
	int indice = hash(codigo);

	Produto *atual = tabelaHash[indice];
	Produto *anterior = NULL;

	while (atual != NULL) {
		if (atual->codigo == codigo) {
			if (anterior == NULL) {
				tabelaHash[indice] = atual->prox;
			} else {
				anterior->prox = atual->prox;
			}
			free(atual);
			return 1;
		}

		anterior = atual;
		atual = atual->prox;
	}

	return 0;
}

void carregarProdutos(const char *nomeArquivo)
{
	FILE *fp = fopen(nomeArquivo, "r");

	if (fp == NULL) {
		printf("Erro ao abrir %s\n", nomeArquivo);
		return;
	}

	Produto p;

	while (fscanf(fp,
		   "%d;%99[^;];%f;%d;%d;%d;%d",
		   &p.codigo,
		   p.nome,
		   &p.preco,
		   &p.quantidade,
		   &p.dataRegistro.dia,
		   &p.dataRegistro.mes,
		   &p.dataRegistro.ano) == 7) {
		inserirProduto(p);
	}

	fclose(fp);
}

void listarProdutos()
{
	for (int i = 0; i < TAM_HASH; i++) {
		Produto *aux = tabelaHash[i];

		while (aux != NULL) {
			printf("Codigo: %d\n", aux->codigo);
			printf("Nome: %s\n", aux->nome);
			printf("Quantidade: %d\n", aux->quantidade);
			printf("Preco: %.2f\n", aux->preco);
			printf("Data: %02d/%02d/%04d\n",
			    aux->dataRegistro.dia,
			    aux->dataRegistro.mes,
			    aux->dataRegistro.ano);

			printf("---------------------\n");

			aux = aux->prox;
		}
	}
}

// soma a quantidade de todas as unidades em estoque para o dashboard do menu
int contarProdutos()
{
	int total = 0;
	for (int i = 0; i < TAM_HASH; i++) {
		Produto *aux = tabelaHash[i];
		while (aux != NULL) {
			total += aux->quantidade;
			aux = aux->prox;
		}
	}
	return total;
}

void liberarHash()
{
	for (int i = 0; i < TAM_HASH; i++) {
		Produto *aux = tabelaHash[i];

		while (aux != NULL) {
			Produto *temp = aux;

			aux = aux->prox;

			free(temp);
		}

		tabelaHash[i] = NULL;
	}
}