#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define L 120
int assigning = 0, compare = 0;

void feelMas(double* m, double* cm)
{
	int i;

	for (i = 0; i < L; i++)
	{
		m[i] = (rand() % 1001 + (rand() % 1000) / 1000.0) * pow(-1.0, (rand() % 2));
		if (m[i] == -0.0)
		{
			m[i] = 0.0;
		}
		cm[i] = m[i];
	}
}

int cmp(const void* a, const void* b)
{
	double fa = *(const double*)a;
	double fb = *(const double*)b;
	return (fa > fb) - (fa < fb);
}

void merge(double* a, int left, int mid, int right)
{
	int i = left, j = mid + 1, l = 0;
	double* c = malloc(sizeof(double) * (right - left + 1));

	while (i <= mid && j <= right)
	{
		if (a[i] < a[j])
		{
			c[l++] = a[i++];
		}
		else
		{
			c[l++] = a[j++];
		}
		compare = compare + 3;
		assigning++;
	}

	for (; i <= mid; l++, i++)
	{
		c[l] = a[i];
		compare++;
		assigning++;
	}

	for (; j <= right; l++, j++)
	{
		c[l] = a[j];
		compare++;
		assigning++;
	}

	for (j = 0, i = left; i <= right; i++, j++)
	{
		a[i] = c[j];
		compare++;
		assigning++;
	}

	free(c);
}

void mergeSort(double* arr, double* second, int l, int r)
{
	if (l < r)
	{
		int q = (l + r) / 2;

		mergeSort(arr, second, l, q);
		mergeSort(arr, second, q + 1, r);

		merge(arr, l, q, r);
	}
}

void main()
{
	int i = 0, ident = 1;
	double mas[L], mas_copy[L];

	srand(1195792);
	feelMas(&mas, &mas_copy);

	mergeSort(mas_copy, mas, 0, L - 1);
	qsort(mas, L, sizeof(double), cmp);

	for (i = 0; i < L; i++)
	{
		if (mas[i] != mas_copy[i])
		{
			ident = 0;
			break;
		}
	}

	if (ident == 1)
	{
		printf_s("Sortiruet pravilno\n");
		printf_s("Dlinna - %d\nAssigning = %d\nCompare = %d\nAssigning/slojnost - %lf\nCompare/slojnost - %lf\n", L, assigning, compare, assigning / (L * log((double)L)), compare / (L * log((double)L)));
	}
	else
	{
		printf("Sortiruet nepravilno\n");
	}
}