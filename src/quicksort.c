#include "quicksort.h"

static void swap(Venda *a, Venda *b)
{
	Venda temp = *a;

	*a = *b;
	*b = temp;
}

static int partition(Venda vendas[], int low, int high)
{
	float pivot = vendas[high].valor_total;
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (vendas[j].valor_total > pivot) {
			i++;
			swap(&vendas[i], &vendas[j]);
		}
	}

	swap(&vendas[i + 1], &vendas[high]);

	return i + 1;
}

static void quickSortRec(Venda vendas[], int low, int high)
{
	if (low < high) {
		int pi = partition(vendas, low, high);

		quickSortRec(vendas, low, pi - 1);
		quickSortRec(vendas, pi + 1, high);
	}
}

void quicksort(Venda vendas[], int length)
{
	if (length > 1)
		quickSortRec(vendas, 0, length - 1);
}