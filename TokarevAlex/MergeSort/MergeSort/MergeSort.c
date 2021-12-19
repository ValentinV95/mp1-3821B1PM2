#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10

int comp = 0, swap = 0;

void merge(float arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	float L[N / 2 + 1], R[N / 2 + 1];

	for (i = 0; i < n1; i++) {
		comp++;
		L[i] = arr[l + i];
		swap++;
	}
	for (j = 0; j < n2; j++) {
		comp++;
		R[j] = arr[m + 1 + j];
		swap++;
	}

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2) {
		comp += 2;
		if (L[i] <= R[j]) {
			comp++;
			arr[k] = L[i];
			swap++;
			i++;
		}
		else {
			arr[k] = R[j];
			swap++;
			j++;
		}
		k++;
	}

	while (i < n1) {
		comp++;
		arr[k] = L[i];
		swap++;
		i++;
		k++;
	}

	while (j < n2) {
		comp++;
		arr[k] = R[j];
		swap++;
		j++;
		k++;
	}

}

void MergeSort(float arr[], int l, int r)
{
	if (l < r) {

		comp++;
		int m = l + (r - l) / 2;

		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void PrintArr(float arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%.3f ", arr[i]);

}

int compare(const void* a, const void* b)
{
	float fa = *(const float*)a;
	float fb = *(const float*)b;
	return (fa > fb) - (fa < fb);
}

int main()
{
	float arr[N];
	float arr_dup[N];
	int i, n = N;

	srand(time(0));

	for (i = 0; i < n; i++)
	{
		arr[i] = pow(-1, i) * (rand() % 1000 / 100.0 + (rand() % 1000) / 1000.0);
		arr_dup[i] = arr[i];
	}
	printf("Original array: ");
	PrintArr(arr, n);

	MergeSort(arr, 0, n - 1);
	qsort(arr_dup, n, sizeof(float), compare);

	printf("\nSorted array: ");
	PrintArr(arr, n);

	printf("\n qsort array: ");
	PrintArr(arr_dup, n);

	printf("\nnumber of swaps and compares: %i %i\n", swap, comp);

	return 0;
}