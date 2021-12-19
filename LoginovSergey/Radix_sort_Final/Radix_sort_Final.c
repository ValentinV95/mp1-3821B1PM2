#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define L 40000
#define ulonglong unsigned long long
#define uchar unsigned char
#define ushort unsigned short

int assigning = 0, compare = 0;

void massiv(double* m, double* cm1, double* cm2)
{
	int i;

	for (i = 0; i < L; i++)
	{
		m[i] = (rand() % 1001 + (rand() % 1000) / 1000.0) * pow(-1.0, (rand() % 2));
		if (m[i] == -0.0)
		{
			m[i] = 0.0;
		}
		cm1[i] = m[i];
		cm2[i] = m[i];
	}
}

int cmp(const void* z, const void* p)
{
	double rch = *(const double*)z;
	double rzl = *(const double*)p;
	return (rch > rzl) - (rch < rzl);
}

int* createCounters(double* data, int N)
{
	uchar* zx = (uchar*)data;
	uchar* finaldata = (uchar*)(data + N);

	ushort i;

	int* counters = (int*)malloc(256 * sizeof(ulonglong) * sizeof(int));
	for (i = 0; i < 256 * sizeof(ulonglong); i++)
	{
		compare++;
		assigning++;
		counters[i] = 0;
	}

	while (zx != finaldata)
	{
		compare++;
		for (i = 0; i < sizeof(ulonglong); i++)
		{
			compare++;
			assigning++;
			counters[256 * i + *(zx++)]++;
		}
	}

	return counters;
}

void radixPass(short Offset, int N, ulonglong* sourse, ulonglong* dest, int* count)
{
	ulonglong* sp;
	int s = 0, c, i, * k = count;
	uchar* zx;

	for (i = 256; i > 0; --i, ++k)
	{
		c = *k;
		*k = s;
		s += c;
		assigning += 3;
		compare++;
	}

	zx = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = N; i > 0; --i, zx += sizeof(ulonglong), ++sp)
	{
		compare++;
		assigning += 4;
		k = count + *zx;
		dest[*k] = *sp;
		(*k)++;
	}
}

void signedRadixSort(double* data, double* sorted_data, int N)
{
	int* count;
	ushort i;
	int numNeg = 0;
	int* counters = createCounters(data, N);

	for (i = 0; i < sizeof(ulonglong); i++)
	{
		compare++;
		count = counters + 256 * i;
		radixPass(i, N, data, sorted_data, count);
		for (int j = 0; j < N; j++)
		{
			compare++;
			assigning++;
			data[j] = sorted_data[j];
		}
	}
}

void main()
{
	int i, id = 1, numNeg = 0;
	double mas[L], mas_copy1[L], mas_copy2[L];

	srand(5737316473);

	feelMas(&mas, &mas_copy1, &mas_copy2);

	signedRadixSort(mas_copy2, mas_copy1, L);

	i = L - 1;
	while (mas_copy2[i] < 0)
	{
		mas_copy1[L - i - 1] = mas_copy2[i];
		numNeg++;
		i--;
		compare++;
		assigning++;
	}

	for (i = 0; i < L - numNeg; i++)
	{
		mas_copy1[numNeg + i] = mas_copy2[i];
		compare++;
		assigning++;
	}

	qsort(mas, L, sizeof(double), cmp);

	for (i = 0; i < L; i++)
	{
		if (mas[i] != mas_copy1[i])
		{
			id = 0;
			break;
		}
	}

	if (id == 1)
	{
		printf("Vse verno\n");
		printf("Dlinna - %d\nPrisvoeni - %d\nSravneni - %d\nPrisvoenia/slojnost - %lf\nSravnenia/slojnost - %lf\n", L, assigning, compare, assigning / (float)(8 * (L + 256)), compare / (float)(8 * (L + 256)));
	}
	else
	{
		printf("Sortirovka ne rabotaet\n");
	}
}


