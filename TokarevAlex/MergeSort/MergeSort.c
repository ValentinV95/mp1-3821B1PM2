#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

int cnt = 0;

void merge(float arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	float L[N/2+1], R[N/2+1];

	for (i = 0; i < n1; i++) {
		cnt++;
		L[i] = arr[l + i];
		cnt++;
	}
	for (j = 0; j < n2; j++) {
		cnt++;
	    R[j] = arr[m + 1 + j];
		cnt++;
	}
	i = 0; 
	j = 0; 
	k = l;
	while (i < n1 && j < n2) {
		cnt+=2;
		if (L[i] <= R[j]) {
			cnt++;
			arr[k] = L[i];
			cnt++;
			i++;
		}
		else {
			arr[k] = R[j];
			cnt++;
			j++;
		}
		k++;
	}

	while (i < n1) {
		cnt++;
		arr[k] = L[i];
		cnt++;
		i++;
		k++;
	}

	while (j < n2) {
		cnt++;
		arr[k] = R[j];
		cnt++;
		j++;
		k++;
	}
	
}

void MergeSort(float arr[], int l, int r)
{
	if (l < r) {

		cnt++;
		int m = l + (r - l) / 2;

		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void printArray(float arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%.3f ", arr[i]);

}

int main()
{   
	float arr[N];
	int n = N, i=0;

	srand(time(0));

	for (i >= 0; i < N; i++) 
	{
		arr[i] = rand() % 1000 / 100 + (rand() % 1000) / 1000.0;
	}
	printf("Original array: ");
	printArray(arr, n);

	MergeSort(arr, 0, n - 1);

	printf("\nSorted array:");
	printArray(arr, n);

	printf("\nComp and Mov: %i\n", cnt);

	return 0;
}
