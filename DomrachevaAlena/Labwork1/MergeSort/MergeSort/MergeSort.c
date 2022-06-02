#include "stdio.h"
#include "stdlib.h"
#include "locale.h"

#define N 10
int global_s = 0;
int global_p = 0;

void Merge(float* array, int first, int last)
{
	int left, right, middle;
	float* mas;
	mas = (float*)malloc((last - first) * sizeof(int));

	middle = (first + last) / 2;
	left = first;
	right = middle + 1;

	for (int j = first; j <= last; j++)
	{
		if ((left <= middle) && ((right > last) || (array[left]) < (array[right])))
		{
			*(mas + j - first) = array[left];
			left++;
		}
		else
		{
			*(mas + j - first) = array[right];
			right++;
		}
		global_p++;
		global_s += 4;
	}
	
	for (int g = first; g <= last; g++)
	{
		array[g] = *(mas + g - first);
		global_p++;
		global_s++;
	}
	

}

void MergeSort(float* array, int start, int end)
{
	if (start < end)
	{
		MergeSort(array, start, (start + end) / 2);
		MergeSort(array, (start + end) / 2 + 1, end);

		Merge(array, start, end);
	}
}

int main()
{
	float array[N];
	setlocale(LC_ALL, "Russian");
	srand(1000);
	for (int i = 0; i < N; i++)
	{
		array[i] = rand() % 2001 + (-1000) + (rand() % 1000) / 10000.0;
		printf("%f ", array[i]);
	}

	MergeSort(array, 0, N - 1);

	for (int a = 0; a < N; a++)
	{
		printf("\n%f ", array[a]);
	}
	printf("\nЧисло перестановок = %d", global_p);
	printf("\nКоличество сравнений = %d", global_s);
	return(0);
}