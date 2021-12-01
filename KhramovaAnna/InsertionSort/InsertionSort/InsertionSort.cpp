#include <stdio.h>
#include <stdlib.h>
int main() {
	const int size = 3;
	double array[size];
	int i = 0;
	int comp = 0, swap = 0;
	srand(777);
	for (i = 0; i < size; i++) {
		array[i] = rand() % 200;
		printf("a[%d] = %.1lf\t\n", i, array[i]);
	}
	printf("\nsorted massive\n");
	for (int i = 1; i < size; i++) {
		comp = comp + 1;
		for (int j = i; j > 0 && array[j - 1] > array[j]; j--) {
			int tmp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = tmp;
			comp = comp + 2;
			swap = swap + 3;
		}
	}

	for (i = 0; i < size; i++) {
		printf("a[%d]= %.1lf\t\n", i, array[i]);
	}
	printf("the number of comparisons = %d\n", comp);
	printf("the number of swaps = %d", swap);
	return 0;
}