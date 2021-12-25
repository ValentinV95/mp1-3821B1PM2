#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void SelectionSort(float* arr, int len)
{
	int i, j, mindx;
	float tmp;
	for (i = 0; i < len - 1; i++)
	{
		mindx = i;
		for (j = i + 1; j < len; j++)
		{
			if (arr[mindx] > arr[j])
			{
				mindx = j;
			}
		}
		tmp = arr[i];
		arr[i] = arr[mindx];
		arr[mindx] = tmp;
	}
}
void main()
{
	setlocale(LC_ALL, "Russian");
	int i, len;
	float* arr;

	printf("Укажите длину массива : ");
	scanf_s("%d", &len);
	getchar();

	arr = (float*)malloc(len * sizeof(float));

	srand(887);
	for (i = 0; i < len; i++)
		arr[i] = rand() % 1000 + rand() % 1000 / 1000.0;

	printf("Исходный массив : ");
	printf("\n");
	for (i = 0; i < len; i++)
		printf("array[%d] = %f\n", i, arr[i]);
	printf("\n");

	SelectionSort(arr, len);

	printf("Отсортированный массив : ");
	printf("\n");
	for (i = 0; i < len; i++)
		printf("array[%d] = %f\n", i, arr[i]);
	printf("\n");

}
