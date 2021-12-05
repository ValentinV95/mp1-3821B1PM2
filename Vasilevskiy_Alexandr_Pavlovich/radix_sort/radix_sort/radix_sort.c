#include <stdio.h>
#include <stdlib.h>

void createCounters(double* data, int* counters, int N)
{
	unsigned char *bp = (unsigned char*)data;
	unsigned char *dataEnd = (unsigned char*)(data + N);
	int i;
	memset( counters, 0, 256*sizeof(double)*sizeof(int));

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(double); i++)
		{
			counters[256*i + *(bp++)]++;
		}
	}
}

void radixPass(short Offset, int N, double* source, double* dest, int* count)
{
	double* sp;
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
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
	}
}

void sign(double* in, double* out, int N)
{
	int i,k;

	for (i = 0; i < N && out[i] >= 0; i++)
	{
	}
	k = i;
	for (i = N-1; i >= k; i--)
	{
		in[N - i - 1] = out[i];
	}
	for (i = 0; i < k; i++)
	{
		in[N - k + i] = out[i];
	}
}
void radixSort(double* in, double* out, int* counters, int N)
{
	int* count;
	int j;
	unsigned short i;
	createCounters(in, counters, N);

	for (i = 0; i < sizeof(double); i++)
	{
		count = counters + 256 * i;
		radixPass(i, N , in , out, count);
		for (j = 0; j < N; j++)
		{
			in[j] = out[j];
		}
	}
	sign(in, out, N);

}

int main()
{
	int i, len = 10, c[256 * sizeof(double)];
	double* ar1;
	double* ar3;
	int* ar2;

	ar1 = (double*)malloc(len * sizeof(double));
	ar2 = (double*)malloc(len * sizeof(double));
	ar3 = (int*)malloc(256 * sizeof(double) * sizeof(int));
	srand(666);
	for (i = 0; i < len; i++)
	{
		ar1[i] = rand() % 1000000 + rand() % 1000000 / 1000000.0;
		printf("a[%d] = %lf\n",i, ar1[i]);
	}
	radixSort(ar1, ar2, ar3, len);


	for (i = 0; i < len; i++)
	{
		printf("a[%d] = %lf\n", i, ar1[i]);
	}
	free(ar1);
	free(ar2);
	free(ar3);

	return 0;
}
