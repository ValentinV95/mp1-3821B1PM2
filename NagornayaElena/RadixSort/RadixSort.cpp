#include <iostream> #include <stdio.h> #include <math.h> #include <stdlib.h> #include <stdafx.h>

void main()
{
	int i, j;
	int c;
	const int n = 50, m = 1000;
	float A[n], B[n];
	int count[m];

	srand(800);

	for (i = 0; i < n; i++) {
		                     A[i] = rand() % 1000; 
							 B[i] == A[i];
	                         printf("%.0f  ", A[i]);
	                        }

	for (i = 0; i < m; i++) 
	                      {
		                   int k = 0;
		                   for (j = 0; j < n; j++)if (A[j] == i) k++;
		                   count[i] = k;
	                       }
	
	printf("\n");
	float dest[m];
	j = 0;
	int k;
	for (i = 0; i < m; i++) 
	    {
		for (k = 0; k < count[i]; k++) {
		                            	dest[j++] = i;
		                               }
	    }

	for (i = 0; i < n; i++) { 
		                     A[i]=dest[i];
		                     printf("%.0f  ", A[i]); 
	                        }
	for (i = 0; i < (n - 1); i++)
		for (j = n - 2; j > (i - 1); j--)
			if (B[j] > B[j + 1]) {
				                 float tmp = B[j];
				                 B[j] = B[j + 1];
				                 B[j + 1] = tmp;
			                     }
	int k = 0;
	printf("\n");
	for (i = 0; i < n; i++) {
		                    if (A[i] == B[i]) { k = k + 1; };
		                    printf("%.0f  ", B[i]);
	                        }
	printf("\n");
	if (k == n) { printf("Correct"); }
	   else { printf("No correct"); }
}