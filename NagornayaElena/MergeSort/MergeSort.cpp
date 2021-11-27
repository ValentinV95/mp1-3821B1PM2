#include <iostream> #include <stdio.h> #include <math.h> #include <stdlib.h>

void mergesort(float a[], int sec[], int l, int r)
{
	if (l < r) {
		       int q = (l + r) / 2;
			   mergesort (a, sec, l, q);
			   mergesort (a, sec, q + 1, r);
			   mergesort(a, sec, l, q, r);
	           }
}