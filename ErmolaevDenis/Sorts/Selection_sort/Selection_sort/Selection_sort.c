#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define N  100

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

void selection_sort(double arr[], int n, int* assignments, int* comparisons)
{
	int i, j, min_idx;
	double tmp;

	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		*assignments = *assignments + 1;
		for (j = i + 1; j < n; j++)
		{
			*comparisons = *comparisons + 1;
			if (arr[j] < arr[min_idx])
			{
				min_idx = j;
				*assignments = *assignments + 1;
			}
		}
		tmp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = tmp;
		*assignments = *assignments + 3;
	}
}

double arr[N];

int main()
{
	int a = 0, c = 0;
	int* comparisons, * assignments;
	comparisons = &c;
	assignments = &a;
	randarr(arr, N);
	printarr(arr, N);
	selection_sort(arr, N, assignments, comparisons);
	//qsort(arr, N, sizeof(double), cmp);
	printarr(arr, N);
	printf(" Assignments=%i \n Comparisons=%i\n\n", a, c);
	return 0;
}