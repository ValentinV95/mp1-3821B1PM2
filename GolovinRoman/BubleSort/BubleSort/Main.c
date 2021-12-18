#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

float* createMas(int length)
{
	int i = 0;
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

void bubleSort(float* data,int length,int* compare,int* swap)
{
	int i, j;
	float tmp;

	for (i = 0; i < length; i++)
	{
		(*compare)++;
		for (j = 0; j < length; j++)
		{
			(*compare)+=2;
			if (data[i] < data[j])
			{
				tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
				(*swap)++;
			}
		}
		(*compare)++;
	}
	(*compare)++;

	return data;
}

int main()
{
	int length = 50;
	int swap = 0, compare = 0, i;
	float *mas = createMas(length),complexity;
	float* mas_copy =(float*)malloc(sizeof(float)*length);

	srand(1005483580247);

	while (length <= 10000)
	{
		for (i = 0; i < length; i++)
		{
			mas_copy[i] = mas[i];
		}

		bubleSort(mas_copy, length, &compare, &swap);
		if (isSortCorrect(mas, mas_copy, length))
		{
			complexity = length * length;
			printf("%d;%d;%d;%lf;%lf\n",length,swap,compare,swap/complexity,compare/complexity);
		}
		else
		{
			printf("The implementation of sorting is incorrect");
			break;
		}

		length += 5;

		compare = 0;
		swap = 0;

		free(mas);
		free(mas_copy);

		mas_copy = (float*)malloc(sizeof(float) * length);
		mas = createMas(length);
	}
		
	free(mas);
	free(mas_copy);
	return 0;
}


