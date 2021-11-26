#include <stdio.h>
#include <stdlib.h>
void Shell_sort(double array[], int n) {
	int i, j, tmp, step;
	for (step = n / 2; step > 0; step = step / 2) {
		for (i = step; i < n; i++) {
			for (j = i-step; j >= 0 && array[j] > array[j+step]; j = j - step){
				tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
			}
		}
	}
}

int main() {
	const int n = 10;
	int i = 0;
	double array[n];
	for (i = 0; i < n; i++) {
		printf("a[%d] = ", i);
		scanf_s("%lf", &array[i]);
	}
	Shell_sort(array, n);
	printf("\nsorted array:\n");
	for (i = 0; i < n; i++) {
		printf("a[%d] = %.1lf\n", i, array[i]);
	}
	return 0;
}