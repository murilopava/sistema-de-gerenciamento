#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente {
	int id;
	char nome[100];
	int dia;
	int mes;
	int ano;

	struct Cliente *prox;
} Cliente;

typedef struct {
	Cliente *inicio;
	Cliente *fim;
	int tamanho;
} Fila;

/* Funções */
void inicializarFila(Fila *f);
void enfileirar(Fila *f, Cliente c);
Cliente desenfileirar(Fila *f);
Cliente proximoCliente(Fila *f);
int tamanhoFila(Fila *f);
void carregarClientes(Fila *f, const char *arquivo);
void liberarFila(Fila *f);

#endif