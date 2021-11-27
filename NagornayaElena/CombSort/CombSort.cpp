#include <iostream> #include <stdio.h> #include <math.h>

int main()
{
	int i;
	const int n = 30;
	float A[n];
	srand(777);
	for (i = 0; i < n; i++) {
		                    A[i] = rand() % 256;
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
	return 0;
}
