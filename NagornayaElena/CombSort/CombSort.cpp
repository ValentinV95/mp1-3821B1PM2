#include <iostream> #include <stdio.h> #include <math.h>

int main()
{
	int i;
	const int n = 30;
	float A[n], B[n];
	srand(777);
	for (i = 0; i < n; i++) {
		                    A[i] = rand() % 256;
							B[i] = A[i];
		                    printf("%.1f  ", A[i]);
	                        }
	double factor = 1.2473309;
	int step = n - 1;
	while (step >= 1) {
		              for (i = 0; i + step < n; i++) {
						                             if (A[i] > A[i + step]) {
														                      float tmp = A[i];
																			  A[i] = A[i + step];
																			  A[i + step] = tmp;
													                          }
					                                 }	
					  step /= factor;
	                   }
	printf("\n");
	for (i = 0; i < n; i++) { printf("%.1f  ", A[i]); }

	printf("\n");
	for (i = 0; i < n; i++) { printf("%.1f  ", A[i]); }
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
		printf("%.1f  ", B[i]);
	}
	printf("\n");
	if (k == n) { printf("Correct"); }
	else { printf("No correct"); }
	return 0;
}
