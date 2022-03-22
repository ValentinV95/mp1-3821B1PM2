#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int per = 0, srav = 0;

int merge(double a[], int first, int middle, int second)
{

	int f = first, j = middle + 1, l = 0;
	double b[SIZE] = { 0 };

	while (f <= middle && j <= second)
	{
		srav += 3;
		if (a[f] < a[j])
		{
			b[l] = a[f];
			f++;
			l++;
		}
		else
		{
			b[l] = a[j];
			j++;
			l++;
		}
		per++;
	}
	while (f <= middle)
	{
		b[l] = a[f];
		f++;
		l++;
		srav++;
		per++;
	}
	while (j <= second)
	{
		b[l] = a[j];
		j++;
		l++;
		srav++;
		per++;
	}
	for (j = 0, f = first; f <= second;)
	{
		a[f] = b[j];
		j++;
		f++;
		srav++;
		per++;
	}
}

void mergeSort(double a[], int l, int r)
{
	if (l < r)
	{
		int q = l + (r - l) / 2;
		mergeSort(a, l, q);
		mergeSort(a, q + 1, r);
		merge(a, l, q, r);

	}
}
void rands(double array[], int b)
{
	int i;
	srand(time(0));
	for (i = 0; i < b; i++)
	{
		array[i] = rand() % 1000000 + (rand() % 1000000) / 1000000.0;
	}
}

void sont(double array[], int i)
{
	int j;
	for (j = 0; j < i; j++)
	{
		printf("%lf ", array[j]);
	}
	printf("\n\n");
}

int main()
{
	double mas[SIZE];
	printf("Unsoretd array\n");
	rands(mas, SIZE);
	sont(mas, SIZE);
	mergeSort(mas, 0, SIZE - 1);
	printf("Sorted array\n");
	sont(mas, SIZE);
	printf("Perestanovok %d\nSravneniy %d\n", per, srav);
}