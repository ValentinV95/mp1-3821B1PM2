#include <stdio.h>
#include <stdlib.h>
#define size 10
void merge(float array[], float second[], int l, int m, int r)
{
	int left = l, p = m + 1, k;

	for (k = l; k <= r; k++)
	{
		if (left == m + 1)
		{
			second[k] = array[p++];
		}
		else if (p == r + 1)
		{
			second[k] = array[left++];
		}
		else if (array[left] < array[p])
		{
			second[k] = array[left++];
		}
		else
		{
			second[k] = array[p++];
		}
		
	}
	for (k = l; k <= r; k++)
	{
		array[k] = second[k];
		
	}
}
void mergesort(float array[], float second[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		mergesort(array, second, l, m);
		mergesort(array, second, m + 1, r);
		merge(array, second, l, m, r);
	}
}


void main()
{
	float array[size];
	srand(1000);

	for (int i = 0; i < size; i++) {
		array[i] = rand() % 1000 + (-500) + rand() % 1000 / 1000.0;
	}
	float* second;
	second = (float*)malloc(size * sizeof(float));
	int i;
	mergesort(array, second, 0, size - 1);
	for (int i = 0; i < size; i++)
		printf("%f\n", array[i]);
}