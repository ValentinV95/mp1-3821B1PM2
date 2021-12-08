#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <process.h>
#include <math.h>

float* createMas(int length)
{
	int i = 0;
	float* m = (float*)malloc(length * sizeof(float));

	for (i; i < length; i++)
	{
		m[i] = (rand() % 1001 + (rand() % 1000) / 1000.0f) * pow(-1.0, (rand() % 2));
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

void shellSort(float* data,int length,int* swap,int*compare)
{
	int i = 0, step, j;
	float tmp;

	for (step = length / 2; step > 0; step /= 2)
	{
		(*compare)++;
		for (i = step; i < length; i++)
		{
			(*compare)++;
			for (j = i - step; j >= 0 && data[j] > data[j + step]; j -= step)
			{
				(*compare)+=2;

				tmp = data[j];
				data[j] = data[j + step];
				data[j + step] = tmp;
				(*swap)++;
			}
			(*compare)+=2;
		}
		(*compare)++;
	}
}

void main()
{
	int length = 100;
	int swap = 0, compare = 0, i;
	float* mas = createMas(length);
	float* mas_copy = (float*)malloc(sizeof(float) * length);
		
	srand(1005483580247);

	while (length < 4000)
	{		
		for (i = 0; i < length; i++)
		{
			mas_copy[i] = mas[i];
		}

		shellSort(mas_copy, length, &compare, &swap);

		if (isSortCorrect(mas, mas_copy, length))
		{
			float tmp = (swap + compare) / (length * pow(log(length), 2));
			printf("%d;%d;%1.0lf,%d\n",length,swap+compare,tmp,(int)(tmp*100)%100);
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
}