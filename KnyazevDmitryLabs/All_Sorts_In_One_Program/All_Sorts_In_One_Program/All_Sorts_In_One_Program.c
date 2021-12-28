#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define Val 1364
#define uchar unsigned char
#define ushort unsigned short
#define udouble unsigned double
#define ulonglong unsigned long long

int cpn = 0;   //Comparisons
int ptn = 0;   //Permutations

void insertion_sort(double array[], int size) //Тут Сортировка Вставками
{
	int i = 0;
    for (int i = 1; i < size; i++) 
	{
		for (int j = i; j > 0 && array[j - 1] > array[j]; j--)
		{
            double tmp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = tmp;
			ptn = ptn + 3;
			cpn = cpn + 2;
		}
	}
}
void shell_sort(double array[], int size) //Тут Сортировка Шелла
{
	for (int step = size / 2; step > 0; step = step / 2) 
	{
		for (int i = step; i < size; i++) 
		{
			for (int j = i - step; j >= 0 && array[j] > array[j + step]; j = j - step) 
			{
				double tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
				ptn = ptn + 3;
				cpn = cpn + 2;
			}
		}
	}
}
void merge(double array[], double second[], int l, int c, int r) //Тут Сортировка Слиянием
{
	int left = l, right = c + 1, j;
    for (j = l; j <= r; j++)
	{
		if (left == c + 1)
		{
			second[j] = array[right++];
			cpn = cpn + 1;
		}
		else if (right == r + 1)
		{
			second[j] = array[left++];
			cpn = cpn + 2;
		}
		else if (array[left] < array[right])
		{
			second[j] = array[left++];
			cpn = cpn + 3;
		}
		else
		{
			second[j] = array[right++];
			cpn = cpn + 3;
		}
		cpn++;
		ptn++;
	}
	for (j = l; j <= r; j++)
	{
		array[j] = second[j];
		cpn++;
		ptn++;
	}
}
void merge_sort(double array[], double second[], int l, int r)
{
	if (l < r)
	{
		int c = (l + r) / 2;
		merge_sort(array, second, l, c);
		merge_sort(array, second, c + 1, r);
		merge(array, second, l, c, r);
	}
}
void sradix(short offset, int N, ulonglong* sourse, ulonglong* dest, int* count) //Тут Поразрядная Сортировка
{
	ulonglong* sd;
	int s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
		cpn++;
		ptn += 3;
	}

	bp = (uchar*)sourse + offset;
	sd = sourse;
    for (i = N; i > 0; --i, bp += sizeof(ulonglong), ++sd)
	{
		cp = count + *bp;
		dest[*cp] = *sd;
		(*cp)++;
		cpn++;
		ptn += 4;
	}
}
int* createCounters(double* data, int N)
{
	uchar* bp = (uchar*)data;
	uchar* dataend = (uchar*)(data + N);
    ushort i;

	int* counters = (int*)malloc(256 * sizeof(ulonglong) * sizeof(int));
	for (i = 0; i < 256 * sizeof(ulonglong); i++)
	{
		counters[i] = 0;
		cpn++;
		ptn++;
	}
	cpn++;
	while (bp != dataend)
	{
		for (i = 0; i < sizeof(ulonglong); i++)
		{
			counters[256 * i + *(bp++)]++;
			cpn++;
			ptn++;
		}
	}
    return counters;
}
void swap(double* out, int N, double* arr)
{
	int numneg = N, kneg, m, i;
	for (i = 0; i < N; i++)
	{
		if (out[i] < 0)
		{
			numneg = i;
			break;
		}
		cpn++;
	}
	kneg = N - numneg;
	for (i = 0, m = N - 1; i < kneg; i++, m--)
	{
		arr[i] = out[m];
		ptn++;
	}
	for (i = kneg; i < N; i++)
	{
		arr[i] = out[i - kneg];
		ptn++;
	}
}
void radix_sort(double* data, double* sorted_data, int N)
{
	int* count;
	ushort i;
	int numNeg = 0;
	int* counters = createCounters(data, N);
    for (i = 0; i < sizeof(ulonglong); i++)
	{
		cpn++;
		count = counters + 256 * i;
		sradix(i, N, data, sorted_data, count);
		for (int j = 0; j < N; j++)
		{
			data[j] = sorted_data[j];
			cpn++;
			ptn++;
		}
	}
    swap(data, N, sorted_data);
}
void main()
{
	double arr[Val];
	double out_arr[Val];
	int i, sort, r;

	printf("Choose The Sorting Method: \n\n1) Insertion Sort  \n2) Shell's Sort  \n3) Merge Sort  \n4) Radix Sort  \n\nYour Choice: ");
	scanf_s("%d", &sort);

	printf_s("\nEnter The Array Size (Limit = 1364!): ");
	scanf_s("%d", &r);

	for (i = 0; i < r; i++)
	{
		scanf_s("%lf", &arr[i]);
		out_arr[i] = arr[i];
	}
	printf("\n");
    if (sort == 1)
	{
		insertion_sort(arr, r);
        for (i = 0; i < r; i++)
		{
			printf_s("%lf ", arr[i]);
		}
		printf("\nTotal Comparisons = %d  Total Permutations = %d", cpn, ptn);
	}
	if (sort == 2)
	{
		shell_sort(arr, r);
        for (i = 0; i < r; i++)
		{
			printf_s("%lf ", arr[i]);
		}
		printf("\nTotal Comparisons = %d  Total Permutations = %d", cpn, ptn);
	}
	if (sort == 3)
	{
		merge_sort(arr, out_arr, 0, r - 1);
        for (i = 0; i < r; i++)
		{
			printf_s("%lf ", arr[i]);
		}
		printf("\nTotal Comparisons = %d  Total Permutations = %d", cpn, ptn);
	}
	if (sort == 4)
	{
		radix_sort(out_arr, arr, r);
        for (i = 0; i < r; i++)
		{
			printf_s("%lf ", arr[i]);
		}
		printf("\nTotal Comparisons = %d  Total Permutations = %d", cpn, ptn);
	}
}