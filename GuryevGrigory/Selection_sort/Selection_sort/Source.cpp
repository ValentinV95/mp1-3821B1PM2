#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Selection_Sort(int *Array)
{

	for (int i = 0; i < 9; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < 10; j++)
		{
			if (*(Array+min_index) > *(Array+j))
			{
				min_index = j;
			}
		}
		int change_var;
		change_var = *(Array+min_index);
		*(Array+min_index) = *(Array+i);
		*(Array+i) = change_var;

	}
}

int main()
{
	int Array[10] = { 0,11,12,3,4,7,6,5,9,8 };
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
	Selection_Sort(Array);
	for (int z = 0; z < 10; z++)
	{
		printf("%i, ", Array[z]);
	}
	return 0;
}