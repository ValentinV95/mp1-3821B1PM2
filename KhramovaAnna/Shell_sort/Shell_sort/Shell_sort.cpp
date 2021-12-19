#include <stdio.h>
#include <stdlib.h>
int main() {
	const int n = 20000;
	double array[n];
	int i = 0, j = 0,step = 0;
	int comp = 0, swap = 0;
	double tmp = 0;
	//for (i = 0; i < n; i++) {
	//	printf("a[%d] = ", i);
	//	scanf_s("%lf", &array[i]);
	//}
	srand(777);
	for (i = 0; i < n; i++) {
		printf("a[%d] = ", i);
		array[i] = rand()%200;
	}

	for (step = n / 2; step > 0; step = step / 2) {
		comp = comp + 1;
		for (i = step; i < n; i++) {
			comp = comp + 1;
			for (j = i-step; j >= 0 && array[j] > array[j+step]; j = j - step){
				comp = comp + 2;
				swap = swap + 3;
				tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;

			}
		}
	}
	printf("\nsorted array:\n");
	for (i = 0; i < n; i++) {
		printf("a[%d] = %.1lf\n", i, array[i]);
	}
	printf("the number of comparisons = %d", comp);
	printf("the number of swaps = %d", swap);
	return 0;
}