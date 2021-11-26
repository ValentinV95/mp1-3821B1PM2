#include <stdio.h>
#define int size 10;
void merge(double a[], double b[],double c[], int n, int m) {
	int i, j, k;
	i = 0; j = 0, k = 0;
	while ((i < n) && (j < m)) {
		if (a[i] < b[j]) {
			c[k] = a[i];
			i++;
		}
		else {
			c[k] = b[j];
			j++;
		}
		k++;
	}
	while (i < n) {
		c[k] = a[i];
		i++;
		k++;
	}
	while (j < m) {
		c[k] = b[j];
		j++;
		k++;
	}

	for (k = 0; k < (n + m); k++) {
		printf("c[%d] = %d\t", k, c[k]);
	}
}

int main() {
	int i; 
	double a[size];
	for (i = 0; i < n; i++) {
		printf("a[%d] = ", i);
		scanf_s("%d", &a[i]);
	}
}