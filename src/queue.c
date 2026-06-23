#include "queue.h"

void inicializarFila(Fila *f)
{
	f->inicio = NULL;
	f->fim = NULL;
	f->tamanho = 0;
}

void enfileirar(Fila *f, Cliente c)
{
	Cliente *novo = (Cliente *)malloc(sizeof(Cliente));

	if (!novo) {
		return;
	}

	*novo = c;
	novo->prox = NULL;

	if (f->fim == NULL) {
		f->inicio = novo;
		f->fim = novo;
	} else {
		f->fim->prox = novo;
		f->fim = novo;
	}

	f->tamanho++;
}

Cliente desenfileirar(Fila *f)
{
	Cliente vazio = {0, "", 0, 0, 0};

	if (f->inicio == NULL) {
		return vazio;
	}

	Cliente *temp = f->inicio;
	Cliente c = *temp;

	f->inicio = f->inicio->prox;

	if (f->inicio == NULL) {
		f->fim = NULL;
	}

	free(temp);
	f->tamanho--;

	return c;
}

Cliente proximoCliente(Fila *f)
{
	Cliente vazio = {0, "", 0, 0, 0};

	if (f->inicio == NULL) {
		return vazio;
	}

	return *(f->inicio);
}

int tamanhoFila(Fila *f)
{
	return f->tamanho;
}

void carregarClientes(Fila *f, const char *arquivo)
{
	// abre o arquivo em modo leitura
	// fp vai guardar o endereço do arquivo aberto
	FILE *fp = fopen(arquivo, "r");

	if (!fp) {
		return;
	}

	Cliente c;

	/*
	   O laço continua executando enquanto conseguir ler corretamente todos
	   os dados de um cliente
	*/
	while (fscanf(fp,
		   " %d;%99[^;];%d;%d;%d",
		   &c.id,
		   c.nome,
		   &c.dia,
		   &c.mes,
		   &c.ano) == 5) {
		c.prox = NULL;
		enfileirar(f, c);
	}

	fclose(fp);
}

void liberarFila(Fila *f)
{
	Cliente *aux = f->inicio;

	while (aux != NULL) {
		Cliente *temp = aux;
		aux = aux->prox;
		free(temp);
	}

	f->inicio = NULL;
	f->fim = NULL;
	f->tamanho = 0;
}