#include <stdio.h>
#include <stdlib.h>
void InsertionSort(double array[], int size_of_array) {
	int flag = 0;
	for (int i = 1; i < size_of_array; i++) {
		for (int j = i; j > 0 && array[j - 1] > array[j]; j--) {
			int tmp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = tmp;
			flag = flag + 1;
		}
	}
	printf("%c\n", flag);
}

int main() {
	const int size = 20;
	double array[size];
	int i = 0;
	int flag = 0;
	srand(777);
	for (i = 0; i < size; i++) {
		array[i] = rand()%200 + (-100);
		printf("a[%d] = %.1lf\t\n", i, array[i]);
	}
	printf("\nsorted massive\n");
	InsertionSort(array, size);
	for (i = 0; i < size; i++) {
		printf("a[%d]= %.1lf\t\n", i, array[i]);
	}
	return 0;
}