#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

int assigning = 0, compare = 0;

float* createMas(int length)
{
	unsigned int i = 0;
	float* m = (float*)malloc(length * sizeof(float));

	for (i; i < length; i++)
	{
		m[i] = (rand() % 1001 + (rand() % 1000) / 1000.0f) * (float)pow(-1.0, (rand() % 2));
		if (m[i] == -0.0f)
		{
			m[i] = 0.0f;
		}
	}

	//for (i = 0; i < length; i++)
	//{
	//	printf_s("%lf\n", m[i]);
	//}

	return m;
}

int compareFunction(const void* a, const void* b)
{
	float fa = *(const float*)a;
	float fb = *(const float*)b;
	return (fa > fb) - (fa < fb);
}

int isSortCorrect(float* orig_mas, float* sort_mas, int length)
{
	int i = 0;

	qsort(orig_mas, length, sizeof(float), compareFunction);

	for (i = 0; i < length; i++)
	{
		if (sort_mas[i] != orig_mas[i])
		{
			return 0;
		}
	}
	return 1;
}

void merge(float* a, int left, int mid, int right)
{
	int i = left, j = mid + 1, l = 0;
	//float* c = (float*)malloc((right - left + 1) * sizeof(float));
	float* c = malloc(sizeof(float)*(right - left + 1));

	while (i <= mid && j <= right)
	{
		compare += 3;
		if (a[i] < a[j])
		{
			c[l++] = a[i++];
		}
		else
		{
			c[l++] = a[j++];
		}
		assigning++;
	}

	for (; i <= mid; l++, i++)
	{
		compare++;
		assigning++;
		c[l] = a[i];
	}

	for (; j <= right; l++, j++)
	{
		compare++;
		assigning++;
		c[l] = a[j];
	}

	for (j = 0, i = left; i <= right; i++, j++)
	{
		compare++;
		assigning++;
		a[i] = c[j];
	}

	free(c);
}

void mergeSort(float* arr, float* second, int l, int r)
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
	int length = 100000000, i = 0;
	float complexity = 0;
	float* mas = createMas(length);
	float* mas_copy = malloc(sizeof(float) * length);

	srand(114536171247);

	while (length <= 10000000)
	{
		for (i = 0; i < length; i++)
		{
			mas_copy[i] = mas[i];
		}

		mergeSort(mas_copy, mas, 0, length - 1);
		//
		//for (i = 0; i < length; i++)
		//{
		//	printf("%lf\n",mas_copy[i]);
		//}

		if (isSortCorrect(mas, mas_copy, length))
		{
			complexity = length*log(length);
			printf("%d;%d;%d;%lf;%lf\n",length,assigning,compare,assigning/complexity,compare/complexity);
		}
		else
		{
			printf("Not okey\n");
			break;
		}

		length += 5;

		assigning = 0;
		compare = 0;

		free(mas);
		free(mas_copy);

		mas = createMas(length);
		mas_copy = malloc(sizeof(float)*length);
	}

	free(mas);
	free(mas_copy);
}