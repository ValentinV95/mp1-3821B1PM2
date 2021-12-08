#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

int assigning = 0, compare = 0;

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

float *merge(float *mas1,int l_mas1,float *mas2,int l_mas2)
{
	int i = 0,j =0, l = 0;
	float *c = (float*)malloc(sizeof(float)*(l_mas2+l_mas1));

	while((i < l_mas1) && (j < l_mas2))
	{
		compare += 2;
		if (mas1[i]<mas2[j])
		{
			c[l++] = mas1[i++];
		}
		else
		{
			c[l++] = mas2[j++];
		}
		compare++;
		assigning++;
	}

	for (;i<l_mas1;i++)
	{
		compare++;
		assigning++;
		c[l++] = mas1[i];
	}

	for (; j < l_mas2; j++)
	{
		compare++;
		assigning++;
		c[l++] = mas2[j];
	}

	return c;
}

float* mergeSort(float *sortable, int left, int right)
{
	compare++;
	if (left<right)
	{
		int q = (left+right) / 2;

		int lright = right - (q+1)+1, lleft = q-left+1;

		float* l_mas = mergeSort(sortable, left, q);
		float* r_mas = mergeSort(sortable,q+1, right);

		return merge(l_mas, lleft,r_mas, lright);
	}

	return &sortable[left];
}

void main()
{
	int length = 100;
	int i;
	float* mas = createMas(length);
	float* mas_copy = (float*)malloc(sizeof(float) * length);

	srand(1005483580247);

	while (length < 4001)
	{
		mas = createMas(length);

		for (i = 0; i < length; i++)
		{
			mas_copy[i] = mas[i];
		}

		mas_copy = mergeSort(mas, 0, length - 1);

		if (isSortCorrect(mas, mas_copy, length))
		{
			double tmp = (assigning + compare) / round(length * log((double)length));
			printf("%d;%d;%1.2lf\n",length,assigning+compare,tmp);
		}
		else
		{
			printf("The implementation of sorting is incorrect");
			break;
		}
		length += 5;

		compare = 0;
		assigning = 0;

		free(mas);
		free(mas_copy);

		mas_copy = (float*)malloc(sizeof(float) * length);
		mas = createMas(length);
	}
	free(mas);
	free(mas_copy);
}