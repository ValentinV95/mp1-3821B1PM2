#include <iostream> #include <stdio.h> #include <math.h>

int main()
{
	int i,j;
	const int n = 10;
	float A[n];
	srand(777);
	for (i = 0; i < n; i++) {
		                    A[i] = rand()%256;
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
	return 0;
}
