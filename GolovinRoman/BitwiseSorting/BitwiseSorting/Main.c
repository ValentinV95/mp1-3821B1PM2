#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int

int assigning = 0, compare = 0;

float* createMas(int length)
{
	int i = 0;
	float* m = (float*)malloc(length*sizeof(float));

	for (i; i < length; i++)
	{
		m[i] = (rand() % 1001 + (rand() % 1000) / 1000.0f) * pow(-1.0, (rand() % 2));
	}

	//for (i = 0; i < length; i++)
	//{
	//	printf_s("%lf\n", m[i]);
	//}

	return m;
}

int compareFunction(const void* a, const void* b)
{
	float fa = *(const float*)a;
	float fb = *(const float*)b;
	return (fa > fb) - (fa < fb);
}

int isSortCorrect(float* orig_mas, float* sort_mas, int length)
{
	int i = 0;

	qsort(orig_mas, length, sizeof(float), compareFunction);

	for (i = 0; i < length; i++)
	{
		if (sort_mas[i] != orig_mas[i])
		{
			return 0;
		}
	}
	return 1;
}

int* createCounters(float* data,int N)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);

	ushort i;

	int* counters = (int*)malloc(256*sizeof(uint)*sizeof(int));
	for (i = 0; i < 256 * sizeof(uint); i++)
	{
		compare++;
		assigning++;
		counters[i] = 0;
	}

	while (bp != dataEnd)
	{
		compare++;
		for (i = 0; i < sizeof(uint); i++)
		{
			compare++;
			assigning++;
			counters[256 * i + *(bp++)]++;
		}
	}

	return counters;
}

void radixPass(short Offset,int N,uint* sourse,uint* dest,int* count)
{
	uint* sp;
	int s = 0,c,i,*cp=count;
	uchar* bp;

	for (i=256;i>0;--i,++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
		assigning+=3;
		compare++;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = N;i>0;--i,bp+= sizeof(uint),++sp)
	{
		compare++;
		assigning++;
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}

void signedRadixSort(float* data,float* sorted_data,int N)
{
	int* count;
	ushort i;
	int numNeg = 0;
	int* counters = createCounters(data,N);

	for (i=0;i<sizeof(int);i++)
	{
		compare++;
		count = counters + 256 * i;
		radixPass(i,N,data,sorted_data,count);
		for (int j = 0; j < N; j++)
		{
			compare++;
			assigning++;
			data[j] = sorted_data[j];
		}
	}
	
	i = N-1;
	while(data[i]<0)
	{
		compare++;
		assigning++;
		sorted_data[N-i-1] = data[i];
		numNeg++;
		i--;
	}

	for (i=0; i < N - numNeg; i++)
	{
		compare++;
		assigning++;
		sorted_data[numNeg+i] = data[i];
	}
}

void main()
{
	int length = 100;
	int i;
	float* mas = createMas(length);
	float* mas_copy1 = (float*)malloc(sizeof(float) * length);
	float* mas_copy2 = (float*)malloc(sizeof(float) * length);

	while (length<4001)
	{
		for (i = 0; i < length; i++)
		{
			mas_copy1[i] = mas[i];
			mas_copy2[i] = mas[i];
		}

		signedRadixSort(mas_copy2, mas_copy1, length);

		if (isSortCorrect(mas, mas_copy1, length))
		{
			float tmp = (assigning + compare) / (float)(4 * (length + 256));
			printf("%d;%d;%lf\n", length, assigning+compare,tmp);
		}
		else
		{
			printf("The implementation of sorting is incorrect");
			break;
		}

		length += 5;

		compare = 0;
		assigning = 0;

		free(mas);
		free(mas_copy1);
		free(mas_copy2);

		mas_copy1 = (float*)malloc(sizeof(float) * length);
		mas_copy2 = (float*)malloc(sizeof(float) * length);
		mas = createMas(length);
	}

	free(mas);
	free(mas_copy1);
	free(mas_copy2);
}



