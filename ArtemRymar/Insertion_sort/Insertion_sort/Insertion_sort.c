#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<math.h>

#define n 10


long assig = 0, compare = 0;

int comp(const void* i, const void* j)
{
	float r1 = *(const float*)i;
	float r2 = *(const float*)j;
	return(r1 > r2) - (r1 < r2);

}

void cout(const float* arr, int i) {
	int j;
	for (j = 0; j < i; j++) {
		printf("%f ", arr[j]);
	}
	printf("\n");
	printf("\n");
}

void rands(float* arr, int l) {
	int i;
	srand(time(NULL));
	for (i = 0; i < l; i++) {
		arr[i] = pow((float)(-1.0), (float)rand()) * ((rand() % 1000) + ((rand() % 1000) / (float)1000));
	}
}

int main() {
	float a[n];
	float b[n];
	float temp;
	int i, j, k, m, f = 0;
	rands(a, n);
	cout(a, n);
	for (k = 0; k < n; k++) b[k] = a[k];
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (a[i] < a[j]) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
				assig += 3;
			}
			compare++;
		}
	}
	cout(a, n);
	qsort(b, n, sizeof(float), comp);
	for (m = 0; m < n; m++) {
		if (a[m] != b[m]) f = 1;
	}
	if (f == 0) printf("Sort is correct\n\n");
	printf("Quantity of elements: %d\n", n);
	printf("Quantity of compares and assignments: %d\n", compare + assig);
	printf("%d;%d", n, compare + assig);

}