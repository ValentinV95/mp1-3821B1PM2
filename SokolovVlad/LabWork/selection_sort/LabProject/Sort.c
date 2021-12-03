#include "stdio.h"


int selection_sort(double array[], const size_t size)
{
	int i = 0;
	int j, min_i, r1;
	double r2;
	int check_time = 0;  // количество сравнений
	int sort_time = 0;	// число перестановок

	for (; i < size - 1; i++)
	{
		min_i = i;

		for (j=i+1; j < size; j++)
		{
			check_time = check_time + 1;
			if (array[j] < array[min_i])
			{
				min_i = j;
				sort_time = sort_time + 1;
			}
		}

		r1 = array[i];
		array[i] = array[min_i];
		array[min_i] = r1;
	}
	for (i = 0; i < size; i++)
	{
		r2 = array[i];
		printf("%lf\n", r2);
		
	}
	printf("sort_times = %d	check_times = %d", sort_time, check_time);
}



int main()
{
	double a[10];
	int i = 0;
	double b;

	printf("please enter the numbers(double) in 10-size array\n It will be sorted by <selection> type\n");

	for (; i < 10; i++)
	{
		scanf_s("%lf", &b);
		a[i] = b;
	}
	selection_sort(a,10);
}