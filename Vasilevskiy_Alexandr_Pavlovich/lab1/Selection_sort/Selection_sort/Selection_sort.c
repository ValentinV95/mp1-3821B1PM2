#include <stdio.h>
#include <stdlib.h>

void selectionSort(double* arr, int len)
{
	int i, j, minID;
	double tmp;
	for (i = 0; i < len - 1; i++)
	{
		minID = i;
		for (j = i + 1; j < len; j++)
		{
			if (arr[minID] > arr[j])
			{
				minID = j;
			}
		}
		tmp = arr[i];
		arr[i] = arr[minID];
		arr[minID] = tmp;
	}
}

int main()
{
	int i, len = 10;
	double* a;
	srand(777);

	a = (double*)malloc(len * sizeof(double));
	for (i = 0; i < len; i++)
	{
		a[i] = rand() % 1000000 + (rand() % 1000000) / 1000000.0;
		printf("a[%d] = %lf;\n", i, a[i]);
	}
	selectionSort(a, len);
	for (i = 0; i < len; i++)
	{
		printf("a[%d] = %lf;\n", i, a[i]);
	}
	return 0;
}