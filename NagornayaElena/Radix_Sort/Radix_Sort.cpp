#include <iostream> 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 

void main()
{
	int i, j, k, c=0;
	const int n = 10, m = 1000;
	float A[n], B[n], dest[m], tmp;
	int count[m];
	srand(1000);

	for (i = 0; i < n; i++)
	{
		A[i] = -100 + rand() % 1000;
		B[i] = A[i];
		printf("%.0f  ", A[i]);
	}


	for (i = -100; i < (m-100); i++)
	{
		k = 0;
		for (j = 0; j < n; j++)  if (A[j] == i) k++;
		count[c] = k;
		c++;
	}


	j = 0;
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < count[i]; k++) 
		{
			dest[j] = i-100; j++;
		}
	}

	printf("\n"); 

	for (i = 0; i < n; i++) 
	{
		A[i] = dest[i];
		printf("%.0f  ", A[i]);
	}
	for (i = 0; i < (n - 1); i++)
		for (j = n - 2; j > (i - 1); j--)
			if (B[j] > B[j + 1])
			{
				tmp = B[j];
				B[j] = B[j + 1];
				B[j + 1] = tmp;
			}
	k = 0;
	printf("\n");
	for (i = 0; i < n; i++)
	{
		if (A[i] == B[i]) { k = k + 1; };
		printf("%.0f  ", B[i]);
	}
	printf("\n");
	if (k == n) { printf("Correct"); }
	    else { printf("No correct"); }
}
