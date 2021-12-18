#include <iostream> #include <stdio.h> #include <math.h>

int main()
{
	int i,j;
	const int n = 10;
	float A[n], B[n];
	srand(800);
	for (i = 0; i < n; i++) {
		                    A[i] = rand()%256;
							B[i] = A[i];
							printf("%.1f  ", A[i]);
                             }
	for (i = 1; i < n; i++)  
		for (j = i; (j > 0) && (A[j - 1] > A[j]); j--) {
			                                           float tmp = A[j - 1];
			                                           A[j - 1] = A[j];
			                                           A[j] = tmp;
		                                               }
	printf("\n");
	for (i = 0; i < n; i++) { printf("%.1f  ", A[i]); }
	for (i=0; i<(n-1); i++) 
		for (j=n-2; j>(i-1);j--)
			if (B[j] > B[j + 1]) {
				                 float tmp = B[j];
								 B[j] = B[j + 1];
								 B[j + 1] = tmp;
								 }
	int k = 0;
	printf("\n");
	for (i = 0; i < n; i++) { 
		                     if (A[i] == B[i]) { k = k + 1; };
	                       	 printf("%.1f  ", B[i]); 
	                         }
	printf("\n");
	if (k == n) { printf("Correct"); }
	else {printf("No correct"); }

	return 0;
}
