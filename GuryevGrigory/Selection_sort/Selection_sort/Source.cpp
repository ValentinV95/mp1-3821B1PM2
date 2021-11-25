#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Selection_Sort(float *Array,int size)
{
	int ng = 0;
	for (int i = 0; i < size-1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			ng=ng + 1;
			if (*(Array+min_index) > *(Array+j))
			{
				min_index = j;
			}
		}
		double change_var;
		change_var = *(Array+min_index);
		*(Array+min_index) = *(Array+i);
		*(Array+i) = change_var;

	}
	return ng;
}

int main()
{
	srand(time(NULL));
	int size = 100;
	int n = 0;
	float Array[100];//= { 0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < 100; i++)
	{
		int a = rand() % 10000;
		float f =  a/ 100.0f;
		Array[i] = f;
	}
	/*
	for (int i = 0; i < 9; i++)
	{
		int min_index = i;

		for (int j = i+1; j < 10; j++)
		{
			if (Array[min_index] > Array[j])
			{
				//min = Array[j];
				min_index = j;
			}
		}
		int change_var;
		change_var = Array[min_index];
		Array[min_index] = Array[i];
		Array[i] = change_var;
	}*/
	for (int z = 0; z < 100; z++)
	{
		printf("%f, ", Array[z]);
	}
	printf("\n");
	n = Selection_Sort(Array,size);
	for (int z = 0; z < 100; z++)
	{
		printf("%f, ", Array[z]);
	}
	printf("\n");
	printf("%i", n);
	//printf("%f Number of iterations:", n);
	return 0;
}