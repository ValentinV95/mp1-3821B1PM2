#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#define uchar unsigned char
#define ushort unsigned short
#define SIZE 5

int srav = 0, per = 0;

int* createCounters(double* data, int* counters, long N)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);
	ushort i;
	memset(counters, 0, 256 * sizeof(double) * sizeof(int));
	while (bp != dataEnd)
	{
		srav++;
		for (i = 0; i < sizeof(double); i++)
		{
			counters[256 * i + *(bp++)]++;
			srav++;
			per++;
		}
	}
	return counters;
}

void radixPass(short Offset, double* sourse, double* dest, int* count, long N)
{
	double* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;
	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
		srav++;
	}
	bp = (uchar*)sourse + Offset;
	sp = sourse;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		srav++;
		per++;
	}
}

void signedRadixLastPass(double* source, double* dest, long N)
{
	int numNeg = 0;
	int i;
	for (i = 0; i < N; i++)
	{
		srav++;
		if (source[i] < 0)
		{
			numNeg++;
			srav++;
		}
	}
	for (i = 0; i < numNeg; i++)
	{
		dest[i] = source[N - 1 - i];
		srav++;
		per++;
	}
	for (i = 0; i < N - numNeg; i++)
	{
		dest[i + numNeg] = source[i];
		srav++;
		per++;
	}
	for (i = 0; i < N; i++)
	{
		source[i] = dest[i];
		srav++;
		per++;
	}
}

void radixSort(double* in, double* out, int* counterss, long N)
{
	int* count;
	int j;
	int* counters = createCounters(in, counterss, N);
	for (ushort i = 0; i < sizeof(double); i++)
	{
		srav++;
		count = counters + 256 * i;
		radixPass(i, in, out, count, N);

		for (j = 0; j < N; j++)
		{
			in[j] = out[j];
			srav++;
			per++;
		}
	}
	signedRadixLastPass(in, out, N);
}

void rands(double array[], int b)
{
	int i;
	srand(time(0));
	for (i = 0; i < b; i++)
	{
		///array[i] = rand() % 1000000 + (rand() % 1000000) / 1000000.0;
		array[i] = pow((double)(-1.0), (double)rand()) * ((rand() % 1000) + ((rand() % 1000) / (double)1000));
	}
}

void sont(double array[], int i)
{
	int j;
	for (j = 0; j < i; j++)
	{
		printf("%lf ", array[j]);
	}
	printf("\n\n");
}

int main()
{
	double mas[SIZE];
	printf("Unsoretd array\n");
	rands(mas, SIZE);
	sont(mas, SIZE);
	double* array = malloc(SIZE * sizeof(double));
	for (int i = 0; i < SIZE; i++)
	{
		array[i] = 0;
	}
	int* counter = malloc(256 * sizeof(double) * sizeof(int));
	radixSort(mas, array, counter, SIZE);
	printf("Sorted array\n");
	sont(mas, SIZE);
	printf("Perestanovok %d\nSravneniy %d\n", per, srav);
}