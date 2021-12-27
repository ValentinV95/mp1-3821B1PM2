#include <stdio.h>
#include <stdlib.h>

void Merge(float* A, float* L, int leftCount, float* R, int rightCount) {
	int i, j, k;


	i = 0; j = 0; k = 0;

	while (i < leftCount && j < rightCount) {
		if (L[i] < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while (i < leftCount) A[k++] = L[i++];
	while (j < rightCount) A[k++] = R[j++];
}


void MergeSort(float* A, int n) {
	int mid, i;
	float* L, * R;
	if (n < 2) return;

	mid = n / 2; // нахождение среднего 

	// создание левого и правого подмассива 
	// средние элементы (от индекса 0 до середины - 1) должны быть частью левого подмассива
	// и (n-средние) элементы (от середины до n-1) будут частью правого подмассива
	L = (float*)malloc(mid * sizeof(float));
	R = (float*)malloc((n - mid) * sizeof(float));

	for (i = 0; i < mid; i++) L[i] = A[i];
	for (i = mid; i < n; i++) R[i - mid] = A[i];

	MergeSort(L, mid); // сортировка левого подмассива
	MergeSort(R, n - mid); //сортировка правого подмассива
	Merge(A, L, mid, R, n - mid); // объединение в отсортированном списке
	free(L);
	free(R);
}

void main() {


	float A[] = { 6.2432, 6.2431, -9.2312, -9.2313, 0.1237 };
	int i;
	float numberOfElements;


	numberOfElements = sizeof(A) / sizeof(A[0]);


	MergeSort(A, numberOfElements);


	for (i = 0; i < numberOfElements; i++) printf("\n%f ", A[i]);
}