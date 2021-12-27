#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>	

void quickSort(float *array, int first, int last)
{
	int l = first;
	int r = last;
	float pivot = array[(l + r) / 2];
	float temp;

	while (l < r)
	{
		while (array[l] < pivot)
			l++;
		while (array[r] > pivot)
			r--;
		if (l <= r)
		{
			temp = array[l];
			array[l] = array[r];
			array[r] = temp;
			l++;
			r--;
		}
	}
	if (r > first)
		quickSort(array, first, r);
	if (l < last)
		quickSort(array, l, last);
}

int comp(const void* a, const void* b)
{
	float fa = *(const float*)a;
	float fb = *(const float*)b;
	return (fa > fb) - (fa < fb);
}

int main()
{
	srand(time(NULL));
	int counter_sort = 0;
	int size = 10;
	float Array[100];
	float A_d[100];
	for (int i = 0; i < 100; i++)
	{
		int a = rand() % 10000;
		float f = a / 100.0f;
		Array[i] = f;
	}
	
	for (int z = 0; z < 100; z++)
	{
		printf("%f, ", Array[z]);
	}
	for (int i = 0; i < 100; i++)
	{
		A_d[i] = Array[i];
	}
	printf("\n");
	quickSort(Array,0, 99);
	qsort(A_d, 100, sizeof(float), comp);
	for (int i = 0; i < 100; i++)
	{
		if (A_d[i] == Array[i])
		{
			counter_sort++;
		}
	}
	if (counter_sort == 100)
	{
		printf("correct");
	}
	else
	{
		printf("not correct");
		printf("%i", counter_sort);
	}
	printf("\n");
	//printf("%i", n);
	//printf("%f Number of iterations:", n);
	return 0;
}
