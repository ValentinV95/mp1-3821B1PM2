#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Selection_Sort(float *Array,int size)
{
	float change_var;

	for (int i = 0; i < size-1; i++)
	{
		float changevar;
		int min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (*(Array+min_index) > *(Array+j))
			{
				min_index = j;
			}
		}
		change_var = *(Array+min_index);
		*(Array+min_index) = *(Array+i);
		*(Array+i) = change_var;

	}
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
	int size = 100;
	int n = 0;
	float Array[100];//= { 0,0,0,0,0,0,0,0,0,0 };
	float A_d[100];
	for (int i = 0; i < 100; i++)
	{
		int a = rand() % 10000;
		float f =  a/ 100.0f;
		Array[i] = f;
	}
	for (int i = 0; i < 100; i++)
	{
		A_d[i] = Array[i];
	}
	printf("\n");
	Selection_Sort(Array,size);
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
	return 0;
}
