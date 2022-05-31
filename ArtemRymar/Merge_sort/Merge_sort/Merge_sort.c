#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include<math.h>
#define b 10

long assig = 0, compare = 0;

void cout(float* arr, int i) {
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
		arr[i] = pow((-1.0), (float)rand()) * ((rand() % 1000) + ((rand() % 1000) / (float)1000));
	}
}

int comp(const void* i, const void* j)
{
	float r1 = *(const float*)i;
	float r2 = *(const float*)j;
	return(r1 > r2) - (r1 < r2);

}

void merge(float* a, int l, int mid, int r) {
	int i, j, d;
	float* c = (float*)malloc((r) * sizeof(float));
	int k = l;
	for (i = l, j = mid;(i < mid) && (j < r);) {
		compare += 3;
		if (a[i] < a[j]) {
			c[k++] = a[i++];
			
			assig++;
		}
		else {
			c[k++] = a[j++];
			assig++;
		}
	}
	for (;i < mid; i++) {
		c[k++] = a[i];
		compare++;
		assig++;
	}
	for (;j < r; j++) {
		c[k++] = a[j];
		compare++;
		assig++;
	}
	for (d = l;d < r;d++) {
		a[d] = c[d];
		compare++;
		assig++;
	}
}

void mergesort(float* array, int l, int r) {
	if ((r - l) > 1) {
		compare++;
		int mid = (l + r) / 2;
		mergesort(array, l, mid);
		mergesort(array, mid, r);
		merge(array, l, mid, r);
	}
}




int main() {
	int m, r, f = 0;
	float arr[b];
	float arr2[b];
	rands(arr, b);
	for (r = 0; r < b; r++) arr2[r] = arr[r];
	cout(arr, b);
	mergesort(arr, 0, b);
	cout(arr, b);
	qsort(arr2, b, sizeof(float), comp);
	for (m = 0; m < b; m++) {
		if (arr[m] != arr2[m])  f = 1;
	}
	if (f == 0) printf("Sort is correct\n\n");
	printf("Quantity of elements: %d\n", b);
	printf("Quantity of compares and assignmentы: %d\n", compare + assig);
	printf("%d;%d", b, compare + assig);

}