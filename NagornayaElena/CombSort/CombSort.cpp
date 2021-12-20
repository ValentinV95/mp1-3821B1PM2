#include <iostream> 
#include <stdio.h> 
#include <math.h>

int main()
{
	int i,j, k = 0;
	const int n = 30;
	float A[n], B[n], tmp;
	double factor = 1.2473309;
	int step = n - 1;
	srand(1000);
	for (i = 0; i < n; i++) {
		                    A[i] = -100+rand() % 1000;
							B[i] = A[i];
		                    printf("%.0f  ", A[i]);
	                        }

	while (step >= 1) {
		              for (i = 0; i + step < n; i++) {
						                             if (A[i] > A[i + step]) {
														                      tmp = A[i];
																			  A[i] = A[i + step];
																			  A[i + step] = tmp;
													                          }
					                                 }	
					  step /= factor;
	                   }
	printf("\n");
	for (i = 0; i < n; i++) { printf("%.0f  ", A[i]); }

	for (i = 0; i < (n - 1); i++)
		for (j = n - 2; j > (i - 1); j--)
			if (B[j] > B[j + 1]) {
				tmp = B[j];
				B[j] = B[j + 1];
				B[j + 1] = tmp;
			}
	printf("\n");
	for (i = 0; i < n; i++) {
		if (A[i] == B[i]) { k = k + 1; };
		printf("%.0f  ", B[i]);
	}
	printf("\n");
	if (k == n) { printf("Correct"); }
	else { printf("No correct"); }
	return 0;
}
