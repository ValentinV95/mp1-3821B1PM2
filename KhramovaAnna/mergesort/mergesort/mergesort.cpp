#include <stdio.h>
#include <stdlib.h>
#define size 7
void merge(double a[], int low, int middle, int high) {

	int j = low;
	int k = middle + 1;
	int count = low - high + 1;
	int i = 0;
	double b[size] = {0};

	while (j <= middle && k <= high) {
		if (a[j] < a[k]) {
			b[i] = a[j];
			j++;
		}
		else {
			b[i] = a[k];
			k++;
		}
		i++;
	}
	while (j <= middle) {
		b[i] = a[j];
		j++;
		i++;
	}
	while (k <= high) {
		b[i] = a[k];
		k++;
		i++;
	}
	for (int i = low; i <= high; i++) {
		a[i] = b[i-low];
	}
}

void Mergesort(double a[], int l, int r) {
	if (l < r) {
		int q = l + (r-l)/2;
		Mergesort(a, l, q);
		Mergesort(a, q + 1, r);
		merge(a, l, q, r);
	}
}

int main() {
	int i = 0; 
	double a[size];
	//double b[size];
	for (i = 0; i < size; i++) {
		printf("a[%d] = ", i);
		scanf_s("%lf", &a[i]);
	}

	printf("sorted massive\n");
	Mergesort(a,0, size - 1);
	for (int i = 0; i < size; i++) {
		printf("a[%d] = %lf\n", i, a[i]);
	}
	return 0;
}