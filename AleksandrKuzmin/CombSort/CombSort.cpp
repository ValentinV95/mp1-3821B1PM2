#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void CombSort(float array[], int size)
{
	float gap = 1.2473309;
	int step = size - 1;

	while (step >= 1)
	{
		for (int i = 0; i + step < size; i++)
		{
			if (array[i] > array[i + step])
			{
				float tmp = array[i];
				array[i] = array[i + step];
				array[i + step] = tmp;
			}
		}
		step /= gap;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int i, len;
	float* arr;

	printf("Введите количество элементов для сортировки: ");
	scanf_s("%d", &len);
	getchar();

	arr = (float*)malloc(len * sizeof(float));

	srand(887);
	for (i = 0; i < len; i++)
		arr[i] = rand() % 100 + rand() % 1000 / 1000.0;
	printf("Неотсортированный массив: ");
	printf("\n");
	for (i = 0; i < len; i++)
		printf("элемент[%d] = %f\n", i, arr[i]);
	printf("\n");

	CombSort(arr, len);
	printf("Отсортированный массив: ");
	printf("\n");
	for (i = 0; i < len; i++)
		printf("элемент[%d] = %f\n", i, arr[i]);
	printf("\n");
}