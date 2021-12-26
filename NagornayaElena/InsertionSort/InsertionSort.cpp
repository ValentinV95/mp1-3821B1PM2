#include <stdlib.h>
#include <iostream> 
#include <stdio.h> 
#include <math.h>

void main()
{
	int i,j,k = 0, sravn=0, perest=0;
	const int n = 50;
	float A[n], B[n], tmp;
	srand(1000);
	for (i = 0; i < n; i++) {
		                    A[i] = -100+ rand()%1000;
							B[i] = A[i];
							printf("%.0f  ", A[i]);
                             }
	for (i = 1; i < n; i++)
	{
		sravn++;
		for (j = i; (j > 0) && (A[j - 1] > A[j]); j--)
		{
			perest++;
			tmp = A[j - 1];
			A[j - 1] = A[j];
			A[j] = tmp;
		}
	}
	printf("\n");
	for (i = 0; i < n; i++) { printf("%.0f  ", A[i]); }
	printf("\n");
	for (i = 0; i < n-1; i++) 
		for (j=n-2; j>(i-1);j--)
			if (B[j] > B[j + 1]) {
				                 tmp = B[j];
								 B[j] = B[j + 1];
								 B[j + 1] = tmp;
								 }
	for (i = 0; i < n; i++) { 
		                     if (A[i] == B[i]) { k = k + 1; };
	                       	 printf("%.0f  ", B[i]); 
	                         }
	printf("\n ");
	if (k == n) { printf("Correct"); }
	else {printf("No correct"); }
	printf("\n");
	printf("%i  %i  %i", n, sravn, perest);
}
