#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
void comb_sort(double array[], const size_t size)
{
	double factor = 1.2473309; //фактор уменьшения
	int step = size - 1; // шаг сортировки
	double tmp;
	while (step >= 1) {
		for (int i = 0; i + step < size; i++) {
			if (array[i] > array[i + step]) {
				tmp = array[i];
				array[i] = array[i + step];
				array[i + step] = tmp;
			}
		}
		step /= factor;
	}
}
void main()
{
	double array[] = { 5.9023948 , 3 , -9.94832 , -50.764 , 10.2387 , 7.4856 , -48.0928 };
	int n = 7;
	comb_sort(array,n);
	int f;
	for (f = 0; f < n; f++)
	{
		printf_s("%lf\n", array[f]);
	}
}
