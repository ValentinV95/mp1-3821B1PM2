#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void CreateCounters(float* data, int* counters, int N)
{
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	int i;
	memset(counters, 0, 256 * sizeof(float) * sizeof(int));

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(float); i++)
		{
			counters[256 * i + *(bp++)]++;
		}
	}
}

void RadixPass(short Offset, int N, float* source, float* dest, int* count)
{
	float* sp;
	int s = 0, c, i, * cp = count;
	unsigned char* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}
	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(float), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}

void Sign(float* in, float* out, int N)
{
	int i, k;
	k = 0;
	for (i = N - 1; i > 0 && out[i] <= 0; i--)
	{
		in[N - i - 1] = out[i];
		k++;
	}

	for (i = 0; i + k < N; i++)
	{
		in[k + i] = out[i];
	}
}
void RadixSort(float* in, float* out, int* counters, int N)
{
	int* count;
	int j;
	unsigned short i;
	CreateCounters(in, counters, N);

	for (i = 0; i < sizeof(float); i++)
	{
		count = counters + 256 * i;
		RadixPass(i, N, in, out, count);
		for (j = 0; j < N; j++)
		{
			in[j] = out[j];
		}
	}
	Sign(in, out, N);

}
int main()
{
	setlocale(LC_ALL, "Russian");
	int i, len;
	float* arr1;
	float* arr2;
	int* arr3;

	printf("Укажите длину массива: ");
	scanf_s("%d", &len);
	getchar();

	arr1 = (float*)malloc(len * sizeof(float));


	srand(887);
	for (i = 0; i < len; i++)
		arr1[i] = rand() % 1000 + rand() % 100 / 100.0;

	for (i = 0; i < len; i++)
		printf("array[%d] = %f\n", i, arr1[i]);
	printf("\n");

	arr2 = (float*)malloc(len * sizeof(float));
	arr3 = (int*)malloc(256 * sizeof(float) * sizeof(int));
	RadixSort(arr1, arr2, arr3, len);

	for (i = 0; i < len; i++)
		printf("array[%d] = %f\n", i, arr1[i]);
	printf("\n");
	return 0;
}