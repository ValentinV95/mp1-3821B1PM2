#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int
#define L 500

int sravn, perest;
int* createCounters(float* data, int N)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);

	uint i;

	int* counters = (int*)malloc(256 * sizeof(uint)*sizeof(int));
	for (i = 0; i < 256 * sizeof(uint); i++)
	{
		sravn++;
		perest++;
		counters[i] = 0;
	}

	while (bp != dataEnd)
	{
		sravn++;
		for (i = 0; i < sizeof(uint); i++)
		{
			sravn++;
			perest++;
			counters[256 * i + *(bp++)]++;
		}
	}

	return counters;
}

void radixPass(short Offset, int N, uint* sourse, uint* dest, int* count)
{
	uint* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
		perest += 3;
		sravn++;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = N; i > 0; --i, bp += sizeof(uint), ++sp)
	{
		sravn++;
		perest += 3;
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}

void signedRadixSort(float* mas, float* sort_mas, int n)
{
	int* count;
	uint i;
	int t = 0;
	int* counters = createCounters(mas, n);

	for (i = 0; i < sizeof(int); i++)
	{
		sravn++;
		count = counters + 256 * i;
		radixPass(i, n, mas,sort_mas,count);
		for (int j = 0; j < n; j++)
		{
			sravn++;
			perest++;
			mas[j] = sort_mas[j];
		}
	}

	i = n - 1;
	while (mas[i] < 0)
	{
		sravn++;
		perest++;
		sort_mas[n - i - 1] = mas[i];
		t++;
		i--;
	}

	for (i = 0; i < n - t; i++)
	{
		sravn++;
		perest++;
		sort_mas[t + i] = mas[i];
	}
	free(counters);
}
void main()
{
	int i, j, k=0;
	float A[L], B[L], C[L], tmp;
	srand(time(0));
	for (i=0; i<L; i++) 
	{
		A[i] = -100 + rand() % 256;
		B[i] = A[i];
		C[i] = A[i];
		printf("%.0f ", B[i]);
	}
	printf("\n");
	signedRadixSort(A, B, L);
	for (i = 0; i < L; i++) printf("%.0f ",  B[i]);
	
	for (i = 0; i < L - 1; i++)
		for (j = L - 2; j > (i - 1); j--)
			if (C[j] > C[j + 1]) {
				tmp = C[j];
				C[j] = C[j + 1];
				C[j + 1] = tmp;
			}
	printf("\n");
	for (i = 0; i < L; i++) {
		if (C[i] == B[i]) k++;
		printf("%.0f ", C[i]);
	}
	printf("\n");
	if (k == L) { printf("Correct"); }
	else { printf("No correct"); }
	printf("\n");
	printf("%i  %i  %i", L, sravn, perest);
}