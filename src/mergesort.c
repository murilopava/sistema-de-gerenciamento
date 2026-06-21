#include <stdlib.h>
#include "mergesort.h"

static void merge(Venda arr[], int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	Venda *L = malloc(n1 * sizeof(Venda));
	Venda *R = malloc(n2 * sizeof(Venda));

	if (!L || !R) {
		free(L);
		free(R);
		return;
	}

	for (int i = 0; i < n1; i++) L[i] = arr[left + i];
	for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (L[i].valor_total >= R[j].valor_total)
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	while (i < n1) arr[k++] = L[i++];
	while (j < n2) arr[k++] = R[j++];

	free(L);
	free(R);
}

void mergeSort(Venda arr[], int left, int right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
