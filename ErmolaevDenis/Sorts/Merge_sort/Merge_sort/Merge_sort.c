#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define N 100

int cmp(const void* a, const void* b)
{
	const double* ad, * bd;

	ad = (const double*)a;
	bd = (const double*)b;

	if (*ad < *bd)
	{
		return -1;
	}
	else if (*ad > *bd)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

double DRand(double fMin, double fMax)
{
	double f = (double)(rand()) / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void randarr(double arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		arr[i] = DRand(-1000, 1000);
}

void printarr(double arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%lf | ", arr[i]);
	printf("\n\n\n");
}

void merge(double arr[], int l, int r, int* comparisons, int* assignments)
{
	int l_iterator, r_iterator, mid, j;
	double* mas;
	mas = (double*)malloc((r - l) * sizeof(double));
	mid = (l + r) / 2;
	l_iterator = l;
	r_iterator = mid + 1;
	*assignments = *assignments + 3;
	for (j = l; j <= r; j++)
	{
		*comparisons =*comparisons + 3;
		*assignments =*assignments + 1;
		if ((l_iterator <= mid) && ((r_iterator > r) || (arr[l_iterator] < arr[r_iterator])))
			mas[j - l] = arr[l_iterator++];
		else mas[j - l] = arr[r_iterator++];
	}
	for (j = l; j <= r; j++)
	{
		arr[j] = mas[j - l];
		*assignments = *assignments + 1;
	}
}

void merge_sort(double arr[], int l, int r, int* comparisons, int* assignments)
{
	*comparisons = *comparisons + 1;
	if (l < r)
	{
		int q = (l + r) / 2;
		*assignments = *assignments + 1;
		merge_sort(arr, l, q, comparisons, assignments);
		merge_sort(arr, q + 1, r, comparisons ,assignments);
		merge(arr, l, r, comparisons, assignments);
	}
}

double arr[N];

int main()
{
	int i, a = 0, c = 0;
	int* comparisons, *assignments;
	comparisons = &c;
	assignments = &a;
	randarr(arr, N);
	printarr(arr, N);
	merge_sort(arr, 0, N - 1, comparisons, assignments);
	//qsort(arr, N, sizeof(double), cmp);
	printarr(arr, N);
	printf(" Assignments=%i \n Comparisons=%i\n\n", a, c);
	return 0;
}
