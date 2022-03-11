#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define uchar unsigned char
#define ushort unsigned short
#define ufloat unsigned float
#define L 10

int comp = 0;
int swap = 0;

void signedRadixLastSort(int N, float* in, float* out)
{
	int Numneg,j, i = 0;
	float temp;
	int id = N;

	for (i >= 0; i < N; i++)
	{
		comp++;
		if (in[i] < 0)
		{
			comp++;
			id = i;
			break;
		}
	}

	Numneg = N - id;
	for (i = 0, j = N - 1; i < Numneg; i++, j--)
	{
		comp++;
		out[i] = in[j];
		swap++;
	}
	for (i = Numneg; i < N; i++) 
	{
		comp++;
		out[i] = in[i - Numneg];
		swap++;
	}
}
void radixPass(short Offset, int N, float* sourse, float* dest, int* count)
{
	float* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		comp++;
		c = *cp;
		*cp = s;
		s += c;
		swap++;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = N; i > 0; --i, bp += sizeof(float), ++sp)
	{
		comp++;
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		swap++;
	}
}

int* createCounters(float* data, int N)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);

	ushort i;

	int* counters = malloc(256 * sizeof(float) * sizeof(int));

	for (i = 0; i < 256 * sizeof(float); i++)
	{
		comp++;
		counters[i] = 0;
		swap++;
	}

	while (bp != dataEnd)
	{
		comp++;
		for (i = 0; i < sizeof(float); i++)
		{
			comp++;
			counters[256 * i + *(bp++)]++;
			swap++;
		}
	}

	return counters;
}

void radixSort(float* in, float* out, int N)
{
	int* count;
	ushort i;
	int j;

	int* counters = createCounters(in, N);

	for (i = 0; i < sizeof(float); i++)
	{
		comp++;
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);

		for (j = 0; j < N; j++)
		{
			comp++;
			in[j] = out[j];
			swap++;
		}
	}

	signedRadixLastSort(N, in, out);
}
int compare(const void* a, const void* b)
{
	float fa = *(const float*)a;
	float fb = *(const float*)b;
	return (fa > fb) - (fa < fb);
}
void PrintArr(float mas[], float N)
{

	int i;
	for (i = 0; i < N; i++)
	{
		printf_s("%.4f ", mas[i]);
	}
}
void main()
{
	float mas[L];
	float out_mas[L]; 
	float mas_dup[L];
	int i, N = L;

	srand(time(0));

		for (i = 0; i < N; i++)
		{
			mas[i] = pow(-1,i)*(rand() % 1000 / 1000 + rand() / 10000.0);
			out_mas[i] = mas[i];
			mas_dup[i] = mas[i];
		}

	printf("\nOriginal array: ");
	PrintArr(out_mas, N);

	radixSort(mas, out_mas, N);
	qsort(mas_dup, N,sizeof(float),compare );

	printf("\n  Sorted array: ");
	PrintArr(out_mas, N);

	printf("\n   qsort array: ");
	PrintArr(mas_dup, N);

	printf("\nNumber of swaps and compares: %i %i",swap, comp);
	
}