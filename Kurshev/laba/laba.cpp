#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <locale.h>
#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int


void swapp(double* a, double* b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void printff(double a[], int n, int* countp, int* counts, int sort)
{
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		printf("%f", a[i]);
	}
	if (sort > 0)
	{
		printf("\nколичество перестановок: %d", *countp);
		printf("\nколичество сравнений: %d \n", *counts);
	}
	else if (sort == 0)
	{
		printf("\n количество перестановок: %d \n", *countp);
	}
}
void v_sort(double a[], int n, int* countp, int* counts)
{
	for (int i = 1; i < n; i++)
	{
		int j = i;
		while (j > 0)
		{
			if (a[j - 1] > a[j])
			{
				swapp(&a[j], &a[j - 1]);
				*countp += +1;
				*counts += 1;
				j--;
			}
			else
			{
				*counts += 1;
				j--;
			}
		}
	}
}

void quick_sort(double a[], int first, int last, int* counts, int* countp)
{
	int i, j;


	double mid;

	if (first < last)
	{
		i = first;
		j = last;
		mid = a[(i / 2) + (j / 2)];

		do
		{
			while (a[i] < mid)
			{
				i++;
				*counts += 1;
			}
			while (a[j] > mid)
			{
				j--;
				*counts += 1;
			}
			if (i <= j)
			{
				swapp(&a[i], &a[j]);
				*countp += 1;
				i++;
				j--;
			}
		} while (i <= j);

		quick_sort(&a[0], first, j, counts, countp);
		quick_sort(&a[0], i, last, counts, countp);

	}


}

void merge(double a[], int left, int mid, int right, int* counts, int* countp)
{

	int n1 = mid - left + 1;
	int n2 = right - mid;
	double* m1 = (double*)malloc(n1 * sizeof(double));
	double* m2 = (double*)malloc(n2 * sizeof(double));
	int i, j, k = left;

	for (i = 0; i < n1; i++)
	{
		m1[i] = a[left + i];
		*countp += 1;
	}
	for (j = 0; j < n2; j++)
	{
		m2[j] = a[mid + 1 + j];
		*countp += 1;
	}
	i = 0;
	j = 0;
	while ((i < n1) && (j < n2))
	{
		if (m1[i] <= m2[j])
		{
			a[k] = m1[i];
			i++;
			*counts += 1;
			*countp += 1;
		}
		else
		{
			a[k] = m2[j];
			j++;
			*counts += 1;
			*countp += 1;
		}
		k++;
	}

	while (i < n1)
	{
		a[k] = m1[i];
		*countp += 1;
		i++;
		k++;
	}
	free(m1);

	while (j < n2)
	{
		a[k] = m2[j];
		*countp += 1;
		j++;
		k++;
	}

	free(m2);
}


void Merge_sort(double a[], int left, int right, int* countp, int* counts)
{
	if (left < right)
	{

		int mid = (left / 2) + (right / 2);

		Merge_sort(a, left, mid, countp, counts);

		Merge_sort(&a[0], mid + 1, right, countp, counts);


		merge(&a[0], left, mid, right, counts, countp);

	}
}
int* createCounters(double* data, int N) {

	int* counters = (int*)malloc(256 * sizeof(double) * sizeof(int));

	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);
	ushort i;

	for (i = 0; i < 256 * sizeof(double); i++)
	{
		counters[i] = 0;
	}

	while (bp != dataEnd) {

		for (i = 0; i < sizeof(double); i++)
		{
			counters[256 * i + *bp++]++;
		}
	}
	return counters;
}
void RadixLastPass(short Offset, int N, double* source, double* dest, int* count, int* countp) {
	double* sp;
	int s, c, i, * cp;
	uchar* bp;

	int numNeg = 0;
	for (i = 128; i < 256; i++) numNeg += count[i];

	s = numNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;
		*cp = s;
		s += c;
		countp += 1;
	}


	s = count[255] = 0;
	cp = count + 254;
	for (i = 254; i >= 128; --i, --cp) {
		*cp += s;
		s = *cp;
		countp += 1;
	}

	bp = (uchar*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp) {
		cp = count + *bp;
		if (*bp < 128) dest[(*cp)++] = *sp;
		else dest[--(*cp)] = *sp;
		countp += 1;
	}
}
void radixPass(short Offset, int N, double* source, double* dest, int* count, int* countp) {

	double* sp;
	int s, c, i, * cp;
	uchar* bp;

	s = 0;
	cp = count;
	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;
		*cp = s;
		s += c;
		countp += 1;
	}


	bp = (uchar*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp) {
		cp = count + *bp;
		dest[*cp] = *sp;
		++(*cp);
		countp += 1;
	}
}

void RadixSort(double* in, double* out, int N, int* countp) {

	ushort i;

	int* counters = createCounters(in, N);
	int* count;

	for (i = 0; i < sizeof(double) - 1; i++) {
		count = counters + 256 * i;

		radixPass(i, N, in, out, count, countp);

		for (int j = 0; j < N; j++)
		{
			in[j] = out[j];
			*countp += 1;
		}
	}
	count = counters + 256 * i;
	RadixLastPass(i, N, in, out, count, countp);
}

int main()
{
	int num = 0;
	int countp, counts;
	int n;
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	while (1)
	{
		countp = 0;
		counts = 0;
		printf("Введите длину массива:");
		scanf_s("%d", &n);
		double* a = (double*)malloc(n * sizeof(double));
		printf("Выберите сортировку:");
		scanf_s("%d", &num);



		for (int i = 0; i < n; i++)
		{
			a[i] = pow(-1, i) * (rand() % 10000001) * 0.001;
			//printf("%f \n", a[i]);
		}
		double* b = (double*)malloc(n * sizeof(double));

		switch (num)
		{
		case 1:
			v_sort(&a[0], n, &countp, &counts);
			printff(&a[0], n, &countp, &counts, 1);
			break;

		case 2:
			quick_sort(&a[0], 0, n - 1, &countp, &counts);
			printff(&a[0], n, &countp, &counts, 1);
			break;

		case 3:
			Merge_sort(&a[0], 0, n - 1, &countp, &counts);
			printff(&a[0], n, &countp, &counts, 1);
			break;


		case 4:

			RadixSort(&a[0], &b[0], n, &countp);
			printff(&b[0], n, &countp, &counts, 0);
			break;

		default: printf("r");
		}

		countp = 0;
		counts = 0;
		free(a);
	}
}