#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define uchar unsigned char
#define ushort unsigned short
#define udouble unsigned double

void radixPass(short Offset, int N, double* sourse, double* dest, int* count)
{
	double* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp)
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

int* createCounters(double* data, int N)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);

	ushort i;

	int* counters = malloc(256 * sizeof(double) * sizeof(int));
	for (i = 0; i < 256 * sizeof(double); i++)
	{
		counters[i] = 0;
	}

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(double); i++)
		{
			counters[256 * i + *(bp++)]++;
		}
	}

	return counters;
}


void obmen(double* out, int N, double* mas)
{
	int numneg = N, kneg, j, i;
	for (i = 0; i < N; i++)
	{
		if (out[i] < 0)
		{
			numneg = i;
			break;
		}
	}
	kneg = N - numneg;
	for (i = 0, j = N - 1; i < kneg; i++, j--)
	{
		mas[i] = out[j];
	}
	for (i = kneg; i < N; i++)
	{
		mas[i] = out[i - kneg];
	}
}


void radixSort(double* in, double* out, int N)
{
	int* count;
	ushort i;
	int j;

	double* counters = createCounters(in, N);

	for (i = 0; i < sizeof(double); i++)
	{
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);

		for (j = 0; j < N; j++)
		{
			in[j] = out[j];
		}
	}
	obmen(in, N, out);
}

void main()
{
	double mas[] = { -5.74, 4.33, 7.31, -4.32, 3.05, 2.69, -3.06, 1.34, 7.83, 9.04 };
	double out_mas[] = { -5.74, 4.33, 7.31, -4.32, 3.05, 2.69, -3.06, 1.34, 7.83, 9.04 };
	int N = 10;

	int i = 0;
	for (i; i < N; i++)
	{
		printf_s("%lf ", mas[i]);
	}

	radixSort(out_mas, mas, N);

	printf("\n");

	i = 0;
	for (i; i < N; i++)
	{
		printf_s("%lf ", mas[i]);
	}

}
