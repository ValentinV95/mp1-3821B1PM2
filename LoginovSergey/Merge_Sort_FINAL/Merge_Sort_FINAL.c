#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define L 120

int assigning = 0, compare = 0;
double c[L] = { 0.0 };

void massiv(double* m, double* cm)
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
	double rch = *(const double*)a;
	double rzl = *(const double*)b;
	return (rch > rzl) - (rch < rzl);
}

void merge(double* a, int levo, int center, int pravo)
{
	int i = levo, j = center + 1, l = 0;

	while (i <= center && j <= pravo)
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

	for (; i <= center; l++, i++)
	{
		c[l] = a[i];
		compare++;
		assigning++;
	}

	for (; j <= pravo; l++, j++)
	{
		c[l] = a[j];
		compare++;
		assigning++;
	}

	for (j = 0, i = levo; i <= pravo; i++, j++)
	{
		a[i] = c[j];
		compare++;
		assigning++;
	}
}

void mergeSort(double* dmass, double* vtoroy, int l, int r)
{
	if (l < r)
	{
		int z = (l + r) / 2;

		mergeSort(dmass, vtoroy, l, z);
		mergeSort(dmass, vtoroy, z + 1, r);

		merge(dmass, l, z, r);
	}
}

void main()
{
	int i = 0, id = 1;
	double mas[L], mas_copy[L];

	srand(1195792);
	massiv(&mas, &mas_copy);

	mergeSort(mas_copy, mas, 0, L - 1);
	qsort(mas, L, sizeof(double), cmp);

	for (i = 0; i < L; i++)
	{
		if (mas[i] != mas_copy[i])
		{
			id = 0;
			break;
		}
	}

	if (id == 1)
	{
		printf_s("Sortiruet pravilno\n");
		printf_s("Dlinna - %d\nAssigning = %d\nCompare = %d\nAssigning/slojnost - %lf\nCompare/slojnost - %lf\n", L, assigning, compare, assigning / (L * log((double)L)), compare / (L * log((double)L)));
	}
	else
	{
		printf("Sortiruet nepravilno\n");
	}
}
