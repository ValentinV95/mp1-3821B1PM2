#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define uchar unsigned char
#define ushort unsigned short
#define udouble unsigned double
#define ulonglong unsigned long long
#define W 1364

int sr = 0;   //сравнений
int z = 0;   //перестановок


//сортировка вставками
void insertion_sort(double mas[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j > 0 && mas[j - 1] > mas[j]; j--)
		{
			double tmp = mas[j - 1];
			mas[j - 1] = mas[j];
			mas[j] = tmp;
			z += 3;
			sr++;
		}
	}
}

//сортировка расчёской
void comb_sort(double array[], const size_t size)
{
	double factor = 1.2473309;
	int step = size - 1;
	while (step >= 1)
	{
		for (int i = 0; i + step < size; i++)
		{
			if (array[i] > array[i + step])
			{
				double tmp = array[i];
				array[i] = array[i + step];
				array[i + step] = tmp;
				z += 3;
			}
			sr++;
		}
		step /= factor;
	}
}

//сортировка слиянием
void merge(double array[], double second[], int l, int q, int r)
{
	int low = l, p = q + 1, k;

	for (k = l; k <= r; k++)
	{
		if (low == q + 1)
		{
			second[k] = array[p++];
			sr += 1;
		}
		else if (p == r + 1)
		{
			second[k] = array[low++];
			sr += 2;
		}
		else if (array[low] < array[p])
		{
			second[k] = array[low++];
			sr += 3;
		}
		else
		{
			second[k] = array[p++];
			sr += 3;
		}
		sr++;
		z++;
	}
	for (k = l; k <= r; k++)
	{
		array[k] = second[k];
		sr++;
		z++;
	}
}
void mergesort(double array[], double second[], int l, int r)
{
	if (l < r)
	{
		int q = (l + r) / 2;
		mergesort(array, second, l, q);
		mergesort(array, second, q + 1, r);
		merge(array, second, l, q, r);
	}
}

//поразрядная сортировка
void radixPass(short Offset, int N, ulonglong* sourse, ulonglong* dest, int* count)
{
	ulonglong* sp;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
		sr++;
		z += 3;
	}

	bp = (uchar*)sourse + Offset;
	sp = sourse;

	for (i = N; i > 0; --i, bp += sizeof(ulonglong), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		sr++;
		z += 4;
	}
}

int* createCounters(double* data, int N)
{
	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);

	ushort i;

	int* counters = (int*)malloc(256 * sizeof(ulonglong) * sizeof(int));
	for (i = 0; i < 256 * sizeof(ulonglong); i++)
	{
		counters[i] = 0;
		sr++;
		z++;
	}
	sr++;
	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(ulonglong); i++)
		{
			counters[256 * i + *(bp++)]++;
			sr++;
			z++;
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
		sr++;
	}
	kneg = N - numneg;
	for (i = 0, j = N - 1; i < kneg; i++, j--)
	{
		mas[i] = out[j];
		z++;
	}
	for (i = kneg; i < N; i++)
	{
		mas[i] = out[i - kneg];
		z++;
	}
}

void signedRadixSort(double* data, double* sorted_data, int N)
{
	int* count;
	ushort i;
	int numNeg = 0;
	int* counters = createCounters(data, N);

	for (i = 0; i < sizeof(ulonglong); i++)
	{
		sr++;
		count = counters + 256 * i;
		radixPass(i, N, data, sorted_data, count);
		for (int j = 0; j < N; j++)
		{
			data[j] = sorted_data[j];
			sr++;
			z++;
		}
	}

	obmen(data, N, sorted_data);
}



void main()
{
	double mas[W];
	double out_mas[W];
	int i, sort, n;

	printf("select the sort method \n\n 1) insertion  \n2) comb  \n3) merge  \n4) radix  \n\ninput the number of sort method ");
	scanf_s("%d", &sort);

	printf_s("\ninput size of massiv ");
	scanf_s("%d", &n);

	for (i = 0; i < n; i++)
	{
		scanf_s("%lf", &mas[i]);
		out_mas[i] = mas[i];
	}
	printf("\n");

	if (sort == 1)//сортировка вставками
	{
		insertion_sort(mas, n);

		for (i = 0; i < n; i++)
		{
			printf_s("%lf ", mas[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", sr, z);
	}
	if (sort == 2)//сортировка расчёской
	{
		comb_sort(mas, n);

		for (i = 0; i < n; i++)
		{
			printf_s("%lf ", mas[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", sr, z);
	}
	if (sort == 3)//сортировка слиянием
	{
		mergesort(mas, out_mas, 0, n - 1);

		for (i = 0; i < n; i++)
		{
			printf_s("%lf ", mas[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", sr, z);
	}
	if (sort == 4)//поразрядная сортировка
	{
		signedRadixSort(out_mas, mas, n);

		for (i = 0; i < n; i++)
		{
			printf_s("%lf ", mas[i]);
		}
		printf("\nsravnen = %d  perestanovok = %d", sr, z);
	}
}