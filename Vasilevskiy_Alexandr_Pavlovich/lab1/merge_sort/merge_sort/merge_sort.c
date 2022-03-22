#include <stdio.h>
#include <stdlib.h>


void merge(double* array1, double* array2, int l, int q, int r)
{
	int i = l, j = q + 1, k = l;
	for (; (i < q+1) && (j < r+1); )
	{
		if (array1[i] < array1[j])
		{
			array2[k] = array1[i];
			i++; k++;
		}
		else
		{
			array2[k++] = array1[j++];
		}
	}
	for (; i < q+1; i++)
	{
		array2[k++] = array1[i];
	}
	for (; j < r+1; j++)
	{
		array2[k++] = array1[j]; 
	}
	for (i = l; i < k; i++)
	{
		array1[i] = array2[i];
	}
}

void merge_sort(double* array1, double* array2,int l ,int r)
{
	if (l< r)
	{
		int q = (l + r) / 2;
		merge_sort(array1, array2, l, q);
		merge_sort(array1, array2, q+1, r);
		merge(array1, array2, l, q, r);

	}
}



void print(double array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("[%d] = %lf;\n", i, array[i]);
	}
}

int main()
{
	int i, len = 15;
	double* ar1;
	double* ar2;

	ar1 = (double*)malloc(len * sizeof(double));
	ar2 = (double*)malloc(len * sizeof(double));
	for (i = 0; i < len; i++)
	{
		ar1[i] =rand() % 10000000 + rand() % 10000000 / 10000000.0;
		printf("a[%d] = %lf\n", i, ar1[i]);
		ar2[i] = 0;
	}
	merge_sort(ar1, ar2, 0, len - 1);
	for (i = 0; i < len; i++)
	{
		printf("a[%d] = %lf\n", i, ar1[i]);
	}
	free(ar1);
	free(ar2);
	return 0;
}