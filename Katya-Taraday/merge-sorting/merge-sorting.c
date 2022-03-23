#include <iostream>

using namespace std;

int t1 = 0;
int t2 = 0;

void merge(double array[], double second[], int i, int q, int r)
{
	int left = i, right = q + 1, d;

	for (d = i; d <= r; d++)
	{
		t1++;
		if (left == q + 1)
			second[d] = array[right++];
		else if (right == r + 1)
			second[d] = array[left++];
		else if (array[left] < array[right])
		{
			second[d] = array[left++];
			t2++;
		}

		else second[d] = array[right++];
	}
	for (d = i; d <= r; d++)
	{
		array[d] = second[d];
	}
}
void mergesort(double array[], double second[], int i, int r)
{
	if (i < r)
	{
		int q = (i + r) / 2;
		mergesort(array, second, i, q);
		mergesort(array, second, q + 1, r);
		merge(array, second, i, q, r);
	}
}

void massive(double array[], const size_t size)
{
	int l = 0;
	for (; l < size; l++)
	{
		printf("%lf\n", array[l]);

	}

}

int main()
{
	double a[7] = { 4.9845, 9.5894, 1.3532, 5.9086, 11.7935, 2.3891, 6.7349 };
	double a1[7];
	int i = 0;

	mergesort(a, a1, 0, 6);
	massive(a1, 7);
	printf("\n");
	printf("Number of comparisons %i/n", t1);
	printf("Number of shuffles %i/n", t2);
}