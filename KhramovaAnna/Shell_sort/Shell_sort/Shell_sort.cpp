#include <stdio.h>
#include <stdlib.h>
int swap = 0, comp = 0;
void check_array(double array[], int size)
{
	for (int i = 1; i < size; i++)
	{
		if (array[i - 1] > array[i])
		{
			printf("\nSort is completed incorrectly\n");
			break;
		}
		else
		{
			printf("\nSort is correctly completed\n");
			break;
		}
	}
}

void Shell_sort(double array[], int size) {
	for (int step = size / 2; step > 0; step = step / 2) {
		for (int i = step; i < size; i++) {
			comp = comp + 1;
			for (int j = i - step; j >= 0 && array[j] > array[j + step]; j = j - step) {
				double tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
				swap = swap + 3;
				comp = comp + 2;
			}
		}
	}
}
int main() {
	const int n = 100;
	double a[n];
	int i = 0, j = 0;
	double tmp = 0;
	for (i = 0; i < n; i++) {
		printf("a[%d] = ", i);
		a[i] = (double)(rand()) / RAND_MAX * (2000) - 1000;
		printf("%lf\n", a[i]);
	}
	Shell_sort(a, n);
	printf("\nsorted array:\n");
	for (i = 0; i < n; i++) {
		printf("a[%d] = %lf\n", i, a[i]);
	}
	printf("cheking the correctness of sort:\n");
	check_array(a, n);
	printf("the number of comparisons = %d\n", comp);
	printf("the number of swap = %d", swap);
	return 0;
}