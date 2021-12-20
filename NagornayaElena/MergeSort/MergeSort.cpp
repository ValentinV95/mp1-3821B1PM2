#include <iostream> 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>

void merge (float A[], int p, int q, int r)
{
	const int n1 = q - p + 1;
	const int n2 = r - q;
	int i, j, k;
	float L[1000], M[1000];
	for (i = 0; i < n1; i++) L[i] = A[p + i];
	for (j = 0; j < n2; j++) M[j] = A[q + 1 + j];
	i = 0; j = 0; k = p;
	while (i < n1 && j < n2)
	{
		if (L[i] <= M[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = M[j];
			j++;
		}
		k++;
	}
	while (i < n1) 
	{
			A[k] = L[i];
			i++; k++;
	}
	while (j < n2)
	{
		A[k] = M[j];
		j++; k++;
	}
}

void mergesort(float A[], int l, int r)
{   
	int m;
	if (l < r)
	{
		m = l + (r - l) / 2;
		mergesort(A, l, m);
		mergesort(A, m + 1, r);
		merge(A, l, m, r);
	}
}

void main()
{
	srand(1000);
	const int n = 30;
	int i, j, k=0;
	float A[n],B[n],tmp;
	for (i = 0; i < n; i++) 
	{ 
		A[i] = -100 + rand() % 1000;
		B[i] = A[i];
		printf("%.0f  ", A[i]);
	}

	mergesort(A, 0, n - 1);
	printf("\n");

	for (i = 0; i < n; i++)
	{
		printf("%.0f  ", A[i]);
	}
	printf("\n");
	for (i = 0; i < n - 1; i++)
		for (j = n - 2; j > (i - 1); j--)
			if (B[j] > B[j + 1]) 
			{
				tmp = B[j];
				B[j] = B[j + 1];
				B[j + 1] = tmp;
			}
	for (i = 0; i < n; i++) 
	{
		if (A[i] == B[i]) { k = k + 1; };
		printf("%.0f  ", B[i]);
	}
	printf("\n ");
	if (k == n) { printf("Correct"); }
	   else { printf("No correct"); }
}