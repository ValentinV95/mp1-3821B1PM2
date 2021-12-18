#include "stdio.h"
#include "math.h"
#include "locale.h"
#include "stdlib.h"
#define N 10

int main()
{
	int i, s = 0, p = 0,g;
	float array[N];
	setlocale(LC_ALL, "Russian");
	srand(1000);
	for (int a = 0; a < N; a++)
	{
		array[a] = rand() % 2001 + (-1000) + (rand() % 1000) / 10000.0;
		printf("%f ", array[a]);
	}
	for (i = 1; i < N; i++)
	{
		if (array[i - 1] > array[i])
		{
			p += 1;
			s += 3;
		}
		else;
		{
			s += 1;
		}
		for (int j = i; j > 0 && array[j - 1] > array[j]; j--)
		{
			float tmp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = tmp;
		}
	}
	for (int k = 0; k < N; k++)
	{
		printf("\n%f", array[k]);
	}
	printf("\nЧисло перестановок = %d", p);
	printf("\nКоличество сравнений = %d", s);
	return 0;
}
