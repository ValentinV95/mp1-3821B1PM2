#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "locale.h"
#include "math.h"

#define N 10
int global_p = 0;

void signedRadixLastSort(float* in, float* out)
{
	int i = 0, j = 0, negative = 0;

	for (i = 0; i < N; i++)
	{
		if (in[i] < 0)
		{
			negative += 1;
		}
	}

	for (i = 0, j = negative; i < (N - negative); i++, j++)
	{
		in[j] = out[i];
		global_p++;
	}
	for (i = N - 1, j = 0; j <= negative - 1; i--, j++)
	{
		in[j] = out[i];
		global_p++;
	}
}

void radixPass(short Offset, float* sourse, float* dest, int* count)
{
	float* sp;
	int s = 0, tmp, * cp = count;
	unsigned char* bp;

	for (int i = 256; i > 0; --i, ++cp)
	{
		tmp = *cp;
		*cp = s;
		s += tmp;
	}

	bp = (unsigned char*)sourse + Offset;
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
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
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
			global_p++;
		}
	}

	signedRadixLastSort(in, out, count);
}

void main()
{
	float array[N];
	float result[N];
	setlocale(LC_ALL, "Russian");
	srand(100000);
	for (int a = 0; a < N; a++)
	{
		array[a] = rand() % 2001 + (-1000) + (rand() % 1000) / 10000.0;
		printf("%f ", array[a]);
	}
	
	radixSort(array, result);

	for (int k = 0; k < N; k++)
	{
		printf("\n%f", array[k]);
	}
	printf("\nЧисло перестановок = %d", global_p);
}