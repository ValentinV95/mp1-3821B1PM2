#include <stdio.h>

int comb_sort(double array[], const size_t size)
{
	double factor = 1.2473309; // оптимальный фактор
	int step = size - 1;  //шаг между эл-тами
	double r1, r2;
	int i;
	int check_time = 0;  // количество сравнений
	int sort_time = 0;	// число перестановок



	while (step >= 1)
	{
		for (i = 0; i + step < size; i++)
		{
			if (array[i] > array[i + step])
			{
				r1 = array[i];
				array[i] = array[i + step];
				array[i + step] = r1;
				sort_time = sort_time + 1;
			}
			check_time = check_time + 1;
		}

		step /= factor;

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

	printf("please enter the numbers(double) in 10-size array\n It will be sorted by <combination(rascheska)> type\n");

	for (; i < 10; i++)
	{
		scanf_s("%lf", &b);
		a[i] = b;
	}

	

	comb_sort(a, 10);
}