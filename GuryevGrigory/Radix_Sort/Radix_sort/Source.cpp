#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<time.h>
#include<math.h>

int compare = 0;
int assign = 0;

int* CreateCounter(float* data, int n)
{
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + n);

	unsigned short i;

	int* counter = (int*)malloc(256 * sizeof(unsigned int) * sizeof(int));
	
	for (i = 0; i < 256 * sizeof(unsigned int); i++)
	{
		compare++;
		assign++;
		counter[i] = 0;
	}
	while (bp != dataEnd)
	{
		compare++;
		for (i = 0; i < sizeof(unsigned int); i++)
		{
			compare++;
			assign++;
			counter[256 * i + *(bp++)]++;
		}
	}

	return counter;
}
void radixPass(short Offs, int n, float* Array, float* dest, int* count)
{
	float* sp;
	int s = 0;
	int c;
	int i;
	int* cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s = s + c;
		assign += 3;
		compare++;
	}
	bp = (unsigned char*)Array + Offs;
	sp = Array;
	for (i = n; i > 0; --i, bp += sizeof(float), ++sp)
	{
		compare++;
		assign++;
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}
void radixSort(float *Array,float* sorted_arr,int n)
{
	int* count;
	unsigned short i;
	int num = 0;
	int* counter = CreateCounter(Array, n);
	for (i = 0; i < sizeof(int); i++)
	{
		compare++;
		count = counter + 256 * i;
		radixPass(i, n,Array, sorted_arr, count);
		for (int j = 0; j < n; j++)
		{
			compare++;
			assign++;
			Array[j] = sorted_arr[j];
		}

	}
	i = n - 1;
	while (Array[i] < 0)
	{
		compare++;
		assign++;
		sorted_arr[n - i - 1] = Array[i];
		num++;
		i--;
	}
	for (i = 0; i < n - num; i++)
	{
		compare++;
		assign++;
		sorted_arr[num + i] = Array[i];
	}
}
void signedsort(float* MainArr, float* Out, int sz)
{
	int i = sz-1;
	int j = 0;
	while (MainArr[i] < 0)
	{
		Out[j] = MainArr[i];
		i--;
		j++;
	}
	i = 0;
	while (MainArr[i] >= 0)
	{
		Out[j] = MainArr[i];
		i++;
		j++;
	}
	
}
int main()
{
	int lenght = 100;
	float* arr = (float*)malloc(lenght * sizeof(float));
	float* arr2;
	float* arr3;
	for (int i = 0; i < lenght; i++)
	{
		arr[i] = (rand() % 1001 + (rand() % 1000) / 1000.0f) * pow(-1.0, (rand() % 2));
	}
	arr2 = (float*)malloc(lenght * sizeof(float));
	arr3 = (float*)malloc(lenght * sizeof(float));
	radixSort(arr, arr2, lenght);
	signedsort(arr, arr3, lenght);
	for (int i = 0; i < lenght; i++)
	{
		printf("%f,\n", arr4[i]);
	}
}
