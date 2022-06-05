#include <stdio.h>
#include <stdlib.h>
int swap = 0;
int comp = 0;

void InsertionSort(double array[], int size) {
	int i = 0;

	for (int i = 1; i < size; i++) {
		comp = comp + 1;
		for (int j = i; j > 0 && array[j - 1] > array[j]; j--) {

			double tmp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = tmp;
			swap = swap + 3;
			comp = comp + 2;
		}
	}
}
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

int main() {
	const int size = 100;
	double array[size];
	int i = 0;
	srand(777);

	for (i = 0; i < size; i++) {
		printf("a[%d] = ", i);
		array[i] = (double)(rand()) / RAND_MAX * (2000) - 1000;
		printf("%lf\n", array[i]);
	}

	InsertionSort(array, size);
	printf("\nSORTED MASSIVE\n");
	for (i = 0; i < size; i++) {
		printf("a[%d]= %lf\n", i, array[i]);
	}

	printf("CHEKING THE CORRECTNESS OF SORTING:\n");
	check_array(array, size);

	printf("the number of comparisons = %d\n", comp);
	printf("the number of swaps = %d\n", swap);

	return 0;
}