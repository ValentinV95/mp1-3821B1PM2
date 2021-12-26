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
			ng=ng + 1;
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
	for (int z = 0; z < 100; z++)
	{
		printf("%f, ", Array[z]);
	}
	printf("\n");
	Selection_Sort(Array,size);
	for (int z = 0; z < 100; z++)
	{
		printf("%f, ", Array[z]);
	}
	printf("\n");
	printf("%i", n);
	return 0;
}
