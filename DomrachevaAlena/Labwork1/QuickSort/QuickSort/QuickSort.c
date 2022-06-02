#include "stdio.h"
#include "math.h"
#include "locale.h"
#include "stdlib.h"
#define N 10

int global_p = 0;
int global_s = 0;

void qsort(float* array, int l, int r)
{
	double v = array[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (array[i] < v)
		{
			i++;
		}
		while (array[j] > v)
		{
			j--;
		}
		if (i <= j)
		{
			if (i < j)
			{
				float tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
				global_p += 1;
				global_s += 5;
			}
			i++;
			j--;
		}
		global_s += 4;
	}
	if (i <= r)
	{
		qsort(array, i, r);
		global_s += 1;
	}
	if (l < j)
	{
		qsort(array, l, j);
		global_s += 1;
	}
}


int main()
{
	float array[N];
	int l, r;
	setlocale(LC_ALL, "Russian");
	srand(100000);
	for (int a = 0; a < N; a++)
	{
		array[a] = rand() % 2001 + (-1000) + (rand() % 1000) / 10000.0;
		printf("%f ", array[a]);
	}
	qsort(array, 0, N-1);
	for (int k = 0; k < N; k++)
	{
		printf("\n%f", array[k]);
	}
	printf("\nЧисло перестановок = %d", global_p);
	printf("\nКоличество сравнений = %d", global_s);
	return 0;
}