#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define uchar unsigned char
#define ushort unsigned short
#define ufloat unsigned float
#define L 10

int cnt = 0;

void signedRadixLastSort(int N, float* out, float* in)
{    
	int j,i= 0;
	float temp;
	int id = L + 1;
	for (i >= 0; i < N; i++)
	{
		cnt++;
		if (in[i] < 0)
		{
			cnt++;
			id = i;
			break;
		}
	}

	if (id < L) 
	{
		i = id;
		j = N;
		while (i < j)
		{
			cnt++;
			temp = in[i];
			in[i] = in[j - 1];
			in[j - 1] = temp;
			i++;
			j--;
			cnt++;
		}

		j = 0;
		for (i = id; i < N; i++)
		{
			out[j++] = in[i];
			cnt++;
		}

		j = 0;
		for (i = N - id; i < N; i++)
		{
			out[i] = in[j++];
			cnt++;
		}
	}
}
void radixPass(short Offset, int N, float* sourse, float* dest, int* count)
{
	float* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		cnt++;
		c = *cp;
		*cp = s;
		s += c;
		cnt++;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;
	cnt+=2;

	for (i = N; i > 0; --i, bp += sizeof(float), ++sp)
	{
		cnt++;
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		cnt ++;
	}
}

int* createCounters(float* data, int N)
{
	uchar* bp = (uchar*)data;                               
	uchar* dataEnd = (uchar*)(data + N);               

	ushort i;

	int* counters = malloc(256 * sizeof(float) * sizeof(int)); 
	cnt++;

	for (i = 0; i < 256 * sizeof(float); i++)
	{
		cnt++;
		counters[i] = 0;
		cnt++;;
	}

	while (bp != dataEnd)                                    
	{
		cnt++;
		for (i = 0; i < sizeof(float); i++)                   
		{
			cnt++;
			counters[256 * i + *(bp++)]++;
			cnt++;
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
	cnt++;

	for (i = 0; i < sizeof(float); i++)
	{
		cnt++;
		count = counters + 256 * i;
		cnt++;
		radixPass(i, N, in, out, count);

		for (j = 0; j < N; j++)
		{
			cnt++;
			in[j] = out[j];
			cnt++;
		}
	}
	
	signedRadixLastSort(N, out, in);
}
void PrintArr(float mas[], float N) 
{
	
	int i;
	for (i = 0; i < N; i++)
	{
		printf_s("%.3f ", mas[i]);
	}

}
void main()
{
	float mas[L];
	float out_mas[L];
	int N = L;
    int i = 0;

	srand(time(0));

	for (i = 0; i < L; i++) 
	{
		mas[i] = rand()%1000 / 100 + rand()/100.0;
		out_mas[i] = mas[i];
	}

	printf("Original array: ");
	PrintArr(mas, N);
	
	radixSort(mas, out_mas, N);

	printf("\nSorted array: ");
	PrintArr(mas, N);

	printf("\nOperations: %i", cnt);
}