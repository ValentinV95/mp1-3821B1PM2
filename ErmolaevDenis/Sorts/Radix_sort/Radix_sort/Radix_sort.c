#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define uchar unsigned char
#define N 100

int cmp(const void* a, const void* b)
{
	const double* ad, * bd;

	ad = (const double*)a;
	bd = (const double*)b;

	if (*ad < *bd)
	{
		return -1;
	}
	else if (*ad > *bd)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

double DRand(double fMin, double fMax)
{
	double f = (double)(rand()) / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void randarr(double arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		arr[i] = DRand(-1000, 1000);
}

void printarr(double arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%lf | ", arr[i]);
	printf("\n\n\n");
}

void createCounters(double data[], long* counters, long n, int* assignments)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + n);
	unsigned short i;

	memset(counters, 0, 256 * sizeof(double) * sizeof(long));
	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(double); i++)
		{
			counters[256 * i + *(bp++)]++;
			*assignments = *assignments + 1;
		}
	}
}

void radixPass(short Offset, long n, double* source, double* dest, long* count, int* assignments)
{
	double* sp;
	long s, c, i, * cp;
	uchar* bp;
	s = 0;
	cp = count;
	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}
	bp = (uchar*)source + Offset;
	sp = source;
	for (i = n; i > 0; --i, ++sp, bp += sizeof(double))
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		*assignments = *assignments + 3;
	}
}

void signedRadixLastPass(short Offset, long n, double* source, double* dest, long* count, int* assignments)
{
	double tmp;
	double* sp;
	long s, c, i, * cp, numNeg = 0;
	uchar* bp;

	for (i = 128; i < 256; i++) numNeg += count[i];
	s = numNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}
	s = count[255] = 0;
	cp = count + 254;
	for (i = 254; i >= 128; --i, --cp)
	{
		*cp += s;
		s = *cp;
	}
	bp = (uchar*)source + Offset;
	sp = source;
	for (i = n; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		if (*bp < 128) dest[(*cp)++] = *sp;
		else dest[--(*cp)] = *sp;
		*assignments = *assignments + 2;
	}
	//for (int i = 0; i < n; i++)
	//{
	//	tmp = source[i];
	//	source[i] = dest[i];
	//	dest[i] = tmp;
	//}
}

void signedRadixSort(double* in, double* out, long* counters, long n, int* assignments)
{
	long* count;
	unsigned short i;
	createCounters(in, counters, n, assignments);

	for (i = 0; i < (sizeof(double) - 1); i++)
	{
		count = counters + 256 * i;
		radixPass(i, n, in, out, count, assignments);
		for (long j = 0; j < n; j++)
		{
			in[j] = out[j];
			*assignments = *assignments + 1;
		}
	}
	count = counters + 256 * i;
	signedRadixLastPass(i, n, in, out, count, assignments);
}

double arr[N], c[N];

int main()
{
	int a = 0;
	int* assignments;
	long counters[256 * sizeof(double)];
	assignments = &a;
	randarr(arr, N);
	printarr(arr, N);
	signedRadixSort(arr, c, counters, N, assignments);
	//qsort(arr, N, sizeof(double), cmp);
	printarr(c, N);
	printf(" Assignments=%i\n\n", a);
	return 0;
}