#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define uchar unsigned char
#define ushort unsigned short
#define ufloat unsigned float

int c=0;		//кол-во сравнений


void radixPass(short Offset, int N, double* sourse, double* dest, long* count)
{
	c++;
	double* sp;
	int s = 0, c, i;
	long*cp = count;
	uchar* bp;

	for (i = 2048; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}

long* createCounters(double* data, int N)
{
	uchar* bp = (uchar*)data;                                
	uchar* dataEnd = (uchar*)(data + N);                   

	ushort i;

	long* counters = malloc(2048 * sizeof(double) * sizeof(int)); 
	for (i = 0; i < 2048 * sizeof(double); i++)
	{
		counters[i] = 0;
	}

	while (bp != dataEnd)                                    
	{
		for (i = 0; i < sizeof(double); i++)                   
		{
			counters[2048 * i + *(bp++)]++;
		}
	}

	return counters;
}

void radixSort(double* in, double* out, int N)
{
	int* count;
	ushort i;
	int j;

	int* counters = createCounters(in, N);

	for (i = 0; i < sizeof(double); i++)
	{
		count = counters + 2048 * i;
		radixPass(i, N, in, out, count);

		for (j = 0; j < N; j++)
		{
			in[j] = out[j];
		}
	}
}

void signedRadixSort(double* in, double* out, int N, double* res)
{
	int i, g=N, kneg, k;
	radixSort(in, out, N);
	for (i = 0; i < N; i++)
		if (out[i] < 0)
		{
			g = i;
			break;
		}
	kneg = N - g;
	for (i = 0, k = N - 1; i < kneg; i++, k--)
		res[i] = out[k];
	for (i = kneg; i < N; i++)
		res[i] = out[i - kneg];
}

void main()
{
	double b1;
	double a[10];
	double b[10]; 
	double r[10];
	int N = 10;

	printf("please enter the numbers(double) in 10-size array\n It will be sorted by <Radix> type\n");

	int i = 0;
	for (i; i < N; i++)
	{
		scanf_s("%lf",&b1);
		a[i] = b1;
		b[i] = b1;
	}

	signedRadixSort(&a, &b, N,r);

	printf("\n\n\n");

	i = 0;
	for (i; i < N; i++)
	{
		printf_s(" %lf\n", r[i]);
	}
	printf_s("\n	%d\n ", c);			//кол-во сравнений
}