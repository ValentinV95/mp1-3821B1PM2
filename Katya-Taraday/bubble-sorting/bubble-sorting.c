#include <stdio.h>

int main() {
	const int n = 5;
	double array[n];
	int i, j;
	i = 0; j = 0;
	for (i = 0; i < n; i++) {
		scanf_s("%lf", &array[i]);
	}
	for (i = 0; i < n - 1; i++) {
		for (j = n - 2; j > i - 1; j--) {
			if (array[j] > array[j + 1]) {
				double tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%lf\n", array[i]);
	}
	return 0;
}

