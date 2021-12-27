#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
int compare = 0;
int change = 0;
int flag = 0;

void sorting_check(double* array, long size)
{
	int flag = 0;
	for (int i = 1; i < size; i++)
	{
		if (array[i] < array[i - 1])
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		printf("Sorting is not correctly \n");
	}
	else
	{
		printf("Sorting is correctly \n");
	}
}

void babble_sort(double* array, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 2; j > i - 1; j--)
		{
			compare++;
			if (array[j] > array[j + 1])
			{
				double tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
				change++;
			}
		}
	}
}

void shell_sort(double* array, int size)
{
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; i++)
		{
			compare++;
			for (int j = i - step; (j >= 0) && (array[j] > array[j + step]); j -= step)
			{
				double tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
				compare++;
				change++;
			}
		}
	}
}

void merge(double* array, double* secondhand, int left, int middle, int right)
{
	middle = (left + right) / 2;
	int minleft = left;
	int minright = middle + 1;
	int minsec = left;
	while ((minleft <= middle) && (minright <= right))
	{
		if (array[minleft] <= array[minright])
		{
			secondhand[minsec] = array[minleft];
			minleft++;
			change++;
		}
		else
		{
			secondhand[minsec] = array[minright];
			minright++;
			change++;
		}
		minsec++;
		compare++;
	}
	if (minleft > middle)
	{
		for (int i = minright; i <= right; i++)
		{
			secondhand[minsec] = array[i];
			minsec++;
			change++;
		}
	}
	else
	{
		for (int i = minleft; i <= middle; i++)
		{
			secondhand[minsec] = array[i];
			minsec++;
			change++;
		}
	}

	for (int i = left; i <= right; i++)
	{
		array[i] = secondhand[i];
	}
}
void merge_sort(double* array, double* secondhand, int left, int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		merge_sort(array, secondhand, left, middle);
		merge_sort(array, secondhand, middle + 1, right);
		merge(array, secondhand, left, middle, right);
	}
}

void createCounters(double* array, long* counters, int N)
{
	int i;
	unsigned char* bp = (unsigned char*)array;
	unsigned char* end = (unsigned char*)(array + N);

	memset(counters, 0, 256 * sizeof(double) * sizeof(int));
	while (bp != end)
	{
		for (i = 0; i < sizeof(double); i++)
		{
			counters[256 * i + *(bp++)]++;
		}
	}
}
void radixPass(short Offset, int size, double* array, double* dest, long* count)
{
	double* sp;
	long s, c, i, * cp;
	unsigned char* bp;

	s = 0;
	cp = count;
	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	bp = (unsigned char*)array + Offset;
	sp = array;
	for (i = size; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		change++;
	}
}
void radixLastPass(short Offset, int size, double* array, double* dest, long* count)
{
	double* sp;
	long sum, c, i, * cp;
	unsigned char* bp;

	long numNeg = 0;
	for (i = 128; i < 256; i++) numNeg += count[i];

	sum = numNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp)
	{
		c = *cp;
		*cp = sum;
		sum += c;
	}

	cp = count + 255;
	sum = 0; *cp = 0;
	for (i = 255; i >= 128; i--, cp--)
	{
		sum += *cp;
		*cp = sum;
	}
	bp = (unsigned char*)array + Offset;
	sp = array;
	for (i = size; i > 0; i--, bp += sizeof(double), sp++)
	{
		cp = count + *bp;
		if (*bp < 128)
		{
			dest[*cp] = *sp;
			(*cp)++;
		}
		else
		{
			(*cp)--;
			dest[*cp] = *sp;
		}
		change++;
	}
}
void radixSort(double* array, int size)
{
	int i;
	double* temp;
	double* dest = (double*)malloc(sizeof(double) * size);
	long* counters = (long*)malloc(sizeof(double) * 256 * sizeof(int));
	long* count;

	createCounters((double*)array, counters, size);

	for (i = 0; i < sizeof(double) - 1; i++)
	{
		count = counters + 256 * i;
		radixPass(i, size, array, dest, count);
		temp = array;
		array = dest;
		dest = temp;
	}
	count = counters + 256 * (sizeof(double) - 1);
	radixLastPass(sizeof(double) - 1, size, array, dest, count);

	temp = array;
	array = dest;
	dest = temp;

	free(dest);
	free(counters);
}


int main()
{
	srand(time(0));
	double array[1000];
	double second[sizeof array];
	int sort;
	int size;
	int i;
	printf("Choose the size of your array: ");
	scanf_s("%d", &size);
	printf("Aviable sorts:\n");
	printf("1) Babble_sort\n");
	printf("2) Shell_sort(\n");
	printf("3) Merge sort\n");
	printf("4) Radix sort\n");
	printf("Choose the type of sort: ");
	scanf_s("%d", &sort);
	printf(" \n");

	for (i = 0; i < size; i++)
		array[i] = rand() * 0.001 * pow(-1, i);

	compare = 0;
	change = 0;

	printf("Default array: \n");
	for (i = 0; i < size; i++)
	{
		printf("array[");
		printf("%d", i);
		printf("]=");
		printf("%lf ", array[i]);
		printf(" \n");
	}
	printf(" \n");
	if (sort == 1) {
		babble_sort(array, size);
		sorting_check(array, size);
	}
	if (sort == 2) {
		shell_sort(array, size);
		sorting_check(array, size);
	}
	if (sort == 3) {
		merge_sort(array, second, 0, size - 1);
		sorting_check(array, size);
	}
	if (sort == 4) {
		radixSort(array, size);
		sorting_check(array, size);
	}
	printf("Sorted array: \n");



	for (i = 0; i < size; i++)
	{
		printf("array[");
		printf("%d", i);
		printf("]=");
		printf("%lf ", array[i]);
		printf(" \n");
	}
	printf(" \n");
	printf("Number of comparisons: ");
	printf("%d", compare);
	printf("\n");
	printf("Number of permutations: ");
	printf("%d", change);
}