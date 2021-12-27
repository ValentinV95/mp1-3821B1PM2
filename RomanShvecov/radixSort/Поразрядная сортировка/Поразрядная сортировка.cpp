#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "math.h"

#define uchar unsigned char
#define N 5

void signedRadixLastSort(float* in, float* out)
{
	int i = 0, j = 0, neg = 0;   //neg - отриц. числа

	for (i = 0; i < N; i++)
	{
		if (in[i] < 0)
		{
			neg += 1;
		}
	}

	for (i = 0, j = neg; i < (N - neg); i++, j++)
	{
		in[j] = out[i];
	}
	for (i = N - 1, j = 0; j <= neg - 1; i--, j++)
	{
		in[j] = out[i];
	}
}

void radixPass(short Offset, float* sourse, float* dest, int* count)
{
	float* sp;
	int s = 0, tmp, * cp = count;
     uchar* bp;

	for (int i = 256; i > 0; --i, ++cp)
	{
		tmp = *cp;
		*cp = s;
		s += tmp;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;
	for (int i = N; i > 0; --i, bp += sizeof(float), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}

int* createCounters(float* data)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);
	int i;

	int* counters = malloc(256 * sizeof(float) * sizeof(int));

	memset(counters, 0, 256 * sizeof(float) * sizeof(int));

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(float); i++)
		{
			counters[256 * i + *(bp++)]++;
		}
	}

	return counters;
}

void radixSort(float* in, float* out)
{
	int* count;
	int* counters = createCounters(in);

	for (int i = 0; i < sizeof(float); i++)
	{
		count = counters + 256 * i;
		radixPass(i, in, out, count);

		for (int j = 0; j < N; j++)
		{
			in[j] = out[j];
		}
	}

	signedRadixLastSort(in, out);
}

void main()
{
	float array[N];
	float r[N];
	srand(1000);
	for (int a = 0; a < N; a++)
	{
		array[a] = rand() % 100 +(-50) + (rand() % 100) / 1000.0;
		printf("%f ", array[a]);
	}

	radixSort(array, r);

	for (int k = 0; k < N; k++)
	{
		printf("\n%f", array[k]);
	}
}