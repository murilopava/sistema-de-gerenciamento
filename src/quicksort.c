#include "quicksort.h"

static void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

static int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

static void quickSortRec(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSortRec(arr, low, pi - 1);
        quickSortRec(arr, pi + 1, high);
    }
}

void quicksort(int arr[], int length)
{
    if (length > 1)
    {
        quickSortRec(arr, 0, length - 1);
    }
}