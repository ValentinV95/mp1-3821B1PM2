#include "stdio.h"
#include "stdlib.h"


int q1 = 0;		//кол-во сравнений
int q2 = 0;		//кол-во перестановок

void merge(double array[], double second[], int l, int q, int r)
{
	int left = l, right = q + 1, j;

	for (j = l; j <= r; j++)
	{
		q1++;
		if (left == q + 1)
			second[j] = array[right++];
		else if (right == r + 1)
			second[j] = array[left++];
		else if (array[left] < array[right])
		{
			second[j] = array[left++];
			q2++;
		}

		else second[j] = array[right++];
	}
	for (j = l; j <= r; j++)
	{
		array[j] = second[j];
	}
}
void mergesort(double array[], double second[], int l, int r)
{
	if (r <= l) return;
	if (l < r)
	{
		int q = (l + r) / 2;
		mergesort(array, second, l, q,r);
		mergesort(array, second, q + 1, r);
		merge(array, second, l, q, r);
	}
}


int massive(double array[], const size_t size)
{
	int i = 0;
	double r2;
	for (; i < size; i++)
	{
		r2 = array[i];
		printf("%lf\n", r2);

	}

}








int main()
{
	double a[10];
	double a1[10];
	double a2[5];
	int i = 0;
	double b, r;

	printf("please enter the numbers(double) in 10-size array\n It will be sorted by <merge> type\n");

	for (; i < 10; i++)
	{
		scanf_s("%lf", &b);
		a[i] = b;
	}

	mergesort(a,a1, 0,9);
	printf("\n");
	massive(a1, 10);
	printf("\n%d	%d", q1, q2);
}