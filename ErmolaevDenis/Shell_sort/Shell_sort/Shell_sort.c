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

void shell_sort(double arr[], int n, int* assignments, int* comparisons)
{
	int step, i, j;
	double tmp;
	for (step = n / 2; step > 0; step /= 2)
	{
		for (i = step; i < n; i++)
		{
			*comparisons =*comparisons + 2;
			for (j = i - step; (j >= 0 && arr[j] > arr[j + step]); j -= step)
			{
				tmp = arr[j];
				arr[j] = arr[j + step];
				arr[j + step] = tmp;
				*assignments =*assignments + 3;
			}
		}
	}
}

double arr[N];

int main()
{
	int i;
	int a = 0, c = 0;
	int* assignments, * comparisons;
	assignments = &a;
	comparisons = &c;
	randarr(arr, N);
	printarr(arr, N);
	shell_sort(arr, N, assignments, comparisons);
	//qsort(arr, N, sizeof(double), cmp);
	printarr(arr, N);
	printf("Assignments=%i \n Comparisons=%i\n\n", a, c);
	return 0;
}