#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void Merge(float* array1, float* array2, int l, int m, int r)
{
	int i = l, j = m + 1, k = l;

	for (; (i < m + 1) && (j < r + 1); )
	{
		if (array1[i] < array1[j])
		{
			array2[k] = array1[i];
			i++; k++;
		}
		else
		{
			array2[k++] = array1[j++];
		}
	}
	for (; i < m + 1; i++)
	{
		array2[k++] = array1[i];
	}
	for (; j < r + 1; j++)
	{
		array2[k++] = array1[j];
	}
	for (i = l; i < k; i++)
	{
		array1[i] = array2[i];
	}
}

void MergeSort(float* array1, float* array2, int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		MergeSort(array1, array2, l, m);
		MergeSort(array1, array2, m + 1, r);
		Merge(array1, array2, l, m, r);

	}
}

void main()
{
	setlocale(LC_ALL, "Russian");
	int i, len;
	float* arr1;
	float* arr2;

	printf("Укажите длину массива : ");
	scanf_s("%d", &len);
	getchar();

	arr1 = (float*)malloc(len * sizeof(float));

		srand(887);
		for (i = 0; i < len; i++)
			arr1[i] = rand() % 1000 + rand() % 1000 / 1000.0;

	printf("Исходный массив : ");
	printf("\n");
	for (i = 0; i < len; i++)
		printf("array[%d] = %f\n", i, arr1[i]);
	printf("\n");


	arr2 = (float*)malloc(len * sizeof(float));
	MergeSort(arr1, arr2, 0, len - 1);

	printf("Отсортированный массив : ");
	printf("\n");
	for (i = 0; i < len; i++)
		printf("array[%d] = %f\n", i, arr1[i]);
	printf("\n");

}

